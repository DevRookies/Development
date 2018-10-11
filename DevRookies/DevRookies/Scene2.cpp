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

Scene2::Scene2() : Module()
{
	name.create("scene2");
}

// Destructor
Scene2::~Scene2()
{}

// Called before render is available
bool Scene2::Awake(pugi::xml_node& conf)
{
	LOG("Loading Scene");
	bool ret = true;
	tile_name = conf.child("tile_name").child_value();
	lvl2_music_name = conf.child("lvl2_music_name").child_value();
	return ret;
}

// Called before the first frame
bool Scene2::Start()
{
	App->map->Load(tile_name.GetString());
	App->audio->PlayMusic(lvl2_music_name.GetString());
	App->player->AddColliderPlayer();
	App->player->SetPosition(0, 0);
	App->render->SetCamera(0, 0);
	return true;
}

// Called each loop iteration
bool Scene2::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene2::Update(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		App->scenemanager->FadeToBlack(App->scene2, App->scene);

	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
		App->scenemanager->FadeToBlack(App->scene2, App->scene2);

	if (App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		App->LoadGame();

	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		App->SaveGame();

	if (App->input->GetKey(SDL_SCANCODE_F8) == KEY_DOWN)
		App->audio->VolumeUp();

	if (App->input->GetKey(SDL_SCANCODE_F7) == KEY_DOWN)
		App->audio->VolumeDown();

	if (App->input->GetKey(SDL_SCANCODE_F11) == KEY_DOWN)
		App->audio->StopMusic();

	if (App->input->GetKey(SDL_SCANCODE_I) == KEY_REPEAT)
		App->render->camera.y += 1;

	if (App->input->GetKey(SDL_SCANCODE_K) == KEY_REPEAT)
		App->render->camera.y -= 1;

	if (App->input->GetKey(SDL_SCANCODE_J) == KEY_REPEAT)
		App->render->camera.x += 1;

	if (App->input->GetKey(SDL_SCANCODE_L) == KEY_REPEAT)
		App->render->camera.x -= 1;

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
bool Scene2::PostUpdate()
{
	bool ret = true;

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool Scene2::CleanUp()
{
	LOG("Freeing scene");

	return true;
}
