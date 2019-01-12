#pragma once
#include <SFML\Audio.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <queue>
#include "Type.hpp"

using namespace sf;
using namespace std;

class Monsters :public RectangleShape{

private:

	IntRect* rect;

	queue <Type::Direct> direct;

	Type::Mob mob;

	bool live;

	int copyHealth;
	int health;

	float speed;

	

public:	

	void loadIntRect(IntRect* rect);

	void setQueue(queue <Type::Direct> direct);

	void setMob(Type::Mob);

	Type::Mob getMob();

	void dmg(int damage);

	bool isLive();

	void reset();

};