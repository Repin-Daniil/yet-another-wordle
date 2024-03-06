#pragma once

#include <memory>

#include "userver/clients/http/client.hpp"
#include "userver/clients/http/component.hpp"
#include "userver/components/component_list.hpp"
#include "userver/storages/postgres/cluster.hpp"
#include "userver/storages/postgres/component.hpp"
#include "userver/utils/assert.hpp"

#include "infrastructure/players/in-memory/memory_mapped_players.h"

namespace infrastructure {

class PlayersComponent : public userver::components::LoggableComponentBase {
 public:
  static constexpr std::string_view kName = "players";

  PlayersComponent(const userver::components::ComponentConfig& config,
                   const userver::components::ComponentContext& context);
  ~PlayersComponent() = default;

  app::IPlayers& GetPlayers();

 private:
  std::unique_ptr<app::IPlayers> players_;
};

void AppendPlayers(userver::components::ComponentList& component_list);

}  // namespace infrastructure
