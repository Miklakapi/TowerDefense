#include "Monsters.hpp"
#include "Towers.hpp"

using namespace sf;

const double PI = 3.14159265;

Texture* Tower::textures = NULL;

bool oneSec = true;

Tower::Tower() : RectangleShape() {
	setOrigin(Vector2f(40, 40));
	setSize(Vector2f(80, 80));
	fire = false;
}

void Tower::loadSound(Sound* sound) {
	this->sound = *sound;
}

void Tower::loadTextures(Texture* textures) {
	this->textures = textures;
}

void Tower::setRange(int range) {
	this->range = range;
}

void Tower::setDamage(int damage) {
	this->damage = damage;
}

void Tower::setCost(int cost) {
	this->cost = cost;
}

int Tower::getRange() {
	return range;
}

int Tower::getCost() {
	return cost;
}

bool Tower::getFire() {
	return fire;
}

void Tower::deviation(Monsters* monster) {
	Vector2f vec = monster->getPosition() - getPosition();
	float grade = float(atan2(vec.y, vec.x) * 180 / PI);
	setRotation(grade + 45);
}

bool Tower::inRange(Monsters* monster) {
	if ((sqrt(((monster->getPosition().x - getPosition().x)*(monster->getPosition().x - getPosition().x)) +
		((monster->getPosition().y - getPosition().y)*(monster->getPosition().y - getPosition().y)))) <= range) return true;
	else return false;
}

int Tower::shoot() {
	if (clock.getElapsedTime().asSeconds() > 0.20) {
		setTexture(textures);
		fire = false;
	}
	if (clock.getElapsedTime().asSeconds() < 0.50) return 0;
	setTexture(textures + 1);
	fire = true;
	clock.restart();
	sound.play();
	return int(damage/2);
}
