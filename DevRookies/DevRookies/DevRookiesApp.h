#ifndef __DEV_ROOKIES_APP_H__
#define __DEV_ROOKIES_APP_H__

#include "p2List.h"
#include "Module.h"
#include "PugiXml\src\pugixml.hpp"

// Modules
class Window;
class Input;
class Render;
class Textures;
class Audio;
class Scene;
class Scene2;
class Map;
class SceneManager;
class Player;
class Collision;
class PathFinding;

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
	Window * win = nullptr;
	Input*				input = nullptr;
	Render*				render = nullptr;
	Textures*			textures = nullptr;
	Audio*				audio = nullptr;
	Scene*				scene = nullptr;
	Scene2*				scene2 = nullptr;
	Map*				map = nullptr;
	SceneManager*		scenemanager = nullptr;
	Player*				player = nullptr;
	Collision*			collision = nullptr;
	PathFinding*		pathfinding = nullptr;

private:

	p2List<Module*>		modules;
	uint				frames;
	float				dt;
	int					argc;
	char**				args;

	p2SString			title;
	p2SString			organization;

	mutable bool		want_to_save;
	bool				want_to_load;
	p2SString			load_game;
	mutable p2SString	save_game;
};

extern DevRookiesApp* App; // I'm happy :-)

#endif