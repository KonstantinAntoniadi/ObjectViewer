#ifndef OBJECTVIEWER_SRC_OBJECTVIEWER_OBJECTVIEWER_H
#define OBJECTVIEWER_SRC_OBJECTVIEWER_OBJECTVIEWER_H

#include <math.h>

#include <QOpenGLWidget>
#include <memory>

#include "src/Command/Command.h"
#include "src/FileReader/ObjectFilereader.h"
#include "src/MediaSaver/MediaSaver.h"
#include "src/Object/Object.h"
#include "src/Settings/Settings.h"
#include "src/Transformer/Transformer.h"

namespace object_viewer {
class ObjectViewer {
 public:
  ObjectViewer(ObjectFileReader* reader, Transformer* transformer,
               MediaSaver* media_saver);

  void UploadObjectFromFile(const std::string& filepath);
  bool ObjectIsUploaded();
  void NormalizeObject(Object* obj);

  void ScaleObject(double scale);
  void MoveObject(double x, double y, double z);
  void RotateObject(double x_angel, double y_angel, double z_angel);

  std::any UndoTransformation();
  std::any RedoTransformation();

  void SaveImage(const QString& filepath, QOpenGLWidget* glwidget);
  void SaveGif(const QString& filepath, QOpenGLWidget* glwidget);

  std::string GetObjectName();
  void* GetVertexes();
  void* GetFacetsToDraw();
  size_t GetCountVertexes();
  size_t GetCountFacets();
  size_t GetCountEdges();

  int GetSize();
  float GetFar();
  float GetFov();
  float GetHeapHeight();

 private:
  Transformer* transformer_;
  MediaSaver* media_saver_;
  ObjectFileReader* reader_;
  std::unique_ptr<Object> obj_;
  bool object_is_uploaded_ = false;
  static int size_;
  static float far_;
  static float fov_;
  static float heap_height_;
};

}  // namespace object_viewer

#endif