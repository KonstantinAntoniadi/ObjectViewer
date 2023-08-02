#ifndef OBJECTVIEWER_SRC_FILEREADER_OBJECTFILEREADER_H
#define OBJECTVIEWER_SRC_FILEREADER_OBJECTFILEREADER_H

#include <string>

#include "BaseFileReader.h"

namespace object_viewer {
class ObjectFileReader : public BaseFileReader {
 public:
  void ReadFile(const std::string& filepath, Object* obj) override;
  void ReadVertex(const std::string& line, Object* obj);
  void ReadFacet(const std::string& line, Object* obj);

 private:
  std::string GetFilename(const std::string& filepath);
};
}  // namespace object_viewer

#endif