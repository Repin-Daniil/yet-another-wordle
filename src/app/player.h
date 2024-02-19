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

#include "domain/game.h"

namespace app {

/**
 * @brief Класс пользователя
 * @todo Создать игровую сессию, чтобы там был набор своих слов. И если кто-то их все отгадал, то уж тогда RandomWord()
 */
class Player {
 public:
  Player(std::string token, std::string_view secret_word) : token_(std::move(token)), secret_word_(secret_word) {
  }

  void AddAttempt(game::WordCheckout attempt);
  void ChangeSecretWord(std::string_view new_secret_word) noexcept;

  // Getters
  int GetAttemptsAmount() const noexcept;
  int GetRemainingAttemptsAmount() const noexcept;
  std::vector<game::WordCheckout> GetAttempts() const noexcept;
  std::string_view GetSecretWord() const noexcept;
  std::string GetToken() const noexcept;

 private:
  void ResetAttempts();

 private:
  std::string token_;
  std::vector<game::WordCheckout> attempts_;
  std::string_view secret_word_;
};

/**
 * @brief Генератор токенов для пользователей
 * @todo Заменить на boost.uuid
 */
struct TokenGenerator {
 public:
  std::string GenerateNewToken();

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

class Players {
 public:
  std::shared_ptr<Player> AddPlayer(std::string_view secret_word);

  // Getters
  std::shared_ptr<Player> GetPlayerByToken(const std::string &token) const;
  size_t GetPlayersAmount() const;

  // Predicates
  bool IsTokenExist(const std::string &token) const;

 private:
  std::unordered_map<std::string, std::shared_ptr<Player>> players_;
  TokenGenerator token_generator_;
};

}  // namespace app
