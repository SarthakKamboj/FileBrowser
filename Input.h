#pragma once

#include "SDL.h"
#include <vector>
#include <map>
#include <functional>
#include <iostream>

class Input {

	struct InputCallbackInfo {
		uint32_t id;
		std::function<void()> function;
	};

public:
	Input(bool& running);
	uint32_t addCallback(SDL_KeyCode key, std::function<void()> func);
	void removeCallback(SDL_KeyCode key, uint32_t id);
	void update();
private:
	std::map < SDL_KeyCode, std::vector<InputCallbackInfo>> inputCallbacks;
	bool& running;
	uint32_t runningId;
};