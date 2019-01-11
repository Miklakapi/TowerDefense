#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <iostream>
#include <time.h>

using namespace std;
using namespace sf;

int main() {
	int x = 60;
	RenderWindow app{ VideoMode{1280,720},"TowerDefense",Style::Close };
		app.setFramerateLimit(x);
		RectangleShape shape;
		Texture  texture;
		texture.loadFromFile("Grass.png");
		shape.setTexture(&texture);
		shape.setSize(Vector2f(40, 40));
	while (app.isOpen()) {

		Event event;
		while (app.pollEvent(event)) {

			if (event.type == Event::Closed) app.close();

			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) app.close();

		}

		app.clear();
		for (int x = 0; x < 32; x++) {
			for (int y = 0; y < 18; y++) {
				shape.setPosition(Vector2f(x * 40, y * 40));
				app.draw(shape);
			}
		}
		app.display();
	}
	return 0;
}