#include "dictionary_component.h"

namespace {

using namespace userver;

}  // namespace

namespace infrastructure {

DictionaryComponent::DictionaryComponent(
    const components::ComponentConfig& config,
    const components::ComponentContext& context)
    : LoggableComponentBase(config, context),
      dict_(new NaiveDictionary({"apple", "heart", "horse"}))  // TODO из конфига брать, а пока так
{}

game::IDictionary& DictionaryComponent::GetDictionary() { return *dict_; }

void AppendDictionary(userver::components::ComponentList& component_list) {
  component_list.Append<DictionaryComponent>();
}
}  // namespace infrastructure