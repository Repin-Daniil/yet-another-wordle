#pragma once

#include <array>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <codecvt>
#include <locale>

#include "constants_storage.h"
#include "dictionary.h"

namespace game {

enum class WordStatus { UNREAL_WORD, WRONG_WORD, RIGHT_WORD };
enum class LetterStatus { NONE, WRONG_PLACE, CORRECT };

std::string WordStatusToString(const WordStatus& status);
std::string LetterStatusToString(const LetterStatus& status);

using constants::GameSettings;

struct WordCheckout {
  WordStatus status;
  std::array<LetterStatus, GameSettings::kWordLength> letters;
  std::u32string word;
};


class Game {
 public:
  explicit Game(IDictionary& dict) : dict_(dict) {
  }

  std::string_view GetRandomWord() const;
  WordCheckout CheckWord(std::string_view user_answer, std::string_view word) const;
  bool IsRealWord(std::string_view word) const;

 private:
  IDictionary& dict_;
};

}  // namespace game
