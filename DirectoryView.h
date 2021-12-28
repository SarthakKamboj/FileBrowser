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
	DirectoryView(std::string& inFontName, Input* input, int width, bool active, int inDirectoryViewPaddingX);
	DirectoryView(const DirectoryView& other);
	~DirectoryView();
	void setPathToDisplay(std::string& path);
	std::string getSelectionPath(int selectionIdx);
	std::string getPath();
	void setWidth(int newWidth);
	void render(int startX, int startY, int selectionIdx, bool error, bool viewingFile);
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
	int directoryViewPaddingX;

	std::string path;

	static SDL_Color dirDackgroundColor;
	static SDL_Color errorBackgroundColor;
	static SDL_Color fileBackgroundColor;
	static int arrowFontSize;

	int width;
	int labelWidth;

	void cleanup();

	int curSelectionBottomY = 0;
	int curSelectionTopY = 0;
	int topOfScreen = 0;
	int bottomOfScreen = 600;

	void updatePath();
};