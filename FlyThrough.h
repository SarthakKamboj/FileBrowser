#pragma once

#include "Input.h"
#include "Flipbook.h"
#include "SoundEffectManager.h"

extern std::string exeFolderPath;

class FlyThrough {
public:
	FlyThrough(Input* input, SoundEffectManager* soundEffectManager);
	void update();
	void render();

private:
	std::string folderPath = exeFolderPath + "\\images\\rick_roller";
	bool active = false;
	Input* input;
	SoundEffectManager* soundEffectManager;
	Flipbook flipBook;

	int startX = 0, startY = 100;
	int offsetX = 0;

	int speed = 5;
	float scale = 1;
};
