#include "src/ObjectViewer/ObjectViewer.h"

#include <algorithm>

namespace object_viewer {

ObjectViewer::ObjectViewer(ObjectFileReader* reader, Transformer* transformer,
                           MediaSaver* media_saver)
    : transformer_(transformer), media_saver_(media_saver), reader_(reader) {}

void ObjectViewer::UploadObjectFromFile(const std::string& filepath) {
  transformer_->ClearCommands();
  obj_ = std::make_unique<Object>();
  reader_->ReadFile(filepath, obj_.get());
  NormalizeObject(obj_.get());
  object_is_uploaded_ = true;
}

bool ObjectViewer::ObjectIsUploaded() { return object_is_uploaded_; }

void ObjectViewer::NormalizeObject(Object* obj) {
  double minX = std::numeric_limits<double>::max();
  double minY = std::numeric_limits<double>::max();
  double minZ = std::numeric_limits<double>::max();
  double maxX = std::numeric_limits<double>::lowest();
  double maxY = std::numeric_limits<double>::lowest();
  double maxZ = std::numeric_limits<double>::lowest();

  for (const Point& vertex : obj->vertexes_) {
    minX = std::min(minX, vertex.x);
    minY = std::min(minY, vertex.y);
    minZ = std::min(minZ, vertex.z);
    maxX = std::max(maxX, vertex.x);
    maxY = std::max(maxY, vertex.y);
    maxZ = std::max(maxZ, vertex.z);
  }

  double maxDiff = std::max({maxX - minX, maxY - minY, maxZ - minZ});

  double centerX = (minX + maxX) / 2.0;
  double centerY = (minY + maxY) / 2.0;
  double centerZ = (minZ + maxZ) / 2.0;

  double scale = 2.0 / maxDiff;

  for (Point& vertex : obj->vertexes_) {
    vertex.x = (vertex.x - centerX) * scale;
    vertex.y = (vertex.y - centerY) * scale;
    vertex.z = (vertex.z - centerZ) * scale;
  }
}

void ObjectViewer::ScaleObject(double scale) {
  transformer_->SetCommand(std::make_shared<Scale>(scale));
  transformer_->Transform(obj_.get());
}

void ObjectViewer::MoveObject(double x, double y, double z) {
  transformer_->SetCommand(std::make_shared<Move>(x, y, z));
  transformer_->Transform(obj_.get());
}

void ObjectViewer::RotateObject(double x_angel, double y_angel,
                                double z_angel) {
  transformer_->SetCommand(std::make_shared<Rotate>(x_angel, y_angel, z_angel));
  transformer_->Transform(obj_.get());
}

std::any ObjectViewer::UndoTransformation() {
  std::any res = transformer_->Undo(obj_.get());
  return res;
}

std::any ObjectViewer::RedoTransformation() {
  std::any res = transformer_->Redo(obj_.get());
  return res;
}

void ObjectViewer::SaveImage(const QString& filepath, QOpenGLWidget* glwidget) {
  media_saver_->SaveImage(filepath, glwidget);
}

void ObjectViewer::SaveGif(const QString& filepath, QOpenGLWidget* glwidget) {
  media_saver_->SaveGif(filepath, glwidget);
}

std::string ObjectViewer::GetObjectName() { return obj_->name_; }

void* ObjectViewer::GetVertexes() { return obj_->vertexes_.data(); }

void* ObjectViewer::GetFacetsToDraw() { return obj_->facets_.data(); }

size_t ObjectViewer::GetCountFacets() { return obj_->facets_.size(); }
size_t ObjectViewer::GetCountVertexes() { return obj_->vertexes_.size(); }
size_t ObjectViewer::GetCountEdges() { return obj_->facets_.size() / 2; }

int ObjectViewer::GetSize() { return size_; }
float ObjectViewer::GetFar() { return far_; }
float ObjectViewer::GetFov() { return fov_; }
float ObjectViewer::GetHeapHeight() { return heap_height_; }

int ObjectViewer::size_ = 1;
float ObjectViewer::far_ = 150.0f;
float ObjectViewer::fov_ = 60.0f * M_PI / 180.0f;
float ObjectViewer::heap_height_ = size_ / (2.0f * std::tan(fov_ / 2.0));

}  // namespace object_viewer
