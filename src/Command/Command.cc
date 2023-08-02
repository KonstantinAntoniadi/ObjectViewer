#include "Command.h"

#include <cmath>

namespace object_viewer {

Move::Move(double x, double y, double z) : x_(x), y_(y), z_(z) {}

void Move::Execute(Object* obj) {
  for (auto& p : obj->vertexes_) {
    p.x += x_;
    p.y += y_;
    p.z += z_;
  }
}

std::any Move::Undo(Object* obj) {
  x_ = -x_;
  y_ = -y_;
  z_ = -z_;
  std::any res(Move(x_, y_, z_));
  Execute(obj);

  return res;
}
double Move::GetX() { return x_; }
double Move::GetY() { return y_; }
double Move::GetZ() { return z_; };

Scale::Scale(double scale) : scale_(scale) {}

void Scale::Execute(Object* obj) {
  for (auto& p : obj->vertexes_) {
    p = p * scale_;
  }
}

std::any Scale::Undo(Object* obj) {
  scale_ = 1.0 / scale_;
  Execute(obj);
  std::any res((Scale(scale_)));
  return res;
}

double Scale::GetScale() { return scale_; }

Rotate::Rotate(double x_angel, double y_angel, double z_angel)
    : x_angel_(x_angel), y_angel_(y_angel), z_angel_(z_angel) {}

void Rotate::Execute(Object* obj) {
  if (std::fabs(x_angel_) > eps_) {
    double x_rad = ConvertDegToRad(x_angel_);
    for (auto& p : obj->vertexes_) {
      double temp_y = p.y;
      double temp_z = p.z;
      p.y = temp_y * std::cos(x_rad) + temp_z * std::sin(x_rad);
      p.z = -temp_y * std::sin(x_rad) + temp_z * std::cos(x_rad);
    }
  }
  if (std::fabs(y_angel_) > eps_) {
    double y_rad = ConvertDegToRad(y_angel_);
    for (auto& p : obj->vertexes_) {
      double temp_x = p.x;
      double temp_z = p.z;
      p.x = std::cos(y_rad) * temp_x + std::sin(y_rad) * temp_z;
      p.z = std::sin(y_rad) * (-temp_x) + std::cos(y_rad) * temp_z;
    }
  }
  if (std::fabs(z_angel_) > eps_) {
    double z_rad = ConvertDegToRad(z_angel_);
    for (auto& p : obj->vertexes_) {
      double temp_x = p.x;
      double temp_y = p.y;
      p.x = temp_x * std::cos(z_rad) + temp_y * std::sin(z_rad);
      p.y = -temp_x * std::sin(z_rad) + temp_y * std::cos(z_rad);
    }
  }
}

double Rotate::ConvertDegToRad(double deg) { return deg * M_PI / 180.0; }

std::any Rotate::Undo(Object* obj) {
  x_angel_ = -x_angel_;
  y_angel_ = -y_angel_;
  z_angel_ = -z_angel_;
  Execute(obj);
  std::any res(Rotate(x_angel_, y_angel_, z_angel_));
  return res;
}

double Rotate::GetXAngel() { return x_angel_; }
double Rotate::GetYAngel() { return y_angel_; };
double Rotate::GetZAngel() { return z_angel_; }

}  // namespace object_viewer
