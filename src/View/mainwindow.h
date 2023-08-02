#ifndef OBJECTVIEWER_SRC_VIEW_MAINWINDOW_H
#define OBJECTVIEWER_SRC_VIEW_MAINWINDOW_H

#include <src/Controller/Controller.h>

#include <QColorDialog>
#include <QMainWindow>
#include <QOpenGLWidget>
#include <any>

#include "src/Settings/Settings.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace object_viewer {

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(Controller *controller, QWidget *parent = nullptr);
  ~MainWindow();

 protected:
  void keyPressEvent(QKeyEvent *event) override;

 private slots:
  void on_dottedRadioButton_clicked();
  void on_solidRadioButton_clicked();
  void on_thicknessEdgeSpinBox_valueChanged(double arg1);
  void on_chooseColorBackgroundLabel_clicked();
  void on_chooseColorEdgeButton_clicked();
  void on_sizeVertexSpinBox_valueChanged(double arg1);
  void on_squareDisplayRadioButton_clicked();
  void on_circleDisplayRadioButton_clicked();
  void on_noneDisplayRadioButton_clicked();
  void on_chooseColorVertexButton_clicked();
  void on_parallelRadioButton_clicked();
  void on_centralRadioButton_clicked();
  void on_xMoveSpinBox_valueChanged(double arg1);
  void on_yMoveSpinBox_valueChanged(double arg1);
  void on_zMoveSpinBox_valueChanged(double arg1);
  void on_scaleSpinBox_valueChanged(double arg1);
  void on_xRotateSpinBox_valueChanged(double arg1);
  void on_yRotateSpinBox_valueChanged(double arg1);
  void on_zRotateSpinBox_valueChanged(double arg1);

  void UpdateGL();
  void OpenFile();
  void SaveImage();
  void SaveGif();
  void UpdateScale(double scale);
  void UpdateRotation(double x_angel, double y_angel, double z_angel);

 private:
  void SincSettings();
  Ui::MainWindow *ui_;
  Controller *controller_;
  Settings *settings_ = Settings::GetInstance();
  void SetMoveValues(double x, double y, double z);
  void SetRotateValues(double x_angel, double y_angel, double z_angel);
  void SetScaleValue(double scale);
  void BlockMoveSignals(bool b);
  void BlockRotateSignals(bool b);
  void BlockScaleSignals(bool b);
  void ClearFields();
  void UpdateMove(double x, double y, double z);

  void UpdateTransformationValues(std::any value);
};
}  // namespace object_viewer
#endif
