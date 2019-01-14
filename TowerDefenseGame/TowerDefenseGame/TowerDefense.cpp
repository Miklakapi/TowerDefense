#include <SFML\Audio.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "Menu.hpp"
#include "Type.hpp"
#include "Map.hpp"
#include "TowerDefense.hpp"

using namespace sf;
using namespace std;

TowerDefense::TowerDefense(RenderWindow* window, string file) : map(window), options(window,file) {
	this->window = window;
	if(options.settings == 1 || options.settings == 0)music = true;
	round = 1;
	game = false;
}

void TowerDefense::setSound(Sound* sound) {
	this->sound = sound;
	this->sound->setLoop(true);
	(this->sound + 1)->setLoop(true);
	playSound();
}

void TowerDefense::playSound() {
	if (music) {
		if (game == false) {
			(sound + round)->stop();
			sound->play();
		}
		else {
			sound->stop();
			(sound + round)->play();
		}
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
					sound->play();
				}
				else if (options.settings == 1) {
					music = true;
					sound->play();
				}
				else if (options.settings == 2) {
					music = false;
					sound->stop();
				}
				else if (options.settings == 3) {
					music = false;
					sound->stop();
				}
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
		window->draw(fireDude);
	}
}