#pragma once

#include <SDL.h>
#include "Application.h"
#include <iostream>

class BackgroundTexture {
public:
	BackgroundTexture(SDL_Color color);
	void draw(int xPos, int yPos, int width, int height);

private:
	SDL_Texture* backgroundTexture;
	SDL_Rect destRect;
	SDL_Color color;

	void createBackgroundTexture();
};