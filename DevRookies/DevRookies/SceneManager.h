#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include "Module.h"
#include "SDL\include\SDL_rect.h"

class SceneManager : public Module
{
public:
	SceneManager();
	~SceneManager();

	bool Start();
	bool Update(float dt);
	bool FadeToBlack(float time = 2.0f);
	

	enum fade_step
	{
		none,
		fade_to_black,
		fade_from_black
	} current_step = fade_step::none;

	

private:

	

	Uint32			start_time = 0;
	Uint32			total_time = 0;
	SDL_Rect		screen;
	uint			scene_on = 0;
};

#endif //__SCENEMANAGER_H__