#pragma once
#include <SFML\Audio.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "Menu.hpp"
#include "Type.hpp"
#include "Map.hpp"
#include "Monsters.hpp"

class TowerDefense {

	RenderWindow* window;

	Sound* sound;

	bool game;

	bool music;

	int round;

	IntRect* mapRect;

	//

	void playSound();

public:

	Menu menu;

	Options options;

	Credits credits;

	Map map;

	Monsters fireDude;

	//

	TowerDefense(RenderWindow* window, string file, Texture* texture, IntRect* rect);

	void setSound(Sound* sound);

	void run();

	void click(Vector2i mousePosition, Mouse::Button button);

	void drawAll();
};