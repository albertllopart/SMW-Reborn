#ifndef __j1APP_H__
#define __j1APP_H__

#include "p2List.h"
#include "j1Module.h"
#include "j1PerfTimer.h"
#include "j1Timer.h"
#include "PugiXml\src\pugixml.hpp"

// Modules
class j1Window;
class j1Input;
class j1Render;
class j1Textures;
class j1Audio;
class j1Scene;
class j1Map;
class j1Player;
class j1EntityModule;
class j1PathFinding;
class j1FadeToBlack;
class j1Collision;
class j1Gui;
class j1Fonts;

class j1App
{
public:

	// Constructor
	j1App(int argc, char* args[]);

	// Destructor
	virtual ~j1App();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update();

	// Called before quitting
	bool CleanUp();

	// Add a new module to handle
	void AddModule(j1Module* module);

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;
	float GetDT() const;

	bool LoadGame();
	bool SaveGame();
	void GetSaveGames(p2List<p2SString>& list_to_fill) const;

private:

	// Load config file
	pugi::xml_node LoadConfig(pugi::xml_document&) const;

	// Call modules before each loop iteration
	void PrepareUpdate();

	// Call modules before each loop iteration
	void FinishUpdate();

	// Call modules before each loop iteration
	bool PreUpdate();

	// Call modules on each loop iteration
	bool DoUpdate();

	// Call modules after each loop iteration
	bool PostUpdate();

	// Load / Save
	void LoadGameNow();
	void SavegameNow();

public:

	// Modules
	j1Window*			win;
	j1Input*			input;
	j1Render*			render;
	j1Textures*			tex;
	j1Audio*			audio;
	j1Scene*			scene;
	j1Map*				map;
	j1EntityModule*		entitymodule;
	j1PathFinding*		pathfinding;
	j1FadeToBlack*		fadetoblack;
	j1Collision*		collision;
	j1Gui*				gui;
	j1Fonts*			fonts;

private:

	p2List<j1Module*>	modules;

	int					argc;
	char**				args;

	p2SString			title;
	p2SString			organization;

	bool		        want_to_save = false;
	bool				want_to_save_audio = false;
	bool                want_to_save_player = false;
	bool				want_to_save_Entity = false;

	bool				want_to_load = false;
	bool				want_to_load_audio = false;
	bool				want_to_load_player = false;
	bool				want_to_load_Entity = false;

	p2SString			load_game;
	mutable p2SString	save_game;

	//timer related
	j1PerfTimer			ptimer;
	uint64				frame_count = 0;
	j1Timer				startup_time;
	j1Timer				frame_time;
	j1Timer				last_sec_frame_time;
	uint32				last_sec_frame_count = 0;
	uint32				prev_last_sec_frame_count = 0;
	float				dt = 0.0f;
	int					capped_ms = -1;

	p2SString			cap;
	p2SString			vsync;
};

extern j1App* App; // No student is asking me about that ... odd :-S

#endif