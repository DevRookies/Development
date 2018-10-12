#ifndef __MAP_H__
#define __MAP_H__

#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2Point.h"
#include "Module.h"
#include "Collision.h"

struct MapLayer
{
	p2SString				name = "";
	uint					width = 0u;
	uint					height = 0u;
	uint*					tiles = nullptr;
	bool					parallax = false;
	~MapLayer() {
		if (tiles != nullptr)
		{
			delete[] tiles;
		}
	}
	uint Get(int x, int y) const {
		return x + (width * y);
	}
};

struct TileSet
{
	SDL_Rect GetTileRect(int id) const;
	bool Contains(int id) const
	{
		return (id >= firstgid && id <= firstgid + tilecount - 1);
	}
	p2SString			name;
	uint				firstgid;
	uint				tilecount;
	uint				margin;
	uint				spacing;
	uint				tile_width;
	uint				tile_height;
	SDL_Texture*		texture;
	uint				tex_width;
	uint				tex_height;
	uint				num_tiles_width;
	uint				num_tiles_height;
	uint				offset_x;
	uint				offset_y;
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
	int					width;
	int					height;
	int					tile_width;
	int					tile_height;
	SDL_Color			background_color;
	MapTypes			type;
	p2List<TileSet*>	tilesets;
	p2List<MapLayer*>	maplayers;
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
	void Draw();

	// Called before quitting
	bool CleanUp();

	// Load new map
	bool Load(const char* path);

	iPoint MapToWorld(int x, int y) const;

private:

	bool LoadMap();
	bool LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set);
	bool LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set);
	bool LoadLayer(pugi::xml_node& node, MapLayer* layer);
	bool LoadCollider(pugi::xml_node& node, uint type);

public:

	MapData				data;
	SDL_Rect			rect;
	

private:

	pugi::xml_document	map_file;
	p2SString			folder;
	bool				map_loaded;
	float				parallax_speed;
};

#endif // __MAP_H__