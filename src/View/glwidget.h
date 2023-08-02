#ifndef OBJECTVIEWER_SRC_VIEW_GLWIDGET_H
#define OBJECTVIEWER_SRC_VIEW_GLWIDGET_H

#define GL_SILENCE_DEPRECATION

#include <QObject>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QtOpenGL>
#include <QtWidgets>

#include "src/Controller/Controller.h"
#include "src/Object/Object.h"
#include "src/Settings/Settings.h"

namespace object_viewer {

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT
 public:
  GLWidget(QWidget* parent = nullptr);
  ~GLWidget();

  void DrawObject();
  void SetController(Controller* controller);

  void SetXLastMove(double val);
  void SetYLastMove(double val);
  void SetZLastMove(double val);

  void SetXRotate(double val);
  void SetYRotate(double val);
  void SetZRotate(double val);

  void SetScaleLast(double scale);

  double GetXLastMove();
  double GetYLastMove();
  double GetZLastMove();

  double GetXRotate();
  double GetYRotate();
  double GetZRotate();

  double GetScaleLast();

 signals:
  void ScaleChanged(double scale);
  void UpdateRotationValues(double x_angel, double y_angel, double z_angel);

 private:
  double x_last_move_ = 0, y_last_move_ = 0, z_last_move_ = 0;
  double angle_x_last_ = 0, angle_y_last_ = 0, angle_z_last_ = 0;
  double scale_last_ = 1;

  QPoint m_last_pos_{};
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;

  int size_;
  float far_;
  float fov_;
  float heap_height_;
  void mouseMoveEvent(QMouseEvent* event) override;
  void mousePressEvent(QMouseEvent* event) override;
  void wheelEvent(QWheelEvent* event) override;
  void DrawVertexes();
  void DrawEdges();
  void SetProection();
  Controller* controller_;
  Settings* settings_ = Settings::GetInstance();
};
}  // namespace object_viewer
#endif
