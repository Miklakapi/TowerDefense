#include <SFML\Audio.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "Type.hpp"
#include "Monsters.hpp"
#include <iostream>

using namespace sf;

IntRect* Monsters::monsterRect = NULL;
Type::Direct* Monsters::direct = NULL;

void Monsters::loadIntRect(IntRect* rect) {
	monsterRect = rect;
}

void Monsters::setRoad(Type::Direct* direct) {
	this->direct = direct;
}

void Monsters::setMob(Type::Mob mob) {
	this->mob = mob;
	setTextureRect(*(monsterRect));
}

Type::Mob Monsters::getMob() {
	return mob;
}

void Monsters::setHealth(int helath) {
	copyHealth = health;
	this->health = health;
}

void Monsters::setSpeed(int speed) {
	this->speed = speed;
}

void Monsters::setMoveNumber(int moveNumber) {
	this->moveNumber = moveNumber;
}

void Monsters::dmg(int damage) {
	health -= damage;
	if (health <= 0) live = false;
}

bool Monsters::isLive() {
	return live;
}

void Monsters::reset() {
	setMob(mob);
	live = true;
	health = copyHealth;
	miniMove = 0;
	aMove = 0;
}

int Monsters::moveMonster() {
	
	if (clock.getElapsedTime().asSeconds() < 0.1 || live == false || aMove == moveNumber) return -1;
	clock.restart();

	miniMove++;

	if (aMove == 0 && miniMove == 1) {
		miniMove = 6;
		setTextureRect(*(monsterRect));
		actualDirect = *direct;
	}

	if (miniMove == 6) {
		if (*(direct + aMove) == Type::Direct::EN) {
			setTextureRect(*(monsterRect + Type::Direct::Top));
			actualDirect = Type::Direct::Top;
		}
		else if (*(direct + aMove) == Type::Direct::NE) {
			setTextureRect(*(monsterRect + Type::Direct::Right));
			actualDirect = Type::Direct::Right;
		}
		else if (*(direct + aMove) == Type::Direct::ES) {
			setTextureRect(*(monsterRect + Type::Direct::Bottom));
			actualDirect = Type::Direct::Bottom;
		}
		else if (*(direct + aMove) == Type::Direct::SE) {
			setTextureRect(*(monsterRect + Type::Direct::Right));
			actualDirect = Type::Direct::Right;
		}
		else if (*(direct + aMove) == Type::Direct::SW) {
			setTextureRect(*(monsterRect + Type::Direct::Left));
			actualDirect = Type::Direct::Left;
		}
		else if (*(direct + aMove) == Type::Direct::WS) {
			setTextureRect(*(monsterRect + Type::Direct::Bottom));
			actualDirect = Type::Direct::Bottom;
		}
		else if (*(direct + aMove) == Type::Direct::NW) {
			setTextureRect(*(monsterRect + Type::Direct::Left));
			actualDirect = Type::Direct::Left;
		}
		else if (*(direct + aMove) == Type::Direct::WN) {
			setTextureRect(*(monsterRect + Type::Direct::Top));
			actualDirect = Type::Direct::Top;
		}
	}

	switch (actualDirect) {
	case Type::Direct::Right:
		move(8, 0);
		break;
	case Type::Direct::Bottom:
		move(0, 8);
		break;
	case Type::Direct::Left:
		move(-8, 0);
		break;
	case Type::Direct::Top:
		move(0, -8);
		break;
	}

	if (miniMove == 10 ) {
		aMove++;
		miniMove = 0;
	}
	return ((moveNumber * 10) + miniMove);
}