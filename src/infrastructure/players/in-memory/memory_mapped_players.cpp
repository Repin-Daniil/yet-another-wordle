#include "memory_mapped_players.h"

namespace {
const userver::storages::postgres::Query kInsertPlayer{
    "INSERT INTO wordle_schema.players (name, token, session_id) VALUES($1, $2, $3) RETURNING id",
    userver::storages::postgres::Query::Name{"insert_player"}};

const userver::storages::postgres::Query kCountToken{"SELECT count(*) FROM wordle_schema.players WHERE token=$1",
                                                     userver::storages::postgres::Query::Name{"count_token"}};
}  // namespace

namespace infrastructure {

std::string TokenGenerator::GenerateNewToken() {
  std::stringstream ss;

  while (ss.str().size() != 32) {
    ss.clear();
    ss << std::setfill('0') << std::setw(16) << std::hex << generator1_();
    ss << std::setfill('0') << std::setw(16) << std::hex << generator2_();
  }

  return ss.str();
}

std::shared_ptr<app::IPlayer> MemoryMappedPlayers::AddPlayer(const std::string& name, game::Game& game) {
  auto session = app::GameSession(game, pg_cluster_);

  auto token = token_generator_.GenerateNewToken();
  bool token_is_unique = pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kMaster, kCountToken, token)
                             .AsSingleRow<int>() == 0;

  while (!token_is_unique) {
    token = token_generator_.GenerateNewToken();
    token_is_unique = pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kMaster, kCountToken, token)
                          .AsSingleRow<int>() == 0;
  }

  auto result_insert = pg_cluster_->Execute(userver::storages::postgres::ClusterHostType::kMaster, kInsertPlayer, name,
                                            token, session.GetId());

  auto player_ptr = players_.Emplace(token, result_insert.AsSingleRow<int>(), name, token, session);

  return player_ptr.value;
}

std::shared_ptr<app::IPlayer> MemoryMappedPlayers::GetPlayerByToken(const app::Token& token) {
  return players_.Get(token);
}

}  // namespace infrastructure
