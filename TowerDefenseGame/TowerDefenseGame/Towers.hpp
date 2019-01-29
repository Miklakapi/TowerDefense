#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <math.h>
#include "Monsters.hpp"

using namespace sf;

class Tower : public RectangleShape{

	static Texture* textures;

	Clock clock;

	int range;

	int damage;

	int cost;

	bool fire;

	bool animation;

public:

	Tower();

	void loadTextures(Texture* texture);

	void setRange(int range);

	void setDamage(int damage);

	void setCost(int cost);

	int getRange();

	int getCost();

	bool getFire();

	bool getAnimation();

	void deviation(Monsters* monster);

	bool inRange(Monsters* monster);

	int shot();
};
