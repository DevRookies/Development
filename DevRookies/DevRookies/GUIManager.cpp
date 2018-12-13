#include "p2Defs.h"
#include "p2Log.h"
#include "DevRookiesApp.h"
#include "Render.h"
#include "Textures.h"
#include "Input.h"
#include "GUIManager.h"
#include "GUIElement.h"
#include "GUIImage.h"
#include "GUIButton.h"
#include "GUILabel.h"
//#include "GUICheckbox.h"
//#include "GUISlider.h"

#include "SDL_ttf/include/SDL_ttf.h"
#include "Brofiler\Brofiler.h"

GUIManager::GUIManager() : Module()
{
	name.create("gui");
}

GUIManager::~GUIManager()
{}

bool GUIManager::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI texture");
	bool ret = true;
	
	atlas_file_name = conf.child("atlas").attribute("file").as_string("");
	
	return ret;
}

// Called before the first frame
bool GUIManager::Start()
{
	bool ret = true;

	atlas = App->textures->Load(atlas_file_name.GetString());

	return ret;
}

// Update all guis
bool GUIManager::PreUpdate()
{
	BROFILER_CATEGORY("PreUpdateGUI", Profiler::Color::Orange)
	bool ret = true;

	if (App->input->GetKey(SDL_SCANCODE_F8) == KEY_DOWN)
		debug = !debug;

	SDL_Rect rect_mouse;

	int x, y;
	App->input->GetMousePosition(x, y);

	for (p2List_item<GUIElement*> * tmp = gui_elements.start; tmp; tmp = tmp->next)
	{
		//define the rect_mouse
		rect_mouse.x = tmp->data->position.x;
		rect_mouse.y = tmp->data->position.y;
		rect_mouse.w = tmp->data->rect.w;
		rect_mouse.h = tmp->data->rect.h;

		//check if the mouse is inside of the rect boundaries AND give a state
		if (x > rect_mouse.x && x < rect_mouse.x + rect_mouse.w && y > rect_mouse.y && y < rect_mouse.y + rect_mouse.h)
		{
			//tmp->data->hovered = true;
			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT)== KEY_DOWN || App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
			{
				tmp->data->state = GUI_State::PRESSED;
			}
			else 
			{
				tmp->data->state = GUI_State::HOVERED;
			}
		}
		else
		{
			tmp->data->state = GUI_State::NORMAL;
		}
	}

	return ret;
}

bool GUIManager::Update(float dt) {

	BROFILER_CATEGORY("UpdateGUI", Profiler::Color::LemonChiffon)
	bool ret = true;

	return ret;
}

// Called after all Updates
bool GUIManager::PostUpdate()
{
	BROFILER_CATEGORY("PostUpdateGUI", Profiler::Color::Purple)
	bool ret = true;

	p2List_item<GUIElement*>* tmp = gui_elements.start;
	while (tmp != nullptr)
	{
		if (tmp->data->enabled)
			tmp->data->PostUpdate();
		
		if (debug) {
			SDL_Rect rect;
			rect.x = tmp->data->position.x;
			rect.y = tmp->data->position.y;
			rect.w = tmp->data->rect.w;
			rect.h = tmp->data->rect.h;

			tmp->data->position;
			App->render->DrawQuad(rect, 255, 0, 255, 100, true, false);
		}
		tmp = tmp->next;
	}

	return ret;
}

// Called before quitting
bool GUIManager::CleanUp()
{
	LOG("Freeing GUI");
	bool ret = true;

	p2List_item<GUIElement*>* tmp = gui_elements.start;
	while (tmp != nullptr)
	{
		RELEASE(tmp->data);
		tmp = tmp->next;
	}
	gui_elements.clear();
	
	return ret;
}

SDL_Texture* GUIManager::GetAtlas()
{
	return atlas;
}


void GUIManager::DestroyGUIElement(GUIElement *element) {

	for (int i = 0; i < gui_elements.count(); i++)
	{
		if (gui_elements[i] == element) {
			delete gui_elements[i];
			gui_elements[i] = nullptr;
		}
	}
}

GUIImage* GUIManager::CreateImage(iPoint pos, SDL_Rect rect, SDL_Texture* texture , Module* callback )
{
	SDL_Texture* tex = nullptr;

	if (texture == nullptr)
	{
		tex = atlas;
	}
	else
	{
		tex = texture;
	}

	GUIImage* tmp_img = new GUIImage(pos, rect, texture);
	tmp_img->callback = callback;
	gui_elements.add(tmp_img);

	return tmp_img;
}

GUILabel* GUIManager::CreateLabel(iPoint pos, p2SString text, _TTF_Font* font, Module* callback )
{
	GUILabel* tmp_lbl = new GUILabel(pos, text, font);
	tmp_lbl->callback = callback;
	gui_elements.add(tmp_lbl);

	return tmp_lbl;
}


GUIButton* GUIManager::CreateButton(iPoint pos, SDL_Rect normal, SDL_Rect hovered, SDL_Rect pressed, SDL_Texture* texture , Module* callback )
{
	SDL_Texture* tex = nullptr;

	if (texture == nullptr)
	{
		tex = atlas;
	}
	else
	{
		tex = texture;
	}

	GUIButton* tmp_btn = new GUIButton(pos,normal,hovered,pressed,texture) ;
	tmp_btn->callback = callback;
	gui_elements.add(tmp_btn);

	return tmp_btn;
}


//GUICheckBox * GUIManager::CreateCheckBox(iPoint pos, bool checked)
//{
//	return nullptr;
//}
//
//GUISlider * GUIManager::CreateSlider(iPoint pos, SDL_Rect slider_rect)
//{
//	return nullptr;
//}
//