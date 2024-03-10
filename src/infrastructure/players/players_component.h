#pragma once

#include <memory>

#include "userver/clients/http/client.hpp"
#include "userver/clients/http/component.hpp"
#include "userver/components/component_list.hpp"
#include "userver/storages/postgres/cluster.hpp"
#include "userver/storages/postgres/component.hpp"
#include <userver/yaml_config/merge_schemas.hpp>
#include <userver/components/component_config.hpp>
#include <userver/components/component_context.hpp>

#include "infrastructure/players/in-memory/memory_mapped_players.h"

namespace infrastructure {

class PlayersComponent : public userver::components::LoggableComponentBase {
 public:
  static constexpr std::string_view kName = "players";

  PlayersComponent(const userver::components::ComponentConfig& config,
                   const userver::components::ComponentContext& context);
  ~PlayersComponent() = default;

  app::IPlayers& GetPlayers();

  static userver::yaml_config::Schema GetStaticConfigSchema();

 private:
  std::unique_ptr<app::IPlayers> players_;
  userver::storages::postgres::ClusterPtr pg_cluster_;
};

void AppendPlayers(userver::components::ComponentList& component_list);

}  // namespace infrastructure
