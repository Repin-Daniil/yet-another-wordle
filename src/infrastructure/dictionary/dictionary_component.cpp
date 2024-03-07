#include "dictionary_component.h"

namespace {

using namespace userver;

}  // namespace

namespace infrastructure {

DictionaryComponent::DictionaryComponent(const components::ComponentConfig& config,
                                         const components::ComponentContext& context)
    : LoggableComponentBase(config, context) {
  auto path = config[constants::ConfigArgs::path_to_words].As<std::string>();

  // TODO вызвать fs_task_processor и считать слова в unordered_set

  std::unordered_set<std::string_view> words{"apple", "heart", "horse"};

  dict_ = std::make_unique<NaiveDictionary>(std::move(words));
}

game::IDictionary& DictionaryComponent::GetDictionary() {
  return *dict_;
}

userver::yaml_config::Schema DictionaryComponent::GetStaticConfigSchema() {
  return userver::yaml_config::MergeSchemas<userver::components::LoggableComponentBase>(
      R"(
type: object
description: dictionary
additionalProperties: false
properties:
    path-to-words:
        type: string
        description: path to words
)");
}

void AppendDictionary(userver::components::ComponentList& component_list) {
  component_list.Append<DictionaryComponent>();
}
}  // namespace infrastructure
