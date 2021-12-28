#include "Input.h"

Input::Input(bool& inRunning) : running(inRunning) {}

void Input::update() {
	SDL_Event event;
	SDL_PollEvent(&event);

	inputPressed = {};

	switch (event.type) {
	case SDL_QUIT:
		running = false;
		break;
	case SDL_KEYDOWN: {

		SDL_KeyCode keyCode = (SDL_KeyCode)event.key.keysym.sym;

		switch (keyCode) {
		case SDLK_w:
			inputPressed.w = true;
			break;
		case SDLK_a:
			inputPressed.a = true;
			break;
		case SDLK_s:
			inputPressed.s = true;
			break;
		case SDLK_d:
			inputPressed.d = true;
			break;
		case SDLK_UP:
			inputPressed.up = true;
			break;
		case SDLK_RIGHT:
			inputPressed.right = true;
			break;
		case SDLK_LEFT:
			inputPressed.left = true;
			break;
		case SDLK_DOWN:
			inputPressed.down = true;
			break;
		case SDLK_RETURN:
			inputPressed.enter = true;
			break;
		case SDLK_ESCAPE:
			inputPressed.escape = true;
			break;
		case SDLK_LCTRL:
			inputPressed.leftCtrl = true;
			break;
		case SDLK_RCTRL:
			inputPressed.rightCtrl = true;
			break;
		case SDLK_PLUS:
			inputPressed.plus = true;
			break;
		case SDLK_EQUALS:
			inputPressed.equals = true;
			break;
		}
	}
	}
}
