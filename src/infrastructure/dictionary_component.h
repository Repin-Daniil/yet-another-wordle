#pragma once

#include <memory>

#include <userver/clients/dns/component.hpp>
#include <userver/clients/http/component.hpp>
#include <userver/components/minimal_server_component_list.hpp>
#include <userver/server/handlers/ping.hpp>
#include <userver/server/handlers/tests_control.hpp>
#include <userver/testsuite/testsuite_support.hpp>
#include <userver/utils/daemon_run.hpp>

#include "domain/game.h"
#include "naive_dictionary.h"

namespace infrastructure {

// TODO подгружать из конфигов слова
class DictionaryComponent : public userver::components::LoggableComponentBase {
 public:
  static constexpr std::string_view kName = "dictionary";

  DictionaryComponent(const userver::components::ComponentConfig& config,
                      const userver::components::ComponentContext& context);
  ~DictionaryComponent() = default;

  game::IDictionary& GetDictionary();

 private:
  std::unique_ptr<game::IDictionary> dict_;
};

void AppendDictionary(userver::components::ComponentList& component_list);

}  // namespace infrastructure
