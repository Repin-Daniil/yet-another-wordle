#pragma once

#include <string>

#include "app/Players/players.h"
#include "app/Scenarios/CheckWord/word_checker.h"
#include "domain/game.h"

namespace app {

using Token = std::string;

class GameStarter {
 public:
  GameStarter(game::Game& game, IPlayers& players) : game_(game), players_(players) {
  }

  Token Start();

 private:
  game::Game game_;
  IPlayers& players_;
};

}  // namespace app
