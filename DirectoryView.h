#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <SDL.h>
#include "Util.h"
#include "BackgroundTexture.h"
#include "Arrow.h"
#include "Input.h"
#include "Label.h"
#include <functional>
#include "Application.h"

class DirectoryView {

public:
	DirectoryView(std::string& inFontName, Input* input, int width, bool active);
	DirectoryView(const DirectoryView& other);
	~DirectoryView();
	void setPathToDisplay(std::string& path);
	std::string getSelectionPath(int selectionIdx);
	std::string getPath();
	void setWidth(int newWidth);
	void draw(int startX, int startY, int selectionIdx, bool error, bool viewingFile);
	int getNumFiles();

private:
	std::vector<std::string> fileNames;
	std::vector<Label> labels;
	std::string fontName;
	BackgroundTexture dirViewBackgroundTexture;
	BackgroundTexture errorBackgroundTexture;
	BackgroundTexture fileViewBackgroundTexture;
	Arrow arrow;
	Input* input;

	Label dirEmptyLabel;

	static SDL_Color textColor;


	std::string path;

	static SDL_Color dirDackgroundColor;
	static SDL_Color errorBackgroundColor;
	static SDL_Color fileBackgroundColor;

	int width;

	void cleanup();

	int curSelectionBottomY = 0;
	int curSelectionTopY = 0;
	int topOfScreen = 0;
	int bottomOfScreen = 600;

	void updatePath();
};