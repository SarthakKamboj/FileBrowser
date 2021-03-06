#include "DirectoryViewManager.h"

SDL_Color DirectoryViewManager::pathLabelBckColor = { 117, 147, 14, 255 };
SDL_Color DirectoryViewManager::pathLabelColor = { 0, 0, 0, 255 };

DirectoryViewManager::DirectoryViewManager(int inWindowWidth, int inWindowHeight, Input* inInput) : windowWidth(inWindowWidth),
windowHeight(inWindowHeight),
input(inInput), imageView(ImageView(windowWidth * 0.75, windowHeight * 0.75)),
pathLabelBackgroundTexture(BackgroundTexture(pathLabelBckColor)),
pathLabel(Label("SpaceMono", "", pathLabelColor, windowWidth))
{
	activeDirectoryView = 0;
	error = false;
}

void DirectoryViewManager::update() {

	if (imageViewShow) {

		if (input->inputDown.leftCtrl) {
			imageView.setScale(imageView.getScale() + 0.1f);
		}
		if (input->inputDown.rightCtrl) {
			imageView.setScale(imageView.getScale() - 0.1f);
		}

		float shiftVal = 10;

		if (input->inputDown.left || input->inputDown.a) {
			imageView.shiftImage(-shiftVal, 0.0);
		}
		if (input->inputDown.right || input->inputDown.d) {
			imageView.shiftImage(shiftVal, 0.0);
		}

		if (input->inputDown.up || input->inputDown.w) {
			imageView.shiftImage(0, -shiftVal);
		}
		if (input->inputDown.down || input->inputDown.s) {
			imageView.shiftImage(0.0, shiftVal);
		}

		if (input->inputPressed.escape) {
			stopImageView();
		}

		return;
	}

	if (input->inputPressed.enter) {
		displayFileOrDir();
	}
	if (input->inputDown.a || input->inputDown.left) {
		moveActiveDirLeft();
	}
	if (input->inputDown.d || input->inputDown.right) {
		moveActiveDirRight();
	}
	if (input->inputDown.w || input->inputDown.up) {
		moveSelectionUp();
	}
	if (input->inputDown.s || input->inputDown.down) {
		moveSelectionDown();
	}

}

void DirectoryViewManager::moveActiveDirLeft() {
	activeDirectoryView = fmax(activeDirectoryView - 1, 0);
	updatePathLabelText();
}

void DirectoryViewManager::moveActiveDirRight() {
	activeDirectoryView = fmin(activeDirectoryView + 1, directoryViews.size() - 1);
	updatePathLabelText();
}

void DirectoryViewManager::moveSelectionDown() {
	DirectoryView& dv = directoryViews[activeDirectoryView];
	int cur = directoryViewSelections[activeDirectoryView];
	directoryViewSelections[activeDirectoryView] = fmin(cur + 1, dv.getNumFiles() - 1);
	updateActiveDirectoryView();
	updatePathLabelText();
}

void DirectoryViewManager::moveSelectionUp() {
	int cur = directoryViewSelections[activeDirectoryView];
	directoryViewSelections[activeDirectoryView] = fmax(cur - 1, 0);
	updateActiveDirectoryView();
	updatePathLabelText();
}

void DirectoryViewManager::updateActiveDirectoryView() {
	if (activeDirectoryView == directoryViews.size() - 1) {
		error = false;
		return;
	}
	directoryViews.erase(directoryViews.begin() + activeDirectoryView + 1, directoryViews.end());
	directoryViewSelections.erase(directoryViewSelections.begin() + activeDirectoryView + 1, directoryViewSelections.end());
	if (addChildDirectory()) {
		activeDirectoryView = directoryViews.size() - 2;
		error = false;
	}
	else {
		error = true;
	}

}

void DirectoryViewManager::updatePathLabelText() {
	pathLabel.setText(directoryViews[activeDirectoryView].getSelectionPath(directoryViewSelections[activeDirectoryView]));
}

bool DirectoryViewManager::addDirectoryView(std::string path) {

	int directoryWidth = windowWidth / (directoryViews.size() + 1);

	std::string fontName = "SpaceMono";
	int directoryPaddingXMultiplier = directoryViews.size() == 0 ? 0 : 1;
	DirectoryView directoryView(fontName, input, directoryWidth, true, directoryPaddingXMultiplier * 5);
	try {
		directoryView.setPathToDisplay(path);
	}
	catch (const std::exception& e) {

		std::cout << e.what() << std::endl;

		int directoryWidth = windowWidth / directoryViews.size();
		for (DirectoryView& directoryView : directoryViews) {
			directoryView.setWidth(directoryWidth);
		}
		return false;
	}

	directoryViews.push_back(directoryView);
	directoryViewSelections.push_back(0);

	activeDirectoryView = directoryViews.size() - 1;

	for (DirectoryView& directoryView : directoryViews) {
		directoryView.setWidth(directoryWidth);
	}

	updatePathLabelText();
	return true;
}

void DirectoryViewManager::displayFileOrDir() {
	std::string selectedPath = directoryViews[activeDirectoryView].getSelectionPath(directoryViewSelections[activeDirectoryView]);
	fs::file_type status = fs::status(selectedPath).type();
	if (status == fs::file_type::directory) {
		addChildDirectory();
	}
	else {
		if (ImageView::isImage(selectedPath)) {
			imageViewShow = true;
			imageView.setFile(selectedPath);
		}
	}
}

bool DirectoryViewManager::addChildDirectory() {
	int lastDirIdx = (int)(directoryViews.size() - 1);
	if (activeDirectoryView != lastDirIdx) return false;
	return addDirectoryView(directoryViews[lastDirIdx].getSelectionPath(directoryViewSelections[lastDirIdx]));
}

void DirectoryViewManager::render() {

	if (directoryViews.size() == 0) return;

	int startIdx = 0, endIdx = directoryViews.size() - 1;

	if (directoryViews.size() > maxVisibleDirectories) {
		if (activeDirectoryView == directoryViews.size() - 1) {
			endIdx = directoryViews.size() - 1;
			startIdx = endIdx - (maxVisibleDirectories - 1);
		}
		else if (activeDirectoryView < maxVisibleDirectories) {
			startIdx = 0;
			endIdx = maxVisibleDirectories - 1;
		}
		else {
			endIdx = activeDirectoryView + 1;
			startIdx = endIdx - (maxVisibleDirectories - 1);
		}
	}

	int directoryWidth = windowWidth / fmin(maxVisibleDirectories, directoryViews.size());
	for (int i = startIdx; i < endIdx + 1; i++) {

		int startX = (i - startIdx) * directoryWidth;
		DirectoryView& curDirView = directoryViews[i];

		curDirView.setWidth(directoryWidth);

		int curSelection = directoryViewSelections[i];

		if (i == activeDirectoryView) {
			std::string path = curDirView.getSelectionPath(curSelection);
			try {
				fs::file_status status = fs::status(path);
				fs::file_type f = status.type();

				if (f != fs::file_type::regular && f != fs::file_type::directory) {
					throw std::exception("not a regular file or directory");
				}

				if (f == fs::file_type::directory && !Util::isTraversable(path)) {
					throw std::exception("not traversable");
				}

				if (f == fs::file_type::regular && !ImageView::isImage(path)) {
					throw std::exception("not supported image file format");
				}

				curDirView.render(startX, 0, curSelection, false, f == fs::file_type::regular);
			}
			catch (const std::exception& exp) {
				curDirView.render(startX, 0, curSelection, true, false);
			}
		}
		else {
			curDirView.render(startX, 0, -1, false, false);
		}
	}

	if (imageViewShow) {
		imageView.render(windowWidth * 0.125, windowHeight * 0.125);
	}

	int pathLabelHeight = 30;
	int pathLabelY = Application::height - pathLabelHeight;
	pathLabelBackgroundTexture.draw(0, pathLabelY, Application::width, pathLabelHeight);
	pathLabel.draw(3, pathLabelY + 2);

}