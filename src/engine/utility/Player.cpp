#include "Player.h"
#include <iostream>
#include <gtx\string_cast.hpp>

//TODO Config file
Player::Player(Model thebm, float radius, float theta, float azimuth, float direction) : MoveableObject() {
	static int num;
	//this->loc = vec4(radius, theta, azimuth, direction);
   this->rm = thebm;
   this->moves[0] = false;
   this->moves[1] = false;
   this->moves[2] = false;
   this->moves[3] = false;

	for (int i = 0; i < 4; ++i)
		this->moves[i] = false;

	this->type = PLAYER;
	//this->velocity = 0;
	this->modelRadius = 7.f;
	if (num)
		this->setMass(100);
	num++; 
}

Player::~Player() {

}


bool Player::getMoving(int index) {
	return moves[index];
}

void Player::setMoving(int index, bool b) {
	moves[index] = b;
}


void Player::integrate(float dt) {

	if (moves[RIGHT]) {
		angle -= 1.f;
	}
	if (moves[LEFT]) {
		angle += 1.f;
		std::cout << "Angle: " << angle << std::endl;
	}

	float cosa = glm::cos(glm::radians(angle));
	float sina = glm::sin(glm::radians(angle));

	float forceConst = 30.f * log(this->getMass());

	if (moves[UP]) {
		this->addForce(cosa * forceConst, sina * forceConst, 0);

	}

	if (moves[DOWN]) {
		this->addForce(cosa * -forceConst, sina * -forceConst, 0);
	}

	MoveableObject::integrate(dt);

}


void Player::collide(float dt, GameObject & target) {
	if (target.getType() == PLAYER) {
		Player & other = dynamic_cast<Player&>(target);
		vec3 v1 = this->velocity;
		vec3 v2 = other.velocity;
		vec3 p1 = this->orientation * vec3(0.f, 0.f, 505.f);
		vec3 p2 = other.orientation * vec3(0.f, 0.f, 505.f);
		float m1 = this->getMass();
		float m2 = other.getMass();

		vec3 unormal12 = (p1 - p2) / (glm::length(p1 - p2));
		vec3 unormal21 = (p2 - p1) / (glm::length(p2 - p1));

		float distance = glm::distance(p1, p2);
		if (distance < this->getModelRadius() + other.getModelRadius()) {
			distance = this->getModelRadius() + other.getModelRadius() - distance;
			//this->orientation = this->orientation * -()
		}
		float component12 = glm::dot(v1, p1 - p2) / glm::length(p1 - p2);
		float component21 = glm::dot(v2, p2 - p1) / glm::length(p2 - p1);

		vec3 u12 = component12 * unormal12;
		vec3 u21 = component21 * unormal21;
		vec3 t12 = v1 - u12;
		vec3 t21 = v2 - u21;

		vec3 v12 = (u12 * (m1 - m2) + 2 * m2 * u21) / (m1 + m2);
		vec3 v21 = (u21 * (m2 - m1) + 2 * m1 * u12) / (m1 + m2);
		
		this->velocity = v12 + t12;
		other.velocity = v21 + t21;
	}

}