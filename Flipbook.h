#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "SDL.h"
#include "Util.h"

class Flipbook {
public:
	Flipbook(std::string folderPath, int numFrames, float secPerFrame);

	void update();
	void render(int x, int y, float scale);

	int imageWidth, imageHeight;

private:
	std::vector<SDL_Texture*> sprites;

	float secPerFrame;

	uint32_t animFrameStartTime;

	int numFrames;
	int curFrame = 0;
};
