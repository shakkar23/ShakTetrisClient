
#include "Input.hpp"
#include <algorithm>

namespace Shakkar {
	inputs::inputs() {}

	void inputs::addKey(SDL_Keycode key) {
		auto i = std::find( cur_buttons.begin(), cur_buttons.end(), key );

		if (i == cur_buttons.end())
			cur_buttons.push_back(key);
	}

	void inputs::removeKey(SDL_Keycode key) {
		for (auto it = cur_buttons.begin(); it != cur_buttons.end(); ++it) {
			if (*it == key) {
				cur_buttons.erase(it);
				break;
			}
		}
	}


	Key inputs::getKey(SDL_Keycode key) const {
		Key keyState{};

		auto cur = std::find( cur_buttons.begin(), cur_buttons.end(), key ) != cur_buttons.end();

		auto prev = std::find( prev_buttons.begin(), prev_buttons.end(), key ) != prev_buttons.end();

		keyState.held = cur && prev;
		keyState.pressed = justPressed(prev, cur);
		keyState.released = cur && !prev;

		return keyState;
	}
	
	void inputs::update() {
		prev_buttons = cur_buttons;
	}
};
