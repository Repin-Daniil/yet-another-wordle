#include "naive_dictionary.h"

namespace infrastructure {

std::string_view NaiveDictionary::GetRandomWord() {
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(0, words_.size() - 1);
  auto it = std::next(words_.begin(), dist(gen));

  return *it;
}

bool NaiveDictionary::IsWordExist(std::string_view word) {
  return words_.contains(word);
}
}  // namespace infrastructure