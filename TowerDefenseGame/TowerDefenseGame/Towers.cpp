#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <math.h>
#include "Monsters.hpp"
#include "Towers.hpp"
#define PI 3.14159265

using namespace sf;


Tower::Tower() : RectangleShape() {
		setOrigin(Vector2f(40, 40));
		setSize(Vector2f(80, 80));

	}
	void Tower::deviation(Monsters*monster) {
		if(ifdmg(monster)) {
			Vector2f xy = monster->getPosition() - getPosition();
			float grade = atan2(xy.y, xy.x) * 180 / PI;
			setRotation(grade + 45);
		}
	}
	bool Tower::ifdmg(Monsters*monster) {
		if ((sqrt(((monster->getPosition().x - getPosition().x)*(monster->getPosition().x - getPosition().x)) +
			((monster->getPosition().y - getPosition().y)*(monster->getPosition().y - getPosition().y)))) < 250) return true;
		else return false;
	}
	int Tower::shoot(Monsters*monster) {
		if (ifdmg(monster)) {
			if (clock.getElapsedTime().asSeconds() < 1) return 0;
			clock.restart();
			return 40;
		}
		else return 0  ;
	}
