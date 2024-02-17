#include "game.h"

namespace game {

bool Game::IsRealWord(std::string_view word) {
  return word.size() == constants::GameSettings::WORD_LENGTH && dict_->IsWordExist(word);
}

std::string_view Game::GetRandomWord() {
  return dict_->GetRandomWord();
}

WordCheckout Game::CheckWord(const std::string &user_answer, const std::string &secret_word) {
  if (!IsRealWord(secret_word)) {
    throw std::runtime_error("Non-existent secret_word!");
  }

  if (!IsRealWord(user_answer)) {
    return {UNREAL_WORD}; //FIXME а как там array проинициализровался
  }

  WordCheckout result{};
  std::unordered_map<char, int> alphabet; //FIXME Rename

  for (const auto &letter : secret_word) {
    ++alphabet[letter]; //FIXME А это сохранит?
  }

  size_t i = 0;
  result.status = SUCCESS;

  for (const auto &letter : user_answer) {
    if (alphabet[letter] > 0) {
      --alphabet[letter];

      if (secret_word[i] == letter) {
        result.letters[i] = CORRECT;
      } else {
        result.status = WRONG;
        result.letters[i] = WRONG_PLACE;
      }
    } else {
      result.status = WRONG;
    }

    ++i;
  }

  return result;
}

}  // namespace game