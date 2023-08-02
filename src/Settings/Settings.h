#ifndef OBJECTVIEWER_SRC_SETTINGS_SETTINGS_H
#define OBJECTVIEWER_SRC_SETTINGS_SETTINGS_H

#include <QSettings>

#include "QtGui/qcolor.h"

namespace object_viewer {

enum class VertexType { kSquare, kCircle, kNone };
enum class ProectionType { kParallel, kCentral };
enum class EdgeType : int { kSolid = 0, kDotted };

class Settings {
 public:
  Settings(Settings &other) = delete;
  ~Settings();
  void operator=(const Settings &other) = delete;
  static Settings *GetInstance();

  void SetBackgroundColor(QColor color);
  void SetEdgeColor(QColor color);
  void SetVertexColor(QColor color);
  void SetEdgeWidth(double width);
  void SetVertexSize(double size);
  void SetEdgeType(EdgeType type);
  void SetVertexType(VertexType type);
  void SetProectionType(ProectionType type);

  QColor GetBackgroundColor();
  QColor GetEdgeColor();
  QColor GetVertexColor();
  double GetEdgeWidth();
  double GetVertexSize();
  EdgeType GetEdgeType();
  VertexType GetVertexType();
  ProectionType GetProectionType();

  void SaveSettings();

  void LoadSettings();

 protected:
  Settings() {}
  static Settings *settings_;

 private:
  QSettings qsettings_;

  QColor background_color_;
  QColor edge_color_;
  QColor vertex_color_;

  double edge_width_;
  double vertex_size_;

  EdgeType edge_type_;
  VertexType vertex_type_;
  ProectionType proection_type_;
};

}  // namespace object_viewer

#endif