
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

namespace fs = std::filesystem;

int main(int argc, char* args[]) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0 || TTF_Init() == -1) {
		return 1;
	}

	const int FPS = 60;
	const int frameDelay = 1000 / 60;

	uint32_t frameStart;
	int frameTime = 0;

	int windowWidth = 800;
	int windowHeight = 600;

	SDL_Window* window = SDL_CreateWindow("Text Editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	std::string imgFilePath = "cpp.png";
	SDL_Texture* imageTex = Util::loadImage(renderer, imgFilePath);

	bool running = true;
	Input input(running);

	SDL_Rect srcRect;
	srcRect.x = 0;
	srcRect.y = 0;
	SDL_QueryTexture(imageTex, NULL, NULL, &srcRect.w, &srcRect.h);

	SDL_Rect destRct;
	destRct.x = 0;
	destRct.y = 0;
	destRct.w = srcRect.w / fmax(srcRect.w, srcRect.h) * 32;
	destRct.h = srcRect.h / fmax(srcRect.w, srcRect.h) * 32;

	SDL_Color backgroundColor;
	backgroundColor.r = 2;
	backgroundColor.g = 43;
	backgroundColor.b = 53;
	backgroundColor.a = 255;

	SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);

	std::string fontName = "SpaceMono";
	std::string fontPath = "fonts/SpaceMono.ttf";
	Util::addFont(fontName, fontPath, 16);

	DirectoryViewManager directoryViewManager(windowWidth, windowHeight, renderer, &input);
	std::string path = "C:\\";
	directoryViewManager.addDirectoryView(path);

	BackgroundTexture background(64, 64, renderer, { 0, 255, 0 });

	while (running) {

		input.update();

		frameStart = SDL_GetTicks();

		SDL_RenderClear(renderer);

		directoryViewManager.drawDirectories();

		SDL_RenderPresent(renderer);

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	return 0;
}