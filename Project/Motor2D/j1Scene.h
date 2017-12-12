#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"
#include "GuiElement.h"

struct SDL_Texture;

class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	bool Save(pugi::xml_node& node)const;
	bool Load(pugi::xml_node& node);
	bool title_2 = false;

	void LoadLvl(int, bool);

	bool GuiTrigger(GuiElement* element);

	int current_lvl = 0;

private:

	bool exit_from_gui = false;
};

#endif // __j1SCENE_H__