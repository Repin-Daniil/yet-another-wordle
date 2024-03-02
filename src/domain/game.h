#pragma once

#include <array>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

#include "constants_storage.h"
#include "dictionary.h"

namespace game {

using constants::GameSettings;

enum class WordStatus { UNREAL_WORD, WRONG_WORD, RIGHT_WORD };
enum class LetterStatus { NONE, WRONG_PLACE, CORRECT };

std::string WordStatusToString(const WordStatus& status);
std::string LetterStatusToString(const LetterStatus& status);

struct WordCheckout {
  WordStatus status;
  std::array<LetterStatus, GameSettings::WORD_LENGTH> letters;
  std::string_view word;
};

/**
 * @brief Yet another Wordle-game
 * @todo Игровую сессию, чтобы можно было загадывать определенные слова. И конфиг на эти слова
 */
class Game {
 public:
  explicit Game(IDictionary& dict) : dict_(dict) {
  }

  [[nodiscard]] std::string_view GetRandomWord() const;
  [[nodiscard]] WordCheckout CheckWord(std::string_view user_answer, std::string_view word) const;
  [[nodiscard]] bool IsRealWord(std::string_view word) const;

 private:
  IDictionary& dict_;
};

}  // namespace game
