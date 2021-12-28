#include "Input.h"

Input::Input(bool& inRunning) : running(inRunning) {
	validToBePressed.setAllTrue();
}

void Input::update() {
	SDL_Event event;
	SDL_PollEvent(&event);

	inputDown = {};
	inputPressed = {};

	switch (event.type) {
	case SDL_QUIT:
		running = false;
		break;
	case SDL_KEYDOWN: {

		SDL_KeyCode keyCode = (SDL_KeyCode)event.key.keysym.sym;

		switch (keyCode) {
		case SDLK_w:
			inputDown.w = true;
			if (validToBePressed.w) {
				inputPressed.w = true;
				validToBePressed.w = false;
			}
			break;
		case SDLK_a:
			inputDown.a = true;
			if (validToBePressed.a) {
				inputPressed.a = true;
				validToBePressed.a = false;
			}
			break;
		case SDLK_s:
			inputDown.s = true;
			if (validToBePressed.s) {
				inputPressed.s = true;
				validToBePressed.s = false;
			}
			break;
		case SDLK_d:
			inputDown.d = true;
			if (validToBePressed.d) {
				inputPressed.d = true;
				validToBePressed.d = false;
			}
			break;
		case SDLK_UP:
			inputDown.up = true;
			if (validToBePressed.up) {
				inputPressed.up = true;
				validToBePressed.up = false;
			}
			break;
		case SDLK_RIGHT:
			inputDown.right = true;
			if (validToBePressed.right) {
				inputPressed.right = true;
				validToBePressed.right = false;
			}
			break;
		case SDLK_LEFT:
			inputDown.left = true;
			if (validToBePressed.left) {
				inputPressed.left = true;
				validToBePressed.left = false;
			}
			break;
		case SDLK_DOWN:
			inputDown.down = true;
			if (validToBePressed.down) {
				inputPressed.down = true;
				validToBePressed.down = false;
			}
			break;
		case SDLK_RETURN:
			inputDown.enter = true;
			if (validToBePressed.enter) {
				inputPressed.enter = true;
				validToBePressed.enter = false;
			}
			break;
		case SDLK_ESCAPE:
			inputDown.escape = true;
			if (validToBePressed.escape) {
				inputPressed.escape = true;
				validToBePressed.escape = false;
			}
			break;
		case SDLK_LCTRL:
			inputDown.leftCtrl = true;
			if (validToBePressed.leftCtrl) {
				inputPressed.leftCtrl = true;
				validToBePressed.leftCtrl = false;
			}
			break;
		case SDLK_RCTRL:
			inputDown.rightCtrl = true;
			if (validToBePressed.rightCtrl) {
				inputPressed.rightCtrl = true;
				validToBePressed.rightCtrl = false;
			}
			break;
		case SDLK_PLUS:
			inputDown.plus = true;
			if (validToBePressed.plus) {
				inputPressed.plus = true;
				validToBePressed.plus = false;
			}
			break;
		case SDLK_EQUALS:
			inputDown.equals = true;
			if (validToBePressed.equals) {
				inputPressed.equals = true;
				validToBePressed.equals = false;
			}
			break;
		}
	}
					break;

	case SDL_KEYUP: {

		SDL_KeyCode keyCode = (SDL_KeyCode)event.key.keysym.sym;

		switch (keyCode) {
		case SDLK_w:
			validToBePressed.w = true;
			break;
		case SDLK_a:
			validToBePressed.a = true;
			break;
		case SDLK_s:
			validToBePressed.s = true;
			break;
		case SDLK_d:
			validToBePressed.d = true;
			break;
		case SDLK_UP:
			validToBePressed.up = true;
			break;
		case SDLK_RIGHT:
			validToBePressed.right = true;
			break;
		case SDLK_LEFT:
			validToBePressed.left = true;
			break;
		case SDLK_DOWN:
			validToBePressed.down = true;
			break;
		case SDLK_RETURN:
			validToBePressed.enter = true;
			break;
		case SDLK_ESCAPE:
			validToBePressed.escape = true;
			break;
		case SDLK_LCTRL:
			validToBePressed.leftCtrl = true;
			break;
		case SDLK_RCTRL:
			validToBePressed.rightCtrl = true;
			break;
		case SDLK_PLUS:
			validToBePressed.plus = true;
			break;
		case SDLK_EQUALS:
			validToBePressed.equals = true;
			break;
		}

	}
				  break;

	}
}
