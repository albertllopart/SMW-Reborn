#ifndef _j1ANIMATION_H_
#define _j1ANIMATION_H_

#include "SDL/include/SDL_rect.h"
#define FRAMES 15

class Animation
{
public:

	float				speed = 0.15f;
	SDL_Rect			frames[FRAMES];

private:

	float				current_frame;
	int					last_frame = 0;

public:

	void PushBack(const SDL_Rect& rect)
	{
		frames[last_frame++] = rect;
	}

	SDL_Rect& GetCurrentFrame()
	{
		current_frame += speed;
		if (current_frame >= last_frame)
		{
			current_frame = 0;
		}
		return frames[(int)current_frame];
	}

};

#endif

