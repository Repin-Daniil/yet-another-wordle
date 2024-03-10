#include "application.h"

namespace {

using namespace userver;
using namespace std::literals;

}  // namespace

namespace app {

Application::Application(const components::ComponentConfig& config, const components::ComponentContext& context)
    : LoggableComponentBase(config, context),
      game_eng_(context.FindComponent<infrastructure::DictionaryComponent>().GetDictionary()),
      pg_cluster_(context.FindComponent<userver::components::Postgres>("postgres-db-1").GetCluster()),
      players_(context.FindComponent<infrastructure::PlayersComponent>().GetPlayers()),
      game_starter_(game_eng_, players_),
      word_checker_(game_eng_, players_) {
}

IPlayers& Application::GetPlayers() {
  return players_;
}

game::Game& Application::GetGame() {
  return game_eng_;
}

Token Application::StartGame(const std::string &name) {
  LOG_INFO() << "Start Game for player with name " << name;
  return game_starter_.Start(name);
}

CheckWordResult Application::CheckWord(const Token& token, std::string_view word) {
  LOG_INFO() << "Check Word " << word << " for player with token " << token;
  return word_checker_.Check(token, word);
}

void AppendApplication(userver::components::ComponentList& component_list) {
  component_list.Append<Application>();
  component_list.Append<userver::components::Postgres>("postgres-db-1");
  component_list.Append<userver::clients::dns::Component>();
}

}  // namespace app
