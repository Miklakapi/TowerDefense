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

TowerDefense::TowerDefense(RenderWindow* window, int lvNumbers){
	this->window = window;
	game = false;
	round = 1;
	this->lvNumbers = lvNumbers;
}

void TowerDefense::loadMenu(Texture* menuTexture, Texture* creditsTexture, Texture* optionsTextures, Field* field, Sound* clickSound, Sound* menuMusic, string optionsFile) {
	this->menuMusic = menuMusic;
	menu = new Menu;
	menu->loadField(*(field), *(field + 1), *(field + 2), *(field + 3));
		menu->loadSound(clickSound);
		menu->setTexture(menuTexture);
	credits = new Credits;
		credits->loadField(*(field), *(field + 1), *(field + 2), *(field + 3));
		credits->loadSound(clickSound);
		credits->setTexture(creditsTexture);
	options = new Options(window, optionsFile);
		options->loadField(*(field), *(field + 1), *(field + 2), *(field + 3));
		options->loadSound(clickSound);
		options->loadTextures(optionsTextures);
	switch (options->settings) {
	case 0:
		music = true;
		break;
	case 1:
		music = true;
		break;
	case 2:
		music = false;
		break;
	case 3:
		music = false;
		break;
	}
	if (music) this->menuMusic->play();
}

void TowerDefense::loadMap(Texture* mapTextures, IntRect* rect, Sound* lvSounds) {
	this->lvSounds = lvSounds;
	map = new Map(window, mapTextures, rect);
}

void TowerDefense::loadLvReader(string* lvFiles) {
	this->lvFiles = lvFiles;
	lvReader = new LvReader(map);
	lvReader->setFile(*lvFiles);
}

void TowerDefense::loadRangeField() {
	rangeField = new RangeField(Color{ 0, 0, 255, 50 });
	rangeField->turnOff();
}

void TowerDefense::loadPointCounter(Font& font) {
	pointCounter = new PointCounter(font);
}

//

void TowerDefense::playSound() {
	if (!game) {
		(lvSounds + (round - 1))->stop();
		if (music) menuMusic->play();
		else menuMusic->stop();
	}
	else {
		menuMusic->stop();
		if (music) (lvSounds + (round - 1))->play();
		else (lvSounds + (round - 1))->stop();
	}
}

//Public:

void TowerDefense::run() {

}

void TowerDefense::click(Vector2i mousePosition, Mouse::Button button) {
	if (button == Mouse::Button::Left) {
		if (menu->open) {
			Type::Options opt = menu->click(mousePosition, music);
			if (opt == Type::Options::Start) {
				menu->open = false;
				game = true;
				playSound();
			}
			else if (opt == Type::Options::Settings) {
				menu->open = false;
				options->open = true;
			}
			else if (opt == Type::Options::Credits) {
				menu->open = false;
				credits->open = true;
			}
			else if (opt == Type::Options::Exit) window->close();
			return;
		}
		if (options->open) {
			Type::Options opt = options->click(mousePosition, music);
			if (opt == Type::Options::Volume) {
				if (options->settings == 0) {
					music = true;
				}
				else if (options->settings == 1) {
					music = true;
				}
				else if (options->settings == 2) {
					music = false;
				}
				else if (options->settings == 3) {
					music = false;
				}
				playSound();
			}
			else if (opt == Type::Options::Undo) {
				menu->open = true;
				options->open = false;
			}
			return;
		}
		if (credits->open) {
			if (credits->click(mousePosition, music) == Type::Options::Undo) {
				menu->open = true;
				credits->open = false;
			}
			return;
		}
	}
	else if (button == Mouse::Button::Right) {
		//
	}
}

void TowerDefense::drawAll() {
	if (menu->open)window->draw(*menu);
	else if (options->open)window->draw(*options);
	else if (credits->open)window->draw(*credits);
	else if (game) {
		map->drawAll();
		//if (fireDude->isLive()) window->draw(*fireDude);
	}
}