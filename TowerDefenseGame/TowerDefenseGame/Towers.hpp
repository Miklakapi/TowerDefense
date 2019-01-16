#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
using namespace sf;
class Tower : public RectangleShape{
	Clock clock;
public:
	Tower();
	void deviation(Monsters*monster);
	bool ifdmg(Monsters*monster);
	int shoot(Monsters*monster);
};