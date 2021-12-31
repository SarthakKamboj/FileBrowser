#include "Application.h"

SDL_Renderer* Application::renderer = NULL;
int Application::width = 0;
int Application::height = 0;

Application::Application() : window(NULL) {}

bool Application::init() {

	int audioRate = 22050;
	uint16_t audioFormat = AUDIO_S16SYS;
	int audioChannels = 2;
	int audioBuffers = 4096;

	Mix_OpenAudioDevice(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, audioBuffers, 0, 0);

	return !(SDL_Init(SDL_INIT_EVERYTHING) != 0 || TTF_Init() == -1) || Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) != 0;
}

void Application::createWindow(int windowWidth, int windowHeight) {
	width = windowWidth;
	height = windowHeight;
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
