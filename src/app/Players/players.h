#pragma once

#include "app/Players/player.h"

namespace app {

class IPlayers {
 public:
  virtual std::shared_ptr<Player> AddPlayer(std::string_view secret_word) = 0;

  virtual std::shared_ptr<Player> GetPlayerByToken(const Token &token) const = 0;
  virtual size_t GetPlayersAmount() const = 0;

  virtual bool IsTokenExist(const Token &token) const = 0;
};

}  // namespace app
