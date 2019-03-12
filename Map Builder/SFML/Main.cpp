#include <iostream>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <math.h>
#include "LvCreator.hpp"

using namespace sf;
using namespace std;
void main() {

	RenderWindow app{ VideoMode{1280,720,32},"Map Builder: Tower Defense",Style::Close };
	app.setFramerateLimit(60);
	LvCreator creator;
	while (app.isOpen()) {
		Event event;
		while (app.pollEvent(event)) {

			if (event.type == Event::Closed) app.close();
			if (event.type == Event::MouseButtonPressed && Mouse::isButtonPressed(Mouse::Left)) { creator.monster_add(&app); creator.texture_change(&app); }
			
		}
		creator.saves(&app);
		creator.change(&app);
		creator.choicedelement(&app);
		app.clear();

		creator.loadScreen(&app);
		app.display();
	}
}