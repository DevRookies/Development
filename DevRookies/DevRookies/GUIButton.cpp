#include "DevRookiesApp.h"
#include "GUIButton.h"
#include "p2Log.h"
#include "Textures.h"
#include "Render.h"

#include "Brofiler\Brofiler.h"


GUIButton::GUIButton(iPoint pos) : GUIElement(GUI_Type::BUTTON)
{
}

GUIButton::~GUIButton()
{}


bool GUIButton::Awake(pugi::xml_node & conf)
{
	bool ret = false;

	pugi::xml_node config = conf.child("GUIImage");

	tex = config.child("texture").child_value();

	return ret;
}

bool GUIButton::Start()
{
	bool ret = false;

	texture = App->textures->Load(tex.GetString());

	return ret;
}

bool GUIButton::CleanUp()
{
	bool ret = false;

	if (texture != nullptr)
		App->textures->UnLoad(texture);
	to_delete = true;

	return ret;
}

bool GUIButton::Update(float dt)
{
	bool ret = false;


	return ret;
}

bool GUIButton::PostUpdate()
{
	bool ret = false;

	App->render->Blit(texture, position.x, position.y, &rect);

	return ret;
}

void GUIButton::PrintText() {

}
