#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine() {
	objectDb = &ObjectDB::getInstance();
	forces.insert(make_pair(GRAVITY, new GravityGenerator()));
	forces.insert(make_pair(DRAG, new DragGenerator()));
}


PhysicsEngine::~PhysicsEngine() {

}


void PhysicsEngine::update(float dt) {
	this->resolveCollisions(dt);
	this->generateForces(dt);
	this->integrateObjects(dt);
}


vector<GameObject*> & PhysicsEngine::getChangedObjects(){
	return this->changed;
}


void PhysicsEngine::registerInteraction(MoveableObject* object, unsigned int flags) {
	assert(object);
	Interaction i;
	i.receiver = object;
	if (flags & GRAVITY) {
		i.generator = forces.find(GRAVITY)->second;
		interactions.push_back(i);
	}
	if (flags & DRAG) {
		i.generator = forces.find(DRAG)->second;
		interactions.push_back(i);
	}
}


// get all the collisions be sure to avoid duplicate collisions
void PhysicsEngine::resolveCollisions(float dt) {

	// lLoop over all pairs of objects. check if they are colliding, if they are call there collision 
	// methods
	vector<MoveableObject*> seen;
	for (auto it = interactions.begin(); it != interactions.end(); ++it) {
		for (auto jt = objectDb->objects.begin(); jt != objectDb->objects.end(); ++jt) {
			
			if (jt->second != it->receiver && this->checkCollision(it->receiver, jt->second)) {
				it->receiver->collide(dt, *jt->second);
				if (jt->second->getType() != MOVEABLE) {
					changed.push_back(jt->second);
				}
				return;
			}
		}
	}
}


void PhysicsEngine::generateForces(float dt) {
	for (Interaction i : interactions) {
		i.generator->updateForce(i.receiver, dt);
	}
}


// update all the objects in the game by one timestep
void PhysicsEngine::integrateObjects(float dt) {
	for (Interaction i : interactions){
		i.receiver->integrate(dt);
		changed.push_back(i.receiver);
	}
}




