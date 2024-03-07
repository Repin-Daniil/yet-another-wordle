#include "word_checker.h"

namespace app {

CheckWordResult WordChecker::Check(const Token& token, std::string_view word) {
  auto player = players_.GetPlayerByToken(token);

  if (!player) {
    throw CheckWordError{CheckWordErrorReason::UNREAL_TOKEN};
  }

  auto attempt = game_.CheckWord(word, player->GetSecretWord());

  if (attempt.status == game::WordStatus::UNREAL_WORD) {
    throw CheckWordError{CheckWordErrorReason::UNREAL_WORD};
  }

  auto result = player->AddAttempt(attempt);

  return {result.attempts, result.is_new_word_set};
}

}  // namespace app
