#include "game.h"

namespace game {

bool Game::IsRealWord(std::string_view word) const {
  return word.size() == constants::GameSettings::WORD_LENGTH && dict_.IsWordExist(word);
}

std::string_view Game::GetRandomWord() const {
  return dict_.GetRandomWord();
}

WordCheckout Game::CheckWord(std::string_view user_answer, std::string_view secret_word) const {
  if (!IsRealWord(secret_word)) {
    throw std::runtime_error("Non-existent secret_word!");
  }

  if (!IsRealWord(user_answer)) {
    return {WordStatus::UNREAL_WORD, {}, {}};
  }

  WordCheckout result{};
  std::unordered_map<char, int> alphabet;  // FIXME Rename

  for (const auto &letter : secret_word) {
    ++alphabet[letter];
  }

  size_t i = 0;
  result.status = WordStatus::RIGHT_WORD;
  result.word = user_answer;

  for (const auto &letter : user_answer) {
    if (alphabet[letter] > 0) {
      --alphabet[letter];

      if (secret_word[i] == letter) {
        result.letters[i] = LetterStatus::CORRECT;
      } else {
        result.status = WordStatus::WRONG_WORD;
        result.letters[i] = LetterStatus::WRONG_PLACE;
      }
    } else {
      result.status = WordStatus::WRONG_WORD;
    }

    ++i;
  }

  return result;
}

std::string WordStatusToString(const game::WordStatus& status) {
  switch (status) {
    case WordStatus::UNREAL_WORD:
      return "UNREAL_WORD";
    case WordStatus::WRONG_WORD:
      return "WRONG_WORD";
    case WordStatus::RIGHT_WORD:
      return "RIGHT_WORD";
    default:
      return "UNKNOWN_WORD_STATUS";
  }
}

std::string LetterStatusToString(const LetterStatus& status) {
  switch (status) {
    case LetterStatus::NONE:
      return "NONE";
    case LetterStatus::WRONG_PLACE:
      return "WRONG_PLACE";
    case LetterStatus::CORRECT:
      return "CORRECT";
    default:
      return "UNKNOWN_LETTER_STATUS";
  }
}

}  // namespace game
