#pragma once

#include <vector>
#include <string>
#include <string_view>

#include "domain/game.h"

namespace app {

using Token = std::string;

struct AddAttemptResult {
  std::vector<game::WordCheckout> attempts;
  bool is_new_word_set = false;
};

class IPlayer {
 public:
    virtual AddAttemptResult AddAttempt(game::WordCheckout attempt) = 0;
//    virtual void ChangeSecretWord(std::string_view new_secret_word) noexcept = 0;

    virtual int GetAttemptsAmount() const noexcept = 0;
    virtual int GetRemainingAttemptsAmount() const noexcept = 0;
    virtual std::vector<game::WordCheckout> GetAttempts() const noexcept = 0;
    virtual std::string_view GetSecretWord() const noexcept = 0;
    virtual std::string GetToken() const noexcept = 0;

    virtual ~IPlayer() = default;
};

}  // namespace app
