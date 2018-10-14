#include "p2Defs.h"
#include "p2Log.h"
#include "Audio.h"
#include "p2List.h"

#include "SDL/include/SDL.h"
#include "SDL_mixer\include\SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

Audio::Audio() : Module()
{
	music = NULL;
	name.create("audio");
}

// Destructor
Audio::~Audio()
{}

// Called before render is available
bool Audio::Awake(pugi::xml_node& config)
{
	LOG("Loading Audio Mixer");
	bool ret = true;

	volume = config.child("volume").attribute("value").as_uint();
	volume_fx = config.child("volume_fx").attribute("value").as_uint();
	default_music_fade_time = config.child("default_music_fade_time").attribute("value").as_float();
	volume_change_ratio = config.child("volume_change_ratio").attribute("value").as_uint();
	mute = config.child("mute").attribute("value").as_bool(false);

	folder_music = config.child("music").child_value("folder");
	folder_sfx = config.child("sfx").child_value("folder");

	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
	{
		LOG("SDL_INIT_AUDIO could not initialize! SDL_Error: %s\n", SDL_GetError());
		active = false;
		ret = true;
	}

	// load support for the JPG and PNG image formats
	int flags = MIX_INIT_OGG;
	int init = Mix_Init(flags);

	if((init & flags) != flags)
	{
		LOG("Could not initialize Mixer lib. Mix_Init: %s", Mix_GetError());
		active = false;
		ret = true;
	}

	//Initialize SDL_mixer
	if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		LOG("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		active = false;
		ret = true;
	}

	return ret;
}

// Called before quitting
bool Audio::CleanUp()
{
	if(!active)
		return true;

	LOG("Freeing sound FX, closing Mixer and Audio subsystem");

	if(music != NULL)
	{
		Mix_FreeMusic(music);
	}

	p2List_item<Mix_Chunk*>* item;
	for(item = fx.start; item != NULL; item = item->next)
		Mix_FreeChunk(item->data);

	fx.clear();

	Mix_CloseAudio();
	Mix_Quit();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);

	return true;
}

// Play a music file
bool Audio::PlayMusic(const char* path)
{
	bool ret = true;

	if(!active)
		return false;

	if(music != NULL)
	{
		if(default_music_fade_time > 0.0f)
		{
			Mix_FadeOutMusic(int(default_music_fade_time * 1000.0f));
		}
		else
		{
			Mix_HaltMusic();
		}

		// this call blocks until fade out is done
		Mix_FreeMusic(music);
	}

	p2SString tmp("%s%s", folder_music.GetString(), path);

	music = Mix_LoadMUS(tmp.GetString());

	if(music == NULL)
	{
		LOG("Cannot load music %s. Mix_GetError(): %s\n", path, Mix_GetError());
		ret = false;
	}
	else
	{
		if(default_music_fade_time > 0.0f)
		{
			if(Mix_FadeInMusic(music, -1, (int) (default_music_fade_time * 1000.0f)) < 0)
			{
				LOG("Cannot fade in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
		else
		{
			if(Mix_PlayMusic(music, -1) < 0)
			{
				LOG("Cannot play in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
	}

	LOG("Successfully playing %s", path);
	return ret;
}

// Load WAV
unsigned int Audio::LoadFx(const char* path)
{
	unsigned int ret = 0;

	if(!active)
		return 0;

	p2SString tmp("%s%s", folder_sfx.GetString(), path);

	Mix_Chunk* chunk = Mix_LoadWAV(tmp.GetString());

	if(chunk == NULL)
	{
		LOG("Cannot load wav %s. Mix_GetError(): %s", path, Mix_GetError());
	}
	else
	{
		fx.add(chunk);
		ret = fx.count();
	}

	return ret;
}

// Play WAV
bool Audio::PlayFx(unsigned int id, int repeat, uint volume)
{
	bool ret = false;

	if(!active)
		return false;

	if(id > 0 && id <= fx.count())
	{
		Mix_VolumeChunk(fx[id - 1], volume_fx);
		Mix_PlayChannel(-1, fx[id - 1], repeat);
	}

	return ret;
}

bool Audio::StopMusic()
{
		Mix_HaltMusic();
		mute = true;
		return true;
}

void Audio::VolumeUp()
{
	volume += volume_change_ratio;
	Mix_VolumeMusic(volume);
	volume_fx += volume_change_ratio;
}

void Audio::VolumeDown()
{
	volume -= volume_change_ratio;
	Mix_VolumeMusic(volume);
	volume_fx -= volume_change_ratio;
}


bool Audio::Load(pugi::xml_node& data)
{
	volume = data.child("volume").attribute("value").as_uint();
	mute = data.child("mute").attribute("value").as_bool();
	volume_fx = data.child("volume_fx").attribute("vale").as_uint();

	return true;
}

bool Audio::Save(pugi::xml_node& data) const
{
	pugi::xml_node vol = data.append_child("volume");
	vol.append_attribute("value") = volume;

	pugi::xml_node vol_fx = data.append_child("volume_fx");
	vol_fx.append_attribute("value") = volume_fx;

	pugi::xml_node mute = data.append_child("mute");
	mute.append_attribute("value") = mute;


	return true;
}