#ifndef OBJECTVIEWER_SRC_MEDIASAVER_MEDIASAVER_H
#define OBJECTVIEWER_SRC_MEDIASAVER_MEDIASAVER_H

#include <QImage>
#include <QObject>
#include <QOpenGLWidget>
#include <QTimer>

#include "qgifimage.h"

namespace object_viewer {
class MediaSaver : public QObject {
 public:
  void SaveImage(const QString& filepath, QOpenGLWidget* glwidget);
  void SaveGif(const QString& filepath, QOpenGLWidget* glwidget);

 private slots:
  void TakeGif(const QString& filepath, QOpenGLWidget* glwidget);

 private:
  QImage TakeSnapshot(QOpenGLWidget* glwidget,
                      std::optional<int> w = std::nullopt,
                      std::optional<int> h = std::nullopt);
  QGifImage* gif_;
  QTimer* timer_;
  int time_ = 0;
  bool timer_ready_ = true;
};
}  // namespace object_viewer

#endif