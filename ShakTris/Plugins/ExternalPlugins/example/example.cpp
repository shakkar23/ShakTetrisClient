
#include "example.hpp"
#include<string>

class bruh : public Shakkar::Tetris {
    public:
    bruh() : Shakkar::Tetris("bruh"){}
    void gameLogic() override {}
    void render(RenderWindow& window) override {}
};

PLUGIN_SETUP("john tronathon", "Shakkar23", "ok so basically this is an example and its for example purposes, and its an example that is used for being an example") {

    Shakkar::Plugins::add<bruh>();
    

}