#pragma once

#include <unordered_set>
#include <vector>

#include "app/Players/player.h"

namespace app {

class WordsArchive {
 public:
  void AddWord(std::string_view word);
  bool IsContainWord(std::string_view word);
  std::vector<std::string_view> GetWords();

 private:
  std::vector<std::string_view> words_;
  std::unordered_set<std::string_view> words_set_;
};

class GameSession {
  explicit GameSession(game::Game& game, uint64_t id) : game_(game), session_id_(id) {
    secret_words_.AddWord(game_.GetRandomWord());
  }

  std::string_view NextSecretWord();
  std::string_view GetSecretWord() const noexcept;
  std::vector<std::string_view> GetSecretWordsHistory() const noexcept;

 private:
  game::Game& game_;
  uint64_t session_id_;
  WordsArchive secret_words_;
};

}  // namespace app
