#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <math.h>
#define PI 3.14159265
using namespace sf;

class Tower :public RectangleShape{
	float deviation(Monsters monster, Tower gun) {
		Vector2f xy = monster.getPosition() - gun.getPosition;
		float grade = atan2(xy.y, xy.x) * 180 / PI;
		return grade;
	}
	bool ifdmg(Monsters monster,Tower tower) {
		if ((sqrt(((monster.getPosition().x - tower.getPosition().x)*(monster.getPosition().x - tower.getPosition().x)) + 
		((monster.getPosition().y - tower.getPosition().y)*(monster.getPosition().y - tower.getPosition().y)))) < 60) return true;
		else return false;
	}
};