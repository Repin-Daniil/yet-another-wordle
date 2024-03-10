#pragma once

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <unordered_set>

#include "app/players/game-session/game_session.h"
#include "app/players/player.h"
#include "model/game.h"

namespace infrastructure {

class MemoryMappedPlayer : public app::IPlayer {
 public:
  MemoryMappedPlayer(int id, std::string name, app::Token token, app::GameSession session)
      : id_(id), name_(std::move(name)), token_(std::move(token)), session_(std::move(session)) {
  }

  app::AddAttemptResult AddAttempt(game::WordCheckout attempt) override;

  // Getters
  int GetAttemptsAmount() const noexcept override;
  int GetRemainingAttemptsAmount() const noexcept override;
  app::Token GetToken() const noexcept override;
  std::vector<game::WordCheckout> GetAttempts() const noexcept override;
  std::string_view GetSecretWord() const noexcept override;
  std::string_view GetName() const noexcept override;
  int GetId() const noexcept override;
  int GetSessionId() const noexcept override;


 private:
  void ResetAttempts();

 private:
  int id_;
  std::string name_;
  app::Token token_;
  app::GameSession session_;
  std::vector<game::WordCheckout> attempts_;
  std::unordered_set<std::string> words_set_;
};

}  // namespace infrastructure
