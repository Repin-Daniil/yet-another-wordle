#pragma once

#include <memory>

#include "app/Players/player.h"

namespace app {

class IPlayers {
 public:
  virtual std::shared_ptr<IPlayer> AddPlayer(std::string_view secret_word) = 0;
  virtual std::shared_ptr<IPlayer> GetPlayerByToken(const Token &token) = 0;

  virtual ~IPlayers() = default;
};

}  // namespace app
