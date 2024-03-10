#include "memory_mapped_player.h"

namespace infrastructure {

app::Token MemoryMappedPlayer::GetToken() const noexcept {
  return token_;
}

std::string_view MemoryMappedPlayer::GetName() const noexcept {
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

  if (!words_set_.contains(attempt.word)) {
    attempts_.push_back(attempt);
    words_set_.insert(attempt.word);
  }

  app::AddAttemptResult result{GetAttempts(), GetRemainingAttemptsAmount()};

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

int MemoryMappedPlayer::GetId() const noexcept {
  return id_;
}

int MemoryMappedPlayer::GetSessionId() const noexcept {
  return session_.GetId();
}

}  // namespace infrastructure
