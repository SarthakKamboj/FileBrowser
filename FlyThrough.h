#pragma once

#include "Input.h"
#include "Flipbook.h"

extern std::string exeFolderPath;

class FlyThrough {
public:
	FlyThrough(Input* input);
	void update();
	void render();

private:
	std::string folderPath = exeFolderPath + "\\images\\genie";
	bool active = false;
	Input* input;
	Flipbook flipBook;

	int startX = 0, startY = 100;
	int offsetX = 0;

	int speed = 7;
	float scale = 1.5f;
};
