#include <userver/utest/utest.hpp>

#include <unordered_set>
#include <iostream>

#include "app/Players/Naive/player.h"

namespace {

using game::CORRECT;
using game::WRONG_PLACE;
using game::NONE;

}  // namespace

UTEST(Player, Getters) {
  // Arrange
  std::string token("token");
  std::string secret_word("apple");
  app::Player player(token, secret_word);

  // Act

  //Assert
  ASSERT_EQ(player.GetToken(), token);
  ASSERT_EQ(player.GetSecretWord(), secret_word);
  ASSERT_EQ(player.GetAttemptsAmount(), 0);
  ASSERT_EQ(player.GetAttempts().size(), 0);
}

UTEST(Player, OneAttempt) {
  // Arrange
  std::string token("token");
  std::string secret_word("apple");
  app::Player player(token, secret_word);
  game::WordCheckout attempt{game::WRONG_WORD, {NONE, NONE, NONE, NONE, NONE}};

  // Act
  player.AddAttempt(attempt);

  // Assert
  ASSERT_EQ(player.GetToken(), token);
  ASSERT_EQ(player.GetSecretWord(), secret_word);
  ASSERT_EQ(player.GetAttemptsAmount(), 1);
  ASSERT_EQ(player.GetAttempts()[0].status, attempt.status);
  ASSERT_EQ(player.GetAttempts()[0].letters, attempt.letters);
}

UTEST(Player, TwoAttempts) {
  // Arrange
  std::string token("token");
  std::string secret_word("apple");
  app::Player player(token, secret_word);
  game::WordCheckout attempt_1{game::WRONG_WORD, {NONE, NONE, NONE, NONE, NONE}};
  game::WordCheckout attempt_2{game::WRONG_WORD, {NONE, WRONG_PLACE, NONE, WRONG_PLACE, NONE}};

  // Act
  player.AddAttempt(attempt_1);
  player.AddAttempt(attempt_2);

  // Assert
  ASSERT_EQ(player.GetToken(), token);
  ASSERT_EQ(player.GetSecretWord(), secret_word);
  ASSERT_EQ(player.GetAttemptsAmount(), 2);
  ASSERT_EQ(player.GetAttempts()[1].status, attempt_2.status);
  ASSERT_EQ(player.GetAttempts()[1].letters, attempt_2.letters);
}

UTEST(Player, ChangeWord) {
  // Arrange
  std::string token("token");
  std::string secret_word("apple");
  std::string next_secret_word("conan");
  app::Player player(token, secret_word);
  game::WordCheckout attempt_1{game::WRONG_WORD, {NONE, NONE, NONE, NONE, NONE}};
  game::WordCheckout attempt_2{game::RIGHT_WORD, {CORRECT, CORRECT, CORRECT, CORRECT, CORRECT}};

  // Act
  player.AddAttempt(attempt_1);
  player.AddAttempt(attempt_2);
  player.ChangeSecretWord(next_secret_word);

  // Assert
  ASSERT_EQ(player.GetToken(), token);
  ASSERT_EQ(player.GetSecretWord(), next_secret_word);
  ASSERT_EQ(player.GetAttemptsAmount(), 0);
  ASSERT_EQ(player.GetAttempts().size(), 0);
}

UTEST(Player, ExceptionAfterExtraAttempt) {
  // Arrange
  std::string token("token");
  std::string secret_word("apple");
  app::Player player(token, secret_word);
  game::WordCheckout attempt{game::WRONG_WORD, {NONE, NONE, NONE, NONE, NONE}};

  // Act
  player.AddAttempt(attempt);
  player.AddAttempt(attempt);
  player.AddAttempt(attempt);
  player.AddAttempt(attempt);
  player.AddAttempt(attempt);
  player.AddAttempt(attempt);

  // Assert
  ASSERT_EQ(player.GetToken(), token);
  ASSERT_EQ(player.GetSecretWord(), secret_word);
  ASSERT_EQ(player.GetAttemptsAmount(), 6);

  ASSERT_THROW(player.AddAttempt(attempt), std::runtime_error);

  ASSERT_EQ(player.GetToken(), token);
  ASSERT_EQ(player.GetSecretWord(), secret_word);
  ASSERT_EQ(player.GetAttemptsAmount(), 6);
}

UTEST(TokenGenerator, TokenHasCorrectLength) {
  // Arrange
  app::TokenGenerator token_generator;

  // Act
  auto token = token_generator.GenerateNewToken();

  // Assert
  ASSERT_EQ(token.size(), 32);
}

UTEST(TokenGenerator, TokenIsRandom) {
  app::TokenGenerator token_generator;
  std::unordered_set<std::string> generated_tokens;

  for (size_t i = 0; i < 10000; ++i) {
    auto yet_another_token = token_generator.GenerateNewToken();

    ASSERT_EQ(yet_another_token.size(), 32);
    ASSERT_FALSE(generated_tokens.contains(yet_another_token));

    generated_tokens.insert(yet_another_token);
  }
}

UTEST(Players, WithoutPlayers) {
  // Arrange
  app::Players players;

  // Act

  // Assert
  ASSERT_EQ(players.GetPlayersAmount(), 0);
  ASSERT_FALSE(players.IsTokenExist("token"));
}

UTEST(Players, OnePlayer) {
  // Arrange
  app::Players players;
  std::string secret_word("apple");

  //Act
  auto player = players.AddPlayer(secret_word);

  // Assert
  ASSERT_EQ(players.GetPlayersAmount(), 1);
  ASSERT_EQ(player->GetSecretWord(), secret_word);
  ASSERT_FALSE(players.IsTokenExist("token"));
  ASSERT_TRUE(players.IsTokenExist(player->GetToken()));

}

UTEST(Players, ALotOfPlayers) {
  app::Players players;
  std::string secret_word("apple");
  std::vector<std::shared_ptr<app::Player>> players_vector;

  for (size_t i = 0; i < 10000; ++i) {
    players_vector.emplace_back(players.AddPlayer(secret_word));
    ASSERT_EQ(players.GetPlayersAmount(), i + 1);
    ASSERT_TRUE(players.IsTokenExist(players_vector[i]->GetToken()));
  }

  ASSERT_EQ(players.GetPlayersAmount(), players_vector.size());
}