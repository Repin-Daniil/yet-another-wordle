#include "game_session.h"



namespace app {

void GameSession::NextSecretWord(bool is_guessed, int attempts_amount) {
  auto new_word = game_.GetRandomWord();

  while (archive_.IsContainWord(new_word)) {
    new_word = game_.GetRandomWord();
  }

  archive_.AddWord({current_secret_word_, is_guessed, attempts_amount});

  current_secret_word_ = new_word;
}

std::string_view GameSession::GetSecretWord() const noexcept {
  return current_secret_word_;
}

std::vector<Word> GameSession::GetSecretWordsHistory() const noexcept {
  return archive_.GetWords();
}

void WordsArchive::AddWord(Word word) {
  words_set_.insert(word.value);
  words_.push_back(word);
}

bool WordsArchive::IsContainWord(std::string_view word) const noexcept {
  return words_set_.contains(word);
}

std::vector<Word> WordsArchive::GetWords() const noexcept {
  return words_;
}

}  // namespace app
