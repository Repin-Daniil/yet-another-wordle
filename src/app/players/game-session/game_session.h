#pragma once

#include <unordered_set>
#include <vector>

#include "userver/storages/postgres/cluster.hpp"

#include "app/players/player.h"

namespace {
const userver::storages::postgres::Query kInsertGameSession{"INSERT INTO wordle_schema.sessions (words_amount) VALUES($1)",
                                                       userver::storages::postgres::Query::Name{"insert_game_session"}};
}

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
  GameSession(game::Game& game, userver::storages::postgres::ClusterPtr& pg_cluster)
      : game_(game), pg_cluster_(pg_cluster), current_secret_word_(game_.GetRandomWord()) {
    auto result_insert = pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kMaster, kInsertGameSession, 0);
  }

  void NextSecretWord(bool is_guessed, int attempts_amount);
  std::string_view GetSecretWord() const noexcept;
  std::vector<Word> GetSecretWordsHistory() const noexcept;

 private:
  uint64_t id_;
  game::Game& game_;
  userver::storages::postgres::ClusterPtr& pg_cluster_;
  std::string_view current_secret_word_;
  WordsArchive archive_;
};

}  // namespace app
