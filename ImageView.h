#pragma once

#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "Util.h"
#include <vector>
#include "Application.h"

class ImageView {
public:
	ImageView(SDL_Renderer* inRenderer, int width, int height);
	ImageView(const ImageView& other);
	ImageView& operator=(const ImageView& other);
	~ImageView();

	void setFile(std::string path);
	void setScale(float scale);

	void render(int x, int y);

	static bool isImage(std::string path);

	float getScale();

private:
	SDL_Texture* imgCanvasTex;
	SDL_Renderer* renderer;
	int width, height;
	std::string path;
	static const std::vector<std::string> supportImgFormats;

	float scale = 1.0f;

	void addBorderToTex();
};