#include <SFML\Audio.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Type.hpp"
#include "TowerDefense.hpp"
#include "Monsters.hpp"

using namespace sf;
using namespace std;

int main() {
	string file = "settings.txt";
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
							//Window Settings
	RenderWindow app{ VideoMode{1280,720,},"TowerDefense",Style::Close };
		app.setFramerateLimit(60);

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
							//Textures
	Texture mainMenu;
		mainMenu.loadFromFile("Img/MenuMain.png");
	Texture optionsMenu[4];
		optionsMenu[0].loadFromFile("Img/MenuOptions60on.png");
		optionsMenu[1].loadFromFile("Img/MenuOptions144on.png");
		optionsMenu[2].loadFromFile("Img/MenuOptions60off.png");
		optionsMenu[3].loadFromFile("Img/MenuOptions144off.png");
	Texture creditsMenu;
		creditsMenu.loadFromFile("Img/MenuCredits.png");
	//
	Texture lv1;
		lv1.loadFromFile("Img/lv1.png");
	Texture lv2;
		lv2.loadFromFile("Img/lv2.png");
	Texture lv3;
		lv3.loadFromFile("Img/lv3.png");
	//

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
							//Sounds
	SoundBuffer clickBuffer;
		clickBuffer.loadFromFile("Sound/click.ogg");

	SoundBuffer menuMusicBuffer;
		menuMusicBuffer.loadFromFile("Sound/menu.ogg");

	SoundBuffer game1MusicBuffer;
		game1MusicBuffer.loadFromFile("Sound/battle1.ogg");
	SoundBuffer game2MusicBuffer;
		game2MusicBuffer.loadFromFile("Sound/battle2.ogg");
	SoundBuffer game3MusicBuffer;
		game3MusicBuffer.loadFromFile("Sound/battle3.ogg");

	Sound clickSound;
		clickSound.setBuffer(clickBuffer);
		clickSound.setVolume(5);

	Sound menuMusic;
		menuMusic.setBuffer(menuMusicBuffer);
		menuMusic.setVolume(10);
		
	Sound game1Music;
		game1Music.setBuffer(game1MusicBuffer);
		game1Music.setVolume(20);
	Sound game2Music;
		game2Music.setBuffer(game2MusicBuffer);
		game2Music.setVolume(20);
	Sound game3Music;
		game3Music.setBuffer(game3MusicBuffer);
		game3Music.setVolume(20);

	Sound sounds[4] = { menuMusic, game1Music, game2Music, game3Music };

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
							//Field
	const Field field1{ Vector2i{974,215},Vector2i{1095,259} };
	const Field field2{ Vector2i{980,274},Vector2i{1094,309} };
	const Field field3{ Vector2i{980,328},Vector2i{1094,369} };
	const Field field4{ Vector2i{980,389},Vector2i{1094,421} };

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
							//IntRect
	IntRect mapRect[8]{ IntRect{1,1,3,3}, IntRect{80,80,80,80}, IntRect{0,80,80,80}, IntRect{80,0,80,80},
		IntRect{0,160,80,80}, IntRect{0,0,80,80}, IntRect{160,0,80,80}, IntRect{80,160,80,80}, };

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
							//Game
	TowerDefense game(&app,file);
		game.menu.setSize(Vector2f{ 1280,720 });
		game.menu.setTexture(&mainMenu);
		game.menu.loadField(field1, field2, field3, field4);
		game.menu.loadSound(&clickSound);

		game.options.setSize(Vector2f{ 1280,720 });
		game.options.loadField(field1, field2, field3, field4);
		game.options.loadSound(&clickSound);
		game.options.loadTextures(optionsMenu);
		

		game.credits.setSize(Vector2f{ 1280,720 });
		game.credits.setTexture(&creditsMenu);
		game.credits.loadField(field1, field2, field3, field4);
		game.credits.loadSound(&clickSound);

		game.setSound(sounds);

		game.map.loadIntRect(mapRect);
		game.map.setTexture(&lv1);

		game.map.setContent(0, Type::Content::RoadEW);
		game.map.setContent(1, Type::Content::RoadSW);
		game.map.setContent(2, Type::Content::Rock);
		game.map.setContent(3, Type::Content::RoadES);
		game.map.setContent(4, Type::Content::RoadEW);
		game.map.setContent(5, Type::Content::RoadEW);
		game.map.setContent(17, Type::Content::RoadNE);
		game.map.setContent(18, Type::Content::RoadEW);
		game.map.setContent(19, Type::Content::RoadWN);


		Texture texturee; texturee.loadFromFile("Img/FireDude.png");
		IntRect rectt[4]{ IntRect{0,0,100,100}, IntRect{100,0,100,100}, IntRect{0,100,100,100}, IntRect{100,100,100,100}, };
		Type::Direct direct[]{ Type::Direct::Right,Type::Direct::Right,Type::Direct::WS,Type::Direct::NE,Type::Direct::Right,Type::Direct::WN,Type::Direct::SE,
		Type::Direct::Right,Type::Direct::Right };

		

		game.fireDude.setTexture(&texturee);
		game.fireDude.setSize(Vector2f{ 80,80 });
		game.fireDude.loadIntRect(rectt);
		game.fireDude.setMoveNumber(9);
		game.fireDude.setMob(Type::Mob::FireDude);
		game.fireDude.setRoad(direct);
		game.fireDude.setOrigin(Vector2f{ 40,40 });
		game.fireDude.setPosition(Vector2f{ -40,40 });
		game.fireDude.reset();
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

		game.run();

		//Draw
		app.clear();
			game.drawAll();
		app.display();
	}
	return 0;
}