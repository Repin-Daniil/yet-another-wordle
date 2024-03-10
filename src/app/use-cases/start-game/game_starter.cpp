#include "game_starter.h"

namespace app {

Token GameStarter::Start(std::string_view name) {
  auto player = players_.AddPlayer(name, game_);

  return player->GetToken();
}

}  // namespace app
