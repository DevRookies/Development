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
	uint volume;
	uint volume_fx;
	float default_music_fade_time;
	uint volume_change_ratio;
	bool mute;

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
	bool PlayFx(unsigned int fx, int repeat = 0, uint volume = 128);

	//Change Volume	
	bool StopMusic();
	void VolumeUp();
	void VolumeDown();

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