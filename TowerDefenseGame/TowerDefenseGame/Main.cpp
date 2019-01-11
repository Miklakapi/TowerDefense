#include <SFML\Audio.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "Menu.hpp"
#include "Type.hpp"

using namespace sf;

int main() {
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

	RenderWindow app{ VideoMode{1280,720,},"TowerDefense",Style::Close };
		app.setFramerateLimit(144);

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

	Texture mainMenu;
		mainMenu.loadFromFile("Img/MenuMain.png");
	Texture optionsMenu;
		optionsMenu.loadFromFile("Img/MenuOptions.png");
	Texture creditsMenu;
		creditsMenu.loadFromFile("Img/MenuCredits.png");

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

	SoundBuffer clickBuffer;
	clickBuffer.loadFromFile("Sound/click.ogg");

	Sound clickSound;
	clickSound.setBuffer(clickBuffer);
	clickSound.setVolume(5);

	const Field field1{ Vector2i{974,215},Vector2i{1095,259} };
	const Field field2{ Vector2i{980,274},Vector2i{1094,309} };
	const Field field3{ Vector2i{980,328},Vector2i{1094,369} };
	const Field field4{ Vector2i{980,389},Vector2i{1094,421} };

	Menu menu;
		menu.setSize(Vector2f{ 1280,720 });
		menu.setTexture(&mainMenu);
		menu.loadField(field1, field2, field3, field4);
		menu.loadSound(&clickSound);

	Options options;
		options.setSize(Vector2f{ 1280,720 });
		options.setTexture(&optionsMenu);
		options.loadField(field1, field2, field3, field4);
		options.loadSound(&clickSound);

	Credits credits;
		credits.setSize(Vector2f{ 1280,720 });
		credits.setTexture(&creditsMenu);
		credits.loadField(field1, field2, field3, field4);
		credits.loadSound(&clickSound);

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

	while (app.isOpen()) {

		Event event;
		while (app.pollEvent(event)) {

			if (event.type == Event::Closed) app.close();

			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) app.close();

			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
				Vector2i mousePosition = Mouse::getPosition(app);

				if (menu.open) {
					if (menu.click(mousePosition) == Type::Options::Start);

					else if (menu.click(mousePosition) == Type::Options::Settings) {
						menu.open = false;
						options.open = true;
					}
					else if (menu.click(mousePosition) == Type::Options::Credits) {
						menu.open = false;
						credits.open = true;
					}

					else if (menu.click(mousePosition) == Type::Options::Exit) app.close();
				}


				if (options.open) {
					if (options.click(mousePosition) == Type::Options::FPS);

					else if (options.click(mousePosition) == Type::Options::Volume);

					else if (options.click(mousePosition) == Type::Options::Undo) {
						menu.open = true;
						options.open = false;
					}
				}

				if (credits.open) {

					if (credits.click(mousePosition) == Type::Options::Undo) {
						menu.open = true;
						credits.open = false;
					}
				}
			}

		}

		app.clear();
			if (menu.open)		app.draw(menu);
			if (options.open)	app.draw(options);
			if (credits.open)	app.draw(credits);
		app.display();
	}
	return 0;
}