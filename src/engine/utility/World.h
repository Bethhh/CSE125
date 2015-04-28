#ifndef WORLD_H
#define WORLD_H

#include "EntityMap.h"
#include "GameObject.h"

class World {

protected:
	//a list of players?
	//a list of resources?
	//a list of NPCs?
	//a map of everything?
	//a map of resources?
	EntityMap<int, GameObject>  map;
public:
	World();
	virtual ~World();

	void init();
	void insert(GameObject go);
	void remove(int id);
	void replace(int id, GameObject go);
	void get(int id);

};
#endif