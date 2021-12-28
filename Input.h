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

		void setAllTrue() {
			enter = true;
			w = true;
			a = true;
			s = true;
			d = true;
			up = true;
			right = true;
			left = true;
			down = true;
			escape = true;
			leftCtrl = true;
			rightCtrl = true;
			equals = true;
			plus = true;
		}
	};

public:
	Input(bool& running);
	void update();
	InputState inputDown;
	InputState inputPressed;

private:

	InputState validToBePressed;
	bool& running;

};