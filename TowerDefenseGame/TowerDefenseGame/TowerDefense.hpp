#pragma once
#include <SFML\Audio.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "Menu.hpp"
#include "Type.hpp"
#include "Square.hpp"

class TowerDefense {

	RenderWindow* window;

	Sound* sound;

	bool game;

	//

	void playSound();

public:

	Menu menu;

	Options options;

	Credits credits;

	//

	void setWindow(RenderWindow* window);

	void setSound(Sound* sound);

	void click(Vector2i mousePosition, Mouse::Button button);

	void drawAll();
};