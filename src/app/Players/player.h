#pragma once

#include <string>
#include <vector>
#include <utility>

#include "domain/game.h"

namespace app {

using Token = std::string;

class Player {
 public:
  Player(Token token, std::string_view secret_word) : token_(std::move(token)), secret_word_(secret_word) {
  }

  void AddAttempt(game::WordCheckout attempt);
  void ChangeSecretWord(std::string_view new_secret_word) noexcept;

  // Getters
  int GetAttemptsAmount() const noexcept;
  int GetRemainingAttemptsAmount() const noexcept;
  std::vector<game::WordCheckout> GetAttempts() const noexcept;
  std::string_view GetSecretWord() const noexcept;
  std::string GetToken() const noexcept;

 private:
  void ResetAttempts();

 private:
  Token token_;
  std::vector<game::WordCheckout> attempts_;
  std::string_view secret_word_;
};



}  // namespace app
