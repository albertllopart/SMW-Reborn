#include "GuiImage.h"
#include "j1Render.h"

GuiImage::GuiImage() {};

GuiImage::GuiImage(iPoint position, SDL_Rect rect)
{
	this->position = position;
	this->rect = rect;
	etype = IMAGE;
}

GuiImage::~GuiImage() {};

void GuiImage::Draw()
{
	if (active)
	{
		App->render->Blit(App->gui->GetAtlas(), position.x, position.y, &rect);
	}
}