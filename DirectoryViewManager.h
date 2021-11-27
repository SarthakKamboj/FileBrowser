#pragma once

#include <vector>
#include "DirectoryView.h"
#include "Input.h"
#include "SDL.h"
#include "ImageView.h"
#include "BackgroundTexture.h"
#include "Util.h"

namespace fs = std::filesystem;

class DirectoryViewManager {
public:
	DirectoryViewManager(int inWindowWidth, int inWindowHeight, SDL_Renderer* inRenderer, Input* input);
	~DirectoryViewManager();
	bool addDirectoryView(std::string path);
	void drawDirectories();
	void updateActiveDirectoryView();

private:
	int windowWidth, windowHeight;
	SDL_Renderer* renderer;
	Input* input;
	bool error;
	bool imageViewShow = false;

	std::vector<DirectoryView> directoryViews;
	std::vector<int> directoryViewSelections;

	ImageView imageView;

	void stopImageView() { imageViewShow = false; }

	bool addChildDirectory();
	void displayFileOrDir();

	int displayFileOrDirId, moveActiveDirLeftId, moveActiveDirRightId, moveSelectionDownId, moveSelectionUpId;
	int endImgViewId;
	int activeDirectoryView;

	void moveActiveDirLeft();
	void moveActiveDirRight();
	void moveSelectionDown();
	void moveSelectionUp();

	void updatePathLabelText();

	static SDL_Color pathLabelBckColor;
	static SDL_Color pathLabelColor;
	BackgroundTexture pathLabelBackgroundTexture;
	Label pathLabel;

};