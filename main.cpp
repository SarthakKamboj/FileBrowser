
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
#include <iostream>
#include <fstream>
#include "Animation.h"
#include "FlyThrough.h"
#include "SoundEffectManager.h"

namespace fs = std::filesystem;

std::string exeFolderPath;

int main(int argc, char* args[]) {

	std::cout << "argc: " << argc << std::endl;
	for (int i = 0; i < argc; i++) {
		std::cout << "args[" << i << "]: " << args[i] << std::endl;
	}

#ifdef _DEBUG
	exeFolderPath = "C:\\Sarthak\\TextEditor\\TextEditor";
#else
	std::string exeFilePath = args[0];
	std::cout << exeFilePath << std::endl;
	size_t lastSlash = exeFilePath.find_last_of("\\");
	exeFolderPath = exeFilePath.substr(0, lastSlash);
#endif

	Application application;

	if (!application.init()) {
		std::cout << "failed initialization" << std::endl;
		std::ofstream myfile;
		myfile.open("init.txt");
		myfile << "sdl init failed.\n";
		myfile.close();
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
	std::string fontPath = exeFolderPath + "\\fonts\\SpaceMono.ttf";
	Util::addFont(fontName, fontPath, 16);

	std::string path = args[1];
	DirectoryViewManager directoryViewManager(windowWidth, windowHeight, &input);
	directoryViewManager.addDirectoryView(path);

	SoundEffectManager soundEffectsManager;
	// soundEffectsManager.addSoundEffect("test", exeFolderPath + "\\audio\\basketball.wav");
	// soundEffectsManager.playSoundEffect("test");

	FlyThrough flyThrough(&input, &soundEffectsManager);

	while (running) {

		input.update();
		flyThrough.update();

		if (input.inputPressed.escape && !directoryViewManager.imageViewShow) {
			running = false;
			continue;
		}

		directoryViewManager.update();

		uint32_t frameStart = SDL_GetTicks();

		SDL_RenderClear(Application::GetRenderer());

		directoryViewManager.render();
		flyThrough.render();

		SDL_RenderPresent(Application::GetRenderer());

		int curFrameDuration = SDL_GetTicks() - frameStart;

		if (secPerFrame > curFrameDuration) {
			SDL_Delay(secPerFrame - curFrameDuration);
		}
	}

	application.cleanUp();

	return 0;
}