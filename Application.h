#pragma once

#include "SDL.h"
#include "SDL_ttf.h"

class Application {
public:
	Application();
	bool init();
	void createWindow(int windowWidth, int windowHeight);
	void cleanUp();

	static SDL_Renderer* GetRenderer();
	static int width, height;

private:
	const int FPS = 60;
	const int frameDelay = 1000 / 60;

	static SDL_Renderer* renderer;
	SDL_Window* window;
};