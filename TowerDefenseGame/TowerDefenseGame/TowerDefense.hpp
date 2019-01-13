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

	bool music;

	int round;

	Texture* textureOptions;

	//

	void playSound();

public:

	Menu menu;

	Options options;

	Credits credits;

	//

	TowerDefense();

	void setWindow(RenderWindow* window);

	void setSound(Sound* sound);

	void setOptionsTexture(Texture* texture);

	void click(Vector2i mousePosition, Mouse::Button button);

	void drawAll();
};