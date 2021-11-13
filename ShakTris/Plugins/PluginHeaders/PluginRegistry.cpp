#include"PluginRegistry.hpp"

namespace Correct {
    std::vector<Shakkar::Tetris*> games;
};
void Shakkar::Plugins::add2(Shakkar::Tetris* game) {
    getEntries().emplace_back(game);
}

std::vector<Shakkar::Tetris*> &Shakkar::Plugins::getEntries() {
    return Correct::games;
}