#include "Util.h"

std::map<std::string, TTF_Font*> Util::fontMap;

SDL_Texture* Util::loadImage(SDL_Renderer* renderer, std::string& path) {
	SDL_Surface* imgSurface = IMG_Load(path.c_str());
	SDL_Texture* imgTex = SDL_CreateTextureFromSurface(renderer, imgSurface);
	SDL_FreeSurface(imgSurface);
	return imgTex;
}

void Util::addFont(std::string fontName, std::string& path, int fontSize) {
	TTF_Font* font = TTF_OpenFont(path.c_str(), fontSize);
	fontMap.emplace(fontName, font);
}


bool Util::isSameColor(SDL_Color c1, SDL_Color c2) {
	return (c1.r == c2.r) && (c1.g == c2.g) && (c1.b == c2.b) && (c1.a == c2.a);
}

bool Util::isTraversable(std::string path) {
	namespace fs = std::filesystem;
	try {
		for (const fs::directory_entry& entry : fs::directory_iterator(path)) {
			return true;
		}
	}
	catch (const std::exception& e) {
		return false;
	}
}


SDL_Color Util::getRenderDrawColor(SDL_Renderer* renderer) {
	SDL_Color col;
	SDL_GetRenderDrawColor(renderer, &col.r, &col.g, &col.b, &col.a);
	return col;
}


void Util::setRenderDrawColor(SDL_Renderer* renderer, SDL_Color color) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

SDL_Color Util::getTransparentColor() {

	static bool loaded = false;
	static SDL_Color transparentColor;

	if (loaded) {
		return transparentColor;
	}

	std::string path = "transparent.png";
	SDL_Surface* imgSurface = IMG_Load(path.c_str());

	char* pixels = (char*)imgSurface->pixels;

	SDL_GetRGBA((Uint32)*pixels, imgSurface->format, &transparentColor.r, &transparentColor.g, &transparentColor.b, &transparentColor.a);

	loaded = true;

	SDL_FreeSurface(imgSurface);

	return transparentColor;

}

SDL_Texture* Util::getText(SDL_Renderer* renderer, std::string fontName, std::string text, SDL_Color color) {

	TTF_Font* font = fontMap[fontName];
	SDL_Surface* fontSurface = TTF_RenderText_Blended(font, text.c_str(), color);

	SDL_Texture* fontTexture = SDL_CreateTextureFromSurface(renderer, fontSurface);
	SDL_FreeSurface(fontSurface);

	return fontTexture;
}