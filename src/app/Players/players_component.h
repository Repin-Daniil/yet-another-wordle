#pragma once

#include <memory>

#include "userver/clients/http/client.hpp"
#include "userver/clients/http/component.hpp"
#include "userver/components/component_list.hpp"
#include "userver/storages/postgres/cluster.hpp"
#include "userver/storages/postgres/component.hpp"
#include "userver/utils/assert.hpp"

#include "app/Players/Naive/naive_players.h"

namespace app {

class PlayersComponent : public userver::components::LoggableComponentBase {
 public:
  static constexpr std::string_view kName = "players";

  PlayersComponent(const userver::components::ComponentConfig& config,
                   const userver::components::ComponentContext& context);
  ~PlayersComponent() = default;

  IPlayers& GetPlayers();

 private:
  std::unique_ptr<IPlayers> players_;
};

void AppendPlayers(userver::components::ComponentList& component_list);

}  // namespace app
