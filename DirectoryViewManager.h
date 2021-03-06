#pragma once

#include <vector>
#include "DirectoryView.h"
#include "Input.h"
#include "SDL.h"
#include "ImageView.h"
#include "BackgroundTexture.h"
#include "Util.h"
#include "Application.h"

namespace fs = std::filesystem;

class DirectoryViewManager {
public:
	DirectoryViewManager(int inWindowWidth, int inWindowHeight, Input* input);
	bool addDirectoryView(std::string path);
	void render();
	void update();
	void updateActiveDirectoryView();
	bool imageViewShow = false;

private:
	int windowWidth, windowHeight;
	Input* input;
	bool error;

	int maxVisibleDirectories = 3;

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