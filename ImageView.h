#pragma once

#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "Util.h"
#include <vector>
#include "Application.h"

class ImageView {
public:
	ImageView(int canvasWidth, int canvasHeight);
	ImageView(const ImageView& other);
	ImageView& operator=(const ImageView& other);
	~ImageView();

	void setFile(std::string path);
	void setScale(float scale);
	void shiftImage(float xShift, float yShift);

	void render(int x, int y);

	static bool isImage(std::string path);

	float getScale();

private:
	SDL_Texture* canvasTex;
	SDL_Rect origImage;
	SDL_Texture* origImageTex;

	int canvasWidth, canvasHeight;
	std::string path;
	static const std::vector<std::string> supportImgFormats;

	float scale = 1.0f;
	float offsetX = 0, offsetY = 0;

	void addBorderToTex();

	void createCanvas(float width, float height);
	void updateCanvasImage();
};