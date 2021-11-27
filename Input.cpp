#include "Input.h"

Input::Input(bool& inRunning) : running(inRunning), runningId(0) {}

uint32_t Input::addCallback(SDL_KeyCode key, std::function<void()> cbk) {

	runningId++;

	if (key == SDLK_p) {
		std::cout << "added callback for p" << std::endl;
	}

	if (inputCallbacks.find(key) == inputCallbacks.end()) {
		inputCallbacks[key] = std::vector<InputCallbackInfo>();
	}
	InputCallbackInfo callbackInfo;
	callbackInfo.id = runningId;
	callbackInfo.function = cbk;
	inputCallbacks[key].push_back(callbackInfo);

	return callbackInfo.id;
}

void Input::removeCallback(SDL_KeyCode key, uint32_t id) {

	if (inputCallbacks.find(key) == inputCallbacks.end()) {
		std::cout << "could not find callback function upon removal" << std::endl;
		return;
	}

	std::vector<InputCallbackInfo>& callbackInfos = inputCallbacks[key];
	int idxToRemove = -1;
	for (unsigned i = 0; i < callbackInfos.size(); i++) {
		if (callbackInfos[i].id == id) {
			idxToRemove = i;
			break;
		}
	}
	if (idxToRemove != -1) {
		callbackInfos.erase(callbackInfos.begin() + idxToRemove, callbackInfos.begin() + idxToRemove + 1);
	}
}

void Input::update() {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_QUIT:
		running = false;
		break;
	case SDL_KEYDOWN: {
		SDL_KeyCode keyCode = (SDL_KeyCode)event.key.keysym.sym;
		if (inputCallbacks.find(keyCode) != inputCallbacks.end()) {
			for (InputCallbackInfo& info : inputCallbacks[keyCode]) {
				info.function();
			}
		}

		/*
		if (keyCode == SDLK_ESCAPE) {
			running = false;
		}
		*/
		break;
	}
	}
}