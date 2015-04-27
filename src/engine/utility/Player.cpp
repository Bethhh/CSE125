#include "Player.h"
#include "Location.h"

int numOfPlayers = 0;

//TODO Config file
Player::Player(BlobModel thebm, float radius, float theta, float azimuth, float direction) {//: GameObject(radius, theta, ) {
	this->numOfPlayers++;
	this->pid = numOfPlayers;
	//this->id = "Player" + this->pid;
	this->speed = 0;
	this->power = 0;
	//this->loc = Location(nx, ny, nz);
	orientation = glm::vec4(radius, theta, azimuth, direction);
	this->bm = thebm;

}

glm::vec4 & Player::getOrientation() {
	return orientation;
}

int Player::getSpeed() {
	return speed;
}

int Player::getPower() {
	return power;
}

int Player::getPid() {
	return pid;
}


void Player::setSpeed(int newSpeed) {
	speed = newSpeed;
}

void Player::setPower(int newPower) {
	power = newPower;
}
