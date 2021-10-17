#include"PluginRegistry.hpp"

namespace Correct {
    static std::vector<Shakkar::Tetris*> views;
};
void Shakkar::Plugins::add2(Shakkar::Tetris* view) {
    getEntries().emplace_back(view);
}

std::vector<Shakkar::Tetris*> Shakkar::Plugins::getEntries() {
    return Correct::views;
}