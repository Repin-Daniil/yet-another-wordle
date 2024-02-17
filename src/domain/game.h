#pragma once

#include <array>
#include <memory>
#include <unordered_map>

#include "constants_storage.h"
#include "dictionary.h"

namespace game {

using constants::GameSettings;

enum WordStatus { UNREAL_WORD, WRONG, SUCCESS };
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
  explicit Game(std::unique_ptr<IDictionary> dict) : dict_(std::move(dict)) {
  }

  std::string_view GetRandomWord();
  WordCheckout CheckWord(const std::string& user_answer, const std::string &word);
  bool IsRealWord(std::string_view word);

 private:
  std::unique_ptr<IDictionary> dict_;
};

}  // namespace game
