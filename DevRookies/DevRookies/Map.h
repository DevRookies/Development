#ifndef __MAP_H__
#define __MAP_H__

#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2Point.h"
#include "Module.h"
#include "Collision.h"
#include "Textures.h"

struct Properties
{
	struct Property
	{
		p2SString name;
		int value;
	};

	~Properties()
	{
		p2List_item<Property*>* item;
		item = list.start;

		while (item != NULL)
		{
			RELEASE(item->data);
			item = item->next;
		}

		list.clear();
	}

	int Get(const char* name, int default_value = 0) const;

	p2List<Property*>	list;
};

struct MapLayer
{
	p2SString				name = "";
	uint					width = 0u;
	uint					height = 0u;
	uint*					data = 0u;
	Properties				properties;
	uint*					tiles = nullptr;
	bool					parallax = false;
	~MapLayer() {
		if (tiles != nullptr)
		{
			delete[] tiles;
		}
	}
	uint Get(int x, int y) const {
		return tiles[x + (width * y)];
	}
};

struct TileSet
{
	SDL_Rect GetTileRect(int id) const;
	bool Contains(int id) const
	{
		return (id >= firstgid && id <= firstgid + tilecount - 1);
	}
	p2SString		name;
	uint			firstgid = 0u;
	uint			tilecount = 0u;
	uint			margin = 0u;
	uint			spacing = 0u;
	uint			tile_width = 0u;
	uint			tile_height = 0u;
	SDL_Texture*	texture = nullptr;
	uint			tex_width = 0u;
	uint			tex_height = 0u;
	uint			num_tiles_width = 0u;
	uint			num_tiles_height = 0u;
	uint			offset_x = 0u;
	uint			offset_y = 0u;
};

struct ObjectsData
{
	uint16_t	name;
	int			x;
	int			y;
	uint		width = 0u;
	uint		height = 0u;

};

struct ObjectsGroups
{
	p2SString				name;
	p2List<ObjectsData*>	objects;
	~ObjectsGroups();
};

enum MapTypes
{
	MAPTYPE_UNKNOWN = 0,
	MAPTYPE_ORTHOGONAL,
	MAPTYPE_ISOMETRIC,
	MAPTYPE_STAGGERED
};

struct MapData
{
	int						width;
	int						height;
	int						tile_width;
	int						tile_height;
	SDL_Color				background_color;
	MapTypes				type;
	p2List<TileSet*>		tilesets;
	p2List<MapLayer*>		maplayers;
	p2List<ObjectsGroups*>	objLayers;

};





class Map : public Module
{
public:

	Map();

	// Destructor
	virtual ~Map();

	// Called before render is available
	bool Awake(pugi::xml_node& config);

	// Called each loop iteration
	void Draw(float dt);

	// Called before quitting
	bool CleanUp();

	// Load new map
	bool Load(const char* path);

	iPoint MapToWorld(int x, int y) const;
	iPoint WorldToMap(int x, int y) const;
	bool CreateWalkabilityMap(int& width, int& height, uchar** buffer) const;

private:

	bool LoadMap();
	bool LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set);
	bool LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set);
	bool LoadLayer(pugi::xml_node& node, MapLayer* layer);
	bool LoadProperties(pugi::xml_node& node, Properties& properties);
	bool LoadCollider(pugi::xml_node& node, uint type);
	bool LoadObjectLayers(pugi::xml_node& node, ObjectsGroups* group);
	bool LoadEnemyPosition(pugi::xml_node& node);

	TileSet* GetTilesetFromTileId(int id) const;


public:

	MapData				data;
	SDL_Rect			rect = { 0,0,0,0 };;
	fPoint				init_player_position;
	p2List<fPoint>		init_JrGargoyle_position;
	p2List<fPoint>		init_Skeleton_position;
	p2List<fPoint>		init_Coin_position;
	

private:

	pugi::xml_document	map_file;
	p2SString			folder;
	bool				map_loaded;
	float				parallax_speed;
};

#endif // __MAP_H__