#pragma once

#include "userver/clients/http/client.hpp"
#include "userver/clients/http/component.hpp"
#include "userver/components/component_list.hpp"
#include "userver/components/minimal_server_component_list.hpp"
#include "userver/server/handlers/http_handler_base.hpp"
#include <userver/formats/json/value.hpp>
#include <userver/formats/json/value_builder.hpp>
#include <userver/formats/serialize/common_containers.hpp>

#include "app/application.h"

namespace handlers {

using namespace userver;
using namespace std::literals;

class CheckHandler final : public server::handlers::HttpHandlerBase {
 public:
  static constexpr std::string_view kName = "handler-check"sv;

  using HttpHandlerBase::HttpHandlerBase;

  CheckHandler(const components::ComponentConfig& config,
               const components::ComponentContext& context);

  std::string HandleRequestThrow(
      const userver::server::http::HttpRequest& request,
      userver::server::request::RequestContext& context) const override;

 private:
  app::Application &app_;
};

void AppendCheckHandler(userver::components::ComponentList& component_list);

}  // namespace handlers