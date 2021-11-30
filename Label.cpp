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
	// SDL_QueryTexture(labelTexture, NULL, NULL, &boundary.w, &boundary.h);

}

void Label::setMaxWidth(int newMaxWidth) {
	maxWidth = newMaxWidth;
	updateRenderWidth();
}

void Label::updateRenderWidth() {
	SDL_QueryTexture(labelTexture, NULL, NULL, &textWidth, &boundary.h);
	boundary.w = fmin(maxWidth, textWidth);
	srcRect.w = boundary.w;
	srcRect.h = boundary.h;
}

/*
void Label::createLabelTexture() {
	SDL_Texture* textTexture = Util::getText(renderer, fontName, text, textColor);
	SDL_QueryTexture(textTexture, NULL, NULL, &boundary.w, &boundary.h);

	labelTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, boundary.w, boundary.h);
	SDL_Color prevColor = Util::getRenderDrawColor(renderer);
	SDL_Texture* prevTarget = SDL_GetRenderTarget(renderer);

	SDL_SetRenderDrawColor(renderer, 2, 43, 53, 255);
	SDL_SetRenderTarget(renderer, labelTexture);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, textTexture, NULL, NULL);

	Util::setRenderDrawColor(renderer, prevColor);
	SDL_SetRenderTarget(renderer, prevTarget);

	SDL_DestroyTexture(textTexture);
}
*/

/*
void Label::createLabelTexture() {
	SDL_Texture* prevTarget = SDL_GetRenderTarget(renderer);

	labelTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, boundary.w, boundary.h);

	SDL_SetRenderTarget(renderer, labelTexture);

	SDL_SetTextureBlendMode(labelTexture, SDL_BlendMode::SDL_BLENDMODE_NONE);
	SDL_RenderCopy(renderer, transparentTex, NULL, NULL);
	SDL_SetTextureBlendMode(labelTexture, SDL_BlendMode::SDL_BLENDMODE_BLEND);

	SDL_RenderCopy(renderer, other.labelTexture, NULL, NULL);
	SDL_SetTextureBlendMode(labelTexture, SDL_BlendMode::SDL_BLENDMODE_NONE);
	SDL_SetRenderTarget(renderer, prevTarget);
}
*/

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
	// SDL_RenderCopy(Application::GetRenderer(), labelTexture, NULL, &boundary);
	SDL_RenderCopy(Application::GetRenderer(), labelTexture, &srcRect, &boundary);
}
