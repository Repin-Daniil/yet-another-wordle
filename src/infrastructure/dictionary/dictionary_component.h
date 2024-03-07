#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <utility>

#include "userver/clients/dns/component.hpp"
#include "userver/clients/http/component.hpp"
#include "userver/components/minimal_server_component_list.hpp"
#include "userver/server/handlers/ping.hpp"
#include "userver/server/handlers/tests_control.hpp"
#include "userver/testsuite/testsuite_support.hpp"
#include <userver/yaml_config/merge_schemas.hpp>
#include "userver/utils/daemon_run.hpp"

#include "model/dictionary.h"
#include "constants_storage.h"
#include "infrastructure/dictionary/in-memory/naive_dictionary.h"

namespace infrastructure {

class DictionaryComponent : public userver::components::LoggableComponentBase {
 public:
  static constexpr std::string_view kName = "dictionary";

  DictionaryComponent(const userver::components::ComponentConfig& config,
                      const userver::components::ComponentContext& context);
  ~DictionaryComponent() = default;

  game::IDictionary& GetDictionary();

  static userver::yaml_config::Schema GetStaticConfigSchema();

 private:
  std::unique_ptr<game::IDictionary> dict_;
};

void AppendDictionary(userver::components::ComponentList& component_list);

}  // namespace infrastructure
