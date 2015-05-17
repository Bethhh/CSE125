#include "MoveableObject.h"

MoveableObject::MoveableObject(float acceleration, float dampening) : GameObject(), velocity(0) {

}


MoveableObject::~MoveableObject() {

}



void MoveableObject::move(float dt) {
	float cosa = glm::cos(glm::radians(angle));
	float sina = glm::sin(glm::radians(angle));
	glm::quat q = orientation * glm::angleAxis(glm::radians(velocity), glm::vec3(cosa, sina, 0));
	orientation = glm::normalize(glm::mix(orientation, q, dt));
}


void MoveableObject::collide(float dt, GameObject & target) {
	this->velocity = 0;
}