#ifndef OBJECTVIEWER_SRC_TRANSFORMER_TRANSFORMER_H
#define OBJECTVIEWER_SRC_TRANSFORMER_TRANSFORMER_H

#include <any>
#include <memory>
#include <vector>

#include "../Command/Command.h"
#include "../Object/Object.h"

namespace object_viewer {
class Transformer {
 public:
  void SetCommand(std::shared_ptr<Command> command);
  void Transform(Object* obj);
  void ClearCommands();

  std::any Undo(Object* obj);
  std::any Redo(Object* obj);

 private:
  std::vector<std::shared_ptr<Command>> commands_;
  int cur_command_ = -1;
};

};  // namespace object_viewer
#endif
