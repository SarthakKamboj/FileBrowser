#include "ImageView.h"

const std::vector<std::string> ImageView::supportImgFormats = { "png", "jpg", "jpeg", "PNG", "tiff", "webp" };

ImageView::ImageView(SDL_Renderer* inRenderer, int inWidth, int inHeight) : renderer(inRenderer),
width(inWidth), height(inHeight)
{
	imgCanvasTex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
	addBorderToTex();
}

ImageView::ImageView(const ImageView& other) : renderer(other.renderer), width(other.width),
height(other.height)
{
	imgCanvasTex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
	addBorderToTex();
}

ImageView& ImageView::operator=(const ImageView& other) {
	renderer = other.renderer;
	width = other.width;
	height = other.height;
	imgCanvasTex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
	addBorderToTex();
	return *this;
}

ImageView::~ImageView() {
	SDL_DestroyTexture(imgCanvasTex);
}

void ImageView::addBorderToTex() {
	SDL_Texture* prevTarget = SDL_GetRenderTarget(renderer);

	SDL_Color prevRenderColor;
	SDL_GetRenderDrawColor(renderer, &prevRenderColor.r, &prevRenderColor.g, &prevRenderColor.b, &prevRenderColor.a);

	SDL_SetRenderTarget(renderer, imgCanvasTex);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, NULL);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawLine(renderer, 0, 0, width, 0);
	SDL_RenderDrawLine(renderer, 0, 0, 0, height);
	SDL_RenderDrawLine(renderer, width - 2, 0, width - 2, height);
	SDL_RenderDrawLine(renderer, 0, height - 2, width, height - 2);

	SDL_SetRenderDrawColor(renderer, prevRenderColor.r, prevRenderColor.g, prevRenderColor.b, prevRenderColor.a);
	SDL_SetRenderTarget(renderer, prevTarget);
}

void ImageView::setFile(std::string inPath) {
	path = inPath;

	offsetX = 0;
	offsetY = 0;

	SDL_Texture* imgTex = Util::loadImage(path);

	SDL_Color prevColor = Util::getRenderDrawColor();

	SDL_Texture* prevTarget = SDL_GetRenderTarget(Application::GetRenderer());
	SDL_SetRenderTarget(renderer, imgCanvasTex);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_Rect destRect;
	SDL_QueryTexture(imgTex, NULL, NULL, &destRect.w, &destRect.h);

	scale = fmax(destRect.w / width, destRect.h / height);
	destRect.w *= scale;
	destRect.h *= scale;

	destRect.x = (width - destRect.w) / 2;
	destRect.y = (height - destRect.h) / 2;

	SDL_RenderCopy(renderer, imgTex, NULL, &destRect);

	SDL_SetRenderTarget(renderer, prevTarget);
	SDL_DestroyTexture(imgTex);

	Util::setRenderDrawColor(prevColor);
}

void ImageView::setScale(float inScale) {
	scale = inScale;
	SDL_Texture* imgTex = Util::loadImage(path);

	SDL_Color prevColor = Util::getRenderDrawColor();

	SDL_Texture* prevTarget = SDL_GetRenderTarget(Application::GetRenderer());
	SDL_SetRenderTarget(renderer, imgCanvasTex);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_Rect destRect;
	SDL_QueryTexture(imgTex, NULL, NULL, &destRect.w, &destRect.h);

	destRect.w *= scale;
	destRect.h *= scale;

	destRect.x = ((width - destRect.w) / 2) + offsetX;
	destRect.y = ((height - destRect.h) / 2) + offsetY;

	SDL_RenderCopy(renderer, imgTex, NULL, &destRect);

	SDL_SetRenderTarget(renderer, prevTarget);
	SDL_DestroyTexture(imgTex);

	Util::setRenderDrawColor(prevColor);
}


void ImageView::shiftImage(float xShift, float yShift) {
	offsetX += xShift;
	offsetY += yShift;
	setScale(scale);
}

float ImageView::getScale() {
	return scale;
}

void ImageView::render(int x, int y) {
	SDL_Rect dest = { x, y, width, height };
	SDL_RenderCopy(renderer, imgCanvasTex, NULL, &dest);
}


bool ImageView::isImage(std::string path) {
	int dotIdx = path.find_last_of(".");
	std::string ext = path.substr(dotIdx + 1);
	auto c = std::find(supportImgFormats.begin(), supportImgFormats.end(), ext);
	return c != supportImgFormats.end();
}
