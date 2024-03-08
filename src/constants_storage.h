#pragma once

#include <string_view>

namespace constants {

using namespace std::literals;

struct GameSettings {
  GameSettings() = delete;

  static constexpr int kWordLength = 5;
  static constexpr int kMaxAttemptsAmount = 6;
};

struct ConfigArgs {
  ConfigArgs() = delete;

  static constexpr std::string_view store_in_memory = "in-memory-storage"sv;
  static constexpr std::string_view path_to_words = "path-to-words"sv;
  static constexpr std::string_view fs_task_processor = "fs-task-processor"sv;
};
}  // namespace constants
