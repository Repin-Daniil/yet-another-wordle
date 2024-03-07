#include "start_game_handler.hpp"

namespace handlers {

GameStarterHandler::GameStarterHandler(const components::ComponentConfig& config,
                                       const components::ComponentContext& context)
    : HttpHandlerBase(config, context), app_(context.FindComponent<app::Application>()) {
}

std::string GameStarterHandler::HandleRequestThrow(const userver::server::http::HttpRequest& request,
                                                   userver::server::request::RequestContext&) const {
  auto token = app_.StartGame();

  return token;
}

void AppendGameStarterHandler(userver::components::ComponentList& component_list) {
  component_list.Append<GameStarterHandler>();
}

}  // namespace handlers
