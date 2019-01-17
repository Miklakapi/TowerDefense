#pragma once
#include <SFML\Audio.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "Menu.hpp"
#include "Type.hpp"
#include "Map.hpp"
#include "Monsters.hpp"
#include "LvReader.hpp"

using namespace std;
using namespace sf;

class TowerDefense {

	RenderWindow* window; //////

	Sound menuMusic; ///////

	Sound* lvSounds; ///////

	bool game; /////////

	bool music; ////////

	int round; //////////

	string* lvFile; /////////

	Menu menu; ////////

	Options options; ////////

	Credits credits; /////////

	Map map; ////////

	LvReader lvReader; ////////

	int lvNumbers;

	///////////

	void playSound();




public:

	Monsters fireDude; ///////

	//

	TowerDefense(RenderWindow* window, Texture* menuTextures, Texture* optionsTextures, Texture* lv, Texture* monsterTexture,
		Field* field, Sound* menuMusic, Sound* lvSounds, string optionsFile, string* lvFile,
		IntRect* lvRect, IntRect* monsterRect, int lvNumbers);

	void run();

	void click(Vector2i mousePosition, Mouse::Button button);

	void drawAll();
};