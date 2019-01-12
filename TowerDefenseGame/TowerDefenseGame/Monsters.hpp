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

	Type::Mob mob;

	bool live;

	int health;

	float speed;

	queue <Type::Direct> direct;

public:	

	void loadIntRect(IntRect* rect);

	void setQueue(queue <Type::Direct> direct);

	void setMob(Type::Mob);

	void dmg(int damage);

	bool isLive();

	void reset();

};