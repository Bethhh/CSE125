#include "ObjectDB.h"

void GameObject::serialize(Packet & p) {
	p.writeUInt(id);
	float* loc = glm::value_ptr(location);
	for (int i = 0; i < 16; ++i){
		p.writeFloat(loc[i]);
	}
}


void GameObject::deserialize(Packet & p) {
	//this->id = p.readUInt();
	float* loc = glm::value_ptr(location);
	for (int i = 0; i < 16; ++i){
		loc[i] = p.readFloat();
	}
}


ObjectDB::ObjectDB() {
	nextId = 0;
}


ObjectDB::~ObjectDB() {
	for (auto it = objects.begin(); it != objects.end(); ++it) {
		if (it->second) {
			delete it->second;
		}
	}
}


ObjectId ObjectDB::add(GameObject* object) {
    ObjectId newId = nextId++;
	object->id = newId;
	objects.insert(make_pair(newId, object));
	return newId;
}


bool ObjectDB::add(ObjectId id, GameObject* object) {
	if (!object) {
		return false;
	}
	auto found = objects.find(id);
	if (found == objects.end()) {
		object->id = id;
		objects.insert(make_pair(id, object));
		if (id >= nextId) {
			nextId = id + 1;
		}
		return true;
	}
	return false;
}


bool ObjectDB::remove(ObjectId objectId) {
	auto it = objects.find(objectId);
	if (it != objects.end()) {
		delete it->second;
		objects.erase(it);
		return true;
	}
	return false;
}


GameObject* ObjectDB::get(ObjectId objectId) {
	auto it = objects.find(objectId);
	if (it == objects.end()){
		return nullptr;	
	}
	return it->second;
}


void ObjectDB::getObjectState(deque<Packet> & state) {
	Packet p;
	for (auto it = objects.begin(); it != objects.end(); ++it){
		it->second->serialize(p);
		state.push_back(p);
		p.clear();
	}
}


ObjectDB & ObjectDB::getInstance() {
	static ObjectDB db;
	return db;
}