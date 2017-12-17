#ifndef __j1AUDIO_H__
#define __j1AUDIO_H__

#include "j1Module.h"
#include "SDL_mixer\include\SDL_mixer.h"
#include "p2List.h"

#define DEFAULT_MUSIC_FADE_TIME 2.0f
#define MAX_CHANNELS 32

struct _Mix_Music;
struct Mix_Chunk;

class j1Audio : public j1Module
{
public:

	j1Audio();

	// Destructor
	virtual ~j1Audio();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before quitting
	bool CleanUp();

	// Play a music file
	bool PlayMusic(const char* path, float fade_time = DEFAULT_MUSIC_FADE_TIME);

	// Load a WAV in memory
	unsigned int LoadFx(const char* path);

	// Play a previously loaded WAV
	bool PlayFx(unsigned int fx, int repeat = 0);

	void MusicUp();
	void MusicDown();
	void FxUp();
	void FxDown();

	bool GuiTrigger(GuiElement* element);

	private:

	uint				music_volume = 96;//possible volumes: 0, 32, 64, 96, 128
	uint				fx_volume = 128;

	_Mix_Music*			music = nullptr;
	p2List<Mix_Chunk*>	fx;
};

#endif // __j1AUDIO_H__