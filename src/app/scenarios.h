#pragma once

#include <optional>
#include <string>

#include "domain/game.h"
#include "player.h"

namespace app {

using Token = std::string;

class GameStarter {
 public:
  GameStarter(game::Game &game,Players& players) : game_(game), players_(players) {}

  Token StartGame();

 private:
  game::Game game_;
  Players& players_;
};

class WordChecker {
 public:
  WordChecker(game::Game &game, Players &players) : game_(game), players_(players) {}

  std::optional<game::WordCheckout> CheckWord(const Token& token, std::string_view word);

 private:
  game::Game &game_;
  Players &players_;
};

}  // namespace app
