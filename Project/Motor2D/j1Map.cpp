#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include "j1Player.h"
#include <math.h>
#include "j1Audio.h"
#include "j1Input.h"
#include "j1EntityModule.h"

#include "Brofiler\Brofiler.h"

j1Map::j1Map() : j1Module(), map_loaded(false)
{
	name.create("map");
}

// Destructor
j1Map::~j1Map()
{}

// Called before render is available
bool j1Map::Awake(pugi::xml_node& config)
{
	LOG("Loading Map Parser");
	bool ret = true;

	folder.create(config.child("folder").child_value());

	
	
	return ret;
}

bool j1Map::Start()
{
	return true;
}

void j1Map::Draw(float dt)
{
	BROFILER_CATEGORY("Map Draw", Profiler::Color::Yellow)

	if(map_loaded == false)
		return;

	// TODO 5: Prepare the loop to draw all tilesets + Blit
	p2List_item<MapLayer*>* fakeLayer = data.layers.start;
	p2List_item<TileSet*>* fakeTileset = data.tilesets.start;

	while (fakeTileset != NULL)
	{
		while (fakeLayer != NULL)
		{
			for (uint x = 0; x < fakeLayer->data->width; x++)
			{
				for (uint y = 0; y < fakeLayer->data->height; y++)
				{
					int ID = fakeLayer->data->GetGid(x, y);
					iPoint position = MapToWorld(x, y);
					SDL_Rect rect = fakeTileset->data->GetTileRect(ID);

					if (fakeLayer->data->name != "Muntanya2" && 
						fakeLayer->data->name != "nuvols" &&
						fakeLayer->data->name != "logica")
						App->render->Blit(fakeTileset->data->texture, position.x - fakeTileset->data->tile_width, position.y, &rect);

					else if (fakeLayer->data->name == "Muntanya2")
					{
						//MOUNTAIN PARALLAX
						App->render->Blit(fakeTileset->data->texture, position.x - fakeTileset->data->tile_width + App->render->camera.x / 12, position.y, &rect);
					}
						
					else if (fakeLayer->data->name == "nuvols")
					{
						//CLOUD PARALLAX
						if (cloud_parallax / fakeTileset->data->tile_width >= fakeLayer->data->width / 2)
						{
							cloud_parallax = 0.0f;
						}
						App->render->Blit(fakeTileset->data->texture, position.x - cloud_parallax - fakeTileset->data->tile_width, position.y, &rect);
						cloud_parallax += (dt * 0.01f);
					}
					else if (fakeLayer->data->name == "logica" && logic)
					{
						App->render->Blit(fakeTileset->data->texture, position.x - fakeTileset->data->tile_width, position.y, &rect);
					}
				}
			}
			fakeLayer = fakeLayer->next;
		}
		fakeTileset = fakeTileset->next;
	}

		// TODO 9: Complete the draw function
		int x, y;
		App->input->GetMousePosition(x, y);
		iPoint tile = WorldToMap(x, y);
		LOG("Mouse tile pos: x - %i, y - %i", tile.x, tile.y);
}

bool j1Map::LoadEntities()
{
	bool ret = false;
	p2List_item<MapLayer*>* iterator;
	p2List_item<MapLayer*>* fakeLayer = nullptr;

	for (iterator = App->map->data.layers.start; iterator != NULL; iterator = iterator->next)
	{
		if (iterator->data->name == "logica")
		{
			fakeLayer = iterator;
		}
	}

	for (uint i = 0; i < data.height; i++)
	{
		for (uint j = 0; j < data.width; j++)
		{
			uint* nextGid = &fakeLayer->data->gid[i * data.width + j];
			if (*nextGid == 9)
			{
				fPoint pos;
				pos.create((float)j * 16, ((float)i * 16) + 5);
				App->entitymodule->CreateChuck(pos);
			}
			if (*nextGid == 1)
			{
				fPoint pos;
				pos.create((float)j * 16, ((float)i * 16));
				App->entitymodule->CreateBoo(pos);
			}

			if (*nextGid == 17)
			{
				fPoint pos;
				pos.create(((float)j * 16) - 13, ((float)i * 16));
				App->entitymodule->CreateCoins(pos);
			}

		}
	}
	return ret;
}

/*bool j1Map::LoadCoins()
{
	bool ret = false;
	p2List_item<MapLayer*>* iterator;
	p2List_item<MapLayer*>* fakeLayer = nullptr;

	for (iterator = App->map->data.layers.start; iterator != NULL; iterator = iterator->next)
	{
		if (iterator->data->name == "logica")
		{
			fakeLayer = iterator;
		}
	}
	for (uint i = 0; i < data.height; i++)
	{
		for (uint j = 0; j < data.width; j++)
		{
			uint* nextGid = &fakeLayer->data->gid[i * data.width + j];
			if (*nextGid == 17)
			{
				fPoint pos;
				pos.create(((float)j * 16) - 13, ((float)i * 16));
				App->entitymodule->CreateCoins(pos);
			}
		}
	}
	return ret;
}*/

iPoint j1Map::MapToWorld(int x, int y) const
{
	iPoint ret;

	ret.x = x * data.tile_width;
	ret.y = y * data.tile_height;

	return ret;
}

iPoint j1Map::WorldToMap(int x, int y) const
{
	iPoint ret;

	ret.x = x / data.tile_width;
	ret.y = y / data.tile_height;

	return ret;
}

SDL_Rect TileSet::GetTileRect(int id) const
{
	int relative_id = id - firstgid;
	SDL_Rect rect;
	rect.w = tile_width;
	rect.h = tile_height;
	rect.x = margin + ((rect.w + spacing) * (relative_id % num_tiles_width));
	rect.y = margin + ((rect.h + spacing) * (relative_id / num_tiles_width));
	return rect;
}

// Called before quitting
bool j1Map::CleanUp()
{
	BROFILER_CATEGORY("Map Cleanup", Profiler::Color::Yellow)

	LOG("Unloading map");

	// Remove all tilesets
	p2List_item<TileSet*>* item;
	item = data.tilesets.start;

	while(item != NULL)
	{
		RELEASE(item->data);
		item = item->next;
	}
	data.tilesets.clear();
	data.layers.clear();

	// TODO 2: clean up all layer data
	// Remove all layers


	// Clean up the pugui tree
	map_file.reset();

	return true;
}

// Load new map
bool j1Map::Load(const char* file_name)
{
	BROFILER_CATEGORY("Map Load", Profiler::Color::Yellow)

	bool ret = true;


	p2SString tmp("%s%s", folder.GetString(), file_name);

	pugi::xml_parse_result result = map_file.load_file(tmp.GetString());

	if(result == NULL)
	{
		LOG("Could not load map xml file %s. pugi error: %s", file_name, result.description());
		ret = false;
	}

	// Load general info ----------------------------------------------
	if(ret == true)
	{
		ret = LoadMap();
	}

	// Load all tilesets info ----------------------------------------------
	pugi::xml_node tileset;
	for(tileset = map_file.child("map").child("tileset"); tileset && ret; tileset = tileset.next_sibling("tileset"))
	{
		TileSet* set = new TileSet();

		if(ret == true)
		{
			ret= LoadTilesetDetails(tileset, set);
		}

		if(ret == true)
		{
			ret = LoadTilesetImage(tileset, set);
		}

		data.tilesets.add(set);
	}

	// TODO 4: Iterate all layers and load each of them
	// Load layer info ----------------------------------------------
	pugi::xml_node layer;
	for (layer = map_file.child("map").child("layer"); layer && ret; layer = layer.next_sibling("layer"))
	{
		MapLayer* yer = new MapLayer();

		if (ret == true)
		{
			ret = LoadLayer(layer, yer);
		}

		data.layers.add(yer);
	}


	if(ret == true)
	{
		LOG("Successfully parsed map XML file: %s", file_name);
		LOG("width: %d height: %d", data.width, data.height);
		LOG("tile_width: %d tile_height: %d", data.tile_width, data.tile_height);

		p2List_item<TileSet*>* item = data.tilesets.start;
		while(item != NULL)
		{
			TileSet* s = item->data;
			LOG("Tileset ----");
			LOG("name: %s firstgid: %d", s->name.GetString(), s->firstgid);
			LOG("tile width: %d tile height: %d", s->tile_width, s->tile_height);
			LOG("spacing: %d margin: %d", s->spacing, s->margin);
			item = item->next;
		}

		// TODO 4: Add info here about your loaded layers
		// Adapt this vcode with your own variables
		
		p2List_item<MapLayer*>* item_layer = data.layers.start;
		while(item_layer != NULL)
		{
			MapLayer* l = item_layer->data;
			LOG("Layer ----");
			LOG("name: %s", l->name.GetString());
			LOG("tile width: %d tile height: %d", l->width, l->height);
			item_layer = item_layer->next;
		}
	}

	map_loaded = ret;

	return ret;
}

// Load map general properties
bool j1Map::LoadMap()
{
	BROFILER_CATEGORY("Map LoadMap", Profiler::Color::Yellow)

	bool ret = true;
	pugi::xml_node map = map_file.child("map");

	if(map == NULL)
	{
		LOG("Error parsing map xml file: Cannot find 'map' tag.");
		ret = false;
	}
	else
	{
		data.width = map.attribute("width").as_int();
		data.height = map.attribute("height").as_int();
		data.tile_width = map.attribute("tilewidth").as_int();
		data.tile_height = map.attribute("tileheight").as_int();
		p2SString bg_color(map.attribute("backgroundcolor").as_string());

		data.background_color.r = 0;
		data.background_color.g = 0;
		data.background_color.b = 0;
		data.background_color.a = 0;

		if(bg_color.Length() > 0)
		{
			p2SString red, green, blue;
			bg_color.SubString(1, 2, red);
			bg_color.SubString(3, 4, green);
			bg_color.SubString(5, 6, blue);

			int v = 0;

			sscanf_s(red.GetString(), "%x", &v);
			if(v >= 0 && v <= 255) data.background_color.r = v;

			sscanf_s(green.GetString(), "%x", &v);
			if(v >= 0 && v <= 255) data.background_color.g = v;

			sscanf_s(blue.GetString(), "%x", &v);
			if(v >= 0 && v <= 255) data.background_color.b = v;
		}

		p2SString orientation(map.attribute("orientation").as_string());

		if(orientation == "orthogonal")
		{
			data.type = MAPTYPE_ORTHOGONAL;
		}
		else if(orientation == "isometric")
		{
			data.type = MAPTYPE_ISOMETRIC;
		}
		else if(orientation == "staggered")
		{
			data.type = MAPTYPE_STAGGERED;
		}
		else
		{
			data.type = MAPTYPE_UNKNOWN;
		}
	}

	return ret;
}

void j1Map::UnloadMap()
{
	data.tilesets.clear();
	data.layers.clear();
}

bool j1Map::LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set)
{
	bool ret = true;
	set->name.create(tileset_node.attribute("name").as_string());
	set->firstgid = tileset_node.attribute("firstgid").as_int();
	set->tile_width = tileset_node.attribute("tilewidth").as_int();
	set->tile_height = tileset_node.attribute("tileheight").as_int();
	set->margin = tileset_node.attribute("margin").as_int();
	set->spacing = tileset_node.attribute("spacing").as_int();
	pugi::xml_node offset = tileset_node.child("tileoffset");

	if(offset != NULL)
	{
		set->offset_x = offset.attribute("x").as_int();
		set->offset_y = offset.attribute("y").as_int();
	}
	else
	{
		set->offset_x = 0;
		set->offset_y = 0;
	}

	return ret;
}

bool j1Map::LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set)
{
	bool ret = true;
	pugi::xml_node image = tileset_node.child("image");

	if(image == NULL)
	{
		LOG("Error parsing tileset xml file: Cannot find 'image' tag.");
		ret = false;
	}
	else
	{
		set->texture = App->tex->Load(PATH(folder.GetString(), image.attribute("source").as_string()));
		int w, h;
		SDL_QueryTexture(set->texture, NULL, NULL, &w, &h);
		set->tex_width = image.attribute("width").as_int();

		if(set->tex_width <= 0)
		{
			set->tex_width = w;
		}

		set->tex_height = image.attribute("height").as_int();

		if(set->tex_height <= 0)
		{
			set->tex_height = h;
		}

		set->num_tiles_width = set->tex_width / set->tile_width;
		set->num_tiles_height = set->tex_height / set->tile_height;
	}

	return ret;
}

//TODO 3: Create the definition for a function that loads a single layer
bool j1Map::LoadLayer(pugi::xml_node& node, MapLayer* layer)
{
	bool ret = true;

	layer->name = node.attribute("name").as_string();
	layer->width = node.attribute("width").as_uint();
	layer->height = node.attribute("height").as_uint();

	layer->gid = new uint[layer->width * layer->height];
	memset(layer->gid, 0, layer->width * layer->height);

	int i = 0;

	for (pugi::xml_node Iterator = node.child("data").child("tile"); Iterator; Iterator = Iterator.next_sibling("tile"))
	{
		layer->gid[i] = Iterator.attribute("gid").as_uint();
		i++;
	}

	if (layer->name == "logica")
	{
		pathfinding = layer;
	}
	
	return ret;
}


bool j1Map::IsWalkable(Entity* entity)
{
	BROFILER_CATEGORY("Map IsWalkable", Profiler::Color::Yellow)

	bool ret = true;
	int player_x	= entity->position.x / 16 ; //check next tile right
	int player_y	= (entity->position.y + 14) / 16;
	p2List_item<MapLayer*>* iterator;
	p2List_item<MapLayer*>* fakeLayer = nullptr;
	
	for (iterator = data.layers.start; iterator != NULL; iterator = iterator->next)
	{
		if (iterator->data->name == "logica")
		{
			fakeLayer = iterator;
		}
	}

	//uint nextGid = fakeLayer->data->GetGid(player_x,player_y);
	uint* nextGid = &fakeLayer->data->gid[1 + player_x + player_y*fakeLayer->data->width];
	if (entity->direction == R)
	{
		nextGid++;
		if (*nextGid == 19) 
			ret = false;
		else if (*nextGid != 19)
			ret = true;
	}
	else if (entity->direction == L)
	{
		nextGid;
		if (*nextGid == 19) 
			ret = false;
		else if (*nextGid != 19) 
			ret = true;
	}


	return ret;
}

bool j1Map::IsFallable(Entity* entity)
{
	bool ret = false;
	int player_x = entity->position.x / 16; //check next tile right
	int player_y = ((entity->position.y + 14) / 16) + 1;
	p2List_item<MapLayer*>* iterator;
	p2List_item<MapLayer*>* fakeLayer = nullptr;

	for (iterator = data.layers.start; iterator != NULL; iterator = iterator->next)
	{
		if (iterator->data->name == "logica")
		{
			fakeLayer = iterator;
		}
	}

	//uint nextGid = fakeLayer->data->GetGid(player_x,player_y);
	uint* nextGid = &fakeLayer->data->gid[1 + player_x + player_y*fakeLayer->data->width];
	if (entity->direction == R)
	{
		nextGid++;
		if (*nextGid == 0)
			ret = true;
		else if (*nextGid != 0)
			ret = false;
	}
	else if (entity->direction == L)
	{
		nextGid;
		if (*nextGid == 0)
			ret = true;
		else if (*nextGid != 0)
			ret = false;
	}

	return ret;
}
