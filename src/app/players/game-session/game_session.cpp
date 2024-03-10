#include "game_session.h"

namespace {
const userver::storages::postgres::Query kInsertGameSession{
    "INSERT INTO wordle_schema.sessions (words_amount) VALUES($1) RETURNING id",
    userver::storages::postgres::Query::Name{"insert_game_session"}};
const userver::storages::postgres::Query kUpdateGameSession{
    "UPDATE wordle_schema.sessions SET words_amount = words_amount + 1 WHERE id = $1",
    userver::storages::postgres::Query::Name{"update_game_session"}};
const userver::storages::postgres::Query kInsertWord{
    "INSERT INTO wordle_schema.words (session_id, word_num, word, is_guessed, attempts_amount) VALUES($1, $2, $3, $4, "
    "$5)",
    userver::storages::postgres::Query::Name{"insert_game_session"}};
}  // namespace

namespace app {

GameSession::GameSession(game::Game& game, userver::storages::postgres::ClusterPtr& pg_cluster)
    : game_(game), pg_cluster_(pg_cluster), current_secret_word_(game_.GetRandomWord()) {
  auto result_insert =
      pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kMaster, kInsertGameSession, 0);

  id_ = result_insert.AsSingleRow<int>();
}

void GameSession::NextSecretWord(bool is_guessed, int attempts_amount) {
  archive_.AddWord({current_secret_word_, is_guessed, attempts_amount});
  pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kMaster, kUpdateGameSession, id_);
  pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kMaster, kInsertWord, id_,
                       archive_.GetWordsAmount(), current_secret_word_, is_guessed, attempts_amount);

  auto new_word = game_.GetRandomWord();

  while (archive_.IsContainWord(new_word)) {
    new_word = game_.GetRandomWord();
  }

  current_secret_word_ = new_word;
}

std::string_view GameSession::GetSecretWord() const noexcept {
  return current_secret_word_;
}

std::vector<Word> GameSession::GetSecretWordsHistory() const noexcept {
  return archive_.GetWords();
}

int GameSession::GetId() const noexcept {
  return id_;
}

void WordsArchive::AddWord(const Word& word) {
  words_set_.insert(word.value);
  words_.push_back(word);
}

bool WordsArchive::IsContainWord(std::string_view word) const noexcept {
  return words_set_.contains(word.data());
}

std::vector<Word> WordsArchive::GetWords() const noexcept {
  return words_;
}

int WordsArchive::GetWordsAmount() const noexcept {
  return words_.size();
}

}  // namespace app
