#pragma once

#include "SDL.h"
#include <string>
#include <iostream>
#include "Util.h"
#include "Application.h"

class Animation {
public:
	Animation(std::string spriteSheetFilePath, int numFrames, int pixelsBetweenFrame, float secPerFrame);

	void update();
	void render(int x, int y, float scale);

	int animFrameWidth;

private:
	SDL_Texture* spriteSheet;
	int pixelsBetweenFrame;
	float secPerFrame;

	uint32_t animFrameStartTime;

	int numFrames;
	int curFrame = 0;
	int spriteSheetWidth, spriteSheetHeight;
};
