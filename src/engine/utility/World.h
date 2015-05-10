#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <unordered_map>


#include "ObjectDB.h"

using std::hash;
using std::pair;
using std::unordered_map;

using glm::pow;
using glm::sqrt;

class World {

public:
	
	World();
	~World();

	void update(float dt);

private:

	bool checkCollision(GameObject* ob1, GameObject* ob2);
	inline vec3 sphereToXYZ(glm::vec4 & spherePos);

	ObjectDB* objectDb;
};


 inline vec3 World::sphereToXYZ(glm::vec4 & spherePos) {
	glm::vec3 xyz(0, 0, spherePos.x);
	xyz = glm::angleAxis(glm::radians(spherePos.y), glm::vec3(0, 1, 0)) * xyz;
	xyz = glm::angleAxis(glm::radians(spherePos.z), glm::vec3(1, 0, 0)) * xyz;
	return xyz;
}

#endif