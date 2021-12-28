#include "BackgroundTexture.h"

BackgroundTexture::BackgroundTexture(SDL_Color inColor) : color(inColor) {
	createBackgroundTexture();
}

void BackgroundTexture::createBackgroundTexture() {
	SDL_Renderer* renderer = Application::GetRenderer();

	Uint8 r, g, b, a;
	SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);

	SDL_Texture* prevTarget = SDL_GetRenderTarget(renderer);

	int width = 1;
	int height = 1;

	backgroundTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
	SDL_SetRenderTarget(renderer, backgroundTexture);
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(renderer);

	SDL_SetRenderTarget(renderer, prevTarget);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	SDL_SetTextureBlendMode(backgroundTexture, SDL_BlendMode::SDL_BLENDMODE_NONE);
}

void BackgroundTexture::draw(int xPos, int yPos, int inWidth, int inHeight) {
	destRect.x = xPos;
	destRect.y = yPos;
	destRect.w = inWidth;
	destRect.h = inHeight;

	SDL_RenderCopy(Application::GetRenderer(), backgroundTexture, NULL, &destRect);
}