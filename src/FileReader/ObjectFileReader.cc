#include "ObjectFileReader.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

namespace object_viewer {
void ObjectFileReader::ReadFile(const std::string& filepath, Object* obj) {
  std::ifstream file(filepath);
  if (!file.is_open()) {
    throw std::invalid_argument("Invalid file extension");
  }

  obj->name_ = GetFilename(filepath);

  std::string line;
  while (std::getline(file, line)) {
    if (line.compare(0, 2, "v ") == 0) {
      ReadVertex(line, obj);
    } else if (line.compare(0, 2, "f ") == 0) {
      ReadFacet(line, obj);
    }
  }
}

void ObjectFileReader::ReadVertex(const std::string& line, Object* obj) {
  std::istringstream iss(line);
  std::string remove_char;
  iss >> remove_char;
  Point ver(0, 0, 0);
  for (int i = 0; i < 3; i++) {
    iss >> ver[i];
  }
  obj->vertexes_.push_back(ver);
}

void ObjectFileReader::ReadFacet(const std::string& line, Object* obj) {
  std::istringstream iss(line);
  iss.ignore(std::numeric_limits<std::streamsize>::max(), ' ');

  int vertex_index{}, prev_vertex_index{}, first_vertex_index{};
  bool first_iteration = true;

  while (iss >> vertex_index) {
    vertex_index -= 1;
    if (vertex_index < 0) {
      vertex_index += obj->vertexes_.size() + 1;
    }
    if (!first_iteration) {
      obj->facets_.push_back(prev_vertex_index);
      obj->facets_.push_back(vertex_index);
    } else {
      first_vertex_index = vertex_index;
      first_iteration = false;
    }
    prev_vertex_index = vertex_index;

    iss.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
  }
  obj->facets_.push_back(prev_vertex_index);
  obj->facets_.push_back(first_vertex_index);
}

std::string ObjectFileReader::GetFilename(const std::string& filepath) {
  std::string filename = filepath.substr(filepath.find_last_of("/\\") + 1);
  return filename;
}
}  // namespace object_viewer
