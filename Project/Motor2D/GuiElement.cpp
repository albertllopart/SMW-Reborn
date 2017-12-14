#include "GuiElement.h"
#include "j1App.h"
#include "j1Gui.h"
#include "j1Render.h"

GuiElement::GuiElement() {};

GuiElement::~GuiElement() {};

void GuiElement::Start() {};

void GuiElement::Update(float dt)
{

};

void GuiElement::Draw() {};

void GuiElement::OnClick() {};

void GuiElement::PositionUpdate()
{
	iPoint fakeposition;
	fakeposition.create(position.x - (App->render->camera.x * 0.5f), position.y);
	position_camera = fakeposition;
}