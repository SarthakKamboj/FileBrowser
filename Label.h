#pragma once

#include <SDL.h>
#include "Util.h"
#include <iostream>
#include "Application.h"

class Label {
public:
	Label();
	Label(std::string fontName, std::string text, SDL_Color textColor, int maxWidth);
	Label(const Label& other);
	Label& operator=(const Label& other);

	~Label();

	void draw(int xPos, int yPos);

	int getHeight();
	int getWidth();
	std::string text;

	void updateRenderWidth();
	void setMaxWidth(int newMaxWidth);

	void setText(std::string newText);

private:
	SDL_Rect boundary;
	SDL_Rect srcRect;
	SDL_Texture* labelTexture;
	SDL_Color textColor;
	std::string fontName;

	int maxWidth;
	int textWidth;

	void copy(const Label& other);
	void createLabelTexture();

};
