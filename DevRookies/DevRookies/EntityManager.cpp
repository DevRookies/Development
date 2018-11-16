#include "EntityManager.h"
#include "DevRookiesApp.h"
#include "Render.h"
#include "Entity.h"
#include "Player.h"
//check if needed
#include "Scene.h"
#include "SceneManager.h"
//----------------
#include "OfficerSkeleton.h"
#include "JrGargoyle.h"
#include "PugiXml/src/pugixml.hpp"
#include "Textures.h"

EntityManager::EntityManager()
{
	name.create("entitymanager");
}

EntityManager::~EntityManager()
{
}

bool EntityManager::Awake(pugi::xml_node &config)
{
	bool ret = true;
	folder.create(config.child("folder").child_value());
	texture_path = config.child("sprite_sheet").attribute("source").as_string();

	return ret;
}

bool EntityManager::Start()
{
	bool ret = true;
	texture = App->textures->Load(PATH(folder.GetString(), texture_path.GetString()));

	return ret;
}

bool EntityManager::Update(float dt)
{
	bool ret = true;
	p2List_item<Entity*>* tmp = Entities.start;
	while (tmp != nullptr)
	{
		/*if (tmp->data->type == Entity::entityType::PLAYER)
			ret = tmp->data->Update(dt);*/
		tmp = tmp->next;
	}

	return ret;
}

bool EntityManager::PostUpdate()
{
	bool ret = true;
	p2List_item<Entity*>* tmp = Entities.start;
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
	p2List_item<Entity*>* tmp = Entities.start;
	while (tmp != nullptr)
	{
		tmp->data->CleanUp();
		tmp = tmp->next;
	}
	return ret;
}

bool EntityManager::Save(pugi::xml_node& file) const
{
	bool ret = true;
	p2List_item<Entity*>* tmp = Entities.start;
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
	p2List_item<Entity*>* tmp = Entities.start;
	pugi::xml_node JrGargoyle = file.child("JrGargoyle");
	pugi::xml_node OfficerSkeleton = file.child("OfficerSkeleton");
	while (tmp != nullptr)
	{
		/*if (tmp->data->type == Entity::entityType::PLAYER)
		{
			tmp->data->Load(file.child("player"));
		}*/
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
	p2List_item<Entity*>* tmp = Entities.end;
	while (tmp != nullptr)
	{
		p2List_item<Entity*>* tmp2 = tmp;
		RELEASE(tmp->data);
		Entities.del(tmp2);
		tmp = tmp->prev;
	}

}

Entity* EntityManager::CreateEntity(Entity::entityType type, iPoint position)
{
	Entity* tmp = nullptr;

	switch (type)
	{
	/*case Entity::entityType::PLAYER:
		tmp = new Player();
		break;*/
	case Entity::entityType::FLYING_ENEMY:
		tmp = new JrGargoyle(position);
		break;
	case Entity::entityType::LAND_ENEMY:
		tmp = new OfficerSkeleton(position);
		break;
	}

	if (tmp)
		Entities.add(tmp);

	return tmp;
}

bool EntityManager::DestroyEntity(Entity * entity)
{
	entity->CleanUp();
	Entities.del(Entities.At(Entities.find(entity)));
	return true;
}