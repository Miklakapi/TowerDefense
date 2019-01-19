#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <math.h>
#include "Monsters.hpp"
#include "Towers.hpp"

using namespace sf;

const double Tower::PI = 3.14159265;

Tower::Tower() : RectangleShape() {
	setOrigin(Vector2f(40, 40));
	setSize(Vector2f(80, 80));
}

void Tower::setRange(int range) {
	this->range = range;
}

void Tower::setDamage(int damage) {
	this->damage = damage;
}

int Tower::getRange() {
	return range;
}

void Tower::deviation(Monsters* monster) {
	if(inRange(monster)) {
		Vector2f vec = monster->getPosition() - getPosition();
		float grade = float(atan2(vec.y, vec.x) * 180 / PI);
		setRotation(grade + 45);
	}
}

bool Tower::inRange(Monsters* monster) {
	if ((sqrt(((monster->getPosition().x - getPosition().x)*(monster->getPosition().x - getPosition().x)) +
		((monster->getPosition().y - getPosition().y)*(monster->getPosition().y - getPosition().y)))) <= range) return true;
	else return false;
}

int Tower::shoot(Monsters *monster) {
	if (inRange(monster)) {
		if (clock.getElapsedTime().asSeconds() < 1) return 0;
		clock.restart();
		return damage;
	}
	else return 0  ;
}
