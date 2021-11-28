#include "BackgroundTexture.h"

BackgroundTexture::BackgroundTexture(SDL_Color inColor) : color(inColor) {
	width = 10;
	height = 10;

	createBackgroundTexture();
}

BackgroundTexture::BackgroundTexture(int inWidth, int inHeight, SDL_Color inColor) : width(inWidth), height(inHeight), color(inColor) {
	createBackgroundTexture();
}

void BackgroundTexture::createBackgroundTexture() {
	Uint8 r, g, b, a;
	SDL_GetRenderDrawColor(Application::GetRenderer(), &r, &g, &b, &a);

	SDL_Renderer* renderer = Application::GetRenderer();

	SDL_Texture* prevTarget = SDL_GetRenderTarget(renderer);

	backgroundTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
	SDL_SetRenderTarget(renderer, backgroundTexture);
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(renderer);

	SDL_SetRenderTarget(renderer, prevTarget);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	destRect.w = width;
	destRect.h = height;

	SDL_SetTextureBlendMode(backgroundTexture, SDL_BlendMode::SDL_BLENDMODE_NONE);
}

void BackgroundTexture::draw(int xPos, int yPos) {
	destRect.x = xPos;
	destRect.y = yPos;

	SDL_RenderCopy(Application::GetRenderer(), backgroundTexture, NULL, &destRect);
}

void BackgroundTexture::draw(int xPos, int yPos, int inWidth, int inHeight) {
	destRect.x = xPos;
	destRect.y = yPos;
	destRect.w = inWidth;
	destRect.h = inHeight;

	SDL_RenderCopy(Application::GetRenderer(), backgroundTexture, NULL, &destRect);
}