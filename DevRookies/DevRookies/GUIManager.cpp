#include "p2Defs.h"
#include "p2Log.h"
#include "DevRookiesApp.h"
#include "Render.h"
#include "Textures.h"
#include "Input.h"
#include "GUIManager.h"

//#include "GUI_Image.h"
//#include "GUIButton.h"
//#include "GUICheckbox.h"
//#include "GUILabel.h"
//#include "GUISlider.h"
#include "GUIElement.h"

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
	
	gui_texture = conf.child("gui").attribute("texture").as_string("");
	p2List_item<GUIElement*>* tmp = gui_elements.start;
	while (tmp != nullptr)
	{
		tmp->data->Awake(conf);
		tmp = tmp->next;
	}
	
	return ret;
}

// Called before the first frame
bool GUIManager::Start()
{
	bool ret = true;

	texture = App->textures->Load(gui_texture.GetString());
	p2List_item<GUIElement*>* tmp = gui_elements.start;
	while (tmp != nullptr)
	{
		tmp->data->Start();
		tmp = tmp->next;
	}

	return ret;
}

// Update all guis
bool GUIManager::PreUpdate()
{
	BROFILER_CATEGORY("PreUpdateGUI", Profiler::Color::Orange)
	bool ret = true;

	p2List_item<GUIElement*>* tmp = gui_elements.start;
	while (tmp != nullptr)
	{
		tmp->data->PreUpdate();
		if (tmp->data->to_delete)
			DestroyGUIElement(tmp->data);
		tmp = tmp->next;

	}

	return ret;
}

bool GUIManager::Update(float dt) {

	BROFILER_CATEGORY("UpdateGUI", Profiler::Color::LemonChiffon)
	bool ret = true;

	p2List_item<GUIElement*>* tmp = gui_elements.start;
	while (tmp != nullptr)
	{
		tmp->data->Update(dt);
		tmp = tmp->next;
	}

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
		tmp->data->PostUpdate();
		if (debug)
			tmp->data->DebugDraw();
		tmp = tmp->next;
	}

	return ret;
}

// Called before quitting
bool GUIManager::CleanUp()
{
	LOG("Freeing GUI");
	bool ret = true;

	App->textures->UnLoad(texture);
	p2List_item<GUIElement*>* tmp = gui_elements.start;
	while (tmp != nullptr)
	{
		tmp->data->CleanUp();
		DestroyGUIElement(tmp->data);
		tmp = tmp->next;
	}
	gui_elements.clear();
	
	return ret;
}

void GUIManager::DestroyGUIElement(GUIElement *element) {

	for (int i = 0; i < gui_elements.count(); i++)
	{
		if (gui_elements[i] == element) {
			gui_elements[i]->CleanUp();
			delete gui_elements[i];
			gui_elements[i] = nullptr;
		}
	}
}

GUIElement* GUIManager::CreateElement(GUI_Type type, iPoint pos)
{
	GUIElement* ret = nullptr;

	switch (type)
	{
	case IMAGE:
		ret = new GUIImage(pos);
		gui_elements.add(ret);
		break;
	/*case BUTTON:
		ret = new GUIButton(pos);
		gui_elements.add(ret);
		break;
	case CHECKBOX:
		ret = new GUICheckBox(pos);
		gui_elements.add(ret);
		break;
	case LABEL:
		ret = new GUILabel(pos);
		gui_elements.add(ret);
		break;
	case SLIDER:
		ret = new GUISlider(pos);
		gui_elements.add(ret);
		break;*/
	}
	return ret;
}

GUIImage* GUIManager::CreateImage(iPoint pos, SDL_Rect rect, Module* callback = nullptr)
{
	GUIImage* tmp_img = (GUIImage*)App->guimanager->CreateElement(IMAGE, pos);
	tmp_img->rect = rect;
	tmp_img->callback = callback;
	tmp_img->Awake(name);
	tmp_img->Start();
	
	return tmp_img;
}

//GUIButton* GUIManager::CreateButton(iPoint pos, SDL_Rect rect)
//{
//	return nullptr;
//}
//
//GUICheckBox * GUIManager::CreateCheckBox(iPoint pos, bool checked)
//{
//	return nullptr;
//}
//
//GUILabel* GUIManager::CreateLabel(iPoint pos, p2SString text)
//{
//	return nullptr;
//}
//
//GUISlider * GUIManager::CreateSlider(iPoint pos, SDL_Rect slider_rect)
//{
//	return nullptr;
//}
//
//GUIElement* GUIManager::GetMouseElement(iPoint pos)
//{
//	return nullptr;
//}