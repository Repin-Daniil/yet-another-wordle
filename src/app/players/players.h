#pragma once

#include <memory>
#include <string>

#include "player.h"

namespace app {

class IPlayers {
 public:
  virtual std::shared_ptr<IPlayer> AddPlayer(const std::string& name, game::Game& game) = 0;
  virtual std::shared_ptr<IPlayer> GetPlayerByToken(const Token& token) = 0;

  virtual ~IPlayers() = default;
};

}  // namespace app
