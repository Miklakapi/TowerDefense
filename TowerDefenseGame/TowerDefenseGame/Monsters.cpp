#include <SFML\Audio.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "Type.hpp"
#include "Monsters.hpp"

using namespace sf;
using namespace std;

IntRect* Monsters::rect = NULL;
Type::Direct* Monsters::direct = NULL;
int Monsters::moveNumber = 0;

void Monsters::loadIntRect(IntRect* rect) {
	this->rect = rect;
}

void Monsters::setRoad(Type::Direct* direct, int moveNumber) {
	this->direct = direct;
	this->moveNumber = moveNumber;
	setTextureRect(*(rect+*direct));
}

void Monsters::setHealth(int health) {
	
	this->health = health;
	copyHealth = health;
}

void Monsters::setSpeed(int speed) {
	this->speed = speed;
}

void Monsters::dmg(int damage) {
	health = health - damage;
	if (health <= 0) live = false;
	else live = true;
}

bool Monsters::isLive() {
	return live;
}

void Monsters::reset() {
	live = true;
	health = copyHealth;
	miniMove = 0;
	aMove = 0;
}

bool Monsters::moveMonster() {
	
	if (clock.getElapsedTime().asSeconds() < float(speed/100.f) || live == false || aMove == moveNumber) return false;
	clock.restart();

	miniMove++;

	if (aMove == 0 && miniMove == 1) {
		miniMove = 6;
		setTextureRect(*(rect+*direct));
		actualDirect = *direct;
	}

	if (miniMove == 6) {
		if (*(direct + aMove) == Type::Direct::EN) {
			setTextureRect(*(rect + Type::Direct::Top));
			actualDirect = Type::Direct::Top;
		}
		else if (*(direct + aMove) == Type::Direct::NE) {
			setTextureRect(*(rect + Type::Direct::Right));
			actualDirect = Type::Direct::Right;
		}
		else if (*(direct + aMove) == Type::Direct::ES) {
			setTextureRect(*(rect + Type::Direct::Bottom));
			actualDirect = Type::Direct::Bottom;
		}
		else if (*(direct + aMove) == Type::Direct::SE) {
			setTextureRect(*(rect + Type::Direct::Right));
			actualDirect = Type::Direct::Right;
		}
		else if (*(direct + aMove) == Type::Direct::SW) {
			setTextureRect(*(rect + Type::Direct::Left));
			actualDirect = Type::Direct::Left;
		}
		else if (*(direct + aMove) == Type::Direct::WS) {
			setTextureRect(*(rect + Type::Direct::Bottom));
			actualDirect = Type::Direct::Bottom;
		}
		else if (*(direct + aMove) == Type::Direct::NW) {
			setTextureRect(*(rect + Type::Direct::Left));
			actualDirect = Type::Direct::Left;
		}
		else if (*(direct + aMove) == Type::Direct::WN) {
			setTextureRect(*(rect + Type::Direct::Top));
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

	if (aMove == moveNumber) {
		live = false;
		return true;
	}
	else return false;
}