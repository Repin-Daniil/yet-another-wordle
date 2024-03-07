#pragma once

#include <memory>

#include "player.h"

namespace app {

class IPlayers {
 public:
  virtual std::shared_ptr<IPlayer> AddPlayer(game::Game& game) = 0;
  virtual std::shared_ptr<IPlayer> GetPlayerByToken(const Token& token) = 0;

  virtual ~IPlayers() = default;
};

}  // namespace app
