#pragma once
#include <SFML\Audio.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "Type.hpp"

using namespace sf;

class Monsters :public RectangleShape{

private:

	Clock clock;

	static IntRect* rect;

	static Type::Direct* direct;	Type::Direct actualDirect;

	static int moveNumber;
	
	int aMove;
	int miniMove;

	bool live;

	int copyHealth;
	int health;

	int speed;	

public:	

	Monsters();

	void loadIntRect(IntRect* rect);

	void setRoad(Type::Direct* direct, int moveNumber);

	void setHealth(int helath);

	void setSpeed(int speed);

	void dmg(int damage);

	bool isLive();

	void reset();

	bool moveMonster();

};