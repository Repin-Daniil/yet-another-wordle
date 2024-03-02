#pragma once

#include <vector>

#include "app/Players/players.h"
#include "domain/game.h"

namespace app {

enum class CheckWordErrorReason { UNREAL_TOKEN, UNREAL_WORD };

struct CheckWordError {
  CheckWordErrorReason reason;
};

struct CheckWordResult {
  std::vector<game::WordCheckout> attempts;
  bool is_new_word = false;
  int max_attempts_amount = constants::GameSettings::MAX_ATTEMPTS_AMOUNT;
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
