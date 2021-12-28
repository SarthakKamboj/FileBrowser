#pragma once

#include "SDL.h"
#include <vector>
#include <map>
#include <functional>
#include <iostream>

class Input {

	struct InputState {
		bool enter, w, a, s, d, up, right, left, down;
		bool escape, leftCtrl, rightCtrl, equals, plus;
	};

public:
	Input(bool& running);
	void update();
	InputState inputPressed;

private:

	bool& running;

};