#ifndef OBJECTVIEWER_SRC_CONTROLLER_CONTROLLER_H
#define OBJECTVIEWER_SRC_CONTROLLER_CONTROLLER_H

#include <QOpenGLWidget>
#include <any>
#include <string>

#include "src/ObjectViewer/ObjectViewer.h"

namespace object_viewer {
class Controller {
 public:
  Controller(ObjectViewer* object_viewer) : object_viewer_(object_viewer) {}

  void UploadObjectFromFile(const std::string& filepath);
  bool ObjectIsUploaded();

  void ScaleObject(double scale);
  void MoveObject(double x, double y, double z);
  void RotateObject(double x_angel, double y_angel, double z_angel);

  std::any UndoTransformation();
  std::any RedoTransformation();

  void SaveImage(const QString& filepath, QOpenGLWidget* glwidget);
  void SaveGif(const QString& filepath, QOpenGLWidget* glwidget);

  void* GetVertexes();
  std::string GetObjectName();
  void* GetFacetsToDraw();
  size_t GetCountFacets();
  size_t GetCountVertexes();
  size_t GetCountEdges();

  int GetSize();
  float GetFar();
  float GetFov();
  float GetHeapHeight();

 private:
  ObjectViewer* object_viewer_;
};
}  // namespace object_viewer

#endif