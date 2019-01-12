#include <SFML\Audio.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <queue>
#include "Type.hpp"
#include "Monsters.hpp"

using namespace sf;

void Monsters::loadIntRect(IntRect* rect) {
	this->rect = rect;
	reset();
}

void Monsters::setQueue(queue <Type::Direct> direct) {
	this->direct = direct;
}

void Monsters::setMob(Type::Mob mob) {
	setTextureRect(*(rect + mob));
}

void Monsters::dmg(int damage) {
	health -= damage;
	if (health <= 0) live = false;
}

bool Monsters::isLive() {
	return live;
}

void Monsters::reset() {
	setMob(Type::Mob::Empty);
	
}