#include "Arrow.h"

Arrow::Arrow(int size) {

	std::string arrowPath = "images/arrow.png";
	arrowTex = Util::loadImage(arrowPath);
	int arrowWidth, arrowHeight;
	SDL_QueryTexture(arrowTex, NULL, NULL, &arrowWidth, &arrowHeight);

	arrowDestRect.w = size;
	arrowDestRect.h = arrowHeight * (((float)size) / arrowWidth);

	width = arrowDestRect.w;
	height = arrowDestRect.h;
}

void Arrow::draw(int xPos, int yPos) {
	arrowDestRect.x = xPos;
	arrowDestRect.y = yPos;
	SDL_RenderCopy(Application::GetRenderer(), arrowTex, NULL, &arrowDestRect);
}

int Arrow::getWidth() {
	return width;
}

int Arrow::getHeight() {
	return height;
}
