#include "application.h"

namespace {

using namespace userver;
using namespace std::literals;

}  // namespace

namespace app {

Application::Application(const components::ComponentConfig& config, const components::ComponentContext& context)
    : LoggableComponentBase(config, context),
      game_(context.FindComponent<infrastructure::DictionaryComponent>().GetDictionary()),
      pg_cluster_(context.FindComponent<userver::components::Postgres>("postgres-db-1").GetCluster()),
      players_(context.FindComponent<app::PlayersComponent>().GetPlayers()),
      game_starter_(game_, players_),
      word_checker_(game_, players_) {
}

IPlayers& Application::GetPlayers() {
  return players_;
}

game::Game& Application::GetGame() {
  return game_;
}

Token Application::StartGame() {
  return game_starter_.Start();  // Тут гонка в векторе с игроками будет. Потом почини
}

CheckWordResult Application::CheckWord(const Token& token, std::string_view word) {
  return word_checker_.Check(token, word);
}

void AppendApplication(userver::components::ComponentList& component_list) {
  component_list.Append<Application>();
  component_list.Append<userver::components::Postgres>("postgres-db-1");
  component_list.Append<userver::clients::dns::Component>();
}

}  // namespace app
