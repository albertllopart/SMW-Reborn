#ifndef _j1ANIMATION_H_
#define _j1ANIMATION_H_

#include "SDL/include/SDL_rect.h"
#include "j1App.h"
#define FRAMES 50

class Animation
{
public:

	float				speed = 10.0f;
	SDL_Rect			frames[FRAMES];

private:

	float				current_frame = 1;
	int					last_frame = 0;

public:

	void PushBack(const SDL_Rect& rect)
	{
		frames[last_frame++] = rect;
	}

	SDL_Rect& GetCurrentFrame()
	{
		current_frame = current_frame + speed * App->GetDT();
		if (current_frame >= last_frame)
		{
			current_frame = 0;
		}
		return frames[(int)current_frame];
	}

};

#endif

