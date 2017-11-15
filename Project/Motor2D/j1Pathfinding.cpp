#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1PathFinding.h"
#include "j1EnemyModule.h"

j1PathFinding::j1PathFinding() : j1Module(), map(NULL), last_path(DEFAULT_PATH_LENGTH), width(0), height(0)
{
	name.create("pathfinding");
}

// Destructor
j1PathFinding::~j1PathFinding()
{
	RELEASE_ARRAY(map);
}

// Called before quitting
bool j1PathFinding::CleanUp()
{
	LOG("Freeing pathfinding library");

	last_path.Clear();
	RELEASE_ARRAY(map);
	return true;
}

// Sets up the walkability map
void j1PathFinding::SetMap(uint width, uint height, uchar* data)
{
	this->width = width;
	this->height = height;

	RELEASE_ARRAY(map);
	map = new uchar[width*height];
	memcpy(map, data, width*height);
}

// Utility: return true if pos is inside the map boundaries
bool j1PathFinding::CheckBoundaries(const iPoint& pos) const
{
	return (pos.x >= 0 && pos.x <= (int)width &&
		pos.y >= 0 && pos.y <= (int)height);
}

// Utility: returns true is the tile is walkable
bool j1PathFinding::IsWalkable(const iPoint& pos) const
{
	uchar t = GetTileAt(pos);
	return t != INVALID_WALK_CODE && t > 0;
}

// Utility: return the walkability value of a tile
uchar j1PathFinding::GetTileAt(const iPoint& pos) const
{
	if (CheckBoundaries(pos))
		return map[(pos.y*width) + pos.x];

	return INVALID_WALK_CODE;
}

// To request all tiles involved in the last generated path
const p2DynArray<iPoint>* j1PathFinding::GetLastPath() const
{
	return &last_path;
}

// PathList ------------------------------------------------------------------------
// Looks for a node in this list and returns it's list node or NULL
// ---------------------------------------------------------------------------------
p2List_item<PathNode>* PathList::Find(const iPoint& point) const
{
	p2List_item<PathNode>* item = list.start;
	while (item)
	{
		if (item->data.pos == point)
			return item;
		item = item->next;
	}
	return NULL;
}

// PathList ------------------------------------------------------------------------
// Returns the Pathnode with lowest score in this list or NULL if empty
// ---------------------------------------------------------------------------------
p2List_item<PathNode>* PathList::GetNodeLowestScore() const
{
	p2List_item<PathNode>* ret = NULL;
	int min = 65535;

	p2List_item<PathNode>* item = list.end;
	while (item)
	{
		if (item->data.Score() < min)
		{
			min = item->data.Score();
			ret = item;
		}
		item = item->prev;
	}
	return ret;
}

// PathNode -------------------------------------------------------------------------
// Convenient constructors
// ----------------------------------------------------------------------------------
PathNode::PathNode() : g(-1), h(-1), pos(-1, -1), parent(NULL)
{}

PathNode::PathNode(int g, int h, const iPoint& pos, const PathNode* parent) : g(g), h(h), pos(pos), parent(parent)
{}

PathNode::PathNode(const PathNode& node) : g(node.g), h(node.h), pos(node.pos), parent(node.parent)
{}

// PathNode -------------------------------------------------------------------------
// Fills a list (PathList) of all valid adjacent pathnodes
// ----------------------------------------------------------------------------------
uint PathNode::FindWalkableAdjacents(PathList& list_to_fill, bool flies) const
{
	iPoint cell;
	uint before = list_to_fill.list.count();

	//if the enemy is flying it can fly in diagonal so we will use all the 8 possible paths
	//if it can't fly we will only use the x axis

	if (flies)
	{
		// north
		cell.create(pos.x, pos.y + 1);
		if (App->pathfinding->IsWalkable(cell))
			list_to_fill.list.add(PathNode(-1, -1, cell, this));

		// south
		cell.create(pos.x, pos.y - 1);
		if (App->pathfinding->IsWalkable(cell))
			list_to_fill.list.add(PathNode(-1, -1, cell, this));

		// east
		cell.create(pos.x + 1, pos.y);
		if (App->pathfinding->IsWalkable(cell))
			list_to_fill.list.add(PathNode(-1, -1, cell, this));

		// west
		cell.create(pos.x - 1, pos.y);
		if (App->pathfinding->IsWalkable(cell))
			list_to_fill.list.add(PathNode(-1, -1, cell, this));

		// north-east
		cell.create(pos.x + 1, pos.y + 1);
		if (App->pathfinding->IsWalkable(cell))
			list_to_fill.list.add(PathNode(-1, -1, cell, this));

		// north-west
		cell.create(pos.x + 1, pos.y + 1);
		if (App->pathfinding->IsWalkable(cell))
			list_to_fill.list.add(PathNode(-1, -1, cell, this));

		// south-east
		cell.create(pos.x + 1, pos.y - 1);
		if (App->pathfinding->IsWalkable(cell))
			list_to_fill.list.add(PathNode(-1, -1, cell, this));

		// south-west
		cell.create(pos.x - 1, pos.y - 1);
		if (App->pathfinding->IsWalkable(cell))
			list_to_fill.list.add(PathNode(-1, -1, cell, this));
	}

	if (!flies)
	{
		// east
		cell.create(pos.x + 1, pos.y);
		if (App->pathfinding->IsWalkable(cell))
			list_to_fill.list.add(PathNode(-1, -1, cell, this));

		// west
		cell.create(pos.x - 1, pos.y);
		if (App->pathfinding->IsWalkable(cell))
			list_to_fill.list.add(PathNode(-1, -1, cell, this));
	}

	

	return list_to_fill.list.count();
}

// PathNode -------------------------------------------------------------------------
// Calculates this tile score
// ----------------------------------------------------------------------------------
int PathNode::Score() const
{
	return g + h;
}

// PathNode -------------------------------------------------------------------------
// Calculate the F for a specific destination tile
// ----------------------------------------------------------------------------------
int PathNode::CalculateF(const iPoint& destination)
{
	g = parent->g + 1;
	h = pos.DistanceTo(destination);

	return g + h;
}

// ----------------------------------------------------------------------------------
// Actual A* algorithm: return number of steps in the creation of the path or -1 ----
// ----------------------------------------------------------------------------------
// Usefull link->https://www.youtube.com/watch?v=-L-WgKMFuhE

int j1PathFinding::CreatePath(iPoint& origin,iPoint& destination, bool flies)
{
	last_path.Clear();
	int ret = 0;
	// TODO 1: if origin or destination are not walkable, return -1
	if (!IsWalkable(origin) || !IsWalkable(destination))
	{
		ret = -1;
	}

	else
	{
		//Open for tiles that have not been evaluated, close fot the evaluated ones
		PathList open;
		PathList close;

		// Add the origin tile to open
		PathNode origin_node(0, origin.DistanceTo(destination), origin, nullptr);
		open.list.add(origin_node);

		// Iterate while we have tile in the open list
		while (open.list.count() > NULL)
		{
			//we need to find the lowest F score cell and close it
			p2List_item<PathNode>* current = open.GetNodeLowestScore();
			close.list.add(current->data);
			open.list.del(current);

			//creating final path by backtracking
			// Use the Pathnode::parent and Flip() the path when you are finish
			if (close.list.end->data.pos == destination)
			{
				for (p2List_item<PathNode>* temp = close.list.end; temp->data.parent != nullptr; close.Find(temp->data.parent->pos))
				{
					last_path.PushBack(temp->data.pos);
				}
				last_path.PushBack(close.list.start->data.pos);
				last_path.Flip();
				//return number of steps in the creation of the path
				ret = last_path.Count();
			}

			else
			{
				//filling a list of the adjacent nodes
				PathList neighbours;
				close.list.end->data.FindWalkableAdjacents(neighbours, flies);

				//iterate neighbours
				p2List_item<PathNode>* temp = neighbours.list.start;

				while (temp != nullptr)
				{
					// we ignote the closed nodes
					if (close.Find(temp->data.pos) != NULL)
					{
						temp = temp->next;
						continue;
					}
					temp->data.CalculateF(destination);

					//if the node is in the open list, compare G to see if there is a better path
					if (open.Find(temp->data.pos) != NULL)
					{
						//if we find a better path we update the parent  *(parent is the node where we come form)
						PathNode update_parent = open.Find(temp->data.pos)->data;
						if (temp->data.g < update_parent.g)
						{
							update_parent.parent = temp->data.parent;
						}
					}

					else
					{
						//if there is not a better path found, calculate the node F and add it to the open list
						open.list.add(temp->data);
					}
					temp = temp->next;
				}

				neighbours.list.clear();
			}
		}


	}

	return ret;
}

