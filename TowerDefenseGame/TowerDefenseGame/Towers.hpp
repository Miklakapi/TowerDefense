#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "Monsters.hpp"

using namespace sf;

class Tower : public RectangleShape{

	Clock clock;

	static const double PI;

	int range;

	int damage;

	int cost;

public:

	Tower();

	void setRange(int range);

	void setDamage(int damage);

	void setCost(int cost);

	int getRange();

	int getCost();

	void deviation(Monsters* monster);

	bool inRange(Monsters* monster);

	int shoot();
};