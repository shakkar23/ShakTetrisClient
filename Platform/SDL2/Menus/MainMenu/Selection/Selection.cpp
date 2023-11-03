#include "Selection.hpp"

SelectionGUI::SelectionGUI() {
	auto plugins = Shakkar::Plugins::getEntries().size();
	if (Shakkar::Plugins::getEntries().empty()) 
	{
		this->plugin = nullptr;
		throw std::exception(":(, there is no Tetris entries");
	}
	else
		 this->plugin = Shakkar::Plugins::getEntries().back();
	pluginReInit = !plugin->isPlaying; // if we are not playing, but the plugin does exist, reload it
}

SelectionGUI::~SelectionGUI() {}

//grabs a plugin from the entries that are registered
void SelectionGUI::init(RenderWindow& window) {
	this->plugin = Shakkar::Plugins::getEntries().at(0);
}

GUI_payload SelectionGUI::update(Shakkar::inputBitmap& input, Shakkar::inputBitmap& prevInput) {
	// in this scenario the top option is 0, and you increment to go down

	if (this->plugin == nullptr) {
		return {nullptr, false};
	}
	else if (!plugin->isPlaying) {
		return { nullptr, false };
	}
	else { plugin->gameLogic(input, prevInput); }
	return { nullptr, true };
}

void SelectionGUI::render(RenderWindow& window) {
	if (pluginReInit) {
		plugin->Init(window);
		pluginReInit = false;
	}
	plugin->render(window);

}