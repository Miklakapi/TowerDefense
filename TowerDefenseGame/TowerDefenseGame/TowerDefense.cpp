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
	information = false;
	infReset = true;
	round = 1;
	baseHealth = 10;
	monsterNr = 0;
	this->lvNumbers = lvNumbers;

	infText.setPosition(520, 250);
	infText.setLetterSpacing(5);
	infText.setCharacterSize(100);
	infText.setStyle(Text::Bold);
	infText.setFillColor(Color::Red);
	infText.setString("Lose");
}

void TowerDefense::loadMenu(Texture* menuTexture, Texture* creditsTexture, Texture* optionsTextures, Field* field, Sound* clickSound, Sound* menuMusic, string optionsFile) {
	this->menuMusic = menuMusic;
	this->menuMusic->setLoop(true);
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
	for (int i = 0; i < lvNumbers; i++) {
		(this->lvSounds + i)->setLoop(true);
	}
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
	infText.setFont(font);
}

void TowerDefense::loadMonsters(Texture* monsterTextures, IntRect* rect) {
	this->monsterTextures = monsterTextures;
	Monsters monst;
	monst.loadIntRect(rect);
}

void TowerDefense::loadTowers(Texture* towerTexture, Sound shotSound) {
	this->towerTexture = towerTexture;
	this->shotSound = new Sound[5];
	for (int i = 0; i < 5; i++) {
		*(this->shotSound + i) = shotSound;
	}
	Tower tower;
	tower.loadTextures(towerTexture);
}

void TowerDefense::createMonsters() {
	monsters = new Monsters[lvReader->getMobNumber()];
	Vector2f vec;
	if (round == 1) vec = { 40,60 };
	else if (round == 2) vec = { 40,60 };
	else if (round == 3) vec = { 40,40 };
	for (int i = 0; i < lvReader->getMobNumber(); i++) {
		(monsters + i)->setOrigin(vec);
		(monsters + i)->setTexture((monsterTextures + (round - 1)));
		(monsters + i)->setHealth(100 + 10 * round);
		(monsters + i)->setSpeed(20 - 2 * round);
		(monsters + i)->setValue(20);
		(monsters + i)->setPosition(lvReader->getStartPosition());
	}
	monsters->setRoad(lvReader->getDirect(), lvReader->getMoveNumber());
	live = lvReader->getMobNumber();
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
		if (music) {
			if(round > 1) (lvSounds + (round - 2))->stop();
			(lvSounds + (round - 1))->play();
		}
		else (lvSounds + (round - 1))->stop();
	}
}

//Public:

void TowerDefense::run() {
	if ((!game) || information) return;
	nrShot = 0;
	for(list<Tower>::iterator iter = towers.begin(); iter != towers.end(); iter++){
		
		for (int i = 0; i < lvReader->getMobNumber(); i++) {
			if (iter->inRange(monsters + i) && (monsters + i)->isLive()) {
				iter->deviation((monsters + i));
				pointCounter->setPoints(pointCounter->getPoints() + (monsters + i)->dmg(iter->shot()));
				if (nrShot < 5 && iter->getFire() && music) {
					(shotSound + nrShot)->play();
					nrShot++;
				}
				if (!(monsters + i)->isLive()) live--;
				break;
			}
			else if (iter->getAnimation()) iter->shot();
		}	
	}
	
	if (live <= 0) {
		infText.setString("WIN");
		information = true;
	}

	if (monsterDelay.getElapsedTime().asSeconds() >= 3-(round / 10) && monsterNr < lvReader->getMobNumber()) {
		monsterDelay.restart();
		(monsters + monsterNr)->reset();
		monsterNr++;
	}
	
	for (int i = 0; i < monsterNr; i++) {
		if ((monsters + i)->moveMonster()) {
			baseHealth--;
			live--;
		}
	}

	if (baseHealth <= 0) {
		infText.setString("LOSE");
		information = true;
	}

}

void TowerDefense::click(Vector2i mousePosition, Mouse::Button button) {
	if (information) return;
	if (button == Mouse::Button::Left && game == false) {
		if (menu->open) {
			Type::Options opt = menu->click(mousePosition, music);
			if (opt == Type::Options::Start) {
				menu->open = false;
				game = true;
				round = 1;
				createMonsters();
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
	else if (button == Mouse::Button::Left && game == true) {
		int x = int(mousePosition.x / 80);
		int y = int(mousePosition.y / 80);
		int position = x + (y * 16);
		if (map->getElement(position) == Type::Content::Grass && pointCounter->getPoints() >= 50) {
			pointCounter->setPoints(pointCounter->getPoints() - 50);
			map->setContent(position, Type::Content::Tower);
			Tower tower;
			tower.setTexture(towerTexture);
			//tower.loadSound(shotSound);
			tower.setPosition(float(x * 80 + 40), float(y * 80 + 40));
			tower.setRange(200);
			tower.setDamage(15);
			towers.push_back(tower);
		}
	}
	else if (button == Mouse::Button::Right && game == true) {
		int x = int(mousePosition.x / 80);
		int y = int(mousePosition.y / 80);
		int position = x + (y * 16);
		if (map->getElement(position) == Type::Content::Tower) {
			Vector2f vec{ float(x * 80 + 40), float(y * 80 + 40) };
			rangeField->set(vec, 200);
			rangeField->turnOn();
		}
		else rangeField->turnOff();
	}
}

void TowerDefense::nextLV() {
	if (!game) return;
	information = false;
	round++;
	if (round > lvNumbers){
		(lvSounds + (lvNumbers-1))->stop();
		resetGame();
	}
	else {
		map->setLv(round);
		lvReader->setFile(*(lvFiles + (round - 1))); 
		delete[] monsters;
		monsterNr = 0;
		createMonsters();
		baseHealth = 10;
		rangeField->turnOff();
		pointCounter->setPoints(100);
		towers.clear();
		playSound();
	}
}

void TowerDefense::resetGame() {
	information = false;
	game = false;
	menu->open = true;
	round = 1;
	baseHealth = 10;
	map->setLv(1);
	lvReader->setFile(*lvFiles);
	rangeField->turnOff();
	pointCounter->setPoints(100);
	delete[] monsters;
	monsterNr = 0;
	towers.clear();
	for (int i = 0; i < lvNumbers; i++) (lvSounds + i)->stop();
	playSound();
}

void TowerDefense::drawAll() {
	if (game) {

		if (!information) {
			map->drawAll();

			for (list<Tower>::iterator iter = towers.begin(); iter != towers.end(); iter++) {

				window->draw(*iter);

			}
			for (int i = 0; i < lvReader->getMobNumber(); i++) {
				if ((monsters + i)->isLive())window->draw(*(monsters + i));
			}

			if (rangeField->isOn()) window->draw(*rangeField);
			window->draw(*pointCounter);
		}
		else {
			if (infReset) {
				infoClock.restart();
				infReset = false;
			}
			window->draw(infText);
			
			if (infoClock.getElapsedTime().asSeconds() >= 3) {
				infReset = true;
				if (infText.getString() == "LOSE") resetGame();
				else if (infText.getString() == "WIN" && round > lvNumbers) resetGame();
				else nextLV();
			}
		}
	}
	else {
		if (menu->open)window->draw(*menu);
		else if (options->open)window->draw(*options);
		else if (credits->open)window->draw(*credits);
	}
	
}