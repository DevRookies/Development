#include "p2Defs.h"
#include "p2Log.h"
#include "DevRookiesApp.h"
#include "Render.h"
#include "Textures.h"
#include "Input.h"
#include "UIManager.h"

#include "UI_Image.h"
//#include "UIButton.h"
//#include "UICheckbox.h"
//#include "UILabel.h"
//#include "UISlider.h"
#include "UIElement.h"

#include "Brofiler\Brofiler.h"

UIManager::UIManager() : Module()
{
	name.create("ui");
}

UIManager::~UIManager()
{}

bool UIManager::Awake(pugi::xml_node& conf)
{
	LOG("Loading UI texture");
	bool ret = true;

	/*ui_texture = conf.child("ui").attribute("texture").as_string("");*/

	return ret;
}

// Called before the first frame
bool UIManager::Start()
{
	/*ui_tex = App->textures->Load(ui_texture.GetString());*/

	return true;
}

// Update all guis
bool UIManager::PreUpdate()
{
	BROFILER_CATEGORY("PreUpdateUI", Profiler::Color::Orange)
	bool ret = true;
	p2List_item<UIElement*>* item = ui_elements.start;
	while (item != nullptr)
	{
		item->data->PreUpdate();
		item = item->next;
	}

	return ret;
}

bool UIManager::Update(float dt) {

	BROFILER_CATEGORY("UpdateUI", Profiler::Color::LemonChiffon)
	bool ret = true;
	p2List_item<UIElement*>* tmp = ui_elements.start;
	while (tmp != nullptr)
	{
		tmp->data->Update(dt);
		tmp = tmp->next;
	}

	return true;
}

// Called after all Updates
bool UIManager::PostUpdate()
{
	BROFILER_CATEGORY("PostUpdateUI", Profiler::Color::Purple)
	bool ret = true;
	p2List_item<UIElement*>* tmp = ui_elements.start;
	while (tmp != nullptr)
	{
		tmp->data->PostUpdate();
		tmp = tmp->next;
	}
	return ret;
}

// Called before quitting
bool UIManager::CleanUp()
{
	LOG("Freeing UI");
	bool ret = true;
	p2List_item<UIElement*>* tmp = ui_elements.start;
	while (tmp != nullptr)
	{
		tmp->data->CleanUp();
		tmp = tmp->next;
	}
	ui_elements.clear();
	return ret;
}

bool UIManager::DestroyUIElement(UIElement *element) {

	for (int i = 0; i < ui_elements.count(); i++)
	{
		if (ui_elements[i] == element) {
			ui_elements[i]->CleanUp();
			delete ui_elements[i];
			ui_elements[i] = nullptr;
		}
	}
	return true;
}

UIElement* UIManager::CreateImage(iPoint pos, SDL_Rect rect) 
{
	UIElement* tmp_img = new UIImage(position, rect);
	
	return tmp_img;

}

UIElement* UIManager::CreateButton(iPoint pos, SDL_Rect rect)
{
	return nullptr;
}

UIElement * UIManager::CreateCheckBox(iPoint pos, bool checked)
{
	return nullptr;
}

UIElement* UIManager::CreateLabel(iPoint pos, p2SString text) 
{
	return nullptr;
}

UIElement * UIManager::CreateSlider(iPoint pos, SDL_Rect slider_rect)
{
	return nullptr;
}

UIElement* UIManager::GetMouseElement(iPoint pos)
{
	return nullptr;
}