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

#include "app/Players/player.h"
#include "app/Players/players.h"
#include "infrastructure/players/in-memory/naive_player.h"

namespace infrastructure {

/**
 * @brief Генератор токенов для пользователей
 * @todo Заменить на boost.uuid
 */
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

/** In-memory playes.
 * @todo Прокинуть сюда engine::SharedMutex из компонента, чтобы убрать гонку при добавлении игроков в мапу
 */
class NaivePlayers : public app::IPlayers {
 public:
  std::shared_ptr<app::IPlayer> AddPlayer(std::string_view secret_word) override;

  std::shared_ptr<app::IPlayer> GetPlayerByToken(const app::Token& token) const override;
  size_t GetPlayersAmount() const override;

  bool IsTokenExist(const app::Token& token) const override;

 private:
  std::unordered_map<std::string, std::shared_ptr<NaivePlayer>> players_;
  TokenGenerator token_generator_;
};

}  // namespace infrastructure
