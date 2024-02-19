#include "application.h"

namespace app {

std::string Application::StartGame() {
  auto player = players_.AddPlayer(game_.GetRandomWord());

  return player->GetToken();
}

std::optional<game::WordCheckout> Application::CheckWord(const std::string &token, std::string_view word) {
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

const Players &Application::GetPlayers() {
  return players_;
}

const game::Game &Application::GetGame() {
  return game_;
}

}  // namespace app
