#include "check_handler.hpp"

#include <iostream>

namespace {

using namespace userver;

void CheckArgument(const std::string& arg, const std::string& arg_name) {
  if (arg.empty()) {
    throw std::invalid_argument("No '" + arg_name + "' argument!");
  }
}

}  // namespace

namespace userver::formats::serialize {

userver::formats::json::Value Serialize(const game::WordStatus& checkout,
                                        userver::formats::serialize::To<userver::formats::json::Value>) {
  userver::formats::json::ValueBuilder builder(game::WordStatusToString(checkout));
  return builder.ExtractValue();
}

userver::formats::json::Value Serialize(const game::LetterStatus& status,
                                        userver::formats::serialize::To<userver::formats::json::Value>) {
  userver::formats::json::ValueBuilder builder(game::LetterStatusToString(status));

  return builder.ExtractValue();
}

userver::formats::json::Value Serialize(const game::WordCheckout& checkout,
                                        userver::formats::serialize::To<userver::formats::json::Value>) {
  userver::formats::json::ValueBuilder builder;

  builder["WordStatus"] = userver::formats::json::ValueBuilder(checkout.status).ExtractValue();
  builder["letters"] = userver::formats::json::ValueBuilder(checkout.letters).ExtractValue();

  return builder.ExtractValue();
}

}  // namespace userver::formats::serialize

namespace handlers {

std::string StringStatus(game::WordStatus& status) {
  switch (status) {
    case game::WordStatus::UNREAL_WORD:
      return "UNREAL_WORD";
    case game::WordStatus::WRONG_WORD:
      return "WRONG_WORD";
    case game::WordStatus::RIGHT_WORD:
      return "RIGHT_WORD";
    default:
      return "UNKNOWN_WORD_STATUS";
  }
}

CheckHandler::CheckHandler(const components::ComponentConfig& config, const components::ComponentContext& context)
    : HttpHandlerBase(config, context), app_(context.FindComponent<app::Application>()) {
}

std::string CheckHandler::HandleRequestThrow(const userver::server::http::HttpRequest& request,
                                             userver::server::request::RequestContext&) const {
  const app::Token& token = request.GetArg("token");
  const std::string& word = request.GetArg("word");

  std::optional<game::WordCheckout> checkout;

  try {
    CheckArgument(token, "token");
    CheckArgument(word, "word");

    checkout = app_.CheckWord(token, word);

  } catch (const std::invalid_argument& e) {
    request.SetResponseStatus(userver::server::http::HttpStatus::kBadRequest);
    throw server::handlers::ClientError(server::handlers::ExternalBody{e.what()});
  }

  if (checkout) {
    request.SetResponseStatus(userver::server::http::HttpStatus::kOk);
    userver::formats::json::ValueBuilder builder(*checkout);
    auto response = builder.ExtractValue();

    request.GetHttpResponse().SetContentType("application/json");

    return ToString(response);
  } else {
    request.SetResponseStatus(userver::server::http::HttpStatus::kInternalServerError);

    throw server::handlers::ClientError(server::handlers::ExternalBody{"Token is not real!"s});
  }
}

void AppendCheckHandler(userver::components::ComponentList& component_list) {
  component_list.Append<CheckHandler>();
}

}  // namespace handlers