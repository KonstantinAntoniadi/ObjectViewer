#include "Settings.h"

namespace object_viewer {

Settings* Settings::settings_ = nullptr;

Settings* Settings::GetInstance() {
  if (settings_ == nullptr) {
    settings_ = new Settings();
  }

  return settings_;
}

Settings::~Settings() { delete settings_; }

void Settings::SetBackgroundColor(QColor color) { background_color_ = color; }
void Settings::SetEdgeColor(QColor color) { edge_color_ = color; }
void Settings::SetVertexColor(QColor color) { vertex_color_ = color; }
void Settings::SetEdgeWidth(double width) { edge_width_ = width; }
void Settings::SetVertexSize(double size) { vertex_size_ = size; }
void Settings::SetEdgeType(EdgeType type) { edge_type_ = type; }
void Settings::SetVertexType(VertexType type) { vertex_type_ = type; }
void Settings::SetProectionType(ProectionType type) { proection_type_ = type; }

QColor Settings::GetBackgroundColor() { return background_color_; }
QColor Settings::GetEdgeColor() { return edge_color_; }
QColor Settings::GetVertexColor() { return vertex_color_; }
double Settings::GetEdgeWidth() { return edge_width_; }
double Settings::GetVertexSize() { return vertex_size_; }
EdgeType Settings::GetEdgeType() { return edge_type_; }
VertexType Settings::GetVertexType() { return vertex_type_; }
ProectionType Settings::GetProectionType() { return proection_type_; }

void Settings::SaveSettings() {
  qsettings_.setValue("background_color", background_color_.name());
  qsettings_.setValue("edge_color", edge_color_.name());
  qsettings_.setValue("vertex_color", vertex_color_.name());

  qsettings_.setValue("edge_width", edge_width_);
  qsettings_.setValue("vertex_size", vertex_size_);

  qsettings_.setValue("edge_type", static_cast<int>(edge_type_));
  qsettings_.setValue("vertex_type", static_cast<int>(vertex_type_));
  qsettings_.setValue("proection_type", static_cast<int>(proection_type_));
}

void Settings::LoadSettings() {
  background_color_ =
      qsettings_.value("background_color", QColor(Qt::white)).value<QColor>();
  edge_color_ =
      qsettings_.value("edge_color", QColor(Qt::black)).value<QColor>();
  vertex_color_ =
      qsettings_.value("vertex_color", QColor(Qt::black)).value<QColor>();

  edge_width_ = qsettings_.value("edge_width", 1.0).toDouble();
  vertex_size_ = qsettings_.value("vertex_size", 1.0).toDouble();

  edge_type_ = static_cast<EdgeType>(
      qsettings_.value("edge_type", static_cast<int>(EdgeType::kSolid))
          .toInt());
  vertex_type_ = static_cast<VertexType>(
      qsettings_.value("vertex_type", static_cast<int>(VertexType::kCircle))
          .toInt());
  proection_type_ = static_cast<ProectionType>(
      qsettings_
          .value("proection_type", static_cast<int>(ProectionType::kParallel))
          .toInt());
}

}  // namespace object_viewer
