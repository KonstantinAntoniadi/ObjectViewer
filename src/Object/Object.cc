#include "Object.h"

namespace object_viewer {

Point::Point(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}

Point Point::operator*(double arg) {
  Point res(x * arg, y * arg, z * arg);
  return res;
}

Point operator*(double arg, Point& p) { return p * arg; }

double& Point::operator[](int i) {
  if (i == 0) {
    return x;
  } else if (i == 1) {
    return y;
  } else if (i == 2) {
    return z;
  }
  return x;
}

}  // namespace object_viewer
