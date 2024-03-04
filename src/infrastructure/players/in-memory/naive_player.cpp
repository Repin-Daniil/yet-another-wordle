#include "naive_player.h"

namespace infrastructure {

std::string NaivePlayer::GetToken() const noexcept {
  return token_;
}

std::string_view NaivePlayer::GetSecretWord() const noexcept {
  return secret_word_;
}

int NaivePlayer::GetAttemptsAmount() const noexcept {
  return static_cast<int>(attempts_.size());
}

std::vector<game::WordCheckout> NaivePlayer::GetAttempts() const noexcept {
  return attempts_;
}

void NaivePlayer::ResetAttempts() {
  attempts_.clear();
}

void NaivePlayer::ChangeSecretWord(std::string_view new_secret_word) noexcept {
  ResetAttempts();
  secret_word_ = new_secret_word;
}

void NaivePlayer::AddAttempt(game::WordCheckout attempt) {
  if (GetAttemptsAmount() >= constants::GameSettings::MAX_ATTEMPTS_AMOUNT) {
    throw std::runtime_error("Game Over! No attempts!");
  }

  attempts_.push_back(attempt);
}

int NaivePlayer::GetRemainingAttemptsAmount() const noexcept {
  return constants::GameSettings::MAX_ATTEMPTS_AMOUNT - GetAttemptsAmount();
}

}  // namespace infrastructure
