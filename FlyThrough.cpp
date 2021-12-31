#include "FlyThrough.h"

FlyThrough::FlyThrough(Input* _input) : input(_input),
flipBook(Flipbook(folderPath, 31, 1.0f / 24.0f))
{
	startX = -flipBook.imageWidth * scale;
}

void FlyThrough::update() {
	if (input->inputPressed.space && !active) {
		active = true;
		offsetX = 0;
	}

	if (active) {
		flipBook.update();
		offsetX += speed;

		if (startX + offsetX > Application::width) {
			active = false;
		}
	}
}

void FlyThrough::render() {
	if (active) {
		flipBook.render(startX + offsetX, startY, scale);
	}
}