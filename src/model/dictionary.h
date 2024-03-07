#pragma once

#include <string>

namespace game {

/**
 * @brief Интерфейс словаря, хранящего слова, участвующие в игре
 * @todo словарь в elastic-search
 */
class IDictionary {
 public:
  virtual std::string_view GetRandomWord() = 0;
  virtual bool IsWordExist(std::string_view word) = 0;

  virtual ~IDictionary() = default;
};

}  // namespace game
