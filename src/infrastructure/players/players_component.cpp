#include "players_component.h"

namespace {

using namespace userver;
using namespace std::literals;

}  // namespace

namespace infrastructure {

PlayersComponent::PlayersComponent(const components::ComponentConfig& config,
                                   const components::ComponentContext& context)
    : LoggableComponentBase(config, context) {
  bool store_in_memory = config[constants::ConfigArgs::store_in_memory].As<bool>();

  if (store_in_memory) {
    players_ = std::make_unique<MemoryMappedPlayers>();
  }
}

app::IPlayers& PlayersComponent::GetPlayers() {
  return *players_;
}

userver::yaml_config::Schema PlayersComponent::GetStaticConfigSchema() {
  return userver::yaml_config::MergeSchemas<userver::components::LoggableComponentBase>(
      R"(
type: object
description: players
additionalProperties: false
properties:
    in-memory-storage:
        type: boolean
        description: use memory_mapped_player or redis
)");
}

void AppendPlayers(userver::components::ComponentList& component_list) {
  component_list.Append<PlayersComponent>();
}

}  // namespace infrastructure
