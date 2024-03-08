#include "dictionary_component.h"

namespace {

using namespace userver;

}  // namespace

namespace infrastructure {

DictionaryComponent::DictionaryComponent(const components::ComponentConfig& config,
                                         const components::ComponentContext& context)
    : LoggableComponentBase(config, context) {
  auto path = config[constants::ConfigArgs::path_to_words].As<std::string>();
  const auto fs_tp_name = config[constants::ConfigArgs::fs_task_processor].As<std::string>();

  auto& fs_task_processor = context.GetTaskProcessor(fs_tp_name);

  if (!fs::FileExists(fs_task_processor, path)) {
    throw std::invalid_argument("File with words not found!");
  }

  std::string raw_words = fs::ReadFileContents(fs_task_processor, path);

  std::istringstream iss(raw_words);

  std::string word;
  std::unordered_set<std::string> words;

  while (std::getline(iss, word, '\n')) {
    words.insert(word);
  }

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
    fs-task-processor:
     type: string
     description: fs-tp name
)");
}

void AppendDictionary(userver::components::ComponentList& component_list) {
  component_list.Append<DictionaryComponent>();
}

}  // namespace infrastructure
