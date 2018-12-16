#pragma once

#include <SDL.h>

namespace ENG
{
	class Clock
	{
	public:
		Clock(const int fps_limit);
		Clock();
		int getFPSLimit() const;
		void setFPSLimit(const int fps_limit);
		float update();

	private:
		int fps_limit = 0;
		int current = 0;
		int last = 0;
		int frame = 0;
		float delta = 0.0f;
	};
}