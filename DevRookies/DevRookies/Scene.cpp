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

	tile_name_scene1 = config.child("tile_name_scene1").child_value();
	tile_name_scene2 = config.child("tile_name_scene2").child_value();
	lvl1_music_name = config.child("lvl1_music_name").child_value();
	lvl2_music_name = config.child("lvl2_music_name").child_value();
	camera.x = config.child("camera").attribute("x").as_int();
	camera.y = config.child("camera").attribute("y").as_int();
	godmode_texture = config.child("godmode_tex").child_value();
	godmode_pos = { config.child("godmode_tex").attribute("x").as_float(),  config.child("godmode_tex").attribute("y").as_float() };
	pause_texture = config.child("pause_tex").child_value();
	pause_pos = { config.child("pause_tex").attribute("x").as_float(),  config.child("pause_tex").attribute("y").as_float() };
	active = true;


	//xml this rects!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	img_rect.x = 4;
	img_rect.y = 120;
	img_rect.w = 115;
	img_rect.h = 114;

	img2_rect.x = 11;
	img2_rect.y = 962;
	img2_rect.w = 681;
	img2_rect.h = 453;

	//normal.x = 0;
	//normal.y = 113;
	//normal.w = 229;
	//normal.h = 69;

	//hovered.x = 411;
	//hovered.y = 169;
	//hovered.w = 229;
	//hovered.h = 69;

	//pressed.x = 642;
	//pressed.y = 169;
	//pressed.w = 229;
	//pressed.h = 69;

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	uchar* data = nullptr;
	switch (scene_actual)
	{
	case 1:
		App->map->Load(tile_name_scene1.GetString());
		App->audio->PlayMusic(lvl1_music_name.GetString());
		App->entitymanager->player->Restart(FIRE);
		int width, height;
		if (App->map->CreateWalkabilityMap(width, height, &data))
			App->pathfinding->SetMap(width, height, data);
		break;
	case 2:
		App->map->Load(tile_name_scene2.GetString());
		App->audio->PlayMusic(lvl2_music_name.GetString());
		App->entitymanager->player->Restart(ICE);
		break;
	default:
		break;
	}
	
	_TTF_Font * font = App->fonts->Load("fonts/open_sans/OpenSans-Bold.ttf", 12);
	image2 = App->guimanager->CreateImage(iPoint(230, 230), img2_rect, App->guimanager->GetAtlas(), this);
	image = App->guimanager->CreateImage(iPoint(250, 250), img_rect, App->guimanager->GetAtlas(), this);


	label = App->guimanager->CreateLabel(iPoint(500, 530), p2SString("Hello World"), font, this);
	button = App->guimanager->CreateButton(iPoint(500, 600), normal, hovered, pressed, App->guimanager->GetAtlas(), this);

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

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN ) {
		scene_actual = 1;
		App->scenemanager->FadeToBlack();
	}
		
	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) {
		Restart(); 
	}

	if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN) {
		scene_actual = 2;
		App->scenemanager->FadeToBlack();
	}
		

	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		App->SaveGame();

	if(App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		App->LoadGame();

	if (App->input->GetKey(SDL_SCANCODE_F7) == KEY_DOWN)
		App->audio->VolumeDown();

	if (App->input->GetKey(SDL_SCANCODE_F8) == KEY_DOWN)
		App->audio->VolumeUp();

	if (App->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN)
		App->audio->StopMusic();
	

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

	if (App->pause) {
		pause_pos.x = App->render->camera.x + App->win->GetScreenWidth() / 6;
		pause_pos.y = App->render->camera.y + App->win->GetScreenHeight() / 3;
		App->render->Blit(pause_tex, pause_pos.x, pause_pos.y, NULL, -1.0f);
	}

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	BROFILER_CATEGORY("PostUpdateScene", Profiler::Color::Purple);
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");
	App->map->CleanUp();
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
}


