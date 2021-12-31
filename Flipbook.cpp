#include "Flipbook.h" 

Flipbook::Flipbook(std::string folderFilePath, int _numFrames, float _secPerFrame) :
	numFrames(_numFrames),
	secPerFrame(_secPerFrame)
{
	if (numFrames == 0) return;

	for (int i = 1; i <= numFrames; i++) {
		std::string filePath = folderFilePath + "\\" + std::to_string(i) + ".png";
		SDL_Texture* texture = Util::loadImage(filePath);
		sprites.push_back(texture);
	}

	SDL_QueryTexture(sprites[0], NULL, NULL, &imageWidth, &imageHeight);

	animFrameStartTime = SDL_GetTicks();
}

void Flipbook::update() {
	uint32_t time = SDL_GetTicks();
	if ((time - animFrameStartTime) >= secPerFrame * 1000) {
		curFrame = (curFrame + 1) % numFrames;
		animFrameStartTime = time;
	}
}

void Flipbook::render(int x, int y, float scale) {
	SDL_Rect spriteRect;
	spriteRect.x = 0;
	spriteRect.y = 0;
	spriteRect.w = imageWidth;
	spriteRect.h = imageHeight;

	SDL_Rect rendererMapping;
	rendererMapping.x = x;
	rendererMapping.y = y;
	rendererMapping.w = imageWidth * scale;
	rendererMapping.h = imageHeight * scale;

	SDL_RenderCopy(Application::GetRenderer(), sprites[curFrame], &spriteRect, &rendererMapping);
}