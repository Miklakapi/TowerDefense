#include <SFML\Audio.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "Type.hpp"
#include "TowerDefense.hpp"

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
	SoundBuffer menuMusicBuffer;
		menuMusicBuffer.loadFromFile("Sound/menu_v1.ogg");
	SoundBuffer gameMusicBuffer;
		gameMusicBuffer.loadFromFile("Sound/battle_v1.ogg");

	Sound clickSound;
		clickSound.setBuffer(clickBuffer);
		clickSound.setVolume(5);

	Sound menuMusic;
		menuMusic.setBuffer(menuMusicBuffer);
		menuMusic.setVolume(10);
		
	Sound gameMusic;
		gameMusic.setBuffer(gameMusicBuffer);
		gameMusic.setVolume(20);

	Sound sound[2] = { menuMusic, gameMusic };
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

	const Field field1{ Vector2i{974,215},Vector2i{1095,259} };
	const Field field2{ Vector2i{980,274},Vector2i{1094,309} };
	const Field field3{ Vector2i{980,328},Vector2i{1094,369} };
	const Field field4{ Vector2i{980,389},Vector2i{1094,421} };

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

	TowerDefense game;
		game.menu.setSize(Vector2f{ 1280,720 });
		game.menu.setTexture(&mainMenu);
		game.menu.loadField(field1, field2, field3, field4);
		game.menu.loadSound(&clickSound);

		game.options.setSize(Vector2f{ 1280,720 });
		game.options.setTexture(&optionsMenu);
		game.options.loadField(field1, field2, field3, field4);
		game.options.loadSound(&clickSound);

		game.credits.setSize(Vector2f{ 1280,720 });
		game.credits.setTexture(&creditsMenu);
		game.credits.loadField(field1, field2, field3, field4);
		game.credits.loadSound(&clickSound);

		game.setWindow(&app);
		game.setSound(sound);
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

	//Main loop
	while (app.isOpen()) {

		//Event loop
		Event event;
		while (app.pollEvent(event)) {

			if (event.type == Event::Closed) app.close();

			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
				//
			}

			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
				Vector2i mousePosition = Mouse::getPosition(app);
				game.click(mousePosition, Mouse::Left);
			}

			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Right) {
				Vector2i mousePosition = Mouse::getPosition(app);
				game.click(mousePosition, Mouse::Right);
			}

		}

		//Draw
		app.clear();
			game.drawAll();
		app.display();
	}
	return 0;
}