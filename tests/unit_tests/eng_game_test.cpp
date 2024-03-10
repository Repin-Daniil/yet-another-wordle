#include <userver/utest/utest.hpp>

#include "infrastructure/dictionary/in-memory/naive_dictionary.h"
#include "model/game.h"

namespace {

using game::LetterStatus;
using game::WordStatus;

}  // namespace

UTEST(IsRealWord, RealEngWords) {
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"words", "apple", "horse"}));
  game::Game game(*dict);

  ASSERT_TRUE(game.IsRealWord("words"));
  ASSERT_TRUE(game.IsRealWord("horse"));
}

UTEST(IsRealWord, UnrealEngWords) {
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"words", "apple", "horse"}));
  game::Game game(*dict);

  ASSERT_FALSE(game.IsRealWord("cbrfj"));
  ASSERT_FALSE(game.IsRealWord("abfkj"));
}

UTEST(IsRealWord, WrongSizeEngWords) {
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"words", "apple", "horse"}));
  game::Game game(*dict);

  ASSERT_FALSE(game.IsRealWord(""));
  ASSERT_FALSE(game.IsRealWord("a"));
  ASSERT_FALSE(game.IsRealWord("umbrella"));
}

UTEST(CheckWord, EngCorrect) {
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"words", "apple", "horse"}));
  game::Game game(*dict);

  auto result = game.CheckWord("words", "words");
  auto answer = std::array<game::LetterStatus, 5>{LetterStatus::CORRECT, LetterStatus::CORRECT, LetterStatus::CORRECT,
                                                  LetterStatus::CORRECT, LetterStatus::CORRECT};

  ASSERT_EQ(game::WordStatus::RIGHT_WORD, result.status);
  ASSERT_EQ(answer, result.letters);
}

UTEST(CheckWord, AlmostEngCorrect) {
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"words", "apple", "horse"}));
  game::Game game(*dict);

  auto result = game.CheckWord("horse", "words");
  auto answer = std::array<game::LetterStatus, 5>{LetterStatus::NONE, LetterStatus::CORRECT, LetterStatus::CORRECT,
                                                  LetterStatus::WRONG_PLACE, LetterStatus::NONE};

  ASSERT_EQ(game::WordStatus::WRONG_WORD, result.status);
  ASSERT_EQ(answer, result.letters);
}

UTEST(CheckWord, WrongEngPlace) {
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"words", "apple", "horse", "clang"}));
  game::Game game(*dict);

  auto result = game.CheckWord("apple", "clang");
  auto answer = std::array<game::LetterStatus, 5>{LetterStatus::WRONG_PLACE, LetterStatus::NONE, LetterStatus::NONE,
                                                  LetterStatus::WRONG_PLACE, LetterStatus::NONE};

  ASSERT_EQ(game::WordStatus::WRONG_WORD, result.status);
  ASSERT_EQ(answer, result.letters);
}

UTEST(CheckWord, TotallyEngIncorrect) {
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"words", "apple", "horse", "clang"}));
  game::Game game(*dict);

  auto result = game.CheckWord("apple", "words");
  auto answer = std::array<game::LetterStatus, 5>{LetterStatus::NONE, LetterStatus::NONE, LetterStatus::NONE,
                                                  LetterStatus::NONE, LetterStatus::NONE};

  ASSERT_EQ(game::WordStatus::WRONG_WORD, result.status);
  ASSERT_EQ(answer, result.letters);
}

UTEST(CheckWord, UnrealEngWord) {
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"words", "apple", "horse", "clang"}));
  game::Game game(*dict);

  auto result = game.CheckWord("cbjkf", "words");
  auto answer = std::array<game::LetterStatus, 5>{LetterStatus::NONE, LetterStatus::NONE, LetterStatus::NONE,
                                                  LetterStatus::NONE, LetterStatus::NONE};

  ASSERT_EQ(game::WordStatus::UNREAL_WORD, result.status);
  ASSERT_EQ(answer, result.letters);
}

UTEST(CheckWord, OnlyOneEngLetterShouldBeCorrect) {
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"words", "apple", "horse", "creep"}));
  game::Game game(*dict);

  auto result = game.CheckWord("apple", "creep");
  auto answer = std::array<game::LetterStatus, 5>{LetterStatus::NONE, LetterStatus::WRONG_PLACE, LetterStatus::NONE,
                                                  LetterStatus::NONE, LetterStatus::WRONG_PLACE};

  ASSERT_EQ(game::WordStatus::WRONG_WORD, result.status);
  ASSERT_EQ(answer, result.letters);
}

UTEST(CheckWord, WrongSizeSecretEngWord) {
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"words", "apple", "horse", "clang"}));
  game::Game game(*dict);

  ASSERT_THROW(game.CheckWord("apple", "terminal"), std::runtime_error);
}


UTEST(GetRandomWord, RandomEngWordsIsReal) {
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"words", "apple", "horse"}));
  game::Game game(*dict);

  ASSERT_TRUE(game.IsRealWord(game.GetRandomWord()));
  ASSERT_TRUE(game.IsRealWord(game.GetRandomWord()));
  ASSERT_TRUE(game.IsRealWord(game.GetRandomWord()));
  ASSERT_TRUE(game.IsRealWord(game.GetRandomWord()));
}
