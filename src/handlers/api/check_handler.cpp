#include "check_handler.hpp"

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

  builder["word"] = userver::formats::json::ValueBuilder(checkout.word).ExtractValue();
  builder["status"] = userver::formats::json::ValueBuilder(checkout.status).ExtractValue();
  builder["letters"] = userver::formats::json::ValueBuilder(checkout.letters).ExtractValue();

  return builder.ExtractValue();
}

userver::formats::json::Value Serialize(const app::CheckWordResult& result,
                                        userver::formats::serialize::To<userver::formats::json::Value>) {
  userver::formats::json::ValueBuilder builder;

  builder["attempts"] = userver::formats::json::ValueBuilder(result.attempts).ExtractValue();
  builder["remaining_attempts"] = result.remaining_attempts;
  builder["is_new_word_set"] = result.is_new_word;

  return builder.ExtractValue();
}

}  // namespace userver::formats::serialize

namespace handlers {

CheckHandler::CheckHandler(const components::ComponentConfig& config, const components::ComponentContext& context)
    : HttpHandlerBase(config, context), app_(context.FindComponent<app::Application>()) {
}

std::string CheckHandler::HandleRequestThrow(const userver::server::http::HttpRequest& request,
                                             userver::server::request::RequestContext&) const {
  const app::Token& token = request.GetArg("token");
  const std::string& word = request.GetArg("word");

  app::CheckWordResult result;

  try {
    CheckArgument(token, "token");
    CheckArgument(word, "word");

    result = app_.CheckWord(token, word);
  } catch (const std::invalid_argument& e) {
    throw server::handlers::ClientError(server::handlers::ExternalBody{e.what()});
  } catch (const app::CheckWordError& error) {
    if (error.reason == app::CheckWordErrorReason::UNREAL_TOKEN) {
      throw server::handlers::ClientError(server::handlers::ExternalBody{"Token is not real!"s});
    } else if (error.reason == app::CheckWordErrorReason::UNREAL_WORD) {
      throw server::handlers::ClientError(server::handlers::ExternalBody{"Word is not real!"s});
    }
  }

  request.SetResponseStatus(userver::server::http::HttpStatus::kOk);
  request.GetHttpResponse().SetContentType("application/json");

  userver::formats::json::ValueBuilder builder(result);

  return ToString(builder.ExtractValue());
}

void AppendCheckHandler(userver::components::ComponentList& component_list) {
  component_list.Append<CheckHandler>();
}

}  // namespace handlers
