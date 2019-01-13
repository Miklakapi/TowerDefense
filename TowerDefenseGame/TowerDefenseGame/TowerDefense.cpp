#include <SFML\Audio.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "Menu.hpp"
#include "Type.hpp"
#include "Map.hpp"
#include "TowerDefense.hpp"

TowerDefense::TowerDefense(RenderWindow* window) : map(window) {
	this->window = window;
	music = true;
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

void TowerDefense::setOptionsTexture(Texture* texture) {
	textureOptions = texture;
	options.settings = 0;
	options.setTexture((texture));
}

void TowerDefense::run() {
	if (game == true) {
		fireDude.moveMonster();
	}
}

void TowerDefense::click(Vector2i mousePosition, Mouse::Button button) {
	if (button == Mouse::Button::Left) {
		if (menu.open) {
			if (menu.click(mousePosition, music) == Type::Options::Start) {
				menu.open = false;
				game = true;
				playSound();
			}

			else if (menu.click(mousePosition, music) == Type::Options::Settings) {
				menu.open = false;
				options.open = true;
			}
			else if (menu.click(mousePosition, music) == Type::Options::Credits) {
				menu.open = false;
				credits.open = true;
			}

			else if (menu.click(mousePosition, music) == Type::Options::Exit) window->close();
			return;
		}
		if (options.open) {
			if (options.click(mousePosition, music) == Type::Options::FPS) {
				if (options.settings == 0) {
					options.settings = 1;
					options.setTexture(textureOptions + options.settings);
					window->setFramerateLimit(144);
				}
				else if (options.settings == 1) {
					options.settings = 0;
					options.setTexture(textureOptions + options.settings);
					window->setFramerateLimit(60);
				}
				else if (options.settings == 2) {
					options.settings = 3;
					options.setTexture(textureOptions + options.settings);
					window->setFramerateLimit(144);
				}
				else if (options.settings == 3) {
					options.settings = 2;
					options.setTexture(textureOptions + options.settings);
					window->setFramerateLimit(60);
				}
			}

			else if (options.click(mousePosition, music) == Type::Options::Volume) {
				if (options.settings == 0) {
					options.settings = 2;
					options.setTexture(textureOptions + options.settings);
					music = false;
					sound->stop();

				}
				else if (options.settings == 1) {
					options.settings = 3;
					options.setTexture(textureOptions + options.settings);
					music = false;
					sound->stop();
				}
				else if (options.settings == 2) {
					options.settings = 0;
					options.setTexture(textureOptions + options.settings);
					music = true;
					sound->play();
				}
				else if (options.settings == 3) {
					options.settings = 1;
					options.setTexture(textureOptions + options.settings);
					music = true;
					sound->play();
				}
			}

			else if (options.click(mousePosition, music) == Type::Options::Undo) {
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