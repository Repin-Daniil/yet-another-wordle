#pragma once

#include <optional>
#include <string>
#include <string_view>
#include <utility>

#include "userver/clients/http/client.hpp"
#include "userver/clients/http/component.hpp"
#include "userver/components/component_list.hpp"
#include "userver/storages/postgres/cluster.hpp"
#include "userver/storages/postgres/component.hpp"
#include "userver/utils/assert.hpp"

#include "domain/game.h"
#include "scenarios.h"
#include "player.h"
#include "infrastructure/dictionary_component.h"

namespace app {

class Application : public userver::components::LoggableComponentBase {
 public:
  static constexpr std::string_view kName = "application";

  Application(const userver::components::ComponentConfig& config,
              const userver::components::ComponentContext& context);
  ~Application() = default;


  app::Players& GetPlayers();
  game::Game& GetGame();

 private:
  game::Game game_;
//  userver::storages::postgres::ClusterPtr pg_cluster_;

  app::Players& players_;

  // Scenarios
  GameStarter game_starter_;
  WordChecker word_checker_;
};

void AppendApplication(userver::components::ComponentList& component_list);

}  // namespace app
