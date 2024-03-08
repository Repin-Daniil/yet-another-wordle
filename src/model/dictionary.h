#pragma once

#include <string>

namespace game {

class IDictionary {
 public:
  virtual std::string_view GetRandomWord() = 0;
  virtual bool IsWordExist(std::string_view word) = 0;

  virtual ~IDictionary() = default;
};

}  // namespace game
