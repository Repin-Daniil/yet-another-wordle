#include "game_starter.h"

namespace app {

Token GameStarter::Start() {
  auto player = players_.AddPlayer(game_);

  return player->GetToken();
}

}  // namespace app
