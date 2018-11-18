#include "EntityManager.h"
#include "DevRookiesApp.h"
#include "Render.h"
#include "Entity.h"
#include "Player.h"
#include "OfficerSkeleton.h"
#include "JrGargoyle.h"
#include "PugiXml/src/pugixml.hpp"
#include "Textures.h"
#include "Map.h"
#include "Brofiler/Brofiler.h"

EntityManager::EntityManager()
{
	name.create("entitymanager");
	CreateEntity(entityType::PLAYER);
	CreateEntity(entityType::FLYING_ENEMY);
	CreateEntity(entityType::LAND_ENEMY);
}

EntityManager::~EntityManager()
{
}

bool EntityManager::Awake(pugi::xml_node &config)
{
	bool ret = true;

	p2List_item<Entity*>* tmp = entities.start;
	while (tmp != nullptr)
	{
		tmp->data->Awake(config);
		tmp = tmp->next;
	}
	folder.create(config.child("folder").child_value());
	texture_path = config.child("sprite_sheet").attribute("source").as_string();

	return ret;
}

bool EntityManager::Start()
{
	bool ret = true;
	
	p2List_item<Entity*>* tmp = entities.start;
	uint i = 0;
	while (tmp != nullptr)
	{
		tmp->data->Start(i);
		tmp = tmp->next;
		i++;
	}

	texture = App->textures->Load(PATH(folder.GetString(), texture_path.GetString()));

	return ret;
}

bool EntityManager::Restart()
{
	bool ret = true;
	p2List_item<Entity*>* tmp = entities.start;
	while (tmp != nullptr)
	{
		tmp->data->Restart();
		tmp = tmp->next;
	}

	return ret;
}

bool EntityManager::PreUpdate()
{
	BROFILER_CATEGORY("PreUpdateEntityManager", Profiler::Color::Orange);
	bool ret = true;
	p2List_item<Entity*>* tmp = entities.start;
	while (tmp != nullptr)
	{
		tmp->data->PreUpdate();
		tmp = tmp->next;
	}

	return ret;
}

bool EntityManager::Update(float dt)
{
	BROFILER_CATEGORY("UpdateEntityManager", Profiler::Color::LemonChiffon);
	bool ret = true;
	p2List_item<Entity*>* tmp = entities.start;
	while (tmp != nullptr)
	{
		tmp->data->Update(dt);
		tmp = tmp->next;
	}

	return ret;
}

bool EntityManager::PostUpdate()
{
	BROFILER_CATEGORY("PostUpdateEntityManager", Profiler::Color::Purple);
	bool ret = true;
	p2List_item<Entity*>* tmp = entities.start;
	while (tmp != nullptr)
	{
		tmp->data->PostUpdate();
		tmp = tmp->next;
	}
	return ret;
}

bool EntityManager::CleanUp()
{
	bool ret = true;
	p2List_item<Entity*>* tmp = entities.start;
	while (tmp != nullptr)
	{
		tmp->data->CleanUp();
		tmp = tmp->next;
	}
	entities.clear();
	return ret;
}

bool EntityManager::Save(pugi::xml_node& file) const
{
	bool ret = true;
	p2List_item<Entity*>* tmp = entities.start;
	while (tmp != nullptr)
	{
		if (tmp->data->type == entityType::PLAYER)
		{
			tmp->data->Save(file.append_child("player"));
		}
		if (tmp->data->type == entityType::FLYING_ENEMY)
		{
			tmp->data->Save(file.append_child("JrGargoyle"));
		}
		if (tmp->data->type == entityType::LAND_ENEMY)
		{
			tmp->data->Save(file.append_child("OfficerSkeleton"));
		}
		tmp = tmp->next;
	}
	return ret;
}

bool EntityManager::Load(pugi::xml_node& file)
{
	bool ret = true;
	p2List_item<Entity*>* tmp = entities.start;
	pugi::xml_node player = file.child("player");
	pugi::xml_node JrGargoyle = file.child("JrGargoyle");
	pugi::xml_node OfficerSkeleton = file.child("OfficerSkeleton");
	while (tmp != nullptr)
	{
		if (tmp->data->type == entityType::PLAYER)
		{
			tmp->data->Load(player);
		}
		if (tmp->data->type == entityType::FLYING_ENEMY)
		{
			tmp->data->Load(JrGargoyle);
			JrGargoyle = JrGargoyle.next_sibling("JrGargoyle");
		}
		if (tmp->data->type == entityType::LAND_ENEMY)
		{
			tmp->data->Load(OfficerSkeleton);
			OfficerSkeleton = OfficerSkeleton.next_sibling("OfficerSkeleton");
		}
		tmp = tmp->next;
	}
	return ret;
}

Entity* EntityManager::CreateEntity(entityType type)
{
	Entity* tmp = nullptr;

	switch (type)
	{
	case entityType::PLAYER:
		player = new Player(type);
		entities.add(player);
		break;
	case entityType::FLYING_ENEMY:
		for (uint i = 0; i < gargoyle_count; i++)
		{
			tmp = new JrGargoyle(type);
			entities.add(tmp);
		}
		break;
	case entityType::LAND_ENEMY:
		for (uint i = 0; i < skeleton_count; i++)
		{
			tmp = new OfficerSkeleton(type);
			entities.add(tmp);
		}
		break;
	}

	return tmp;
}

bool EntityManager::DestroyEntity(Entity * entity)
{
	for (int i = 0; i < entities.count(); i++)
	{
		if (entities[i] == entity) {
			entities[i]->CleanUp();
			delete entities[i];
			entities[i] = nullptr;
		}
	}
	return true;
}

void EntityManager::OnCollision(Collider* collider1, Collider* collider2)
{
	for (int i = 0; i < entities.count(); i++)
	{

	}
}
