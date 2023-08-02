#include "src/Controller/Controller.h"

namespace object_viewer {
void Controller::UploadObjectFromFile(const std::string& filepath) {
  object_viewer_->UploadObjectFromFile(filepath);
}

void* Controller::GetVertexes() { return object_viewer_->GetVertexes(); }

std::string Controller::GetObjectName() {
  return object_viewer_->GetObjectName();
}

void Controller::ScaleObject(double scale) {
  object_viewer_->ScaleObject(scale);
}

void Controller::MoveObject(double x, double y, double z) {
  object_viewer_->MoveObject(x, y, z);
}

void Controller::RotateObject(double x_angel, double y_angel, double z_angel) {
  object_viewer_->RotateObject(x_angel, y_angel, z_angel);
}

std::any Controller::UndoTransformation() {
  std::any res = object_viewer_->UndoTransformation();
  return res;
}

std::any Controller::RedoTransformation() {
  std::any res = object_viewer_->RedoTransformation();
  return res;
}

bool Controller::ObjectIsUploaded() {
  return object_viewer_->ObjectIsUploaded();
}

void Controller::SaveImage(const QString& filepath, QOpenGLWidget* glwidget) {
  object_viewer_->SaveImage(filepath, glwidget);
}

void Controller::SaveGif(const QString& filepath, QOpenGLWidget* glwidget) {
  object_viewer_->SaveGif(filepath, glwidget);
}

void* Controller::GetFacetsToDraw() {
  return object_viewer_->GetFacetsToDraw();
}
size_t Controller::GetCountFacets() { return object_viewer_->GetCountFacets(); }
size_t Controller::GetCountVertexes() {
  return object_viewer_->GetCountVertexes();
}
size_t Controller::GetCountEdges() { return object_viewer_->GetCountEdges(); }

int Controller::GetSize() { return object_viewer_->GetSize(); };
float Controller::GetFar() { return object_viewer_->GetFar(); };
float Controller::GetFov() { return object_viewer_->GetFov(); };
float Controller::GetHeapHeight() { return object_viewer_->GetHeapHeight(); };

}  // namespace object_viewer
