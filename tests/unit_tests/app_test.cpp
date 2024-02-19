#include <userver/utest/utest.hpp>

#include "app/application.h"
#include "infrastructure/naive_dictionary.h"

namespace {

using game::RIGHT_WORD;
using game::WRONG_WORD;
using game::UNREAL_WORD;

using game::CORRECT;
using game::WRONG_PLACE;
using game::NONE;

}  // namespace

UTEST(Application, StartGame) {
  // Arrange
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"words", "apple", "horse"}));
  app::Application app(game::Game(std::move(dict)));

  // Act
  auto token = app.StartGame();
  const auto &game = app.GetGame();
  const auto &players = app.GetPlayers();

  // Assert
  ASSERT_EQ(players.GetPlayersAmount(), 1);
  ASSERT_TRUE(players.IsTokenExist(token));
  ASSERT_TRUE(game.IsRealWord(players.GetPlayerByToken(token)->GetSecretWord()));
}

UTEST(Application, CheckWordWrongToken) {
  // Arrange
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"words", "apple", "horse"}));
  app::Application app(game::Game(std::move(dict)));

  // Act
  auto token = app.StartGame();
  std::string wrong_token("wrong token");
  auto result = app.CheckWord(wrong_token, "words");

  // Assert
  ASSERT_EQ(result, std::nullopt);
}

UTEST(Application, CheckWordUnrealWord) {
  // Arrange
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"words", "apple", "horse"}));
  app::Application app(game::Game(std::move(dict)));

  // Act
  auto token = app.StartGame();
  const auto &players = app.GetPlayers();

  auto result = app.CheckWord(token, "conan");
  // Assert
  auto expected = std::array<game::LetterStatus, 5>{NONE, NONE, NONE, NONE, NONE};
  ASSERT_NE(result, std::nullopt);
  ASSERT_EQ(result->status, UNREAL_WORD);
  ASSERT_EQ(result->letters, expected);
  ASSERT_EQ(players.GetPlayerByToken(token)->GetAttemptsAmount(), 0);
}

UTEST(Application, CheckWordWrongWord) {
  // Arrange
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"words", "apple", "horse"}));
  app::Application app(game::Game(std::move(dict)));

  // Act
  auto token = app.StartGame();
  const auto &players = app.GetPlayers();
  const auto &game = app.GetGame();

  auto wrong_word = game.GetRandomWord();

  while (wrong_word == players.GetPlayerByToken(token)->GetSecretWord()) {
    wrong_word = game.GetRandomWord();
  }

  auto result = app.CheckWord(token, wrong_word);

  // Assert
  ASSERT_NE(result, std::nullopt);
  ASSERT_EQ(result->status, WRONG_WORD);
}

UTEST(Application, CheckWordCorrect) {
  // Arrange
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"words", "apple", "horse"}));
  app::Application app(game::Game(std::move(dict)));

  // Act
  auto token = app.StartGame();
  const auto &players = app.GetPlayers();

  auto result = app.CheckWord(token, players.GetPlayerByToken(token)->GetSecretWord());

  // Assert
  auto expected =
      std::array<game::LetterStatus, 5>{CORRECT, CORRECT, CORRECT, CORRECT, CORRECT};
  ASSERT_NE(result, std::nullopt);
  ASSERT_EQ(result->status, RIGHT_WORD);
  ASSERT_EQ(result->letters, expected);
}

UTEST(Application, NewWordAfterCorrectAnswer) {
  // Arrange
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"words", "apple", "horse"}));
  app::Application app(game::Game(std::move(dict)));

  // Act
  auto token = app.StartGame();
  const auto &players = app.GetPlayers();

  auto secret_word_1 = players.GetPlayerByToken(token)->GetSecretWord();
  auto result = app.CheckWord(token, secret_word_1);
  auto secret_word_2 = players.GetPlayerByToken(token)->GetSecretWord();

  // Assert
  ASSERT_NE(result, std::nullopt);
  ASSERT_EQ(result->status, RIGHT_WORD);
  ASSERT_NE(secret_word_1, secret_word_2);
}

UTEST(Application, NewWordAfterAllAttempts) {
  // Arrange
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"words", "apple", "horse"}));
  app::Application app(game::Game(std::move(dict)));

  // Act
  auto token = app.StartGame();
  const auto &players = app.GetPlayers();
  const auto &game = app.GetGame();

  auto wrong_word = game.GetRandomWord();

  while (wrong_word == players.GetPlayerByToken(token)->GetSecretWord()) {
    wrong_word = game.GetRandomWord();
  }

  auto secret_word_1 = players.GetPlayerByToken(token)->GetSecretWord();

  for (int i = 0; i < constants::GameSettings::MAX_ATTEMPTS_AMOUNT; ++i) {
    app.CheckWord(token, wrong_word);
  }

  auto secret_word_2 = players.GetPlayerByToken(token)->GetSecretWord();

  // Assert
  ASSERT_NE(secret_word_1, secret_word_2);
}
