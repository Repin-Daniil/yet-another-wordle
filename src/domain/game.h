#pragma once

#include <array>
#include <memory>
#include <unordered_map>
#include <utility>

#include "constants_storage.h"
#include "dictionary.h"

namespace game {

using constants::GameSettings;

enum WordStatus { UNREAL_WORD, WRONG_WORD, RIGHT_WORD };
enum LetterStatus { NONE, WRONG_PLACE, CORRECT };

struct WordCheckout {
  WordStatus status;
  std::array<LetterStatus, GameSettings::WORD_LENGTH> letters;
};

/**
 * @brief Yet another Wordle-game
 * @todo Игровую сессию, чтобы можно было загадывать определенные слова. И конфиг на эти слова
 */
class Game {
 public:
  explicit Game(IDictionary &dict) : dict_(dict){
  }

  std::string_view GetRandomWord() const;
  WordCheckout CheckWord(std::string_view user_answer, std::string_view word) const;
  bool IsRealWord(std::string_view word) const;

 private:
  IDictionary &dict_;
};

}  // namespace game
