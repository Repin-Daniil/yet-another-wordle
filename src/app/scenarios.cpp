#include "scenarios.h"

namespace app {

Token GameStarter::StartGame() {
  auto player = players_.AddPlayer(game_.GetRandomWord());

  return player->GetToken();
}

std::optional<game::WordCheckout> WordChecker::CheckWord(const std::string& token, std::string_view word) {
  auto player = players_.GetPlayerByToken(token);

  if (!player) {
    return std::nullopt;
  }

  auto attempt = game_.CheckWord(word, player->GetSecretWord());

  if (attempt.status != game::UNREAL_WORD) {
    player->AddAttempt(attempt);
  }

  if (attempt.status == game::RIGHT_WORD || player->GetRemainingAttemptsAmount() == 0) {
    auto new_word = game_.GetRandomWord();

    while (new_word == player->GetSecretWord()) {
      new_word = game_.GetRandomWord();  // FIXME, убрать после введения игровых сессий
    }

    player->ChangeSecretWord(new_word);  // TODO Потом вызывать здесь session->NextWord()
  }

  return attempt;
}

}  // namespace app