#include "game.h"

namespace game {

bool Game::IsRealWord(std::string_view word) const {
  return word.size() == constants::GameSettings::WORD_LENGTH && dict_->IsWordExist(word);
}

std::string_view Game::GetRandomWord() const {
  return dict_->GetRandomWord();
}

WordCheckout Game::CheckWord(std::string_view user_answer, std::string_view secret_word) const {
  if (!IsRealWord(secret_word)) {
    throw std::runtime_error("Non-existent secret_word!");
  }

  if (!IsRealWord(user_answer)) {
    return {UNREAL_WORD};
  }

  WordCheckout result{};
  std::unordered_map<char, int> alphabet;  // FIXME Rename

  for (const auto &letter : secret_word) {
    ++alphabet[letter];
  }

  size_t i = 0;
  result.status = RIGHT_WORD;

  for (const auto &letter : user_answer) {
    if (alphabet[letter] > 0) {
      --alphabet[letter];

      if (secret_word[i] == letter) {
        result.letters[i] = CORRECT;
      } else {
        result.status = WRONG_WORD;
        result.letters[i] = WRONG_PLACE;
      }
    } else {
      result.status = WRONG_WORD;
    }

    ++i;
  }

  return result;
}

}  // namespace game
