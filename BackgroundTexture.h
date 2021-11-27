#pragma once

#include <SDL.h>

class BackgroundTexture {
public:
	BackgroundTexture(SDL_Renderer* renderer, SDL_Color color);
	BackgroundTexture(int width, int height, SDL_Renderer* renderer, SDL_Color color);
	void draw(int xPos, int yPos);
	void draw(int xPos, int yPos, int width, int height);

private:
	int width;
	int height;
	SDL_Renderer* renderer;
	SDL_Texture* backgroundTexture;
	SDL_Rect destRect;
	SDL_Color color;

	void createBackgroundTexture();
};