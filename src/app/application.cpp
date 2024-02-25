#include "application.h"

namespace {

using namespace userver;
using namespace std::literals;

}  // namespace

namespace app {

Application::Application(const components::ComponentConfig& config,
                         const components::ComponentContext& context)
    : LoggableComponentBase(config, context),
      game_(context.FindComponent<infrastructure::DictionaryComponent>().GetDictionary()),
//      pg_cluster_(context.FindComponent<userver::components::Postgres>("postgres-db-1").GetCluster()),
      players_(context.FindComponent<app::Players>()),
      game_starter_(game_, players_),
      word_checker_(game_, players_)
{}


Players& Application::GetPlayers() { return players_; }

game::Game& Application::GetGame() { return game_; }


void AppendApplication(userver::components::ComponentList& component_list) {
  component_list.Append<Application>();
}

}  // namespace app
