#pragma once

#include <iomanip>
#include <memory>
#include <random>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

#include <userver/rcu/rcu_map.hpp>
#include "userver/storages/postgres/cluster.hpp"

#include "app/players/game-session/game_session.h"
#include "app/players/player.h"
#include "app/players/players.h"
#include "infrastructure/players/in-memory/memory_mapped_player.h"

namespace infrastructure {

struct TokenGenerator {
 public:
  app::Token GenerateNewToken();

 private:
  std::random_device random_device_;
  std::mt19937_64 generator1_{[this] {
    std::uniform_int_distribution<std::mt19937_64::result_type> dist;
    return dist(random_device_);
  }()};

  std::mt19937_64 generator2_{[this] {
    std::uniform_int_distribution<std::mt19937_64::result_type> dist;
    return dist(random_device_);
  }()};
};

class MemoryMappedPlayers : public app::IPlayers {
 public:
  explicit MemoryMappedPlayers(userver::storages::postgres::ClusterPtr& pg_cluster) : pg_cluster_(pg_cluster) {
  }

  std::shared_ptr<app::IPlayer> AddPlayer(const std::string& name, game::Game &game) override;
  std::shared_ptr<app::IPlayer> GetPlayerByToken(const app::Token& token) override;

 private:
  userver::storages::postgres::ClusterPtr& pg_cluster_;
  userver::rcu::RcuMap<std::string, MemoryMappedPlayer> players_;
  TokenGenerator token_generator_;
};

}  // namespace infrastructure
