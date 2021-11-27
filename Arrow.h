#pragma once

#include <SDL.h>
#include "Util.h"

class Arrow {
public:
	Arrow(SDL_Renderer* renderer, int size);
	void draw(int xPos, int yPos);

	int getWidth();
	int getHeight();

private:
	SDL_Renderer* renderer;
	SDL_Texture* arrowTex;
	SDL_Rect arrowDestRect;

	int width;
	int height;
};
