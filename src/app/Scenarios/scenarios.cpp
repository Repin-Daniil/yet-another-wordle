#include "scenarios.h"

namespace app {

Token GameStarter::Start() {
  auto player = players_.AddPlayer(game_.GetRandomWord()); //FIXME А вот здесь может быть гонка с players

  return player->GetToken();
}


}  // namespace app