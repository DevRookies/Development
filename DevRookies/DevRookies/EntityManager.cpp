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

	return ret;
}

bool EntityManager::Start()
{
	bool ret = true;
	p2List_item<Entity*>* tmp = entities.start;
	while (tmp != nullptr)
	{
		if (tmp->data->type == Entity::entityType::PLAYER)
			ret = tmp->data->Start();
		tmp = tmp->next;
	}


	texture = App->textures->Load(PATH(folder.GetString(), texture_path.GetString()));



	return ret;
}

bool EntityManager::PreUpdate()
{
	BROFILER_CATEGORY("PreUpdateEntityManager", Profiler::Color::Aqua);
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
	player->CleanUp();
	return ret;
}

bool EntityManager::Save(pugi::xml_node& file) const
{
	bool ret = true;
	p2List_item<Entity*>* tmp = entities.start;
	while (tmp != nullptr)
	{
		tmp->data->Save(file);
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

void EntityManager::DestroyEntities()
{
	p2List_item<Entity*>* tmp = entities.end;
	while (tmp != nullptr)
	{
		p2List_item<Entity*>* tmp2 = tmp;
		RELEASE(tmp->data);
		entities.del(tmp2);
		tmp = tmp->prev;
	}

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
	entity->CleanUp();
	entities.del(entities.At(entities.find(entity)));
	return true;
}