#pragma once
#include <SFML\Audio.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "Menu.hpp"
#include "Type.hpp"
#include "Map.hpp"

class TowerDefense {

	RenderWindow* window;

	Sound* sound;

	bool game;

	bool music;

	int round;

	Texture* textureOptions;

	IntRect* mapRect;

	//

	void playSound();

public:

	Menu menu;

	Options options;

	Credits credits;

	Map map;



	//

	TowerDefense(RenderWindow* window);

	void setSound(Sound* sound);

	void setOptionsTexture(Texture* texture);

	

	void click(Vector2i mousePosition, Mouse::Button button);

	void drawAll();
};