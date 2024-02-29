#include "player.h"

namespace app {

std::string Player::GetToken() const noexcept {
  return token_;
}

std::string_view Player::GetSecretWord() const noexcept {
  return secret_word_;
}

int Player::GetAttemptsAmount() const noexcept {
  return static_cast<int>(attempts_.size());
}

std::vector<game::WordCheckout> Player::GetAttempts() const noexcept {
  return attempts_;
}

void Player::ResetAttempts() {
  attempts_.clear();
}

void Player::ChangeSecretWord(std::string_view new_secret_word) noexcept {
  ResetAttempts();
  secret_word_ = new_secret_word;
}

void Player::AddAttempt(game::WordCheckout attempt) {
  if (GetAttemptsAmount() >= constants::GameSettings::MAX_ATTEMPTS_AMOUNT) {
    throw std::runtime_error("Game Over! No attempts!");
  }

  attempts_.push_back(attempt);
}

int Player::GetRemainingAttemptsAmount() const noexcept {
  return constants::GameSettings::MAX_ATTEMPTS_AMOUNT - GetAttemptsAmount();
}

}  // namespace app
