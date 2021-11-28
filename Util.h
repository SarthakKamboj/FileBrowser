#pragma once

#include <map>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <format>
#include <filesystem>
#include "Application.h"

class Util {
public:
	static SDL_Texture* loadImage(std::string& path);
	static void addFont(std::string fontName, std::string& path, int fontSize);
	static SDL_Texture* getText(std::string fontName, std::string text, SDL_Color color);
	static bool isSameColor(SDL_Color c1, SDL_Color c2);
	static SDL_Color getTransparentColor();
	static bool isTraversable(std::string path);
	static SDL_Color getRenderDrawColor();
	static void setRenderDrawColor(SDL_Color color);

private:
	static std::map<std::string, TTF_Font*> fontMap;
};
