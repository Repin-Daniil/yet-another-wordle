#pragma once

#include <unordered_set>
#include <vector>

#include "app/Players/player.h"

namespace app {

struct Word {
  std::string_view value;
  bool is_guessed;
  int attempts_amount;
};

class WordsArchive {
 public:
  void AddWord(Word word);
  bool IsContainWord(std::string_view word) const noexcept;
  std::vector<Word> GetWords() const noexcept;

 private:
  std::vector<Word> words_;
  std::unordered_set<std::string_view> words_set_;
};

class GameSession {
 public:
  GameSession(game::Game& game, const Token& token)
      : game_(game), current_secret_word_(game_.GetRandomWord()), player_token_(token) {
  }

  void NextSecretWord(bool is_guessed, int attempts_amount);
  std::string_view GetSecretWord() const noexcept;
  std::vector<Word> GetSecretWordsHistory() const noexcept;

 private:
  game::Game& game_;
  std::string_view current_secret_word_;
  Token player_token_;
  WordsArchive archive_;
};

}  // namespace app
