#pragma once

#include <unordered_set>
#include <random>
#include <utility>

#include "domain/dictionary.h"

namespace infrastructure {

class NaiveDictionary : public game::IDictionary {
 public:
  explicit NaiveDictionary(std::unordered_set<std::string> words) : words_(std::move(words)) {
  }

  std::string_view GetRandomWord() override;
  bool IsWordExist(std::string_view word) override;

 private:
  std::unordered_set<std::string_view> words_;
  std::random_device rd;
};

}  // namespace infrastructure
