#include "scenarios.h"

namespace app {

Token GameStarter::Start() {
  auto player = players_.AddPlayer(game_.GetRandomWord()); //FIXME А вот здесь может быть гонка с players

  return player->GetToken();
}

game::WordCheckout WordChecker::Check(std::shared_ptr<Player> player, std::string_view word) {
  auto attempt = game_.CheckWord(word, player->GetSecretWord());

  if (attempt.status != game::WordStatus::UNREAL_WORD) {
    player->AddAttempt(attempt);
  }

  if (attempt.status == game::WordStatus::RIGHT_WORD || player->GetRemainingAttemptsAmount() == 0) {
    auto new_word = game_.GetRandomWord();

//    while (new_word == player->GetSecretWord()) {
//      new_word = game_.GetRandomWord();  // FIXME, убрать после введения игровых сессий
//    }

    player->ChangeSecretWord(new_word);  // TODO Потом вызывать здесь session->NextWord()
  }

  return attempt;
}

}  // namespace app