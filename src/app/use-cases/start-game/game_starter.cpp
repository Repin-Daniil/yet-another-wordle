#include "game_starter.h"

namespace app {

Token GameStarter::Start(const std::string& name) {
  auto player = players_.AddPlayer(name, game_);

  return player->GetToken();
}

}  // namespace app
