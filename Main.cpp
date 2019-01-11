#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

int main() {
	
	RenderWindow app{ VideoMode{1920,1080,},"TowerDefense",Style::Fullscreen };
		app.setFramerateLimit(144);

	while (app.isOpen()) {

		Event event;
		while (app.pollEvent(event)) {

			if (event.type == Event::Closed) app.close();

			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) app.close();

		}

		app.clear();
			//app.draw();
		app.display();
	}
	return 0;
}