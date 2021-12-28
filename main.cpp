
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <cmath>
#include <SDL_ttf.h>
#include <string>
#include <filesystem>
#include <vector>
#include "Util.h"
#include "DirectoryView.h"
#include "Input.h"
#include "DirectoryViewManager.h"
#include "Application.h"

namespace fs = std::filesystem;

int main(int argc, char* args[]) {

	Application application;

	if (!application.init()) {
		return 1;
	}

	const int FPS = 60;
	const int secPerFrame = 1000 / FPS;

	int windowWidth = 1200;
	int windowHeight = 675;

	application.createWindow(windowWidth, windowHeight);

	bool running = true;
	Input input(running);

	SDL_Color backgroundColor;
	backgroundColor.r = 2;
	backgroundColor.g = 43;
	backgroundColor.b = 53;
	backgroundColor.a = 255;

	SDL_SetRenderDrawColor(Application::GetRenderer(), backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);

	std::string fontName = "SpaceMono";
	std::string fontPath = "fonts/SpaceMono.ttf";
	Util::addFont(fontName, fontPath, 16);

	std::string path = "C:\\Users\\kambo\\Downloads\\towerDefense";
	DirectoryViewManager directoryViewManager(windowWidth, windowHeight, &input);
	directoryViewManager.addDirectoryView(path);

	while (running) {

		input.update();

		directoryViewManager.update();

		uint32_t frameStart = SDL_GetTicks();

		SDL_RenderClear(Application::GetRenderer());

		directoryViewManager.render();

		SDL_RenderPresent(Application::GetRenderer());

		int curFrameDuration = SDL_GetTicks() - frameStart;

		if (secPerFrame > curFrameDuration) {
			SDL_Delay(secPerFrame - curFrameDuration);
		}
	}

	application.cleanUp();

	return 0;
}