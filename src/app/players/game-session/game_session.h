#pragma once

#include <unordered_set>
#include <vector>

#include "userver/storages/postgres/cluster.hpp"

#include "app/players/player.h"

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
  int GetWordsAmount() const noexcept;

 private:
  std::vector<Word> words_;
  std::unordered_set<std::string_view> words_set_;
};

class GameSession {
 public:
  GameSession(game::Game& game, userver::storages::postgres::ClusterPtr& pg_cluster);


  void NextSecretWord(bool is_guessed, int attempts_amount);
  std::string_view GetSecretWord() const noexcept;
  std::vector<Word> GetSecretWordsHistory() const noexcept;
  int GetId() const noexcept;
  //TODO Проверка было ли такое слово уже введено пользователем. Идемпотентность такая вот!

 private:
  int id_;
  game::Game& game_;
  userver::storages::postgres::ClusterPtr& pg_cluster_;
  std::string_view current_secret_word_;
  WordsArchive archive_;
};

}  // namespace app
