#include "Arrow.h"

Arrow::Arrow(SDL_Renderer* inRenderer, int size) : renderer(inRenderer) {

	std::string arrowPath = "arrow.png";
	arrowTex = Util::loadImage(renderer, arrowPath);
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
	SDL_RenderCopy(renderer, arrowTex, NULL, &arrowDestRect);
}

int Arrow::getWidth() {
	return width;
}

int Arrow::getHeight() {
	return height;
}
