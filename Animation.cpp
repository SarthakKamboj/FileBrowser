#include "Animation.h"

Animation::Animation(std::string spriteSheetFilePath, int _numFrames, int _pixelsBetweenFrames, float _secPerFrame) :
	numFrames(_numFrames),
	pixelsBetweenFrame(_pixelsBetweenFrames), secPerFrame(_secPerFrame)
{
	spriteSheet = Util::loadImage(spriteSheetFilePath);
	SDL_QueryTexture(spriteSheet, NULL, NULL, &spriteSheetWidth, &spriteSheetHeight);

	animFrameWidth = (spriteSheetWidth - ((numFrames - 1) * pixelsBetweenFrame)) / numFrames;

	animFrameStartTime = SDL_GetTicks();
}

void Animation::update() {
	uint32_t time = SDL_GetTicks();
	if ((time - animFrameStartTime) >= secPerFrame * 1000) {
		curFrame = (curFrame + 1) % numFrames;
		animFrameStartTime = time;
	}
}

void Animation::render(int x, int y, float scale) {
	SDL_Rect spriteRect;
	spriteRect.x = ((animFrameWidth + pixelsBetweenFrame) * curFrame);
	spriteRect.y = 0;
	spriteRect.w = animFrameWidth;
	spriteRect.h = spriteSheetHeight;

	SDL_Rect rendererMapping;
	rendererMapping.x = x;
	rendererMapping.y = y;
	rendererMapping.w = animFrameWidth * scale;
	rendererMapping.h = spriteSheetHeight * scale;

	SDL_RenderCopy(Application::GetRenderer(), spriteSheet, &spriteRect, &rendererMapping);
}
