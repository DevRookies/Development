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
#include "Scene2.h"
#include "SceneManager.h"
#include "Player.h"

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
	tile_name = config.child("tile_name").child_value();
	lvl1_music_name = config.child("lvl1_music_name").child_value();
	player.x = config.child("player").attribute("x").as_int();
	player.y = config.child("player").attribute("y").as_int();
	camera.x = config.child("camera").attribute("x").as_int();
	camera.y = config.child("camera").attribute("y").as_int();
	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	App->map->Load(tile_name.GetString());
	App->audio->PlayMusic(lvl1_music_name.GetString());
	App->player->Start(FIRE);
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
	
	

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
		App->scenemanager->FadeToBlack(App->scene, App->scene);

	if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)
		App->scenemanager->FadeToBlack(App->scene, App->scene2);

	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		App->SaveGame();

	if(App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		App->LoadGame();

	if (App->input->GetKey(SDL_SCANCODE_F8) == KEY_DOWN)
		App->audio->VolumeUp();

	if (App->input->GetKey(SDL_SCANCODE_F7) == KEY_DOWN)
		App->audio->VolumeDown();

	if (App->input->GetKey(SDL_SCANCODE_F11) == KEY_DOWN)
		App->audio->StopMusic();
	

	//App->render->Blit(img, 0, 0);
	App->map->Draw();

	p2SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
					App->map->data.width, App->map->data.height,
					App->map->data.tile_width, App->map->data.tile_height,
					App->map->data.tilesets.count());

	App->win->SetTitle(title.GetString());
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

	return true;
}


// Load Game State
bool Scene::Load(pugi::xml_node& data)
{
	camera.x = data.child("camera").attribute("x").as_int();
	camera.y = data.child("camera").attribute("y").as_int();
	player.x = data.child("player").attribute("x").as_int();
	player.y = data.child("player").attribute("y").as_int();

	return true;
}

// Save Game State
bool Scene::Save(pugi::xml_node& data) const
{
	pugi::xml_node node = data.append_child("camera");

	node.append_attribute("x") = camera.x;
	node.append_attribute("y") = camera.y;

	node = data.append_child("player");

	node.append_attribute("x") = player.x;
	node.append_attribute("y") = player.y;

	return true;
}