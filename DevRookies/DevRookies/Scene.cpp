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
#include "Player.h"
#include "SceneManager.h"

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
	active = true;
	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	switch (scene_actual)
	{
	case 1:
		App->player->Start(FIRE);
		App->map->Load(tile_name_scene1.GetString());
		App->audio->PlayMusic(lvl1_music_name.GetString());
		break;
	case 2:
		App->player->Start(ICE);
		App->map->Load(tile_name_scene2.GetString());
		App->audio->PlayMusic(lvl2_music_name.GetString());
		break;
	default:
		break;
	}
	player.x = App->map->init_player_position.x;
	player.y = App->map->init_player_position.y;
	App->player->AddColliderPlayer();
	App->player->SetPosition(player.x, player.y);
	App->render->SetCamera(camera.x, camera.y);
	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	
	

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN ) {
		App->scenemanager->FadeToBlack(1);
	}
		
	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) {
		Restart(); 
	}

	if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN) {
		App->scenemanager->FadeToBlack(2);
	}
		

	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		App->SaveGame();

	if(App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		App->LoadGame();

	if (App->input->GetKey(SDL_SCANCODE_F7) == KEY_DOWN)
		App->audio->VolumeDown();

	if (App->input->GetKey(SDL_SCANCODE_F8) == KEY_DOWN)
		App->audio->VolumeUp();

	if (App->input->GetKey(SDL_SCANCODE_F11) == KEY_DOWN)
		App->audio->StopMusic();
	

	App->map->Draw();

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
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
	App->player->CleanUp();

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
}

