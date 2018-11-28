#ifndef __DEV_ROOKIES_APP_H__
#define __DEV_ROOKIES_APP_H__

#include "p2List.h"
#include "Module.h"
#include "PerfTimer.h"
#include "Timer.h"
#include "PugiXml\src\pugixml.hpp"

// Modules
class Window;
class Input;
class Render;
class Textures;
class Audio;
class Scene;
class Map;
class SceneManager;
class Collision;
class PathFinding;
class EntityManager;
class GUIManager;
class Fonts;

class DevRookiesApp
{
public:

	// Constructor
	DevRookiesApp(int argc, char* args[]);

	// Destructor
	virtual ~DevRookiesApp();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update();

	// Called before quitting
	bool CleanUp();

	// Add a new module to handle
	void AddModule(Module* module, bool active = true);

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;

	void LoadGame();
	void SaveGame() const;
	void GetSaveGames(p2List<p2SString>& list_to_fill) const;

	bool pause = false;

private:

	// Load config file
	pugi::xml_node LoadConfig(pugi::xml_document&) const;

	// Call modules before each loop iteration
	void PrepareUpdate();

	// Call modules before each loop iteration
	void FinishUpdate();

	// Call modules before each loop iteration
	bool PreUpdate();

	// Call modules on each loop iteration
	bool DoUpdate();

	// Call modules after each loop iteration
	bool PostUpdate();

	// Load / Save
	bool LoadGameNow();
	bool SavegameNow() const;



public:

	// Modules
	Window *			win = nullptr;
	Input*				input = nullptr;
	Render*				render = nullptr;
	Textures*			textures = nullptr;
	Audio*				audio = nullptr;
	Scene*				scene = nullptr;
	Map*				map = nullptr;
	SceneManager*		scenemanager = nullptr;
	Collision*			collision = nullptr;
	PathFinding*		pathfinding = nullptr;
	EntityManager*		entitymanager = nullptr;
	GUIManager*			guimanager = nullptr;
	Fonts*				fonts = nullptr;

private:

	p2List<Module*>		modules;
	uint				frames;
	int					argc;
	char**				args;

	p2SString			title;
	p2SString			organization;
	uint32				frame_rate;

	mutable bool		want_to_save;
	bool				want_to_load;
	p2SString			load_game;
	mutable p2SString	save_game;

	PerfTimer			ptimer;
	uint64				frame_count = 0;
	Timer				startup_time;
	Timer				frame_time;
	Timer				last_sec_frame_time;
	uint32				last_sec_frame_count = 0;
	uint32				prev_last_sec_frame_count = 0;
	float				dt = 0.0f;
	bool				framerate_cap_enabled = true;
	

};

extern DevRookiesApp* App; 

#endif