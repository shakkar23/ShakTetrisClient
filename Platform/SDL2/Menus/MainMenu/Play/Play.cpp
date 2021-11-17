#include "Play.hpp"

PlayMenuGUI::PlayMenuGUI(menuGUI* parentMenu) {
	isInitialized = false;
	this->metaMenu = parentMenu;
	auto plugins = Shakkar::Plugins::getEntries().size();
	if (Shakkar::Plugins::getEntries().empty()) 
	{
		printf(":(, there is no Tetris entries");
		plugin = nullptr;
		metaMenu->submenuWasDeleted = true;
		delete this;

	}
	else
		 this->plugin = Shakkar::Plugins::getEntries().back();
	pluginReInit = !plugin->isPlaying; // if we are not playing, but the plugin does exist, reload it
}
PlayMenuGUI::~PlayMenuGUI() {
	
}
void PlayMenuGUI::Init(RenderWindow& window) {
	this->plugin = Shakkar::Plugins::getEntries().at(0);
	return;
}

void PlayMenuGUI::menuLogic(Shakkar::inputBitmap& input, Shakkar::inputBitmap& prevInput) {
	// in this scenario the top option is 0, and you increment to go down

	if (this->plugin == nullptr) {
		metaMenu->submenuWasDeleted = true;
		delete this;
	}
	else if (pluginReInit)
		;
	else if (!plugin->isPlaying) {
		metaMenu->submenuWasDeleted = true;
		delete this;
	}
	else { plugin->gameLogic(input, prevInput); }

}

void PlayMenuGUI::render(RenderWindow& window) {
	if (pluginReInit) {
		plugin->Init(window);
		pluginReInit = false;
	}
	plugin->render(window);

}