#include <userver/utest/utest.hpp>

#include "infrastructure/dictionary/in-memory/naive_dictionary.h"
#include "model/game.h"

namespace {

using game::LetterStatus;
using game::WordStatus;

}  // namespace

UTEST(IsRealWord, RealRuWords) {
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"ружье", "дамба", "багаж"}));
  game::Game game(*dict);

  ASSERT_TRUE(game.IsRealWord("ружье"));
  ASSERT_TRUE(game.IsRealWord("багаж"));
}

UTEST(IsRealWord, UnrealRuWords) {
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"ружье", "дамба", "багаж"}));
  game::Game game(*dict);

  ASSERT_FALSE(game.IsRealWord("авыар"));
  ASSERT_FALSE(game.IsRealWord("зщшуа"));
}

UTEST(IsRealWord, WrongSizeRuWords) {
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"ружье", "дамба", "багаж"}));
  game::Game game(*dict);

  ASSERT_FALSE(game.IsRealWord(""));
  ASSERT_FALSE(game.IsRealWord("а"));
  ASSERT_FALSE(game.IsRealWord("подгонка"));
}


UTEST(CheckWord, RusCorrect) {
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"ружье", "дамба", "багаж"}));
  game::Game game(*dict);

  auto result = game.CheckWord("ружье", "багаж");
  auto answer = std::array<game::LetterStatus, 5>{LetterStatus::CORRECT, LetterStatus::CORRECT, LetterStatus::CORRECT,
                                                  LetterStatus::CORRECT, LetterStatus::CORRECT};

  ASSERT_EQ(game::WordStatus::RIGHT_WORD, result.status);
  ASSERT_EQ(answer, result.letters);
}

UTEST(CheckWord, AlmostRusCorrect) {
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"ружье", "дамба", "багаж"}));
  game::Game game(*dict);

  auto result = game.CheckWord("багаж", "дамба");
  auto answer = std::array<game::LetterStatus, 5>{LetterStatus::WRONG_PLACE, LetterStatus::CORRECT, LetterStatus::NONE,
                                                  LetterStatus::NONE, LetterStatus::NONE};

  ASSERT_EQ(game::WordStatus::WRONG_WORD, result.status);
  ASSERT_EQ(answer, result.letters);
}


UTEST(CheckWord, WrongRusPlace) {
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"ружье", "дамба", "багаж"}));
  game::Game game(*dict);

  auto result = game.CheckWord("ружье", "багаж");
  auto answer = std::array<game::LetterStatus, 5>{LetterStatus::NONE, LetterStatus::NONE, LetterStatus::WRONG_PLACE,
                                                  LetterStatus::NONE, LetterStatus::NONE};

  ASSERT_EQ(game::WordStatus::WRONG_WORD, result.status);
  ASSERT_EQ(answer, result.letters);
}

UTEST(CheckWord, TotallyRusIncorrect) {
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"ружье", "дамба", "багаж", "бозон"}));
  game::Game game(*dict);

  auto result = game.CheckWord("ружье", "бозон");
  auto answer = std::array<game::LetterStatus, 5>{LetterStatus::NONE, LetterStatus::NONE, LetterStatus::NONE,
                                                  LetterStatus::NONE, LetterStatus::NONE};

  ASSERT_EQ(game::WordStatus::WRONG_WORD, result.status);
  ASSERT_EQ(answer, result.letters);
}

UTEST(CheckWord, UnrealRusWord) {
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"ружье", "дамба", "багаж", "бозон"}));
  game::Game game(*dict);

  auto result = game.CheckWord("несущ", "бозон");
  auto answer = std::array<game::LetterStatus, 5>{LetterStatus::NONE, LetterStatus::NONE, LetterStatus::NONE,
                                                  LetterStatus::NONE, LetterStatus::NONE};

  ASSERT_EQ(game::WordStatus::UNREAL_WORD, result.status);
  ASSERT_EQ(answer, result.letters);
}

UTEST(CheckWord, OnlyOneRusLetterShouldBeCorrect) {
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"ружье", "дамба", "багаж", "автор"}));
  game::Game game(*dict);

  auto result = game.CheckWord("дамба", "автор");
  auto answer = std::array<game::LetterStatus, 5>{LetterStatus::NONE, LetterStatus::WRONG_PLACE, LetterStatus::NONE,
                                                  LetterStatus::NONE, LetterStatus::NONE};

  ASSERT_EQ(game::WordStatus::WRONG_WORD, result.status);
  ASSERT_EQ(answer, result.letters);
}

UTEST(CheckWord, WrongSizeSecretRusWord) {
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"ружье", "дамба", "багаж", "автор"}));
  game::Game game(*dict);

  ASSERT_THROW(game.CheckWord("ружье", "длинное"), std::runtime_error);
}


UTEST(GetRandomWord, RandomRusWordsIsReal) {
  std::unique_ptr<game::IDictionary> dict(new infrastructure::NaiveDictionary({"ружье", "дамба", "багаж", "автор"}));
  game::Game game(*dict);

  ASSERT_TRUE(game.IsRealWord(game.GetRandomWord()));
  ASSERT_TRUE(game.IsRealWord(game.GetRandomWord()));
  ASSERT_TRUE(game.IsRealWord(game.GetRandomWord()));
  ASSERT_TRUE(game.IsRealWord(game.GetRandomWord()));
}
