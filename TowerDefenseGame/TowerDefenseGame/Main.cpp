#include <SFML\Audio.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "Type.hpp"
#include "TowerDefense.hpp"

using namespace sf;
using namespace std;

int main() {
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
							//File
	string settingsFile = "settings.txt";
	string lv1File = "lv1.txt";
	string lv2File = "lv2.txt";
	string lv3File = "lv3.txt";
	string lvFile[3] = { lv1File, lv2File, lv3File };

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
							//Window Settings
	RenderWindow app{ VideoMode{1280,720,32},"TowerDefense",Style::Close };
		app.setFramerateLimit(60);

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
							//Fonts

	Font font;
		font.loadFromFile("Fonts/arial.ttf");

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
							//Textures

							//Menu
	Texture mainMenu;
		mainMenu.loadFromFile("Img/MenuMain.png");

							//Options
	Texture optionsMenu[4];
		optionsMenu[0].loadFromFile("Img/MenuOptions60on.png");
		optionsMenu[1].loadFromFile("Img/MenuOptions144on.png");
		optionsMenu[2].loadFromFile("Img/MenuOptions60off.png");
		optionsMenu[3].loadFromFile("Img/MenuOptions144off.png");

							//Credits
	Texture creditsMenu;
		creditsMenu.loadFromFile("Img/MenuCredits.png");
	
	Texture menuTextures[2] = { mainMenu,creditsMenu };

							//Square(Levels)
	Texture lv1;
		lv1.loadFromFile("Img/lv1.png");

	Texture lv2;
		lv2.loadFromFile("Img/lv2.png");

	Texture lv3;
		lv3.loadFromFile("Img/lv3.png");

							//Towers
	Texture tower1Texture, tower1fireTexture;
		tower1Texture.loadFromFile("Img/Tower1.png");
		tower1fireTexture.loadFromFile("Img/Tower1fire.png");

							//Monsters
	Texture monster1Texture; 
		monster1Texture.loadFromFile("Img/Bush.png");
	Texture monster2Texture;
		monster2Texture.loadFromFile("Img/Cactus.png");
	Texture monster3Texture;
		monster3Texture.loadFromFile("Img/FireDude.png");

							//Texture Arrays
	Texture lvTextures[3] = { lv1,lv2,lv3 };
	Texture towerTextures[2] = { tower1Texture, tower1fireTexture};
	Texture monsterTextures[3] = { monster1Texture, monster2Texture, monster3Texture };

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
							//Sounds

							//Click Sound
	SoundBuffer clickBuffer;
		clickBuffer.loadFromFile("Sound/click.ogg");

	Sound clickSound;
		clickSound.setBuffer(clickBuffer);
		clickSound.setVolume(5);

							//Menu Music
	SoundBuffer menuMusicBuffer;
		menuMusicBuffer.loadFromFile("Sound/menu.ogg");

	Sound menuMusic;
		menuMusic.setBuffer(menuMusicBuffer);
		menuMusic.setVolume(8);

							//Game Musics
	SoundBuffer game1MusicBuffer;
		game1MusicBuffer.loadFromFile("Sound/battle1.ogg");
	Sound game1Music;
		game1Music.setBuffer(game1MusicBuffer);
		game1Music.setVolume(20);

	SoundBuffer game2MusicBuffer;
		game2MusicBuffer.loadFromFile("Sound/battle2.ogg");
	Sound game2Music;
		game2Music.setBuffer(game2MusicBuffer);
		game2Music.setVolume(20);

	SoundBuffer game3MusicBuffer;
		game3MusicBuffer.loadFromFile("Sound/battle3.ogg");
	Sound game3Music;
		game3Music.setBuffer(game3MusicBuffer);
		game3Music.setVolume(20);

							//Shot sound
	SoundBuffer shotBuffer;
		shotBuffer.loadFromFile("Sound/shot.ogg");
	Sound shot;
		shot.setBuffer(shotBuffer);
		shot.setVolume(7);

							//Music Arrays
	Sound lvSounds[3] = { game1Music, game2Music, game3Music };

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
							//Field
	Field field1{ Vector2i{974,215},Vector2i{1095,259} };
	Field field2{ Vector2i{980,274},Vector2i{1094,309} };
	Field field3{ Vector2i{980,328},Vector2i{1094,369} };
	Field field4{ Vector2i{980,389},Vector2i{1094,421} };

	Field field[4] = { field1,field2,field3,field4 };

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
							//IntRect

							//Map Rect
	IntRect mapRect[9]{ IntRect{1,1,3,3}, IntRect{80,80,80,80}, IntRect{0,80,80,80}, IntRect{80,0,80,80},
		IntRect{0,160,80,80}, IntRect{0,0,80,80}, IntRect{160,0,80,80}, IntRect{80,160,80,80},IntRect{160,160,80,80} };
							
							//Monster Rect
	IntRect monstersRect[4]{ IntRect{0,0,100,100}, IntRect{100,0,100,100}, IntRect{0,100,100,100}, IntRect{100,100,100,100}, };


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
							//Tower Defense

	TowerDefense game(&app, 3);
		game.loadMenu(&mainMenu, &creditsMenu, optionsMenu, field, &clickSound, &menuMusic, settingsFile);
		game.loadMap(lvTextures, mapRect, lvSounds);
		game.loadLvReader(lvFile);
		game.loadRangeField();
		game.loadPointCounter(font);
		game.loadMonsters(monsterTextures, monstersRect);
		game.loadTowers(towerTextures, shot);


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


	//Main loop
	while (app.isOpen()) {
		

		//Event loop
		Event event;
		while (app.pollEvent(event)) {

			if (event.type == Event::Closed) app.close();

			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) game.resetGame();
			
			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
				Vector2i mousePosition = Mouse::getPosition(app);
				game.click(mousePosition, Mouse::Left);
			}

			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Right) {
				Vector2i mousePosition = Mouse::getPosition(app);
				game.click(mousePosition, Mouse::Right);
			}

			//Skip Level if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space) game.nextLV();

		}

		game.run();

		//Draw
		app.clear();
			game.drawAll();
		app.display();
	}
	return 0;
}