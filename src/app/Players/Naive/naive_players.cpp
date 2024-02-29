#include "naive_players.h"

namespace app {

std::string TokenGenerator::GenerateNewToken() {
  std::stringstream ss;

  while (ss.str().size() != 32) {
    ss.clear();
    ss << std::setfill('0') << std::setw(16) << std::hex << generator1_();
    ss << std::setfill('0') << std::setw(16) << std::hex << generator2_();
  }

  return ss.str();
}

std::shared_ptr<Player> NaivePlayers::AddPlayer(std::string_view secret_word) {
  auto token = token_generator_.GenerateNewToken();
  auto player_ptr = std::make_shared<Player>(token, secret_word);
  players_.insert({token, player_ptr});

  return player_ptr;
}

bool NaivePlayers::IsTokenExist(const std::string& token) const {
  return players_.contains(token);
}

size_t NaivePlayers::GetPlayersAmount() const {
  return players_.size();
}

std::shared_ptr<Player> NaivePlayers::GetPlayerByToken(const std::string& token) const {
  if (!IsTokenExist(token)) {
    return nullptr;  // TODO или throw?
  }

  return players_.at(token);
}

}  // namespace app