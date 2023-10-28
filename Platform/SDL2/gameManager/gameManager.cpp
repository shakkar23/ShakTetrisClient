#include "gameManager.hpp"

bool gameManager::update(Shakkar::inputBitmap& input, Shakkar::inputBitmap& prevInput) {
    // get last element
    auto last = subGUIs.back();

    GUI_payload payload = last->update(input, prevInput);

    if (!payload.second)
    {
        auto iter = std::find(subGUIs.begin(), subGUIs.end(), payload.first);

        if (iter != subGUIs.end())
        {
			subGUIs.erase(iter);
			delete payload.first;
			payload.first = nullptr;
		}
    }
    else if (payload.first != nullptr)
    {
		subGUIs.push_back(payload.first);
	}
    return true;
}
void gameManager::render(RenderWindow &window) {
    if (!subGUIs.back()->isInitialized) {
        subGUIs.back()->init(window);
    }
    subGUIs.back()->render(window);
    window.display();
}
