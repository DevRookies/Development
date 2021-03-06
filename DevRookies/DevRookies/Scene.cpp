#include "p2Defs.h"
#include "p2Log.h"
#include "DevRookiesApp.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Map.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Player.h"
#include "SceneManager.h"
#include "Pathfinding.h"
#include "Brofiler/Brofiler.h"
#include "EntityManager.h"
#include "Entity.h"

Scene::Scene() : Module()
{
	name.create("scene");
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;

	tile_name_scene0 = config.child("tile_name_scene0").child_value();
	tile_name_scene1 = config.child("tile_name_scene1").child_value();
	tile_name_scene2 = config.child("tile_name_scene2").child_value();
	lvl0_music_name = config.child("lvl0_music_name").child_value();
	lvl1_music_name = config.child("lvl1_music_name").child_value();
	lvl2_music_name = config.child("lvl2_music_name").child_value();
	press_fx_name = config.child("press_fx_name").attribute("source").as_string();
	camera.x = config.child("camera").attribute("x").as_int();
	camera.y = config.child("camera").attribute("y").as_int();
	godmode_texture = config.child("godmode_tex").child_value();
	godmode_pos = { config.child("godmode_tex").attribute("x").as_float(),  config.child("godmode_tex").attribute("y").as_float() };
	active = true;

	//Images
	LoadRect(config.child("rects").child("windows_rect").child("rect"), windows_rect);
	LoadRect(config.child("rects").child("title_rect").child("rect"), title_rect);
	LoadRect(config.child("rects").child("license_rect").child("rect"), license_rect);
	LoadRect(config.child("rects").child("coins_rect").child("rect"), coins_rect);
	LoadRect(config.child("rects").child("life_rect").child("rect"), life_rect);
	LoadRect(config.child("rects").child("score_rect").child("rect"), score_rect);
	LoadRect(config.child("rects").child("lock_rect").child("rect"), lock_rect);

	//Buttons
	LoadRect(config.child("rects").child("play_normal").child("rect"), play_normal);
	LoadRect(config.child("rects").child("play_hovered").child("rect"), play_hovered);
	LoadRect(config.child("rects").child("play_pressed").child("rect"), play_pressed);

	LoadRect(config.child("rects").child("continue_normal").child("rect"), continue_normal);
	LoadRect(config.child("rects").child("continue_hovered").child("rect"), continue_hovered);
	LoadRect(config.child("rects").child("continue_pressed").child("rect"), continue_pressed);

	LoadRect(config.child("rects").child("settings_normal").child("rect"), settings_normal);
	LoadRect(config.child("rects").child("settings_hovered").child("rect"), settings_hovered);
	LoadRect(config.child("rects").child("settings_pressed").child("rect"), settings_pressed);

	LoadRect(config.child("rects").child("credits_normal").child("rect"), credits_normal);
	LoadRect(config.child("rects").child("credits_hovered").child("rect"), credits_hovered);
	LoadRect(config.child("rects").child("credits_pressed").child("rect"), credits_pressed);

	LoadRect(config.child("rects").child("exit_normal").child("rect"), exit_normal);
	LoadRect(config.child("rects").child("exit_hovered").child("rect"), exit_hovered);
	LoadRect(config.child("rects").child("exit_pressed").child("rect"), exit_pressed);

	LoadRect(config.child("rects").child("resume_normal").child("rect"), resume_normal);
	LoadRect(config.child("rects").child("resume_hovered").child("rect"), resume_hovered);
	LoadRect(config.child("rects").child("resume_pressed").child("rect"), resume_pressed);

	LoadRect(config.child("rects").child("back_menu_normal").child("rect"), back_menu_normal);
	LoadRect(config.child("rects").child("back_menu_hovered").child("rect"), back_menu_hovered);
	LoadRect(config.child("rects").child("back_menu_pressed").child("rect"), back_menu_pressed);

	LoadRect(config.child("rects").child("mute_music_normal").child("rect"), mute_music_normal);
	LoadRect(config.child("rects").child("mute_music_hovered").child("rect"), mute_music_hovered);

	LoadRect(config.child("rects").child("mute_fx_normal").child("rect"), mute_fx_normal);
	LoadRect(config.child("rects").child("mute_fx_hovered").child("rect"), mute_fx_hovered);

	LoadRect(config.child("rects").child("little_back_menu_normal").child("rect"), little_back_menu_normal);
	LoadRect(config.child("rects").child("little_back_menu_pressed").child("rect"), little_back_menu_pressed);
	LoadRect(config.child("rects").child("little_back_menu_hovered").child("rect"), little_back_menu_hovered);

	LoadRect(config.child("rects").child("music_normal").child("rect"), music_normal);
	LoadRect(config.child("rects").child("music_pressed").child("rect"), music_pressed);
	LoadRect(config.child("rects").child("music_hovered").child("rect"), music_hovered);

	LoadRect(config.child("rects").child("fx_normal").child("rect"), fx_normal);
	LoadRect(config.child("rects").child("fx_pressed").child("rect"), fx_pressed);
	LoadRect(config.child("rects").child("fx_hovered").child("rect"), fx_hovered);

	LoadRect(config.child("rects").child("minus_normal").child("rect"), minus_normal);
	LoadRect(config.child("rects").child("minus_hovered").child("rect"), minus_hovered);
	LoadRect(config.child("rects").child("minus_pressed").child("rect"), minus_pressed);

	LoadRect(config.child("rects").child("plus_normal").child("rect"), plus_normal);
	LoadRect(config.child("rects").child("plus_hovered").child("rect"), plus_hovered);
	LoadRect(config.child("rects").child("plus_pressed").child("rect"), plus_pressed);

	LoadRect(config.child("rects").child("web_normal").child("rect"), web_normal);
	LoadRect(config.child("rects").child("web_hovered").child("rect"), web_hovered);
	LoadRect(config.child("rects").child("web_pressed").child("rect"), web_pressed);

	//Slider

	LoadRect(config.child("rects").child("slider_rect").child("rect"), slider_rect);
	LoadRect(config.child("rects").child("slider_normal").child("rect"), slider_normal);
	LoadRect(config.child("rects").child("slider_hovered").child("rect"), slider_hovered);
	LoadRect(config.child("rects").child("slider_pressed").child("rect"), slider_pressed);

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	uchar* data = nullptr;
	switch (scene_actual)
	{
	case 0:
		App->map->Load(tile_name_scene0.GetString());
		App->audio->PlayMusic(lvl0_music_name.GetString());
		App->entitymanager->player->Restart(FIRE);
		break;
	case 1:
		App->map->Load(tile_name_scene1.GetString());
		App->audio->PlayMusic(lvl1_music_name.GetString());
		App->entitymanager->player->Restart(FIRE);

		break;
	case 2:
		App->map->Load(tile_name_scene2.GetString());
		App->audio->PlayMusic(lvl2_music_name.GetString());
		App->entitymanager->player->Restart(ICE);

		break;
	default:
		break;
	}

	App->audio->LoadFx(press_fx_name.GetString());

	//----GUI-------------
	if (!guicreated) {
		GUICreate();
		guicreated = true;
	}
	GUIStart();

	//--------------------------------------------------------------------------Pathfinding.......................................................................
	int width, height;
	if (App->map->CreateWalkabilityMap(width, height, &data))
		App->pathfinding->SetMap(width, height, data);

	App->entitymanager->Restart();
	App->render->SetCamera(camera.x, camera.y);
	App->render->start_time = App->render->restart_start_time;

	debug_tex = App->textures->Load("maps/navigation.png");
	godmode_tex = App->textures->Load(godmode_texture.GetString());




	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	BROFILER_CATEGORY("PreUpdateScene", Profiler::Color::Orange);

	if (App->render->debug_path) {

		static iPoint origin;
		static bool origin_selected = false;

		int x, y;
		App->input->GetMousePosition(x, y);
		iPoint p = App->render->ScreenToWorld(x, y);
		p = App->map->WorldToMap(p.x, p.y);

		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
		{
			if (origin_selected == true)
			{
				App->pathfinding->CreatePath(origin, p);
				origin_selected = false;
			}
			else
			{
				origin = p;
				origin_selected = true;
			}
		}
	}

	return true;
}
// Called each loop iteration
bool Scene::Update(float dt)
{
	BROFILER_CATEGORY("UpdateScene", Profiler::Color::GoldenRod);

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN || play_btn->state == PRESSED) {
		scene_actual = 1;
		Restart();
	}

	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) {
		Restart();
	}

	if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN) {
		scene_actual = 2;
		Restart();
	}

	if ((App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN && scene_actual!=0) || back_menu_btn->state == PRESSED)
		App->SaveGame();

	if (App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN || continue_btn->state == PRESSED) {
		App->LoadGame();
	}

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN)
		App->audio->VolumeDown(-1);

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN)
		App->audio->VolumeUp(-1);

	if (App->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN)
		App->audio->StopMusic(-1);

	//----GUI-------
	GUIUpdate();

	App->map->Draw(dt);

	if (App->render->debug_path) {
		int x, y;
		App->input->GetMousePosition(x, y);
		iPoint map_coordinates = App->map->WorldToMap(x - App->render->camera.x, y - App->render->camera.y);
		p2SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d Tile:%d,%d",
			App->map->data.width, App->map->data.height,
			App->map->data.tile_width, App->map->data.tile_height,
			App->map->data.tilesets.count(),
			map_coordinates.x, map_coordinates.y);

		//App->win->SetTitle(title.GetString());

		// Debug pathfinding ------------------------------
		App->input->GetMousePosition(x, y);
		iPoint p = App->render->ScreenToWorld(x, y);
		p = App->map->WorldToMap(p.x, p.y);
		p = App->map->MapToWorld(p.x, p.y);

		App->render->Blit(debug_tex, p.x, p.y);

		const p2DynArray<iPoint>* path = App->pathfinding->GetLastPath();

		for (uint i = 0; i < path->Count(); ++i)
		{
			iPoint pos = App->map->MapToWorld(path->At(i)->x, path->At(i)->y);
			App->render->Blit(debug_tex, pos.x, pos.y);
		}
	}

	if (App->entitymanager->player->godmode) {
		godmode_pos.x = App->render->camera.x;
		godmode_pos.y = App->render->camera.y;
		App->render->Blit(godmode_tex, godmode_pos.x, godmode_pos.y, NULL, -1.0f);
	}

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	BROFILER_CATEGORY("PostUpdateScene", Profiler::Color::Purple);
	bool ret = true;

	if (exit_btn->state == PRESSED)
		ret = false;

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");
	App->map->CleanUp();
	App->entitymanager->player->CleanUp();
	p2List_item<Entity*>* tmp = App->entitymanager->entities.start;
	while (tmp != nullptr)
	{
		tmp->data->CleanUp();
		tmp = tmp->next;
	}
	App->collision->CleanUp();

	App->textures->UnLoad(debug_tex);
	debug_tex = nullptr;
	App->textures->UnLoad(godmode_tex);
	godmode_tex = nullptr;

	return true;
}


bool Scene::Load(pugi::xml_node& node)
{
	bool ret = true;

	scene_actual = node.child("scene_actual").attribute("value").as_int();
	timeminute = node.child("timeminute").attribute("value").as_int();
	timesecond = node.child("timesecond").attribute("value").as_int();

	CleanUp();
	Start();

	return ret;
}

bool Scene::Save(pugi::xml_node& node) const
{
	bool ret = true;

	node.append_child("scene_actual").append_attribute("value") = scene_actual;
	node.append_child("timeminute").append_attribute("value") = timeminute;
	node.append_child("timesecond").append_attribute("value") = timesecond;

	return ret;
}

void Scene::Restart() const
{
	App->scenemanager->FadeToBlack(scene_actual);
	App->pause = false;
	App->entitymanager->player->visibility = false;
	p2List_item<Entity*>* tmp = App->entitymanager->entities.start;
	while (tmp != nullptr)
	{
		tmp->data->visibility = false;
		tmp = tmp->next;
	}

}

void Scene::AddFX(const int channel, const int repeat) const
{
	App->audio->PlayFx(channel, repeat);
}

void Scene::GUICreate()
{
	BROFILER_CATEGORY("GUICreate", Profiler::Color::OrangeRed);

	//_TTF_Font * font = App->fonts->Load("fonts/open_sans/OpenSans-Bold.ttf", 12);
	//label = App->guimanager->CreateLabel(iPoint(500, 530), p2SString("Copyright (c) [2018] [Llu�s Moreu & Cere Venteo] Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files(the Software), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions : The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software. THE SOFTWARE IS PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE."), font, this);

	//HEADERS
	settings_home_btn = App->guimanager->CreateButton(iPoint(310, 187), settings_normal, settings_hovered, settings_pressed, false);
	credits_home_btn = App->guimanager->CreateButton(iPoint(310, 187), credits_normal, credits_hovered, credits_pressed, false);
	settings_hud_home_btn = App->guimanager->CreateButton(iPoint(310, 187), settings_normal, settings_hovered, settings_pressed, false);

	//BASE UI
	title_img = App->guimanager->CreateImage(iPoint(354, 145), title_rect);
	windows_img = App->guimanager->CreateImage(iPoint(300, 254), windows_rect);
	windows_hud_img = App->guimanager->CreateImage(iPoint(300, 254), windows_rect);

	//CREDITS
	license_img = App->guimanager->CreateImage(iPoint(392, 340), license_rect);
	credits_little_back_menu_btn = App->guimanager->CreateButton(iPoint(613, 607), little_back_menu_normal, little_back_menu_hovered, little_back_menu_pressed, false);
	web_btn = App->guimanager->CreateButton(iPoint(840, 314), web_normal, web_hovered, web_pressed, false);

	//MAIN_MENU
	play_btn = App->guimanager->CreateButton(iPoint(409, 345), play_normal, play_hovered, play_pressed, false);
	continue_btn = App->guimanager->CreateButton(iPoint(581, 345), continue_normal, continue_hovered, continue_pressed, false);
	lock_continue_img = App->guimanager->CreateImage(iPoint(581, 345), lock_rect, false);
	settings_btn = App->guimanager->CreateButton(iPoint(757, 345), settings_normal, settings_hovered, settings_pressed, false);
	credits_btn = App->guimanager->CreateButton(iPoint(495, 505), credits_normal, credits_hovered, credits_pressed, false);
	exit_btn = App->guimanager->CreateButton(iPoint(667, 505), exit_normal, exit_hovered, exit_pressed, false);

	//SETTINGS

	music_btn = App->guimanager->CreateButton(iPoint(433, 350), music_normal, music_hovered, music_pressed, false);
	fx_btn = App->guimanager->CreateButton(iPoint(733, 350), fx_normal, fx_hovered, fx_pressed, false);
	minus_music_btn = App->guimanager->CreateButton(iPoint(346, 504), minus_normal, minus_hovered, minus_pressed, false);
	plus_music_btn = App->guimanager->CreateButton(iPoint(600, 504), plus_normal, plus_hovered, plus_pressed, false);
	minus_fx_btn = App->guimanager->CreateButton(iPoint(646, 504), minus_normal, minus_hovered, minus_pressed, false);
	plus_fx_btn = App->guimanager->CreateButton(iPoint(900, 504), plus_normal, plus_hovered, plus_pressed, false);
	music_sli = App->guimanager->CreateSlider(iPoint(381, 502), slider_rect, slider_normal, slider_hovered, slider_pressed, true);
	fx_sli = App->guimanager->CreateSlider(iPoint(681, 502), slider_rect, slider_normal, slider_hovered, slider_pressed, true);

	music_sli->SetValue(App->audio->volume);
	fx_sli->SetValue(App->audio->volume_fx);
	mute_music_btn = App->guimanager->CreateButton(iPoint(433, 350), mute_music_normal, mute_music_hovered, mute_music_normal, false);
	mute_fx_btn = App->guimanager->CreateButton(iPoint(733, 350), mute_fx_normal, mute_fx_hovered, mute_fx_normal, false);
	little_back_menu_btn = App->guimanager->CreateButton(iPoint(613, 607), little_back_menu_normal, little_back_menu_hovered, little_back_menu_pressed, false);

	//HUD
	coins_img = App->guimanager->CreateImage(iPoint(814, 11), coins_rect);
	life_img = App->guimanager->CreateImage(iPoint(1054, 11), life_rect);
	time_img = App->guimanager->CreateImage(iPoint(12, 16), score_rect);
	score_img = App->guimanager->CreateImage(iPoint(429, 16), score_rect);
	resume_btn = App->guimanager->CreateButton(iPoint(155, 113), resume_normal, resume_hovered, resume_pressed, false, windows_hud_img);
	settings_hud_btn = App->guimanager->CreateButton(iPoint(410, 113), settings_normal, settings_hovered, settings_pressed, false, windows_hud_img);
	back_menu_btn = App->guimanager->CreateButton(iPoint(283, 263), back_menu_normal, back_menu_hovered, back_menu_pressed, false, windows_hud_img);
	little_back_hud_btn = App->guimanager->CreateButton(iPoint(613, 607), little_back_menu_normal, little_back_menu_hovered, little_back_menu_pressed, false);


	_TTF_Font * font = App->fonts->Load(DEFAULT_FONT, DEFAULT_FONT_SIZE);

	times = App->guimanager->CreateLabel(iPoint(200, 46), time_str, font);
	score = App->guimanager->CreateLabel(iPoint(600, 46), score_str, font);
	coins = App->guimanager->CreateLabel(iPoint(950, 46), coin_str, font);
	lifes = App->guimanager->CreateLabel(iPoint(1150, 46), life_str, font);
}

void Scene::GUIStart()
{
	BROFILER_CATEGORY("GUIStart", Profiler::Color::YellowGreen);

	switch (scene_actual)
	{
	case 0:
		//MAINMENU
		title_img->Enabled(true);
		play_btn->Enabled(true);
		App->GetContinueState();
		//continue_btn->Enabled(true);
		settings_btn->Enabled(true);
		credits_btn->Enabled(true);
		exit_btn->Enabled(true);
		windows_img->Enabled(true);
		//disable HUD
		coins_img->Enabled(false);
		life_img->Enabled(false);
		time_img->Enabled(false);
		score_img->Enabled(false);
		times->Enabled(false);
		score->Enabled(false);
		coins->Enabled(false);
		lifes->Enabled(false);
		break;
	case 1:
		//disable MAINMENU
		title_img->Enabled(false);
		play_btn->Enabled(false);
		continue_btn->Enabled(false);
		lock_continue_img->Enabled(false);
		settings_btn->Enabled(false);
		credits_btn->Enabled(false);
		exit_btn->Enabled(false);
		windows_img->Enabled(false);
		//enable HUD
		coins_img->Enabled(true);
		life_img->Enabled(true);
		time_img->Enabled(true);
		score_img->Enabled(true);
		times->Enabled(true);
		score->Enabled(true);
		coins->Enabled(true);
		lifes->Enabled(true);
		break;
	case 2:
		//disable MAINMENU
		title_img->Enabled(false);
		play_btn->Enabled(false);
		continue_btn->Enabled(false);
		lock_continue_img->Enabled(false);
		settings_btn->Enabled(false);
		credits_btn->Enabled(false);
		exit_btn->Enabled(false);
		windows_img->Enabled(false);
		//enable HUD
		coins_img->Enabled(true);
		life_img->Enabled(true);
		time_img->Enabled(true);
		score_img->Enabled(true);
		times->Enabled(true);
		score->Enabled(true);
		coins->Enabled(true);
		lifes->Enabled(true);
		break;
	default:
		break;
	}

}

void Scene::GUIUpdate()
{
	if (restarting) {
		restarting = false;
		scene_actual = 0;
		Restart();
	}

	

	if (play_btn->state == PRESSED || continue_btn->state == PRESSED) {
		title_img->Enabled(false);
		play_btn->Enabled(false);
		continue_btn->Enabled(false);
		lock_continue_img->Enabled(false);
		settings_btn->Enabled(false);
		credits_btn->Enabled(false);
		exit_btn->Enabled(false);
		windows_img->Enabled(false);
		timesecond = 0;
		timeminute = 0;
		App->entitymanager->player->score = 0;
		App->entitymanager->player->coin_counter = 0;
		App->entitymanager->player->lifes = 3;
		times->SetText("0:00");
		score->SetText("0");
		coins->SetText("0");
		lifes->SetText("3");
	}
	else if (settings_btn->state == PRESSED) {
		//disable
		title_img->Enabled(false);
		play_btn->Enabled(false);
		continue_btn->Enabled(false);
		lock_continue_img->Enabled(false);
		settings_btn->Enabled(false);
		credits_btn->Enabled(false);
		exit_btn->Enabled(false);

		//enable
		settings_home_btn->Enabled(true);
		if (App->audio->mute_volume) mute_music_btn->Enabled(true);
		music_btn->Enabled(true);
		if (App->audio->mute_fx) mute_fx_btn->Enabled(true);
		fx_btn->Enabled(true);
		minus_music_btn->Enabled(true);
		plus_music_btn->Enabled(true);
		minus_fx_btn->Enabled(true);
		plus_fx_btn->Enabled(true);
		music_sli->Enabled(true);
		fx_sli->Enabled(true);
		little_back_menu_btn->Enabled(true);
	}
	else if (settings_home_btn->state == PRESSED || little_back_menu_btn->state == PRESSED) {

		//disable
		settings_home_btn->Enabled(false);
		little_back_menu_btn->Enabled(false);
		music_btn->Enabled(false);
		mute_music_btn->Enabled(false);
		fx_btn->Enabled(false);
		mute_fx_btn->Enabled(false);
		minus_music_btn->Enabled(false);
		plus_music_btn->Enabled(false);
		minus_fx_btn->Enabled(false);
		plus_fx_btn->Enabled(false);
		music_sli->Enabled(false);
		fx_sli->Enabled(false);

		//enable
		title_img->Enabled(true);
		play_btn->Enabled(true);
		App->GetContinueState();
		//continue_btn->Enabled(true);
		settings_btn->Enabled(true);
		credits_btn->Enabled(true);
		exit_btn->Enabled(true);
	}
	else if (credits_btn->state == PRESSED) {
		printUI_base == false;

		//disable
		title_img->Enabled(false);
		play_btn->Enabled(false);
		continue_btn->Enabled(false);
		lock_continue_img->Enabled(false);
		settings_btn->Enabled(false);
		credits_btn->Enabled(false);
		exit_btn->Enabled(false);

		//enable
		credits_home_btn->Enabled(true);
		license_img->Enabled(true);
		credits_little_back_menu_btn->Enabled(true);
		web_btn->Enabled(true);
	}
	else if (credits_home_btn->state == PRESSED || credits_little_back_menu_btn->state == PRESSED) {
		//disable
		credits_home_btn->Enabled(false);
		license_img->Enabled(false);
		credits_little_back_menu_btn->Enabled(false);
		web_btn->Enabled(false);

		//enable
		title_img->Enabled(true);
		play_btn->Enabled(true);
		App->GetContinueState();
		//continue_btn->Enabled(true);
		settings_btn->Enabled(true);
		credits_btn->Enabled(true);
		exit_btn->Enabled(true);
	}
	else if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN && scene_actual != 0 && !windows_hud_img->enabled) { // IN GAME MENU---------------
		App->pause = true;
		guianimation = true;
		//enable HUD pause
		windows_hud_img->Enabled(true);
		resume_btn->Enabled(true);
		settings_hud_btn->Enabled(true);
		back_menu_btn->Enabled(true);
	}
	else if (resume_btn->state == PRESSED) {
		App->pause = false;

		//disable HUD pause
		windows_hud_img->Enabled(false);
		resume_btn->Enabled(false);
		settings_hud_btn->Enabled(false);
		back_menu_btn->Enabled(false);
	}
	else if (settings_hud_btn->state == PRESSED) {
		//disable HUD pause
		resume_btn->Enabled(false);
		settings_hud_btn->Enabled(false);
		back_menu_btn->Enabled(false);

		//enable settings
		settings_hud_home_btn->Enabled(true);
		if (App->audio->mute_volume) mute_music_btn->Enabled(true);
		music_btn->Enabled(true);
		if (App->audio->mute_fx) mute_fx_btn->Enabled(true);
		fx_btn->Enabled(true);
		minus_music_btn->Enabled(true);
		plus_music_btn->Enabled(true);
		minus_fx_btn->Enabled(true);
		plus_fx_btn->Enabled(true);
		music_sli->Enabled(true);
		fx_sli->Enabled(true);
		little_back_hud_btn->Enabled(true);
	}
	else if (settings_hud_home_btn->state == PRESSED || little_back_hud_btn->state == PRESSED) {
		//disable
		settings_hud_home_btn->Enabled(false);
		little_back_hud_btn->Enabled(false);
		music_btn->Enabled(false);
		mute_music_btn->Enabled(false);
		fx_btn->Enabled(false);
		mute_fx_btn->Enabled(false);
		minus_music_btn->Enabled(false);
		plus_music_btn->Enabled(false);
		minus_fx_btn->Enabled(false);
		plus_fx_btn->Enabled(false);
		music_sli->Enabled(false);
		fx_sli->Enabled(false);

		//enable
		resume_btn->Enabled(true);
		settings_hud_btn->Enabled(true);
		back_menu_btn->Enabled(true);
	}
	else if (back_menu_btn->state == PRESSED) {
		//disable HUD pause
		windows_hud_img->Enabled(false);
		resume_btn->Enabled(false);
		settings_hud_btn->Enabled(false);
		back_menu_btn->Enabled(false);
		coins_img->Enabled(false);
		life_img->Enabled(false);
		time_img->Enabled(false);
		score_img->Enabled(false);
		times->Enabled(false);
		score->Enabled(false);
		coins->Enabled(false);
		lifes->Enabled(false);

		restarting = true;

	}

	if (play_btn->state == PRESSED || continue_btn->state == PRESSED || settings_btn->state == PRESSED || settings_home_btn->state == PRESSED || little_back_menu_btn->state == PRESSED || credits_btn->state == PRESSED || credits_home_btn->state == PRESSED
		|| resume_btn->state == PRESSED || settings_hud_btn->state == PRESSED || settings_hud_home_btn->state == PRESSED || back_menu_btn->state == PRESSED
		|| minus_music_btn->state == PRESSED || plus_music_btn->state == PRESSED || minus_fx_btn->state == PRESSED || plus_fx_btn->state == PRESSED || little_back_hud_btn->state == PRESSED || mute_fx_btn->state == PRESSED || mute_music_btn->state == PRESSED)
		App->scene->AddFX(1, 0);

	//Audio------
	if (music_btn->state == PRESSED) {
		App->audio->StopMusic(-2);
		mute_music_btn->Enabled(true);
	}
	else if (fx_btn->state == PRESSED) {
		App->audio->StopMusic(-3);
		mute_fx_btn->Enabled(true);
	}
	else if (minus_music_btn->state == PRESSED) {
		App->audio->VolumeDown(-2);
	}
	else if (plus_music_btn->state == PRESSED) {
		App->audio->VolumeUp(-2);
	}
	else if (minus_fx_btn->state == PRESSED) {
		App->audio->VolumeDown(-3);
	}
	else if (plus_fx_btn->state == PRESSED) {
		App->audio->VolumeUp(-3);
	}

	if (mute_music_btn->state == PRESSED) {
		mute_music_btn->Enabled(false);
	}

	if (mute_fx_btn->state == PRESSED) {
		mute_fx_btn->Enabled(false);
	}

	if (App->audio->mute_volume && music_btn->enabled) mute_music_btn->Enabled(true);
	else mute_music_btn->Enabled(false);
	if (App->audio->mute_fx && fx_btn->enabled) mute_fx_btn->Enabled(true);
	else mute_fx_btn->Enabled(false);

	if (!App->audio->mute_volume) Mix_VolumeMusic(music_sli->GetValue());
	if (!App->audio->mute_fx) App->audio->SliderVolumeFx(fx_sli->GetValue());
	App->audio->volume = music_sli->GetValue();
	App->audio->volume_fx = fx_sli->GetValue();

	if (guianimation) {

		windows_hud_img->SetLocalPosition(animation.x, animation.y);

		animation.y -= 20;
		if (windows_hud_img->GetPosition().y < 254) {
			guianimation = false;
			animation = { 300, 254 };
			windows_hud_img->SetLocalPosition(animation.x, animation.y);
			animation = { 300, 900 };
		}


	}

	if (web_btn->state == PRESSED) {
		ShellExecuteA(NULL, "open", "https://devrookies.github.io/Development/", NULL, NULL, SW_SHOWNORMAL);
	}

}

void Scene::HUDUpdate()
{
	BROFILER_CATEGORY("GUIStart", Profiler::Color::CadetBlue);

	if (App->render->start_time == 0 && windows_hud_img->enabled == false && (scene_actual == 1 || scene_actual == 2)) {
		timesecond++;
		if (timesecond == 60) {
			timesecond = 0;
			timeminute++;
		}
		if (timesecond < 10) {
			p2SString time_str("%i:0%i", timeminute, timesecond);
			times->SetText(time_str);
		}
		else {
			p2SString time_str("%i:%i", timeminute, timesecond);
			times->SetText(time_str);
		}

		p2SString score_str("%i", App->entitymanager->player->score);
		p2SString coin_str("%i", App->entitymanager->player->coin_counter);
		p2SString life_str("%i", App->entitymanager->player->lifes);


		score->SetText(score_str);
		coins->SetText(coin_str);
		lifes->SetText(life_str);
	}
}

bool Scene::LoadRect(pugi::xml_node &node, SDL_Rect &rect) {

	/*SDL_Rect rect;*/
	rect.x = node.attribute("x").as_int();
	rect.y = node.attribute("y").as_int();
	rect.w = node.attribute("width").as_int();
	rect.h = node.attribute("height").as_int();
	return true;
}

