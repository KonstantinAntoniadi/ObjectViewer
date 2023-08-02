#include "mainwindow.h"

#include <QSettings>
#include <any>
#include <iostream>
#include <typeinfo>

#include "glwidget.h"
#include "src/Command/Command.h"
#include "ui_mainwindow.h"

namespace object_viewer {
MainWindow::MainWindow(Controller* controller, QWidget* parent)
    : controller_(controller), QMainWindow(parent), ui_(new Ui::MainWindow) {
  ui_->setupUi(this);
  ui_->GLwidget->SetController(controller);
  this->setFixedSize(1420, 810);
  SincSettings();
  connect(ui_->Open, SIGNAL(triggered()), this, SLOT(OpenFile()));
  connect(ui_->Image, SIGNAL(triggered()), this, SLOT(SaveImage()));
  connect(ui_->Gif, SIGNAL(triggered()), this, SLOT(SaveGif()));
  connect(ui_->GLwidget, &GLWidget::ScaleChanged, this,
          &MainWindow::UpdateScale);
  connect(ui_->GLwidget, &GLWidget::UpdateRotationValues, this,
          &MainWindow::UpdateRotation);
}

void MainWindow::OpenFile() {
  QString file =
      QFileDialog::getOpenFileName(this, "Upload file ", "", "OBJ (*.obj)");
  if (!file.isEmpty()) {
    ClearFields();
    controller_->UploadObjectFromFile(file.toUtf8().constData());
    ui_->filenameValue->setText(controller_->GetObjectName().data());
    ui_->vertexCountValue->setText(
        QString::number(controller_->GetCountVertexes()));
    ui_->edgeCountValue->setText(QString::number(controller_->GetCountEdges()));
    UpdateGL();
  }
}

void MainWindow::SaveImage() {
  QString filepath = QFileDialog::getSaveFileName(
      this, "Save as...", "screen.bmp", "Images (*.bmp *.jpeg)");
  if (!filepath.isEmpty()) {
    controller_->SaveImage(filepath, ui_->GLwidget);
  }
}

void MainWindow::SaveGif() {
  QString filepath = QFileDialog::getSaveFileName(
      this, "Save as...", "animation.gif", "GIF (*.gif)");

  if (!filepath.isEmpty()) {
    controller_->SaveGif(filepath, ui_->GLwidget);
  }
}

void MainWindow::UpdateGL() { ui_->GLwidget->update(); }

void MainWindow::ClearFields() {
  double default_value = 0.0;
  double default_scale = 1.0;

  UpdateMove(default_value, default_value, default_value);
  UpdateRotation(default_value, default_value, default_value);
  SetScaleValue(default_scale);
}

void MainWindow::BlockMoveSignals(bool b) {
  ui_->xMoveSpinBox->blockSignals(b);
  ui_->yMoveSpinBox->blockSignals(b);
  ui_->zMoveSpinBox->blockSignals(b);
}

void MainWindow::BlockRotateSignals(bool b) {
  ui_->xRotateSpinBox->blockSignals(b);
  ui_->yRotateSpinBox->blockSignals(b);
  ui_->zRotateSpinBox->blockSignals(b);
}

void MainWindow::BlockScaleSignals(bool b) {
  ui_->scaleSpinBox->blockSignals(b);
}

void MainWindow::SetMoveValues(double x, double y, double z) {
  ui_->GLwidget->SetXLastMove(x);
  ui_->GLwidget->SetYLastMove(y);
  ui_->GLwidget->SetZLastMove(z);
  ui_->xMoveSpinBox->setValue(x);
  ui_->yMoveSpinBox->setValue(y);
  ui_->zMoveSpinBox->setValue(z);
}

void MainWindow::SetRotateValues(double x_angel, double y_angel,
                                 double z_angel) {
  ui_->GLwidget->SetXRotate(x_angel);
  ui_->GLwidget->SetYRotate(y_angel);
  ui_->GLwidget->SetZRotate(z_angel);
  ui_->xRotateSpinBox->setValue(x_angel);
  ui_->yRotateSpinBox->setValue(y_angel);
  ui_->zRotateSpinBox->setValue(z_angel);
}

void MainWindow::SetScaleValue(double scale) {
  ui_->GLwidget->SetScaleLast(scale);
  ui_->scaleSpinBox->setValue(scale);
}

void MainWindow::UpdateMove(double x, double y, double z) {
  BlockMoveSignals(true);
  SetMoveValues(x, y, z);
  BlockMoveSignals(false);
}

void MainWindow::UpdateRotation(double x_angel, double y_angel,
                                double z_angel) {
  BlockRotateSignals(true);
  SetRotateValues(x_angel, y_angel, z_angel);
  BlockRotateSignals(false);
}

void MainWindow::UpdateScale(double scale) {
  BlockScaleSignals(true);
  SetScaleValue(scale);
  BlockScaleSignals(false);
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
  if (event->key() == Qt::Key_Z && (event->modifiers() & Qt::MetaModifier) &&
      (event->modifiers() & Qt::ShiftModifier)) {
    std::any res = controller_->RedoTransformation();
    UpdateTransformationValues(res);

  } else if (event->key() == Qt::Key_Z &&
             (event->modifiers() & Qt::MetaModifier)) {
    std::any res = controller_->UndoTransformation();
    UpdateTransformationValues(res);
  }
}

void MainWindow::UpdateTransformationValues(std::any value) {
  if (value.type() == typeid(Move)) {
    Move* move = std::any_cast<Move>(&value);
    UpdateMove(ui_->GLwidget->GetXLastMove() + move->GetX(),
               ui_->GLwidget->GetYLastMove() + move->GetY(),
               ui_->GLwidget->GetZLastMove() + move->GetZ());
    UpdateGL();
  } else if (value.type() == typeid(Rotate)) {
    Rotate* rotate = std::any_cast<Rotate>(&value);
    UpdateRotation(ui_->GLwidget->GetXLastMove() + rotate->GetXAngel(),
                   ui_->GLwidget->GetYLastMove() + rotate->GetYAngel(),
                   ui_->GLwidget->GetZLastMove() + rotate->GetZAngel());
    UpdateGL();
  } else if (value.type() == typeid(Scale)) {
    Scale* scale = std::any_cast<Scale>(&value);
    UpdateScale(ui_->GLwidget->GetScaleLast() * scale->GetScale());
    UpdateGL();
  }
}

void MainWindow::SincSettings() {
  settings_->LoadSettings();
  if (settings_->GetEdgeType() == EdgeType::kSolid) {
    ui_->solidRadioButton->setChecked(true);
  } else if (settings_->GetEdgeType() == EdgeType::kDotted) {
    ui_->dottedRadioButton->setChecked(true);
  }

  ui_->thicknessEdgeSpinBox->setValue(settings_->GetEdgeWidth());
  ui_->sizeVertexSpinBox->setValue(settings_->GetVertexSize());

  if (settings_->GetVertexType() == VertexType::kCircle) {
    ui_->circleDisplayRadioButton->setChecked(true);
  } else if (settings_->GetVertexType() == VertexType::kSquare) {
    ui_->squareDisplayRadioButton->setChecked(true);
  } else if (settings_->GetVertexType() == VertexType::kNone) {
    ui_->noneDisplayRadioButton->setChecked(true);
  }

  if (settings_->GetProectionType() == ProectionType::kParallel) {
    ui_->parallelRadioButton->setChecked(true);
  } else if (settings_->GetProectionType() == ProectionType::kCentral) {
    ui_->centralRadioButton->setChecked(true);
  }
}

MainWindow::~MainWindow() {
  settings_->SaveSettings();
  delete ui_;
}

void MainWindow::on_solidRadioButton_clicked() {
  settings_->SetEdgeType(EdgeType::kSolid);
  UpdateGL();
}

void MainWindow::on_dottedRadioButton_clicked() {
  settings_->SetEdgeType(EdgeType::kDotted);
  UpdateGL();
}

void MainWindow::on_thicknessEdgeSpinBox_valueChanged(double arg1) {
  settings_->SetEdgeWidth(arg1);
  UpdateGL();
}

void MainWindow::on_chooseColorBackgroundLabel_clicked() {
  QColor color = QColorDialog::getColor(Qt::yellow, this);
  if (color.isValid()) {
    settings_->SetBackgroundColor(color);
    UpdateGL();
  }
}

void MainWindow::on_chooseColorEdgeButton_clicked() {
  QColor color = QColorDialog::getColor(Qt::yellow, this);
  if (color.isValid()) {
    settings_->SetEdgeColor(color);
    UpdateGL();
  }
}

void MainWindow::on_chooseColorVertexButton_clicked() {
  QColor color = QColorDialog::getColor(Qt::yellow, this);
  if (color.isValid()) {
    settings_->SetVertexColor(color);
    UpdateGL();
  }
}

void MainWindow::on_sizeVertexSpinBox_valueChanged(double arg1) {
  settings_->SetVertexSize(arg1);
  UpdateGL();
}

void MainWindow::on_noneDisplayRadioButton_clicked() {
  settings_->SetVertexType(VertexType::kNone);
  UpdateGL();
}

void MainWindow::on_squareDisplayRadioButton_clicked() {
  settings_->SetVertexType(VertexType::kSquare);
  UpdateGL();
}

void MainWindow::on_circleDisplayRadioButton_clicked() {
  settings_->SetVertexType(VertexType::kCircle);
  UpdateGL();
}

void MainWindow::on_parallelRadioButton_clicked() {
  settings_->SetProectionType(ProectionType::kParallel);
  UpdateGL();
}

void MainWindow::on_centralRadioButton_clicked() {
  settings_->SetProectionType(ProectionType::kCentral);
  UpdateGL();
}

void MainWindow::on_xMoveSpinBox_valueChanged(double arg1) {
  if (controller_->ObjectIsUploaded()) {
    controller_->MoveObject(arg1 - ui_->GLwidget->GetXLastMove(), 0, 0);
    ui_->GLwidget->SetXLastMove(arg1);
    UpdateGL();
  }
}

void MainWindow::on_yMoveSpinBox_valueChanged(double arg1) {
  if (controller_->ObjectIsUploaded()) {
    controller_->MoveObject(0, arg1 - ui_->GLwidget->GetYLastMove(), 0);
    ui_->GLwidget->SetYLastMove(arg1);
    UpdateGL();
  }
}

void MainWindow::on_zMoveSpinBox_valueChanged(double arg1) {
  if (controller_->ObjectIsUploaded()) {
    controller_->MoveObject(0, 0, arg1 - ui_->GLwidget->GetZLastMove());
    ui_->GLwidget->SetYLastMove(arg1);
    UpdateGL();
  }
}

void MainWindow::on_scaleSpinBox_valueChanged(double arg1) {
  if (controller_->ObjectIsUploaded()) {
    controller_->ScaleObject(arg1 / ui_->GLwidget->GetScaleLast());
    ui_->GLwidget->SetScaleLast(arg1);
    UpdateGL();
  }
}

void MainWindow::on_xRotateSpinBox_valueChanged(double arg1) {
  if (controller_->ObjectIsUploaded()) {
    controller_->RotateObject(arg1 - ui_->GLwidget->GetXLastMove(), 0, 0);
    ui_->GLwidget->SetXRotate(arg1);
    UpdateGL();
  }
}

void MainWindow::on_yRotateSpinBox_valueChanged(double arg1) {
  if (controller_->ObjectIsUploaded()) {
    controller_->RotateObject(0, arg1 - ui_->GLwidget->GetYRotate(), 0);
    ui_->GLwidget->SetYRotate(arg1);
    UpdateGL();
  }
}

void MainWindow::on_zRotateSpinBox_valueChanged(double arg1) {
  if (controller_->ObjectIsUploaded()) {
    controller_->RotateObject(0, 0, arg1 - ui_->GLwidget->GetZRotate());
    ui_->GLwidget->SetZRotate(arg1);
    UpdateGL();
  }
}
}  // namespace object_viewer
