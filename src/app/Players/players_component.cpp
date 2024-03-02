#include "players_component.h"

namespace {

using namespace userver;
using namespace std::literals;

}  // namespace

namespace app {

PlayersComponent::PlayersComponent(const components::ComponentConfig& config,
                                   const components::ComponentContext& context)
    : LoggableComponentBase(config, context), players_(new NaivePlayers()) {
  // FIXME Здесь нужно исходя из статик конфига создавать нужного наследника IPlayers
}

void AppendPlayers(userver::components::ComponentList& component_list) {
  component_list.Append<PlayersComponent>();
}

IPlayers& PlayersComponent::GetPlayers() {
  return *players_;
}
}  // namespace app
