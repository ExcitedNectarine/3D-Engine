#include "Clock.h"

namespace ENG
{
	Clock::Clock(const int fps_limit)
		: fps_limit(fps_limit)
	{
	}

	Clock::Clock()
	{
	}

	int Clock::getFPSLimit() const
	{
		return fps_limit;
	}

	void Clock::setFPSLimit(const int fps_limit)
	{
		this->fps_limit = fps_limit;
	}

	float Clock::update()
	{
		last = current;
		current = SDL_GetTicks();
		frame = current - last;

		if ((1000.0 / fps_limit) > frame)
		{
			SDL_Delay(static_cast<Uint32>((1000.0 / fps_limit) - frame));
		}

		delta = static_cast<float>(frame / 1000.0);

		return delta;
	}
}