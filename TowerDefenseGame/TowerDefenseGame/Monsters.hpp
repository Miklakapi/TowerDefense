#pragma once
#include <SFML\Audio.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "Type.hpp"

using namespace sf;
using namespace std;

class Monsters :public RectangleShape{

private:

	Clock clock;

	static IntRect* monsterRect;

	static Type::Direct* direct;
	Type::Direct actualDirect;
	int moveNumber;
	int aMove;
	int miniMove;

	Type::Mob mob;

	bool live;

	int copyHealth;
	int health;

	int speed;	

public:	

	void loadIntRect(IntRect* rect);

	void setRoad(Type::Direct* direct);

	void setMob(Type::Mob mob);

	Type::Mob getMob();

	void setHealth(int helath);

	void setSpeed(int speed);

	void setMoveNumber(int moveNumber);

	void dmg(int damage);

	bool isLive();

	void reset();

	int moveMonster();

};