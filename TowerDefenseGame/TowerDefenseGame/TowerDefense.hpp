#pragma once
#include <SFML\Audio.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <list>
#include "Type.hpp"
#include "Menu.hpp"
#include "Map.hpp"
#include "LvReader.hpp"
#include "Monsters.hpp"
#include "Towers.hpp"
#include "RangeField.hpp"
#include "PointCounter.hpp"

using namespace std;
using namespace sf;

class TowerDefense {

	RenderWindow* window;

	bool game;

	bool information;

	bool infReset;

	int round;

	int lvNumbers;

	int baseHealth;

	//

	Menu* menu;

	Credits* credits;

	Options* options;

	Sound* menuMusic;

	bool music;

	//
	
	Map* map;

	Sound* lvSounds; //Array
	
	//

	LvReader* lvReader;

	string* lvFiles;

	//

	RangeField* rangeField;
	
	//

	PointCounter* pointCounter;

	//

	Monsters* monsters;

	Texture* monsterTextures; //Array

	Clock monsterDelay;

	int monsterNr;

	int live;

	//

	list<Tower> towers;

	Texture* towerTexture;

	Sound* shotSound;

	Clock shotSoundClock;

	int nrShot;

	//

	Text infText;

	Clock infoClock;

	///////////

	void playSound();

public:

	TowerDefense(RenderWindow* window, int lvNumbers);
	
	void loadMenu(Texture* menuTexture, Texture* creditsTexture, Texture* optionsTexture, Field* field, Sound* clickSound, Sound* menuMusic, string optionsFile);

	void loadMap(Texture* mapTextures, IntRect* rect, Sound* lvSounds);

	void loadLvReader(string* lvFiles);

	void loadRangeField();

	void loadPointCounter(Font& font);

	void loadMonsters(Texture* monsterTextures, IntRect* rect);

	void loadTowers(Texture* towerTexture, Sound shotSound);

	void createMonsters();

	//

	void run();

	void click(Vector2i mousePosition, Mouse::Button button);

	void nextLV();

	void resetGame();

	void drawAll();
};