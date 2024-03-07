#pragma once

#include <string>
#include <utility>
#include <vector>

#include "app/players/game-session/game_session.h"
#include "app/players/player.h"
#include "model/game.h"

namespace infrastructure {

class MemoryMappedPlayer : public app::IPlayer {
 public:
  MemoryMappedPlayer(app::Token token, app::GameSession session)
      : token_(std::move(token)), session_(std::move(session)) {
  }

  app::AddAttemptResult AddAttempt(game::WordCheckout attempt) override;

  // Getters
  int GetAttemptsAmount() const noexcept override;
  int GetRemainingAttemptsAmount() const noexcept override;
  std::vector<game::WordCheckout> GetAttempts() const noexcept override;
  std::string_view GetSecretWord() const noexcept override;
  std::string GetToken() const noexcept override;

 private:
  void ResetAttempts();

 private:
  app::Token token_;
  app::GameSession session_;
  std::vector<game::WordCheckout> attempts_;
};

}  // namespace infrastructure
