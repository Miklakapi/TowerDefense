#include <SFML\Audio.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "Menu.hpp"
#include "Type.hpp"
#include "Map.hpp"
#include "LvReader.hpp"
#include "TowerDefense.hpp"

using namespace sf;
using namespace std;

TowerDefense::TowerDefense(RenderWindow* window, Texture* menuTextures, Texture* optionsTextures, Texture* lv, Texture* monsterTexture,
	Field* field, Sound* menuMusic, Sound* lvSounds, string settingsFile, string* lvFile,
	IntRect* lvRect, IntRect* monsterRect, int lvNumbers)
	: options(window,settingsFile), map(window,lv,lvRect), lvReader(&map), rangeField(Color::Black)  {

	menu.setTexture(menuTextures);
	credits.setTexture(menuTextures + 1);
	options.loadTextures(optionsTextures);
	
	menu.loadSound(menuMusic);
	credits.loadSound(menuMusic);
	options.loadSound(menuMusic);
	
	menu.loadField(*(field), *(field + 1), *(field + 2), *(field + 3));
	credits.loadField(*(field), *(field + 1), *(field + 2), *(field + 3));
	options.loadField(*(field), *(field + 1), *(field + 2), *(field + 3));
	
	lvReader.setFile(*lvFile);

	fireDude.loadIntRect(monsterRect);
	fireDude.setTexture(monsterTexture);
	fireDude.setHealth(100);
	fireDude.setSpeed(10);
	fireDude.setRoad(lvReader.getDirect(),lvReader.getMoveNumber());
	fireDude.setPosition(lvReader.getStartPosition());

	this->window = window;

	this->lvFile = lvFile;

	this->menuMusic = *(menuMusic + 1);
	this->menuMusic.setLoop(true);

	this->lvSounds = lvSounds;
	for (int i = 0; i < lvNumbers; i++) {
		(this->lvSounds + i)->setLoop(true);
	}

	switch (options.settings) {
	case 0:
		window->setFramerateLimit(60);
		music = true;
		break;
	case 1:
		window->setFramerateLimit(144);
		music = true;
		break;
	case 2:
		window->setFramerateLimit(60);
		music = false;
		break;
	case 3:
		window->setFramerateLimit(144);
		music = false;
		break;
	}

	game = false;

	round = 1;
	
	this->lvNumbers = lvNumbers;

	playSound();
}

void TowerDefense::playSound() {
	if (!game) {
		(lvSounds + (round - 1))->stop();
		if (music) menuMusic.play();
		else menuMusic.stop();
	}
	else {
		menuMusic.stop();
		if (music) (lvSounds + (round - 1))->play();
		else (lvSounds + (round - 1))->stop();
	}
}

void TowerDefense::run() {
	if (game == true) {
		fireDude.moveMonster();
	}
}

void TowerDefense::click(Vector2i mousePosition, Mouse::Button button) {
	if (button == Mouse::Button::Left) {
		if (menu.open) {
			Type::Options opt = menu.click(mousePosition, music);
			if (opt == Type::Options::Start) {
				menu.open = false;
				game = true;
				playSound();
			}
			else if (opt == Type::Options::Settings) {
				menu.open = false;
				options.open = true;
			}
			else if (opt == Type::Options::Credits) {
				menu.open = false;
				credits.open = true;
			}
			else if (opt == Type::Options::Exit) window->close();
			return;
		}
		if (options.open) {
			Type::Options opt = options.click(mousePosition, music);
			if (opt == Type::Options::Volume) {
				if (options.settings == 0) {
					music = true;
				}
				else if (options.settings == 1) {
					music = true;
				}
				else if (options.settings == 2) {
					music = false;
				}
				else if (options.settings == 3) {
					music = false;
				}
				playSound();
			}
			else if (opt == Type::Options::Undo) {
				menu.open = true;
				options.open = false;
			}
			return;
		}
		if (credits.open) {
			if (credits.click(mousePosition, music) == Type::Options::Undo) {
				menu.open = true;
				credits.open = false;
			}
			return;
		}
	}
	else if (button == Mouse::Button::Right) {
		//
	}
}

void TowerDefense::drawAll() {
	if (menu.open)window->draw(menu);
	else if (options.open)window->draw(options);
	else if (credits.open)window->draw(credits);
	else if (game) {
		map.drawAll();
		if (fireDude.isLive()) window->draw(fireDude);
	}
}