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


	//xml this rects!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//Images
	windows_rect.x = 11;
	windows_rect.y = 962;
	windows_rect.w = 681;
	windows_rect.h = 453;

	title_rect.x = 560;
	title_rect.y = 1456;
	title_rect.w = 518;
	title_rect.h = 134;

	license_rect.x = 10;
	license_rect.y = 1470;
	license_rect.w = 447;
	license_rect.h = 268;

	music_rect.x = 769;
	music_rect.y = 358;
	music_rect.w = 115;
	music_rect.h = 113;

	fx_rect.x = 769;
	fx_rect.y = 239;
	fx_rect.w = 115;
	fx_rect.h = 114;

	minus_rect.x = 599;
	minus_rect.y = 518;
	minus_rect.w = 33;
	minus_rect.h = 32;

	plus_rect.x = 599;
	plus_rect.y = 485;
	plus_rect.w = 33;
	plus_rect.h = 32;

	coins_rect.x = 7;
	coins_rect.y = 834;
	coins_rect.w = 216;
	coins_rect.h = 77;

	life_rect.x = 245;
	life_rect.y = 834;
	life_rect.w = 217;
	life_rect.h = 77;

	score_rect.x = 497;
	score_rect.y = 842;
	score_rect.w = 308;
	score_rect.h = 66;

	//Buttons
	play_normal.x = 255;
	play_normal.y = 120;
	play_normal.w = 115;
	play_normal.h = 114;

	play_hovered.x = 4;
	play_hovered.y = 120;
	play_hovered.w = 115;
	play_hovered.h = 114;

	play_pressed.x = 129;
	play_pressed.y = 120;
	play_pressed.w = 116;
	play_pressed.h = 114;

	continue_normal.x = 254;
	continue_normal.y = 238;
	continue_normal.w = 116;
	continue_normal.h = 114;

	continue_hovered.x = 4;
	continue_hovered.y = 238;
	continue_hovered.w = 114;
	continue_hovered.h = 113;

	continue_pressed.x = 128;
	continue_pressed.y = 238;
	continue_pressed.w = 116;
	continue_pressed.h = 113;

	settings_normal.x = 254;
	settings_normal.y = 354;
	settings_normal.w = 116;
	settings_normal.h = 113;

	settings_hovered.x = 4;
	settings_hovered.y = 354;
	settings_hovered.w = 114;
	settings_hovered.h = 113;

	settings_pressed.x = 128;
	settings_pressed.y = 354;
	settings_pressed.w = 116;
	settings_pressed.h = 113;

	credits_normal.x = 254;
	credits_normal.y = 472;
	credits_normal.w = 116;
	credits_normal.h = 114;

	credits_hovered.x = 4;
	credits_hovered.y = 472;
	credits_hovered.w = 114;
	credits_hovered.h = 114;

	credits_pressed.x = 128;
	credits_pressed.y = 472;
	credits_pressed.w = 116;
	credits_pressed.h = 114;

	exit_normal.x = 254;
	exit_normal.y = 593;
	exit_normal.w = 116;
	exit_normal.h = 113;

	exit_hovered.x = 4;
	exit_hovered.y = 593;
	exit_hovered.w = 114;
	exit_hovered.h = 113;

	exit_pressed.x = 128;
	exit_pressed.y = 593;
	exit_pressed.w = 116;
	exit_pressed.h = 113;

	resume_normal.x = 255;
	resume_normal.y = 713;
	resume_normal.w = 115;
	resume_normal.h = 113;

	resume_hovered.x = 4;
	resume_hovered.y = 713;
	resume_hovered.w = 115;
	resume_hovered.h = 113;

	resume_pressed.x = 129;
	resume_pressed.y = 713;
	resume_pressed.w = 116;
	resume_pressed.h = 113;

	back_menu_normal.x = 769;
	back_menu_normal.y = 121;
	back_menu_normal.w = 115;
	back_menu_normal.h = 113;

	back_menu_hovered.x = 517;
	back_menu_hovered.y = 121;
	back_menu_hovered.w = 116;
	back_menu_hovered.h = 113;

	back_menu_pressed.x = 643;
	back_menu_pressed.y = 121;
	back_menu_pressed.w = 116;
	back_menu_pressed.h = 113;

	slider_rect.x = 641;
	slider_rect.y = 559;
	slider_rect.w = 53;
	slider_rect.h = 51;

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
	pause_tex = App->textures->Load(pause_texture.GetString());


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

	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN || back_menu_btn->state == PRESSED)
		App->SaveGame();

	if (App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN || continue_btn->state == PRESSED) {
		App->LoadGame();
	}

	if (App->input->GetKey(SDL_SCANCODE_F7) == KEY_DOWN)
		App->audio->VolumeDown();

	if (App->input->GetKey(SDL_SCANCODE_F8) == KEY_DOWN)
		App->audio->VolumeUp();

	if (App->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN)
		App->audio->StopMusic();

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
	App->textures->UnLoad(pause_tex);
	pause_tex = nullptr;

	return true;
}


bool Scene::Load(pugi::xml_node& node)
{
	bool ret = true;

	scene_actual = node.child("scene_actual").attribute("value").as_int();

	CleanUp();
	Start();

	return ret;
}

bool Scene::Save(pugi::xml_node& node) const
{
	bool ret = true;

	node.append_child("scene_actual").append_attribute("value") = scene_actual;

	return ret;
}

void Scene::Restart() const
{
	App->scenemanager->FadeToBlack(scene_actual);
	App->entitymanager->player->visibility = false;
	p2List_item<Entity*>* tmp = App->entitymanager->entities.start;
	App->pause = false;
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
	//_TTF_Font * font = App->fonts->Load("fonts/open_sans/OpenSans-Bold.ttf", 12);
	//label = App->guimanager->CreateLabel(iPoint(500, 530), p2SString("Copyright (c) [2018] [Llu�s Moreu & Cere Venteo] Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files(the Software), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions : The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software. THE SOFTWARE IS PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE."), font, this);

	//HEADERS
	settings_home_btn = App->guimanager->CreateButton(iPoint(310, 187), settings_normal, settings_hovered, settings_pressed, this);
	credits_home_btn = App->guimanager->CreateButton(iPoint(310, 187), credits_normal, credits_hovered, credits_pressed, this);
	settings_hud_home_btn = App->guimanager->CreateButton(iPoint(310, 187), settings_normal, settings_hovered, settings_pressed, this);

	//BASE UI
	title_img = App->guimanager->CreateImage(iPoint(354, 145), title_rect, this);
	windows_img = App->guimanager->CreateImage(iPoint(300, 254), windows_rect, this);
	windows_hud_img = App->guimanager->CreateImage(iPoint(300, 254), windows_rect, this);

	//CREDITS
	license_img = App->guimanager->CreateImage(iPoint(392, 340), license_rect, this);

	//MAIN_MENU
	play_btn = App->guimanager->CreateButton(iPoint(409, 345), play_normal, play_hovered, play_pressed, this);
	continue_btn = App->guimanager->CreateButton(iPoint(581, 345), continue_normal, continue_hovered, continue_pressed, this);
	settings_btn = App->guimanager->CreateButton(iPoint(757, 345), settings_normal, settings_hovered, settings_pressed, this);
	credits_btn = App->guimanager->CreateButton(iPoint(495, 505), credits_normal, credits_hovered, credits_pressed, this);
	exit_btn = App->guimanager->CreateButton(iPoint(667, 505), exit_normal, exit_hovered, exit_pressed, this);

	//SETTINGS
	music_img = App->guimanager->CreateImage(iPoint(433, 350), music_rect, this);
	fx_img = App->guimanager->CreateImage(iPoint(733, 350), fx_rect, this);
	minus_music_img = App->guimanager->CreateImage(iPoint(346, 504), minus_rect, this);
	plus_music_img = App->guimanager->CreateImage(iPoint(600, 504), plus_rect, this);
	minus_fx_img = App->guimanager->CreateImage(iPoint(646, 504), minus_rect, this);
	plus_fx_img = App->guimanager->CreateImage(iPoint(900, 504), plus_rect, this);
	music_sli = App->guimanager->CreateSlider(iPoint(400, 504), slider_rect, this);
	fx_sli = App->guimanager->CreateSlider(iPoint(700, 504), slider_rect, this);

	//HUD
	coins_img = App->guimanager->CreateImage(iPoint(814, 11), coins_rect, this);
	life_img = App->guimanager->CreateImage(iPoint(1054, 11), life_rect, this);
	time_img = App->guimanager->CreateImage(iPoint(12, 16), score_rect, this);
	score_img = App->guimanager->CreateImage(iPoint(429, 16), score_rect, this);
	resume_btn = App->guimanager->CreateButton(iPoint(455, 367), resume_normal, resume_hovered, resume_pressed, this);
	settings_hud_btn = App->guimanager->CreateButton(iPoint(710, 367), settings_normal, settings_hovered, settings_pressed, this);
	back_menu_btn = App->guimanager->CreateButton(iPoint(583, 517), back_menu_normal, back_menu_hovered, back_menu_pressed, this);

	_TTF_Font * font = App->fonts->Load("fonts/zombiebites/Zombiebites.ttf", 48);

	time = App->guimanager->CreateLabel(iPoint(200, 46), time_str, font, this);
	score = App->guimanager->CreateLabel(iPoint(600, 46), score_str, font, this);
	coins = App->guimanager->CreateLabel(iPoint(950, 46), coin_str, font, this);
	lifes = App->guimanager->CreateLabel(iPoint(1150, 46), life_str, font, this);

}

void Scene::GUIStart()
{
	switch (scene_actual)
	{
	case 0:
		//MAINMENU
		title_img->Enabled(true);
		play_btn->Enabled(true);
		continue_btn->Enabled(true);
		settings_btn->Enabled(true);
		credits_btn->Enabled(true);
		exit_btn->Enabled(true);
		windows_img->Enabled(true);
		break;
	case 1:
		//enable HUD
		coins_img->Enabled(true);
		life_img->Enabled(true);
		time_img->Enabled(true);
		score_img->Enabled(true);
		time->Enabled(true);
		score->Enabled(true);
		coins->Enabled(true);
		lifes->Enabled(true);
		break;
	case 2:
		//enable HUD
		coins_img->Enabled(true);
		life_img->Enabled(true);
		time_img->Enabled(true);
		score_img->Enabled(true);
		time->Enabled(true);
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
		settings_btn->Enabled(false);
		credits_btn->Enabled(false);
		exit_btn->Enabled(false);
		windows_img->Enabled(false);
	}
	else if (settings_btn->state == PRESSED) {
		//disable
		title_img->Enabled(false);
		play_btn->Enabled(false);
		continue_btn->Enabled(false);
		settings_btn->Enabled(false);
		credits_btn->Enabled(false);
		exit_btn->Enabled(false);

		//enable
		settings_home_btn->Enabled(true);
		music_img->Enabled(true);
		fx_img->Enabled(true);
		minus_music_img->Enabled(true);
		plus_music_img->Enabled(true);
		minus_fx_img->Enabled(true);
		plus_fx_img->Enabled(true);
	}
	else if (settings_home_btn->state == PRESSED) {
		//disable
		settings_home_btn->Enabled(false);
		music_img->Enabled(false);
		fx_img->Enabled(false);
		minus_music_img->Enabled(false);
		plus_music_img->Enabled(false);
		minus_fx_img->Enabled(false);
		plus_fx_img->Enabled(false);

		//enable
		title_img->Enabled(true);
		play_btn->Enabled(true);
		continue_btn->Enabled(true);
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
		settings_btn->Enabled(false);
		credits_btn->Enabled(false);
		exit_btn->Enabled(false);

		//enable
		credits_home_btn->Enabled(true);
		license_img->Enabled(true);
	}
	else if (credits_home_btn->state == PRESSED) {
		//disable
		credits_home_btn->Enabled(false);
		license_img->Enabled(false);

		//enable
		title_img->Enabled(true);
		play_btn->Enabled(true);
		continue_btn->Enabled(true);
		settings_btn->Enabled(true);
		credits_btn->Enabled(true);
		exit_btn->Enabled(true);
	}
	else if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN && scene_actual != 0) { // IN GAME MENU---------------
		App->pause = true;

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
		music_img->Enabled(true);
		fx_img->Enabled(true);
		minus_music_img->Enabled(true);
		plus_music_img->Enabled(true);
		minus_fx_img->Enabled(true);
		plus_fx_img->Enabled(true);
	}
	else if (settings_hud_home_btn->state == PRESSED) {
		//disable
		settings_hud_home_btn->Enabled(false);
		music_img->Enabled(false);
		fx_img->Enabled(false);
		minus_music_img->Enabled(false);
		plus_music_img->Enabled(false);
		minus_fx_img->Enabled(false);
		plus_fx_img->Enabled(false);

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
		time->Enabled(false);
		score->Enabled(false);
		coins->Enabled(false);
		lifes->Enabled(false);

		restarting = true;

	}

	if (play_btn->state == PRESSED || continue_btn->state == PRESSED || settings_btn->state == PRESSED || settings_home_btn->state == PRESSED || credits_btn->state == PRESSED || credits_home_btn->state == PRESSED
		|| resume_btn->state == PRESSED || settings_hud_btn->state == PRESSED || settings_hud_home_btn->state == PRESSED || back_menu_btn->state == PRESSED)
		App->scene->AddFX(1, 0);


}

void Scene::HUDUpdate()
{
	p2SString time_str("%.1f", App->seconds_since_startup);
	p2SString score_str("%i", App->entitymanager->player->score);
	p2SString coin_str("%i", App->entitymanager->player->coin_counter);
	p2SString life_str("%i", App->entitymanager->player->lifes);

	time->SetText(time_str);
	score->SetText(score_str);
	coins->SetText(coin_str);
	lifes->SetText(life_str);
}


