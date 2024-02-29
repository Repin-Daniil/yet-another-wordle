#include "application.h"
#include "app/Players/PlayersComponent.h"
#include "app/Players/players.h"

#include <userver/formats/serialize/common_containers.hpp>

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

std::optional<game::WordCheckout> Application::CheckWord(const Token& token, std::string_view word) {
  auto player = players_.GetPlayerByToken(token);

  if (!player) {
    return std::nullopt;
  }

  //TODO Оборачивать здесь в другую стуктуру. Включить туда еше и количество попыток и прочую инфу игрока
  return word_checker_.Check(player, word);
}

void AppendApplication(userver::components::ComponentList& component_list) {
  component_list.Append<Application>();
  component_list.Append<userver::components::Postgres>("postgres-db-1");
  component_list.Append<userver::clients::dns::Component>();
}

}  // namespace app
