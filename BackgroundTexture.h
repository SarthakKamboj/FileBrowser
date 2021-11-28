#pragma once

#include <SDL.h>
#include "Application.h"

class BackgroundTexture {
public:
	BackgroundTexture(SDL_Color color);
	BackgroundTexture(int width, int height, SDL_Color color);
	void draw(int xPos, int yPos);
	void draw(int xPos, int yPos, int width, int height);

private:
	int width;
	int height;
	SDL_Texture* backgroundTexture;
	SDL_Rect destRect;
	SDL_Color color;

	void createBackgroundTexture();
};