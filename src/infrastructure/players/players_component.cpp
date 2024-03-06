#include "players_component.h"

namespace {

using namespace userver;
using namespace std::literals;

}  // namespace

namespace infrastructure {

PlayersComponent::PlayersComponent(const components::ComponentConfig& config,
                                   const components::ComponentContext& context)
    : LoggableComponentBase(config, context), players_(new MemoryMappedPlayers()) {
  // FIXME Здесь нужно исходя из статик конфига создавать нужного наследника IPlayers
}

void AppendPlayers(userver::components::ComponentList& component_list) {
  component_list.Append<PlayersComponent>();
}

app::IPlayers& PlayersComponent::GetPlayers() {
  return *players_;
}
}  // namespace infrastructure
