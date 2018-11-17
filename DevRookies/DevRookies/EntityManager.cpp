#include "EntityManager.h"
#include "DevRookiesApp.h"
#include "Render.h"
#include "Entity.h"
#include "Player.h"
#include "OfficerSkeleton.h"
#include "JrGargoyle.h"
#include "PugiXml/src/pugixml.hpp"
#include "Textures.h"
#include "Brofiler/Brofiler.h"

EntityManager::EntityManager()
{
	name.create("entitymanager");
	CreateEntity(Entity::entityType::PLAYER, {0,0});
}

EntityManager::~EntityManager()
{
}

bool EntityManager::Awake(pugi::xml_node &config)
{
	bool ret = true;
	player->Awake(config.child("player"));
	folder.create(config.child("folder").child_value());
	texture_path = config.child("sprite_sheet").attribute("source").as_string();

	LoadEntityInfo(Entity::entityType::LAND_ENEMY, config.child("enemy"));
	return ret;
}

bool EntityManager::Start()
{
	bool ret = true;
	p2List_item<Entity*>* tmp = entities.start;
	while (tmp != nullptr)
	{
		//tmp->data->Start();
		if (tmp->data->type == Entity::entityType::PLAYER)
			ret = tmp->data->Start();
		tmp = tmp->next;
		/*else if (tmp->data->type == Entity::entityType::LAND_ENEMY)
			ret = tmp->data->Start();
		tmp = tmp->next;*/
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
	player->CleanUp();
	return ret;
}

bool EntityManager::Save(pugi::xml_node& file) const
{
	bool ret = true;
	p2List_item<Entity*>* tmp = entities.start;
	while (tmp != nullptr)
	{
		if (tmp->data->type == Entity::entityType::PLAYER)
		{
			tmp->data->Save(file.append_child("player"));
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
		if (tmp->data->type == Entity::entityType::PLAYER)
		{
			tmp->data->Load(file.child("player"));
		}
		if (tmp->data->type == Entity::entityType::FLYING_ENEMY)
		{
			tmp->data->Load(JrGargoyle);
			JrGargoyle = JrGargoyle.next_sibling("JrGargoyle");

		}
		else if (tmp->data->type == Entity::entityType::LAND_ENEMY)
		{
			tmp->data->Load(OfficerSkeleton);
			OfficerSkeleton = OfficerSkeleton.next_sibling("OfficerSkeleton");
		}
		tmp = tmp->next;
	}
	return ret;
}

Entity* EntityManager::CreateEntity(Entity::entityType type, iPoint position)
{
	Entity* tmp = nullptr;

	switch (type)
	{
	case Entity::entityType::PLAYER:
		player = new Player(type);
		entities.add(player);
		break;
	case Entity::entityType::FLYING_ENEMY:
		tmp = new JrGargoyle(position);
		break;
	case Entity::entityType::LAND_ENEMY:
		tmp = new OfficerSkeleton(position);
		break;
	}

	if (tmp)
		entities.add(tmp);

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

void EntityManager::LoadEntityInfo(Entity::entityType type, pugi::xml_node & node)
{
	switch (type)
	{
	
	case Entity::entityType::LAND_ENEMY: {
		pugi::xml_node officer_skeleton = node.child("OfficerSkeleton");
		skeleton_info.speed.x = officer_skeleton.child("speed").attribute("x").as_float();
		skeleton_info.speed.y = officer_skeleton.child("speed").attribute("y").as_float();
		skeleton_info.acceleration.x = officer_skeleton.child("acceleration").attribute("x").as_float();
		skeleton_info.acceleration.y = officer_skeleton.child("acceleration").attribute("y").as_float();
		skeleton_info.range_of_trigger = officer_skeleton.child("range_of_trigger").attribute("value").as_float();

	}break;
	case  Entity::entityType::NO_TYPE:
		break;
	default:
		break;
	}
}