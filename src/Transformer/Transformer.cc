#include "Transformer.h"

namespace object_viewer {
void Transformer::SetCommand(std::shared_ptr<Command> command) {
  commands_.resize(cur_command_ + 1);
  commands_.push_back(command);
  cur_command_ = commands_.size() - 1;
}

void Transformer::Transform(Object* obj) { commands_.back()->Execute(obj); }

void Transformer::ClearCommands() {
  commands_.clear();
  cur_command_ = -1;
}

std::any Transformer::Undo(Object* obj) {
  std::any res = nullptr;
  if (cur_command_ >= 0) {
    res = commands_[cur_command_]->Undo(obj);
    cur_command_--;
  }

  return res;
}

std::any Transformer::Redo(Object* obj) {
  std::any res = nullptr;
  if (cur_command_ < (int)commands_.size() - 1) {
    res = commands_[++cur_command_]->Undo(obj);
  }

  return res;
}
}  // namespace object_viewer
