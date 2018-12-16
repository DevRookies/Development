#ifndef __AUDIO_H__
#define __AUDIO_H__

#include "Module.h"
#include "SDL_mixer\include\SDL_mixer.h"
#include "p2List.h"

struct _Mix_Music;
struct Mix_Chunk;

class Audio : public Module
{
public:
	uint volume = 0u;
	uint volume_fx = 0u;
	uint max_volume = 0u;
	float default_music_fade_time;
	uint volume_change_ratio = 0u;
	bool mute;
	bool mute_volume;
	bool mute_fx;

	Audio();

	// Destructor
	virtual ~Audio();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before quitting
	bool CleanUp();

	// Play a music file
	bool PlayMusic(const char* path);

	// Load a WAV in memory
	unsigned int LoadFx(const char* path);

	// Play a previously loaded WAV
	bool PlayFx(unsigned int fx, int repeat = 0);

	//Change Volume	
	void StopMusic(int mut);
	void VolumeUp(int vol);
	void VolumeDown(int vol);
	void SliderVolumeFx(int vol);

	//Save & Load volume
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

private:

	_Mix_Music*			music = nullptr;
	p2List<Mix_Chunk*>	fx;

public:	
	p2SString			folder_music;
	p2SString			folder_sfx;
};

#endif // __AUDIO_H__