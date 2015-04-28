#include "Player.h"
#include "Location.h"

ObjectId numOfPlayers = 0;

//TODO Config file
Player::Player(BlobModel thebm, int nx, int ny, int nz) : GameObject(nx, nx, nz) {
	this->numOfPlayers++;
	this->pid = numOfPlayers;
	this->speed = 0;
	this->power = 0;
	this->loc = Location(nx, ny, nz);
	this->bm = thebm;
}



int Player::getSpeed() {
	return speed;
}

int Player::getPower() {
	return power;
}

ObjectId Player::getPid() {
	return pid;
}


void Player::setSpeed(int newSpeed) {
	speed = newSpeed;
}

void Player::setPower(int newPower) {
	power = newPower;
}