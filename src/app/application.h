#pragma once

#include <optional>
#include <string>
#include <string_view>
#include <utility>

#include "userver/clients/http/client.hpp"
#include "userver/clients/http/component.hpp"
#include <userver/components/component_config.hpp>
#include <userver/components/component_context.hpp>
#include "userver/components/component_list.hpp"
#include "userver/storages/postgres/cluster.hpp"
#include "userver/storages/postgres/component.hpp"
#include "userver/utils/assert.hpp"
#include <userver/formats/serialize/common_containers.hpp>

#include "app/use-cases/scenarios.h"
#include "model/game.h"
#include "infrastructure/dictionary/dictionary_component.h"
#include "infrastructure/players/players_component.h"

namespace app {

class Application : public userver::components::LoggableComponentBase {
 public:
  static constexpr std::string_view kName = "application";

  Application(const userver::components::ComponentConfig& config,
              const userver::components::ComponentContext& context);
  ~Application() = default;

  Token StartGame();
  CheckWordResult CheckWord(const Token &token, std::string_view word);

  IPlayers& GetPlayers();
  game::Game& GetGame();

 private:
  game::Game game_eng_;
  userver::storages::postgres::ClusterPtr pg_cluster_;
  IPlayers& players_;

  // Scenarios
  GameStarter game_starter_;
  WordChecker word_checker_;
};

void AppendApplication(userver::components::ComponentList& component_list);

}  // namespace app
