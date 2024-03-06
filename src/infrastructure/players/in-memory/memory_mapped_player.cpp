#include "memory_mapped_player.h"

namespace infrastructure {

std::string MemoryMappedPlayer::GetToken() const noexcept {
  return token_;
}

std::string_view MemoryMappedPlayer::GetSecretWord() const noexcept {
  return secret_word_;
}

int MemoryMappedPlayer::GetAttemptsAmount() const noexcept {
  return static_cast<int>(attempts_.size());
}

std::vector<game::WordCheckout> MemoryMappedPlayer::GetAttempts() const noexcept {
  return attempts_;
}

void MemoryMappedPlayer::ResetAttempts() {
  attempts_.clear();
}

void MemoryMappedPlayer::ChangeSecretWord(std::string_view new_secret_word) noexcept {
  ResetAttempts();
  secret_word_ = new_secret_word;
}

void MemoryMappedPlayer::AddAttempt(game::WordCheckout attempt) {
  if (GetAttemptsAmount() >= constants::GameSettings::MAX_ATTEMPTS_AMOUNT) {
    throw std::runtime_error("Game Over! No attempts!");
  }

  attempts_.push_back(attempt);
}

int MemoryMappedPlayer::GetRemainingAttemptsAmount() const noexcept {
  return constants::GameSettings::MAX_ATTEMPTS_AMOUNT - GetAttemptsAmount();
}

}  // namespace infrastructure
