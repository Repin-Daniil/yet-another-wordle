#include <userver/utest/utest.hpp>

#include "infrastructure/naive_dictionary.h"
#include "domain/game.h"

namespace {

using game::CORRECT;
using game::WRONG_PLACE;
using game::NONE;

}  // namespace


UTEST(IsRealWord, RealWords) {
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"words", "apple", "horse"}));
  game::Game game(std::move(dict));

  ASSERT_TRUE(game.IsRealWord("words"));
  ASSERT_TRUE(game.IsRealWord("horse"));
}

UTEST(IsRealWord, UnrealWords) {
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"words", "apple", "horse"}));
  game::Game game(std::move(dict));

  ASSERT_FALSE(game.IsRealWord("cbrfj"));
  ASSERT_FALSE(game.IsRealWord("abfkj"));
}

UTEST(IsRealWord, WrongSizeWords) {
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"words", "apple", "horse"}));
  game::Game game(std::move(dict));

  ASSERT_FALSE(game.IsRealWord(""));
  ASSERT_FALSE(game.IsRealWord("a"));
  ASSERT_FALSE(game.IsRealWord("umbrella"));
}

UTEST(CheckWord, Correct) {
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"words", "apple", "horse"}));
  game::Game game(std::move(dict));

  auto result = game.CheckWord("words", "words");
  auto answer = std::array<game::LetterStatus, 5>{CORRECT, CORRECT, CORRECT, CORRECT, CORRECT};

  ASSERT_EQ(game::WordStatus::RIGHT_WORD, result.status);
  ASSERT_EQ(answer, result.letters);
}

UTEST(CheckWord, AlmostCorrect) {
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"words", "apple", "horse"}));
  game::Game game(std::move(dict));

  auto result = game.CheckWord("horse", "words");
  auto answer = std::array<game::LetterStatus, 5>{NONE, CORRECT, CORRECT, WRONG_PLACE, NONE};

  ASSERT_EQ(game::WordStatus::WRONG_WORD, result.status);
  ASSERT_EQ(answer, result.letters);
}

UTEST(CheckWord, WrongPlace) {
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"words", "apple", "horse", "clang"}));
  game::Game game(std::move(dict));

  auto result = game.CheckWord("apple", "clang");
  auto answer = std::array<game::LetterStatus, 5>{WRONG_PLACE, NONE, NONE, WRONG_PLACE, NONE};

  ASSERT_EQ(game::WordStatus::WRONG_WORD, result.status);
  ASSERT_EQ(answer, result.letters);
}

UTEST(CheckWord, TotallyIncorrect) {
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"words", "apple", "horse", "clang"}));
  game::Game game(std::move(dict));

  auto result = game.CheckWord("apple", "words");
  auto answer = std::array<game::LetterStatus, 5>{NONE, NONE, NONE, NONE, NONE};

  ASSERT_EQ(game::WordStatus::WRONG_WORD, result.status);
  ASSERT_EQ(answer, result.letters);
}

UTEST(CheckWord, UnrealWord) {
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"words", "apple", "horse", "clang"}));
  game::Game game(std::move(dict));

  auto result = game.CheckWord("cbjkf", "words");
  auto answer = std::array<game::LetterStatus, 5>{NONE, NONE, NONE, NONE, NONE};

  ASSERT_EQ(game::WordStatus::UNREAL_WORD, result.status);
  ASSERT_EQ(answer, result.letters);
}

UTEST(CheckWord, WrongSizeSecretWord) {
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"words", "apple", "horse", "clang"}));
  game::Game game(std::move(dict));

  ASSERT_THROW(game.CheckWord("apple", "terminal"), std::runtime_error);
}

UTEST(GetRandomWord, RandomWordsIsReal) {
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"words", "apple", "horse"}));
  game::Game game(std::move(dict));

  ASSERT_TRUE(game.IsRealWord(game.GetRandomWord()));
  ASSERT_TRUE(game.IsRealWord(game.GetRandomWord()));
  ASSERT_TRUE(game.IsRealWord(game.GetRandomWord()));
  ASSERT_TRUE(game.IsRealWord(game.GetRandomWord()));
}
