#ifndef OBJECTVIEWER_SRC_OBJECT_OBJECT_H
#define OBJECTVIEWER_SRC_OBJECT_OBJECT_H

#include <string>
#include <vector>

namespace object_viewer {

class Point {
 public:
  Point(double x_, double y_, double z_);
  double x;
  double y;
  double z;

  double& operator[](int i);

  Point operator*(double arg);
  friend Point operator*(double arg, const Point& p);
};

struct Object {
  std::string name_;
  std::vector<Point> vertexes_;
  std::vector<unsigned int> facets_;
};

}  // namespace object_viewer

#endif