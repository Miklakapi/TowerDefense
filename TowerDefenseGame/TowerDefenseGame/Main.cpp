#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "Menu.hpp"
#include "Type.hpp"
#include <iostream>

using namespace sf;
using namespace std;

int main() {
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

	RenderWindow app{ VideoMode{1280,720,},"TowerDefense",Style::Close };
		app.setFramerateLimit(144);

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

	Texture mainMenu;
		mainMenu.loadFromFile("img/MenuMain.png");
	Texture options;
	//	options.loadFromFile();
	Texture credits;
	//	credits.loadFromFile();

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

	const Field field1{ Vector2i{974,215},Vector2i{1095,259} };
	const Field field2{ Vector2i{980,274},Vector2i{1094,309} };
	const Field field3{ Vector2i{980,328},Vector2i{1094,369} };
	const Field field4{ Vector2i{980,389},Vector2i{1094,421} };

	Menu menu;
		menu.setSize(Vector2f{ 1280,720 });
		menu.setTexture(&mainMenu);
		menu.loadField(field1, field2, field3, field4);

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

	while (app.isOpen()) {

		Event event;
		while (app.pollEvent(event)) {

			if (event.type == Event::Closed) app.close();

			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) app.close();

			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
				Vector2i mousePosition = Mouse::getPosition(app);
				if (menu.click(mousePosition) == Type::Options::Start) cout << "Start\n";
				else if (menu.click(mousePosition) == Type::Options::Settings) cout << "Settings\n";
				else if (menu.click(mousePosition) == Type::Options::Credits) cout << "Credits\n";
				else if (menu.click(mousePosition) == Type::Options::Exit) app.close();
			}

		}

		app.clear();
			if (menu.open) app.draw(menu);
		app.display();
	}
	return 0;
}