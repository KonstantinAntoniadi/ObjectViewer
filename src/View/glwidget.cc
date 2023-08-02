#include "glwidget.h"

namespace object_viewer {

GLWidget::GLWidget(QWidget* parent) : QOpenGLWidget(parent) {}

GLWidget::~GLWidget() {}
void GLWidget::SetController(Controller* controller) {
  controller_ = controller;
  size_ = controller_->GetSize();
  far_ = controller_->GetFar();
  fov_ = controller_->GetFov();
  heap_height_ = controller_->GetHeapHeight();
}

void GLWidget::SetXLastMove(double val) { x_last_move_ = val; }
void GLWidget::SetYLastMove(double val) { y_last_move_ = val; }
void GLWidget::SetZLastMove(double val) { z_last_move_ = val; }

void GLWidget::SetXRotate(double val) { angle_x_last_ = val; }
void GLWidget::SetYRotate(double val) { angle_y_last_ = val; }
void GLWidget::SetZRotate(double val) { angle_z_last_ = val; }

void GLWidget::SetScaleLast(double scale) { scale_last_ = scale; }

double GLWidget::GetXLastMove() { return x_last_move_; }
double GLWidget::GetYLastMove() { return y_last_move_; }
double GLWidget::GetZLastMove() { return z_last_move_; }

double GLWidget::GetXRotate() { return angle_x_last_; }
double GLWidget::GetYRotate() { return angle_y_last_; }
double GLWidget::GetZRotate() { return angle_z_last_; }

double GLWidget::GetScaleLast() { return scale_last_; }

void GLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
}

void GLWidget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void GLWidget::paintGL() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glClearColor(settings_->GetBackgroundColor().redF(),
               settings_->GetBackgroundColor().greenF(),
               settings_->GetBackgroundColor().blueF(), 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  SetProection();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0, 0, -3 * heap_height_);
  DrawObject();
}

void GLWidget::SetProection() {
  if (settings_->GetProectionType() == ProectionType::kParallel) {
    glOrtho(-size_, size_, -size_, size_, -far_, far_);
  } else {
    glFrustum(-size_, size_, -size_, size_, heap_height_, far_);
  }
}

void GLWidget::mousePressEvent(QMouseEvent* event) {
  m_last_pos_ = event->globalPosition().toPoint();
}

void GLWidget::mouseMoveEvent(QMouseEvent* event) {
  if (controller_->ObjectIsUploaded()) {
    QPoint m_pos_diff_ = event->globalPosition().toPoint() - m_last_pos_;
    controller_->RotateObject(-m_pos_diff_.y(), m_pos_diff_.x(), 0);
    m_last_pos_ = event->globalPosition().toPoint();
    update();
    emit UpdateRotationValues(angle_x_last_ + (-m_pos_diff_.y()),
                              angle_y_last_ + m_pos_diff_.x(), 0.0);
  }
}

void GLWidget::wheelEvent(QWheelEvent* event) {
  if (controller_->ObjectIsUploaded()) {
    double step = 0.1;
    double wheel_y = event->angleDelta().y();
    double scale_new = (wheel_y > 0) ? scale_last_ + step : scale_last_ - step;
    if (scale_new > step) {
      controller_->ScaleObject(scale_new / scale_last_);
      update();
      emit ScaleChanged(scale_new);
    }
  }
}

void GLWidget::DrawObject() {
  if (controller_->ObjectIsUploaded()) {
    DrawVertexes();
    DrawEdges();
    glDisableClientState(GL_VERTEX_ARRAY);
  }
}

void GLWidget::DrawVertexes() {
  glPointSize(settings_->GetVertexSize());
  glVertexPointer(3, GL_DOUBLE, 0, controller_->GetVertexes());
  glEnableClientState(GL_VERTEX_ARRAY);
  if (settings_->GetVertexType() == VertexType::kSquare) {
    glDisable(GL_POINT_SMOOTH);
    glEnable(GL_POINT_SPRITE);
  } else if (settings_->GetVertexType() == VertexType::kCircle) {
    glDisable(GL_POINT_SPRITE);
    glEnable(GL_POINT_SMOOTH);
  }

  if (settings_->GetVertexType() != VertexType::kNone) {
    glColor4f(settings_->GetVertexColor().redF(),
              settings_->GetVertexColor().greenF(),
              settings_->GetVertexColor().blueF(),
              settings_->GetVertexColor().alphaF());
    glDrawArrays(GL_POINTS, 0, controller_->GetCountVertexes());
  }
}

void GLWidget::DrawEdges() {
  glLineWidth(settings_->GetEdgeWidth());
  if (settings_->GetEdgeType() == EdgeType::kDotted) {
    glPushAttrib(GL_ENABLE_BIT);
    glLineStipple(4, 0x00FF);
    glEnable(GL_LINE_STIPPLE);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }
  glColor4f(
      settings_->GetEdgeColor().redF(), settings_->GetEdgeColor().greenF(),
      settings_->GetEdgeColor().blueF(), settings_->GetEdgeColor().alphaF());

  glDrawElements(GL_LINES, controller_->GetCountFacets(), GL_UNSIGNED_INT,
                 controller_->GetFacetsToDraw());
}

}  // namespace object_viewer
