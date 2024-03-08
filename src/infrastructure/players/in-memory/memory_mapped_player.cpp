#include "memory_mapped_player.h"

namespace infrastructure {

std::string MemoryMappedPlayer::GetToken() const noexcept {
  return token_;
}

std::string MemoryMappedPlayer::GetName() const noexcept {
  return name_;
}

std::string_view MemoryMappedPlayer::GetSecretWord() const noexcept {
  return session_.GetSecretWord();
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

app::AddAttemptResult MemoryMappedPlayer::AddAttempt(game::WordCheckout attempt) {
  if (GetAttemptsAmount() >= constants::GameSettings::kMaxAttemptsAmount) {
    throw std::runtime_error("Game Over! No attempts!");
  }

  attempts_.push_back(attempt);

  app::AddAttemptResult result{GetAttempts()};

  if (attempt.status == game::WordStatus::RIGHT_WORD || GetRemainingAttemptsAmount() == 0) {
    session_.NextSecretWord(attempt.status == game::WordStatus::RIGHT_WORD, GetAttemptsAmount());
    result.is_new_word_set = true;
    ResetAttempts();
  }

  return result;
}

int MemoryMappedPlayer::GetRemainingAttemptsAmount() const noexcept {
  return constants::GameSettings::kMaxAttemptsAmount - GetAttemptsAmount();
}

}  // namespace infrastructure
