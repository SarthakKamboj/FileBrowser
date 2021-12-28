#include "Label.h"

Label::Label() : fontName("SpaceMono"), text("uninitialized label") {}

Label::Label(std::string inFontName, std::string inText, SDL_Color inTextColor, int inMaxWidth) :
	fontName(inFontName), text(inText), textColor(inTextColor), maxWidth(inMaxWidth) {
	srcRect.x = 0;
	srcRect.y = 0;
	createLabelTexture();
}

void Label::setText(std::string newText) {
	text = newText;
	SDL_DestroyTexture(labelTexture);
	createLabelTexture();
}

void Label::createLabelTexture() {
	labelTexture = Util::getText(fontName, text, textColor);
	updateRenderWidth();

}

void Label::setMaxWidth(int newMaxWidth) {
	maxWidth = newMaxWidth;
	updateRenderWidth();
}

void Label::updateRenderWidth() {
	int textWidth = 0;
	SDL_QueryTexture(labelTexture, NULL, NULL, &textWidth, &boundary.h);
	boundary.w = fmin(maxWidth, textWidth);
	srcRect.w = boundary.w;
	srcRect.h = boundary.h;
}

Label::Label(const Label& other) : fontName(other.fontName), text(other.text) {
	copy(other);
}

Label& Label::operator=(const Label& other) {
	fontName = other.fontName;
	text = other.text;
	copy(other);
	return *this;
}


int Label::getHeight() {
	return boundary.h;
}

int Label::getWidth() {
	return boundary.w;
}

void Label::copy(const Label& other) {
	boundary = other.boundary;
	textColor = other.textColor;
	maxWidth = other.maxWidth;
	srcRect.x = 0;
	srcRect.y = 0;
	createLabelTexture();
}

Label::~Label() {
	SDL_DestroyTexture(labelTexture);
}

void Label::draw(int xPos, int yPos) {
	boundary.x = xPos;
	boundary.y = yPos;
	SDL_RenderCopy(Application::GetRenderer(), labelTexture, &srcRect, &boundary);
}
