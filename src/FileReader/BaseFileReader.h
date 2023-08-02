#ifndef OBJECTVIEWER_SRC_FILEREADER_BASEFILEREADER_H
#define OBJECTVIEWER_SRC_FILEREADER_BASEFILEREADER_H

#include <string>

#include "../Object/Object.h"

namespace object_viewer {
class BaseFileReader {
 public:
  virtual ~BaseFileReader() = default;
  virtual void ReadFile(const std::string &filepath, Object *obj) = 0;
};
}  // namespace object_viewer

#endif