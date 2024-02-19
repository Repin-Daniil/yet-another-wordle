#pragma once

#include <optional>
#include <string_view>
#include <string>
#include <utility>

#include "domain/game.h"
#include "player.h"

namespace app {

/**
 * @brief
 */
class Application {
 public:
  explicit Application(game::Game game) : game_(std::move(game)) {
  }

  std::string StartGame();  // Return token
  std::optional<game::WordCheckout> CheckWord(const std::string &token, std::string_view word);

  // Getters
  const Players &GetPlayers();
  const game::Game &GetGame();

 private:
  game::Game game_;
  Players players_;
};

}  // namespace app
