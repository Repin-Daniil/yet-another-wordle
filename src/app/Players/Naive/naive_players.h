#pragma once

#include <string_view>
#include <random>
#include <iomanip>
#include <sstream>
#include <vector>
#include <memory>
#include <string>
#include <utility>
#include <unordered_map>

#include "app/Players/players.h"

namespace app {

/**
 * @brief Генератор токенов для пользователей
 * @todo Заменить на boost.uuid
 */
struct TokenGenerator {
 public:
  Token GenerateNewToken();

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

class NaivePlayers : public IPlayers {
 public:
  std::shared_ptr<Player> AddPlayer(std::string_view secret_word) override;

  std::shared_ptr<Player> GetPlayerByToken(const Token &token) const override;
  size_t GetPlayersAmount() const override;

  bool IsTokenExist(const Token &token) const override;

 private:
  std::unordered_map<std::string, std::shared_ptr<Player>> players_;
  TokenGenerator token_generator_;
};

}  // namespace app
