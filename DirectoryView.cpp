#include "DirectoryView.h"

SDL_Color DirectoryView::dirDackgroundColor = { 11, 55, 65, 255 };
SDL_Color DirectoryView::errorBackgroundColor = { 203, 3, 1, 255 };
SDL_Color DirectoryView::fileBackgroundColor = { 38, 2, 53, 255 };
SDL_Color DirectoryView::textColor = { 150, 150, 150, 255 };

int DirectoryView::arrowFontSize = 9;

DirectoryView::DirectoryView(std::string& inFontName, Input* inInput, int inWidth, bool inActive)
	: fontName(inFontName),
	dirViewBackgroundTexture(BackgroundTexture(dirDackgroundColor)),
	errorBackgroundTexture(BackgroundTexture(errorBackgroundColor)),
	arrow(Arrow(arrowFontSize)), width(inWidth),
	fileViewBackgroundTexture(BackgroundTexture(fileBackgroundColor)),
	path(""), dirEmptyLabel(Label("SpaceMono", "Directory is empty", textColor))
{


	fileNames.clear();
	labels.clear();

	input = inInput;
}

std::string DirectoryView::getSelectionPath(int selectionIdx) {

	if (selectionIdx >= labels.size()) return "";

	Label& label = labels[selectionIdx];
	std::string newPath = path + "\\" + label.text;
	return newPath;
}

DirectoryView::DirectoryView(const DirectoryView& other) : fontName(other.fontName),
dirViewBackgroundTexture(BackgroundTexture(other.dirDackgroundColor)),
errorBackgroundTexture(BackgroundTexture(other.errorBackgroundColor)),
arrow(Arrow(arrowFontSize)), width(other.width),
input(other.input), fileViewBackgroundTexture(other.fileViewBackgroundTexture), path(other.path),
dirEmptyLabel(other.dirEmptyLabel)
{

	fileNames.clear();
	labels.clear();

	fileNames.resize(other.fileNames.size());
	labels.resize(other.labels.size());

	std::copy(other.fileNames.begin(), other.fileNames.end(), fileNames.begin());
	std::copy(other.labels.begin(), other.labels.end(), labels.begin());
}

DirectoryView::~DirectoryView() {}

void DirectoryView::setWidth(int newWidth) {
	width = newWidth;
}

void DirectoryView::setPathToDisplay(std::string& inPath) {

	cleanup();

	path = inPath;

	namespace fs = std::filesystem;

	try {
		for (const fs::directory_entry& entry : fs::directory_iterator(path)) {
			fs::path path = entry.path();
			std::string pathString = path.u8string();
			std::string fileName = pathString.substr(pathString.find_last_of("\\") + 1);
			fileNames.push_back(fileName);
		}
	}
	catch (const std::exception& e) {
		throw std::exception("folder not available");
	}

	labels.reserve(fileNames.size());
	for (unsigned i = 0; i < fileNames.size(); i++) {
		std::string& fileName = fileNames[i];
		Label label(fontName, fileName, textColor);
		labels.push_back(label);
	}
}

void DirectoryView::cleanup() {
	fileNames.clear();
	labels.clear();
}

int DirectoryView::getNumFiles() {
	return (int)fileNames.size();
}

std::string DirectoryView::getPath() {
	return path;
}

void DirectoryView::draw(int startX, int startY, int selectionIdx, bool error, bool viewingFile) {

	int labelPaddingLeft = 5;
	if (fileNames.size() == 0) {
		dirEmptyLabel.draw(startX + labelPaddingLeft, startY);
		return;
	}

	int arrowPaddingLeft = 5;

	int runningHeight = startY;

	int bottomPadding = 30;

	if (curSelectionBottomY > bottomOfScreen) {
		bottomOfScreen = curSelectionBottomY;
		topOfScreen = bottomOfScreen - Application::height + bottomPadding;
	}
	else if (curSelectionTopY < topOfScreen) {
		topOfScreen = curSelectionTopY;
		bottomOfScreen = topOfScreen + Application::height - bottomPadding;
	}

	for (unsigned i = 0; i < labels.size(); i++) {

		if (i == selectionIdx) {
			Label& selectedLabel = labels[selectionIdx];

			curSelectionTopY = runningHeight;
			curSelectionBottomY = runningHeight + selectedLabel.getHeight();

			int arrowX = startX + width - arrowPaddingLeft - arrow.getWidth();
			int arrowY = runningHeight + ((selectedLabel.getHeight() - arrow.getHeight()) / 2.0f);

			if (error) {
				errorBackgroundTexture.draw(startX, runningHeight - topOfScreen, width, selectedLabel.getHeight());
			}
			else if (viewingFile) {
				fileViewBackgroundTexture.draw(startX, runningHeight - topOfScreen, width, selectedLabel.getHeight());
			}
			else {
				dirViewBackgroundTexture.draw(startX, runningHeight - topOfScreen, width, selectedLabel.getHeight());
			}
			arrow.draw(arrowX, arrowY - topOfScreen);
		}

		Label& label = labels[i];

		int labelBottomY = runningHeight + label.getHeight();

		if (labelBottomY > bottomOfScreen) break;
		if (runningHeight >= topOfScreen) {
			label.draw(startX + labelPaddingLeft, runningHeight - topOfScreen);
		}

		runningHeight += label.getHeight();
	}

}

