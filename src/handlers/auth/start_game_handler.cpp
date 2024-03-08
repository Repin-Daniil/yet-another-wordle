#include "start_game_handler.hpp"

namespace {

using namespace userver;

void CheckArgument(const std::string& arg, const std::string& arg_name) {
  if (arg.empty()) {
    throw std::invalid_argument("No '" + arg_name + "' argument!");
  }
}

}  // namespace

namespace handlers {

GameStarterHandler::GameStarterHandler(const components::ComponentConfig& config,
                                       const components::ComponentContext& context)
    : HttpHandlerBase(config, context), app_(context.FindComponent<app::Application>()) {
}

std::string GameStarterHandler::HandleRequestThrow(const userver::server::http::HttpRequest& request,
                                                   userver::server::request::RequestContext&) const {
  const std::string& name = request.GetArg("name");

  try {
    CheckArgument(name, "name");
  } catch (const std::invalid_argument& e) {
    throw server::handlers::ClientError(server::handlers::ExternalBody{e.what()});
  }

  auto token = app_.StartGame(name);

  return token;
}

void AppendGameStarterHandler(userver::components::ComponentList& component_list) {
  component_list.Append<GameStarterHandler>();
}

}  // namespace handlers
