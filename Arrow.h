#pragma once

#include <SDL.h>
#include "Util.h"
#include "Application.h"

class Arrow {
public:
	Arrow(int size);
	void draw(int xPos, int yPos);

	int getWidth();
	int getHeight();

private:
	SDL_Texture* arrowTex;
	SDL_Rect arrowDestRect;

	int width;
	int height;
};
