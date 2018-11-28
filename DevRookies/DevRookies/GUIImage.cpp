#include "DevRookiesApp.h"
#include "GUIImage.h"
#include "p2Log.h"
#include "Textures.h"
#include "Render.h"

#include "Brofiler\Brofiler.h"


GUIImage::GUIImage(iPoint pos): GUIElement(GUI_Type::IMAGE)
{
}

GUIImage::~GUIImage()
{}


bool GUIImage::Awake(pugi::xml_node & conf)
{
	bool ret = false;

	pugi::xml_node config = conf.child("GUIImage");

	tex = config.child("texture").child_value();
	
	return ret;
}

bool GUIImage::Start()
{
	bool ret = false;

	texture = App->textures->Load(tex.GetString());

	return ret;
}

bool GUIImage::CleanUp()
{
	bool ret = false;

	if (texture != nullptr)
		App->textures->UnLoad(texture);
	to_delete = true;

	return ret;
}

bool GUIImage::Update(float dt)
{
	bool ret = false;


	return ret;
}

bool GUIImage::PostUpdate()
{
	bool ret = false;

	App->render->Blit(texture, position.x, position.y, &rect);

	return ret;
}
