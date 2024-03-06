#include "memory_mapped_players.h"

namespace infrastructure {

std::string TokenGenerator::GenerateNewToken() {
  std::stringstream ss;

  while (ss.str().size() != 32) {
    ss.clear();
    ss << std::setfill('0') << std::setw(16) << std::hex << generator1_();
    ss << std::setfill('0') << std::setw(16) << std::hex << generator2_();
  }

  return ss.str();
}

std::shared_ptr<app::IPlayer> MemoryMappedPlayers::AddPlayer(game::Game &game) {
  auto token = token_generator_.GenerateNewToken();
  auto player_ptr = players_.Emplace(token, token, app::GameSession(game, token));

  while (!player_ptr.inserted) {
    token = token_generator_.GenerateNewToken();
    auto player_ptr = players_.Emplace(token, token, app::GameSession(game, token));
  }

  return player_ptr.value;
}

std::shared_ptr<app::IPlayer> MemoryMappedPlayers::GetPlayerByToken(const app::Token& token) {
  return players_.Get(token);
}

}  // namespace infrastructure
