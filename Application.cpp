#include "Application.h"

SDL_Renderer* Application::renderer = NULL;

Application::Application() : window(NULL) {}

bool Application::init() {
	return !(SDL_Init(SDL_INIT_EVERYTHING) != 0 || TTF_Init() == -1);
}

void Application::createWindow(int windowWidth, int windowHeight) {
	window = SDL_CreateWindow("window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, 0);
}

SDL_Renderer* Application::GetRenderer() {
	return renderer;
}

void Application::cleanUp() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
