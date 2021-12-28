#include "ImageView.h"

const std::vector<std::string> ImageView::supportImgFormats = { "png", "jpg", "jpeg", "PNG", "tiff", "webp" };

ImageView::ImageView(int inCanvasWidth, int inCanvasHeight) : canvasWidth(inCanvasWidth), canvasHeight(inCanvasHeight)
{
	createCanvas(inCanvasWidth, inCanvasHeight);
}

ImageView::ImageView(const ImageView& other) : canvasWidth(other.canvasWidth), canvasHeight(other.canvasHeight)
{
	createCanvas(other.canvasWidth, other.canvasHeight);
}


ImageView& ImageView::operator=(const ImageView& other) {
	createCanvas(other.canvasWidth, other.canvasHeight);
	return *this;
}


void ImageView::createCanvas(float inWidth, float inHeight) {
	canvasWidth = inWidth;
	canvasHeight = inHeight;
	canvasTex = SDL_CreateTexture(Application::GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, canvasWidth, canvasHeight);
}

ImageView::~ImageView() {
	SDL_DestroyTexture(canvasTex);
}

void ImageView::addBorderToTex() {
	SDL_Renderer* renderer = Application::GetRenderer();

	SDL_Texture* prevTarget = SDL_GetRenderTarget(renderer);

	SDL_Color prevRenderColor;
	SDL_GetRenderDrawColor(renderer, &prevRenderColor.r, &prevRenderColor.g, &prevRenderColor.b, &prevRenderColor.a);

	SDL_SetRenderTarget(renderer, canvasTex);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, NULL);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawLine(renderer, 0, 0, canvasWidth, 0);
	SDL_RenderDrawLine(renderer, 0, 0, 0, canvasHeight);
	SDL_RenderDrawLine(renderer, canvasWidth - 2, 0, canvasWidth - 2, canvasHeight);
	SDL_RenderDrawLine(renderer, 0, canvasHeight - 2, canvasWidth, canvasHeight - 2);

	SDL_SetRenderDrawColor(renderer, prevRenderColor.r, prevRenderColor.g, prevRenderColor.b, prevRenderColor.a);
	SDL_SetRenderTarget(renderer, prevTarget);
}

void ImageView::setFile(std::string inPath) {

	if (origImageTex != NULL) {
		SDL_DestroyTexture(origImageTex);
	}

	SDL_Renderer* renderer = Application::GetRenderer();
	path = inPath;

	offsetX = 0;
	offsetY = 0;

	origImageTex = Util::loadImage(path);

	SDL_QueryTexture(origImageTex, NULL, NULL, &origImage.w, &origImage.h);
	scale = fmax(((float)canvasWidth) / origImage.w, ((float)canvasHeight) / origImage.h) * 0.75f;

	updateCanvasImage();

}

void ImageView::setScale(float inScale) {
	SDL_Renderer* renderer = Application::GetRenderer();
	scale = inScale;

	updateCanvasImage();

}

void ImageView::updateCanvasImage() {

	SDL_Renderer* renderer = Application::GetRenderer();

	SDL_Color prevRenderColor = Util::getRenderDrawColor();
	SDL_Texture* prevTarget = SDL_GetRenderTarget(Application::GetRenderer());

	SDL_SetRenderTarget(renderer, canvasTex);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_Rect canvasMapping;
	canvasMapping.w = origImage.w * scale;
	canvasMapping.h = origImage.h * scale;

	canvasMapping.x = ((canvasWidth - canvasMapping.w) / 2) + offsetX;
	canvasMapping.y = ((canvasHeight - canvasMapping.h) / 2) + offsetY;

	SDL_RenderCopy(renderer, origImageTex, NULL, &canvasMapping);

	SDL_SetRenderTarget(renderer, prevTarget);
	SDL_SetRenderDrawColor(renderer, prevRenderColor.r, prevRenderColor.g, prevRenderColor.b, prevRenderColor.a);
}

void ImageView::shiftImage(float xShift, float yShift) {
	offsetX += xShift;
	offsetY += yShift;
	updateCanvasImage();
}

float ImageView::getScale() {
	return scale;
}

void ImageView::render(int x, int y) {
	SDL_Renderer* renderer = Application::GetRenderer();
	SDL_Rect dest = { x, y, canvasWidth, canvasHeight };
	SDL_RenderCopy(renderer, canvasTex, NULL, &dest);
}


bool ImageView::isImage(std::string path) {
	int dotIdx = path.find_last_of(".");
	std::string ext = path.substr(dotIdx + 1);
	auto c = std::find(supportImgFormats.begin(), supportImgFormats.end(), ext);
	return c != supportImgFormats.end();
}
