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

  player->AddAttempt(attempt);

  CheckWordResult result{player->GetAttempts()};

  if (attempt.status == game::WordStatus::RIGHT_WORD || player->GetRemainingAttemptsAmount() == 0) {
    result.is_new_word = true;
    auto new_word = game_.GetRandomWord();

    //    while (new_word == player->GetSecretWord()) {
    //      new_word = game_.GetRandomWord();  // FIXME, убрать после введения игровых сессий
    //    }

    player->ChangeSecretWord(new_word);  // TODO Потом вызывать здесь session->NextWord()
  }

  return result;
}

}  // namespace app
