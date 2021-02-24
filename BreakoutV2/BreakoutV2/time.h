#pragma once
#include "SDL.h"

namespace timess
{

	inline float recordTime() {

		float t = SDL_GetTicks();
		t *= 0.001f;

		return t;

	}

}



