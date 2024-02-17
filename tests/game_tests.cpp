#include <gtest/gtest.h>
#include "infrasrtucture/naive_dictionary.h"
#include "domain/game.h"

namespace {

using game::CORRECT;
using game::WRONG_PLACE;
using game::NONE;

}  // namespace


TEST(IsRealWord, RealWords) {
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"words", "apple", "horse"}));
  game::Game game(std::move(dict));

  ASSERT_TRUE(game.IsRealWord("words"));
  ASSERT_TRUE(game.IsRealWord("horse"));
}

TEST(IsRealWord, UnrealWords) {
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"words", "apple", "horse"}));
  game::Game game(std::move(dict));

  ASSERT_FALSE(game.IsRealWord("cbrfj"));
  ASSERT_FALSE(game.IsRealWord("abfkj"));
}

TEST(IsRealWord, WrongSizeWords) {
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"words", "apple", "horse"}));
  game::Game game(std::move(dict));

  ASSERT_FALSE(game.IsRealWord(""));
  ASSERT_FALSE(game.IsRealWord("a"));
  ASSERT_FALSE(game.IsRealWord("umbrella"));
}

TEST(CheckWord, Correct) {
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"words", "apple", "horse"}));
  game::Game game(std::move(dict));

  auto result = game.CheckWord("words", "words");
  auto answer = std::array<game::LetterStatus, 5>{CORRECT, CORRECT, CORRECT, CORRECT, CORRECT};

  ASSERT_EQ(game::WordStatus::SUCCESS, result.status);
  ASSERT_EQ(answer, result.letters);
}

TEST(CheckWord, AlmostCorrect) {
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"words", "apple", "horse"}));
  game::Game game(std::move(dict));

  auto result = game.CheckWord("horse", "words");
  auto answer = std::array<game::LetterStatus, 5>{NONE, CORRECT, CORRECT, WRONG_PLACE, NONE};

  ASSERT_EQ(game::WordStatus::WRONG, result.status);
  ASSERT_EQ(answer, result.letters);
}

TEST(CheckWord, WrongPlace) {
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"words", "apple", "horse", "clang"}));
  game::Game game(std::move(dict));

  auto result = game.CheckWord("apple", "clang");
  auto answer = std::array<game::LetterStatus, 5>{WRONG_PLACE, NONE, NONE, WRONG_PLACE, NONE};

  ASSERT_EQ(game::WordStatus::WRONG, result.status);
  ASSERT_EQ(answer, result.letters);
}

TEST(CheckWord, TotallyIncorrect) {
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"words", "apple", "horse", "clang"}));
  game::Game game(std::move(dict));

  auto result = game.CheckWord("apple", "words");
  auto answer = std::array<game::LetterStatus, 5>{NONE, NONE, NONE, NONE, NONE};

  ASSERT_EQ(game::WordStatus::WRONG, result.status);
  ASSERT_EQ(answer, result.letters);
}

TEST(CheckWord, UnrealWord) {
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"words", "apple", "horse", "clang"}));
  game::Game game(std::move(dict));

  auto result = game.CheckWord("cbjkf", "words");
  auto answer = std::array<game::LetterStatus, 5>{NONE, NONE, NONE, NONE, NONE};

  ASSERT_EQ(game::WordStatus::UNREAL_WORD, result.status);
  ASSERT_EQ(answer, result.letters);
}

TEST(CheckWord, WrongSizeSecretWord) {
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"words", "apple", "horse", "clang"}));
  game::Game game(std::move(dict));

  ASSERT_THROW(game.CheckWord("apple", "terminal"), std::runtime_error);
}

TEST(GetRandomWord, RandomWordsIsReal) {
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"words", "apple", "horse"}));
  game::Game game(std::move(dict));

  ASSERT_TRUE(game.IsRealWord(game.GetRandomWord()));
  ASSERT_TRUE(game.IsRealWord(game.GetRandomWord()));
  ASSERT_TRUE(game.IsRealWord(game.GetRandomWord()));
  ASSERT_TRUE(game.IsRealWord(game.GetRandomWord()));
}
