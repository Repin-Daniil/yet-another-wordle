#include "game_starter.h"

namespace app {

Token GameStarter::Start() {
  auto player = players_.AddPlayer(game_.GetRandomWord());  // FIXME А вот здесь гонка!

  return player->GetToken();
}

}  // namespace app
