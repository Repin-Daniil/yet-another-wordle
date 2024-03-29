#pragma once

#include <vector>
#include <optional>

#include "app/players/players.h"
#include "model/game.h"

namespace app {

enum class CheckWordErrorReason { UNREAL_TOKEN, UNREAL_WORD, REPEATED_WORD };

struct CheckWordError {
  CheckWordErrorReason reason;
};

struct CheckWordResult {
  std::vector<game::WordCheckout> attempts;
  int remaining_attempts;
  bool is_new_word = false;
};

class WordChecker {
 public:
  WordChecker(game::Game& game, IPlayers& players) : game_(game), players_(players) {
  }

  CheckWordResult Check(const Token& token, std::string_view word);

 private:
  game::Game& game_;
  IPlayers& players_;
};

}  // namespace app
