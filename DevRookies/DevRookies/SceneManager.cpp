#include <math.h>
#include "DevRookiesApp.h"
#include "SceneManager.h"
#include "Render.h"
#include "Window.h"
#include "Map.h"
#include "SDL/include/SDL_render.h"
#include "SDL/include/SDL_timer.h"

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{}

// Load assets
bool SceneManager::Start()
{
	screen = { 0, 0, App->win->GetScreenWidth(), App->win->GetScreenHeight() };
	SDL_SetRenderDrawBlendMode(App->render->renderer, SDL_BLENDMODE_BLEND);
	return true;
}

// Update: draw background
bool SceneManager::Update(float dt)
{
	if (current_step == fade_step::none)
		return true;

	Uint32 now = SDL_GetTicks() - start_time;
	float normalized = MIN(1.0f, (float)now / (float)total_time);

	switch (current_step)
	{
	case fade_step::fade_to_black:
	{
		if (now >= total_time)
		{
			module_disable->active = false;
			App->map->CleanUp();
			module_enable->active = true;;
			module_enable->OnFade();

			total_time += total_time;
			start_time = SDL_GetTicks();
			current_step = fade_step::fade_from_black;
		}
	} break;

	case fade_step::fade_from_black:
	{
		normalized = 1.0F - normalized;

		if (now >= total_time)
			current_step = fade_step::none;
	} break;
	}

	// Finally render the black square with alpha on the screen
	SDL_SetRenderDrawColor(App->render->renderer, 0, 0, 0, (Uint8)(normalized * 255.0F));
	SDL_RenderFillRect(App->render->renderer, &screen);

	return true;
}

// Fade to black. At mid point deactivate one module, then activate the other
bool SceneManager::FadeToBlack(Module* module_off, Module* module_on, float time)
{
	bool ret = false;

	if (current_step == fade_step::none)
	{
		current_step = fade_step::fade_to_black;
		start_time = SDL_GetTicks();
		total_time = (Uint32)(time * 0.5f * 1000.0f);
		module_disable = module_off;
		module_enable = module_on;
		ret = true;
	}

	return ret;
}