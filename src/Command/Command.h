#ifndef OBJECTVIEWER_SRC_COMMAND_COMMAND_H
#define OBJECTVIEWER_SRC_COMMAND_COMMAND_H

#include <any>

#include "../Object/Object.h"

namespace object_viewer {

class Command {
 public:
  virtual ~Command() {}
  virtual void Execute(Object* obj) = 0;
  virtual std::any Undo(Object* obj) = 0;
};

class Move : public Command {
 public:
  Move(double x, double y, double z);
  void Execute(Object* obj) override;
  std::any Undo(Object* obj) override;
  double GetX();
  double GetY();
  double GetZ();

 private:
  double x_, y_, z_;
};

class Rotate : public Command {
 public:
  Rotate(double x_angel, double y_angel, double z_angel);
  void Execute(Object* obj) override;
  double ConvertDegToRad(double deg);
  std::any Undo(Object* obj) override;
  double GetXAngel();
  double GetYAngel();
  double GetZAngel();

 private:
  double x_angel_, y_angel_, z_angel_;
  static constexpr double eps_ = 1e-07;
};

class Scale : public Command {
 public:
  Scale(double scale);
  void Execute(Object* obj) override;
  std::any Undo(Object* obj) override;
  double GetScale();

 private:
  double scale_;
};
}  // namespace object_viewer

#endif