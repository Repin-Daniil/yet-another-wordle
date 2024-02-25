#include "player.h"

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

std::string Player::GetToken() const noexcept { return token_; }

std::string_view Player::GetSecretWord() const noexcept { return secret_word_; }

int Player::GetAttemptsAmount() const noexcept {
  return static_cast<int>(attempts_.size());
}

std::vector<game::WordCheckout> Player::GetAttempts() const noexcept {
  return attempts_;
}

void Player::ResetAttempts() { attempts_.clear(); }

void Player::ChangeSecretWord(std::string_view new_secret_word) noexcept {
  ResetAttempts();
  secret_word_ = new_secret_word;
}

void Player::AddAttempt(game::WordCheckout attempt) {
  if (GetAttemptsAmount() >= constants::GameSettings::MAX_ATTEMPTS_AMOUNT) {
    throw std::runtime_error("Game Over! No attempts!");
  }

  attempts_.push_back(attempt);
}

int Player::GetRemainingAttemptsAmount() const noexcept {
  return constants::GameSettings::MAX_ATTEMPTS_AMOUNT - GetAttemptsAmount();
}

std::shared_ptr<Player> Players::AddPlayer(std::string_view secret_word) {
  auto token = token_generator_.GenerateNewToken();
  auto player_ptr = std::make_shared<Player>(token, secret_word);
  players_.insert({token, player_ptr});

  return player_ptr;
}

bool Players::IsTokenExist(const std::string& token) const {
  return players_.contains(token);
}

size_t Players::GetPlayersAmount() const { return players_.size(); }

std::shared_ptr<Player> Players::GetPlayerByToken(
    const std::string& token) const {
  if (!IsTokenExist(token)) {
    return nullptr;  // TODO или throw?
  }

  return players_.at(token);
}

Players::Players(const components::ComponentConfig& config,
                 const components::ComponentContext& context)
    : LoggableComponentBase(config, context),
      pg_cluster_(
          context.FindComponent<userver::components::Postgres>("postgres-db-1")
              .GetCluster()),
      game_(context.FindComponent<game::Game>()) {}

void AppendPlayers(userver::components::ComponentList& component_list) {
  component_list.Append<Players>();
}

}  // namespace app
