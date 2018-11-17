#include <iostream> 
#include "p2Defs.h"
#include "p2Log.h"
#include "Window.h"
#include "Input.h"
#include "Render.h"
#include "Textures.h"
#include "Audio.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Map.h"
#include "Player.h"
#include "Collision.h"
#include "Pathfinding.h"
#include "EntityManager.h"
#include "DevRookiesApp.h"
#include"Brofiler/Brofiler.h"

// Constructor
DevRookiesApp::DevRookiesApp(int argc, char* args[]) : argc(argc), args(args)
{
	PERF_START(ptimer);
	frames = 0;
	want_to_save = want_to_load = false;

	input = new Input();
	win = new Window();
	render = new Render();
	textures = new Textures();
	audio = new Audio();
	map = new Map();
	scene = new Scene();
	scenemanager = new SceneManager();
	collision = new Collision();
	pathfinding = new PathFinding();
	entitymanager = new EntityManager();

	// Ordered for awake / Start / Update
	// Reverse order of CleanUp
	AddModule(input);
	AddModule(win);
	AddModule(textures);
	AddModule(audio);
	AddModule(map);
	AddModule(scene);
	AddModule(scenemanager);
	AddModule(collision);
	AddModule(pathfinding);
	AddModule(entitymanager);

	// render last to swap buffer
	AddModule(render);

	PERF_PEEK(ptimer);
}

// Destructor
DevRookiesApp::~DevRookiesApp()
{
	// release modules
	p2List_item<Module*>* item = modules.end;

	while(item != NULL)
	{
		RELEASE(item->data);
		item = item->prev;
	}

	modules.clear();
}

void DevRookiesApp::AddModule(Module* module, bool active)
{
	module->Init(active);
	modules.add(module);
}

// Called before render is available
bool DevRookiesApp::Awake()
{
	PERF_START(ptimer);

	pugi::xml_document	config_file;
	pugi::xml_node		config;
	pugi::xml_node		app_config;

	

	bool ret = false;
		
	config = LoadConfig(config_file);

	if(config.empty() == false)
	{
		// self-config
		ret = true;
		app_config = config.child("app");
		title.create(app_config.child("title").child_value());
		organization.create(app_config.child("organization").child_value());
		frame_rate = app_config.child("framerate_cap").attribute("rate").as_uint();
		framerate_cap_enabled = app_config.child("framerate_cap").attribute("enabled").as_bool();
		save_game.create(app_config.child("save").child_value());
		load_game = save_game;
		
	}

	if(ret == true)
	{
		p2List_item<Module*>* item;
		item = modules.start;

		while(item != NULL && ret == true)
		{
			ret = item->data->Awake(config.child(item->data->name.GetString()));
			item = item->next;
		}
	}

	PERF_PEEK(ptimer);

	return ret;
}

// Called before the first frame
bool DevRookiesApp::Start()
{
	PERF_START(ptimer);

	bool ret = true;
	p2List_item<Module*>* item;
	item = modules.start;
	Module* module = NULL;

	for (item = modules.start; item != NULL && ret == true; item = item->next)
	{
		module = item->data;

		if (module->active == false) {
			continue;
		}

		ret = item->data->Start();
	}

	PERF_PEEK(ptimer);

	return ret;
}

// Called each loop iteration
bool DevRookiesApp::Update()
{
	BROFILER_CATEGORY("Update", Profiler::Color::LimeGreen);
	bool ret = true;
	PrepareUpdate();

	if(input->GetWindowEvent(WE_QUIT) == true)
		ret = false;

	if(ret == true)
		ret = PreUpdate();

	if(ret == true)
		ret = DoUpdate();

	if(ret == true)
		ret = PostUpdate();

	FinishUpdate();
	return ret;
}

// ---------------------------------------------
pugi::xml_node DevRookiesApp::LoadConfig(pugi::xml_document& config_file) const
{
	pugi::xml_node ret;

	pugi::xml_parse_result result = config_file.load_file("config.xml");

	if(result == NULL)
		LOG("Could not load map xml file config.xml. pugi error: %s", result.description());
	else
		ret = config_file.child("config");

	return ret;
}

// ---------------------------------------------
void DevRookiesApp::PrepareUpdate()
{
	BROFILER_CATEGORY("PrepareUpdate", Profiler::Color::Blue);
	frame_count++;
	last_sec_frame_count++;

	dt = frame_time.ReadSec();
	frame_time.Start();
}

// ---------------------------------------------
void DevRookiesApp::FinishUpdate()
{
	BROFILER_CATEGORY("FinishUpdate", Profiler::Color::PaleVioletRed);

	if(want_to_save == true)
		SavegameNow();

	if(want_to_load == true)
		LoadGameNow();

	// Framerate calculations --
	if (last_sec_frame_time.Read() > 1000)
	{
		last_sec_frame_time.Start();
		prev_last_sec_frame_count = last_sec_frame_count;
		last_sec_frame_count = 0;
	}

	float avg_fps = float(frame_count) / startup_time.ReadSec();
	float seconds_since_startup = startup_time.ReadSec();
	uint32 last_frame_ms = frame_time.Read();
	uint32 frames_on_last_update = prev_last_sec_frame_count;

	BROFILER_CATEGORY("Waiting", Profiler::Color::SeaGreen);

	if (last_frame_ms < frame_rate && framerate_cap_enabled)
	{
		PerfTimer delay_timer;
		SDL_Delay(frame_rate - last_frame_ms);
		LOG("waited for: %.2f ms expected time: %u ms", delay_timer.ReadMs(), frame_rate - last_frame_ms);
	}

	static char title[256];
	sprintf_s(title, 256, "Av.FPS: %.2f Last Frame Ms: %02u Last sec frames: %i  Time since startup: %.3f Frame Count: %lu ",
		avg_fps, last_frame_ms, frames_on_last_update, seconds_since_startup, frame_count);
	App->win->SetTitle(title);
}

// Call modules before each loop iteration
bool DevRookiesApp::PreUpdate()
{
	BROFILER_CATEGORY("PreUpdate", Profiler::Color::Orange);

	bool ret = true;
	p2List_item<Module*>* item;
	item = modules.start;
	Module* pModule = NULL;

	for(item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if(pModule->active == false) {
			continue;
		}

		ret = item->data->PreUpdate();
	}

	return ret;
}

// Call modules on each loop iteration
bool DevRookiesApp::DoUpdate()
{
	BROFILER_CATEGORY("DoUpdate", Profiler::Color::GoldenRod);

	bool ret = true;
	if (App->input->GetKey(SDL_SCANCODE_F11) == KEY_DOWN)
		framerate_cap_enabled = !framerate_cap_enabled;

	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
		pause = !pause;

	if (pause)
		dt = 0;

	p2List_item<Module*>* item;
	item = modules.start;
	Module* pModule = NULL;

	for(item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if(pModule->active == false) {
			continue;
		}

		ret = item->data->Update(dt);
	}

	return ret;
}

// Call modules after each loop iteration
bool DevRookiesApp::PostUpdate()
{
	BROFILER_CATEGORY("PostUpdate", Profiler::Color::Purple);

	bool ret = true;
	p2List_item<Module*>* item;
	Module* pModule = NULL;

	for(item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if(pModule->active == false) {
			continue;
		}

		ret = item->data->PostUpdate();
	}

	return ret;
}

// Called before quitting
bool DevRookiesApp::CleanUp()
{
	BROFILER_CATEGORY("CleanUp", Profiler::Color::Salmon);

	PERF_START(ptimer);

	bool ret = true;
	p2List_item<Module*>* item;
	item = modules.end;

	while(item != NULL && ret == true)
	{
		ret = item->data->CleanUp();
		item = item->prev;
	}

	PERF_PEEK(ptimer);

	return ret;
}

// ---------------------------------------
int DevRookiesApp::GetArgc() const
{
	return argc;
}

// ---------------------------------------
const char* DevRookiesApp::GetArgv(int index) const
{
	if(index < argc)
		return args[index];
	else
		return NULL;
}

// ---------------------------------------
const char* DevRookiesApp::GetTitle() const
{
	return title.GetString();
}

// ---------------------------------------
const char* DevRookiesApp::GetOrganization() const
{
	return organization.GetString();
}

// Load / Save
void DevRookiesApp::LoadGame()
{
	// we should be checking if that file actually exist
	// from the "GetSaveGames" list
	want_to_load = true;
}

// ---------------------------------------
void DevRookiesApp::SaveGame() const
{
	// we should be checking if that file actually exist
	// from the "GetSaveGames" list ... should we overwrite ?

	want_to_save = true;
}

// ---------------------------------------
void DevRookiesApp::GetSaveGames(p2List<p2SString>& list_to_fill) const
{
	// need to add functionality to file_system module for this to work
}

bool DevRookiesApp::LoadGameNow()
{
	bool ret = false;

	pugi::xml_document data;
	pugi::xml_node root;

	pugi::xml_parse_result result = data.load_file(load_game.GetString());

	if(result != NULL)
	{
		LOG("Loading new Game State from %s...", load_game.GetString());

		root = data.child("game_state");

		p2List_item<Module*>* item = modules.start;
		ret = true;

		while(item != NULL && ret == true)
		{
			ret = item->data->Load(root.child(item->data->name.GetString()));
			item = item->next;
		}

		data.reset();
		if(ret == true)
			LOG("...finished loading");
		else
			LOG("...loading process interrupted with error on module %s", (item != NULL) ? item->data->name.GetString() : "unknown");
	}
	else
		LOG("Could not parse game state xml file %s. pugi error: %s", load_game.GetString(), result.description());

	want_to_load = false;
	return ret;
}

bool DevRookiesApp::SavegameNow() const
{
	bool ret = true;

	LOG("Saving Game State to %s...", save_game.GetString());

	// xml object were we will store all data
	pugi::xml_document data;
	pugi::xml_node root;
	
	root = data.append_child("game_state");

	p2List_item<Module*>* item = modules.start;

	while(item != NULL && ret == true)
	{
		ret = item->data->Save(root.append_child(item->data->name.GetString()));
		item = item->next;
	}

	if(ret == true)
	{
		data.save_file(save_game.GetString());
		LOG("... finished saving", );
	}
	else
		LOG("Save process halted from an error in module %s", (item != NULL) ? item->data->name.GetString() : "unknown");

	data.reset();
	want_to_save = false;
	return ret;
}
