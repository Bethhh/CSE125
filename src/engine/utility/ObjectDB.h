#ifndef OBJECTDB_H
#define OBJECTDB_H

#include <deque>
#include <unordered_map>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include <gtx\string_cast.hpp>
#include "Serializable.h"
#include "../graphics/GraphicsEngine.h"

using glm::mat4;
using glm::vec3;
using std::pair;
using std::deque;
using std::make_pair;
using std::unordered_map;

typedef unsigned int ObjectId;

class GameObject : Serializable {

public:
	 
	void serialize(Packet & p);
	void deserialize(Packet & p);

	mat4 location;
	ObjectId id;
	MatrixNode* node;
};

class ObjectDB {

public:

	ObjectDB();
	~ObjectDB();

	ObjectId add(GameObject* object);
	bool ObjectDB::add(ObjectId id, GameObject* object);
	bool remove(ObjectId objectId);
	GameObject* get(ObjectId objectId);

	void getObjectState(deque<Packet> & state);

	static ObjectDB & getInstance();

private:

	ObjectId nextId;
	unordered_map<ObjectId, GameObject*> objects;
};


#endif