#include "FlyThrough.h"

FlyThrough::FlyThrough(Input* _input, SoundEffectManager* _soundEffectManager) : input(_input),
flipBook(Flipbook(folderPath, 14, 1.0f / 24.0f)), soundEffectManager(_soundEffectManager)
{
	startX = -flipBook.imageWidth * scale;
	soundEffectManager->addSoundEffect("background", exeFolderPath + "\\audio\\rick_rolls.wav");
}

void FlyThrough::update() {
	if (input->inputPressed.space && !active) {
		active = true;
		offsetX = 0;
		soundEffectManager->playSoundEffect("background");
	}

	if (active) {
		flipBook.update();
		offsetX += speed;

		if (startX + offsetX > Application::width) {
			active = false;
			soundEffectManager->stopSoundEffects();
		}
	}
}

void FlyThrough::render() {
	if (active) {
		flipBook.render(startX + offsetX, startY, scale);
	}
}