#pragma once

#include <string>

#include "app/players/players.h"
#include "model/game.h"

namespace app {

using Token = std::string;

class GameStarter {
 public:
  GameStarter(game::Game& game, IPlayers& players) : game_(game), players_(players) {
  }

  Token Start(const std::string& name);

 private:
  game::Game game_;
  IPlayers& players_;
};

}  // namespace app
