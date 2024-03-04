#include <userver/clients/http/component.hpp>
#include <userver/components/minimal_server_component_list.hpp>
#include <userver/server/handlers/ping.hpp>
#include <userver/server/handlers/tests_control.hpp>
#include <userver/testsuite/testsuite_support.hpp>
#include <userver/utils/daemon_run.hpp>

#include "app/application.h"
#include "handlers/CheckWord/check_handler.hpp"
#include "handlers/StartGame/start_game_handler.hpp"
#include "infrastructure/dictionary/dictionary_component.h"
#include "infrastructure/players/players_component.h"

int main(int argc, char* argv[]) {
  auto component_list = userver::components::MinimalServerComponentList()
                            .Append<userver::server::handlers::Ping>()
                            .Append<userver::components::TestsuiteSupport>()
                            .Append<userver::components::HttpClient>()
                            .Append<userver::server::handlers::TestsControl>();

  infrastructure::AppendDictionary(component_list);
  infrastructure::AppendPlayers(component_list);
  app::AppendApplication(component_list);

  handlers::AppendGameStarterHandler(component_list);
  handlers::AppendCheckHandler(component_list);

  return userver::utils::DaemonMain(argc, argv, component_list);
}
