#include <SFML\Audio.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "Menu.hpp"
#include "Type.hpp"
#include "TowerDefense.hpp"

void TowerDefense::setWindow(RenderWindow* window) {
	this->window = window;
}

void TowerDefense::setSound(Sound* sound) {
	this->sound = sound;
	this->sound->setLoop(true);
	(this->sound + 1)->setLoop(true);
	playSound();
}

void TowerDefense::playSound() {
	if (game == false) {
		(sound + 1)->stop();
		sound->play();
	}
	else {
		sound->stop();
		(sound + 1)->play();
	}
}

void TowerDefense::click(Vector2i mousePosition, Mouse::Button button) {
	if (button == Mouse::Button::Left) {
		if (menu.open) {
			if (menu.click(mousePosition) == Type::Options::Start) {
				menu.open = false;
				game = true;
				playSound();
			}

			else if (menu.click(mousePosition) == Type::Options::Settings) {
				menu.open = false;
				options.open = true;
			}
			else if (menu.click(mousePosition) == Type::Options::Credits) {
				menu.open = false;
				credits.open = true;
			}

			else if (menu.click(mousePosition) == Type::Options::Exit) window->close();
			return;
		}
		if (options.open) {
			if (options.click(mousePosition) == Type::Options::FPS);

			else if (options.click(mousePosition) == Type::Options::Volume);

			else if (options.click(mousePosition) == Type::Options::Undo) {
				menu.open = true;
				options.open = false;
			}
			return;
		}
		if (credits.open) {
			if (credits.click(mousePosition) == Type::Options::Undo) {
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
	if (options.open)window->draw(options);
	if (credits.open)window->draw(credits);
}