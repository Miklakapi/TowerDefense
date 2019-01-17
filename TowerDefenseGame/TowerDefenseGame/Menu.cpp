#include <SFML\Audio.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <fstream>
#include "Menu.hpp"
#include "Type.hpp"

using namespace sf;
using namespace std;

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

Field::Field() {};

Field::Field(Vector2i left, Vector2i right) {
	leftPosition = left;
	rightPosition = right;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

MenuPlan::MenuPlan() : RectangleShape() {
	setSize(Vector2f{ 1280,720 });
}

void MenuPlan::loadField(Field field1, Field field2, Field field3, Field field4) {
	this->field1 = field1;
	this->field2 = field2;
	this->field3 = field3;
	this->field4 = field4;
}

void MenuPlan::loadSound(Sound* clickSound) {
	this->clickSound = clickSound;
}

Type::Options MenuPlan::click(Vector2i mousePosition, bool playSound) {
	return Type::Options::Miss;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

Menu::Menu() : MenuPlan(){
	open = true;
}

Type::Options Menu::click(Vector2i mousePosition, bool playSound) {

	if (mousePosition.x > field1.leftPosition.x && mousePosition.x < field1.rightPosition.x && mousePosition.y > field1.leftPosition.y && mousePosition.y < field1.rightPosition.y) {
		if (playSound)clickSound->play();
		return Type::Options::Start;
	}

	else if (mousePosition.x > field2.leftPosition.x && mousePosition.x < field2.rightPosition.x && mousePosition.y > field2.leftPosition.y && mousePosition.y < field2.rightPosition.y) {
		if (playSound)clickSound->play();
		return Type::Options::Settings;
	}

	else if (mousePosition.x > field3.leftPosition.x && mousePosition.x < field3.rightPosition.x && mousePosition.y > field3.leftPosition.y && mousePosition.y < field3.rightPosition.y) {
		if (playSound)clickSound->play();
		return Type::Options::Credits;
	}

	else if (mousePosition.x > field4.leftPosition.x && mousePosition.x < field4.rightPosition.x && mousePosition.y > field4.leftPosition.y && mousePosition.y < field4.rightPosition.y) {
		if (playSound)clickSound->play();
		return Type::Options::Exit;
	}

	else return Type::Options::Miss;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

Options::Options(RenderWindow* window, string file) : MenuPlan(){
	open = false;
	this->window = window;

	this->file = file;
	settings = 0;

	fstream settingsF;
	settingsF.open(file, ios::in);

	if (!settingsF.is_open()) {
		settingsF.open(file, ios::out);
		settingsF << "FPS: 60\n";
		settingsF << "Sound: ON";
		settings = 0;
		settingsF.close();
		window->setFramerateLimit(60);
	}
	else {
		string line;
		getline(settingsF, line);
		if (line == "FPS: 60") {
			settings = 0;
			window->setFramerateLimit(60);
		}
		else if (line == "FPS: 144") {
			settings = 1;
			window->setFramerateLimit(144);
		}
		else {
			settingsF.close();
			settingsF.open(file, ios::out);
			settingsF << "FPS: 60\n";
			settingsF << "Sound: ON";
			settingsF.close();
			settings = 0;
			window->setFramerateLimit(60);
			return;
		}
		getline(settingsF, line);
		if (line == "Sound: ON")settings += 0;
		else if (line == "Sound: OFF")settings += 2;
		else {
			settingsF.close();
			settingsF.open(file, ios::out);
			settingsF << "FPS: 60\n";
			settingsF << "Sound: ON";
			settingsF.close();
			settings = 0;
			return;
		}
	}
}

void Options::loadTextures(Texture* texture) {
	this->texture = texture;
	setTexture((texture + settings));
}

Type::Options Options::click(Vector2i mousePosition, bool playSound) {

	if (mousePosition.x > field1.leftPosition.x && mousePosition.x < field1.rightPosition.x && mousePosition.y > field1.leftPosition.y && mousePosition.y < field1.rightPosition.y) {
		if (playSound)clickSound->play();
		if (settings == 0 || settings == 2) {
			window->setFramerateLimit(144);
			settings += 1;
		}
		else if (settings == 1 || settings == 3) {
			window->setFramerateLimit(60);
			settings -= 1;
		}
		setTexture((texture + settings));
		return Type::Options::FPS;
	}

	else if (mousePosition.x > field2.leftPosition.x && mousePosition.x < field2.rightPosition.x && mousePosition.y > field2.leftPosition.y && mousePosition.y < field2.rightPosition.y) {
		if (playSound)clickSound->play();
		if (settings == 0 || settings == 1) {
			settings += 2;
		}
		else if (settings == 2 || settings == 3) {
			settings -= 2;
		}
		setTexture((texture + settings));
		return Type::Options::Volume;
	}

	else if (mousePosition.x > field4.leftPosition.x && mousePosition.x < field4.rightPosition.x && mousePosition.y > field4.leftPosition.y && mousePosition.y < field4.rightPosition.y) {
		if (playSound)clickSound->play();
		fstream settingsF;
		settingsF.open(file, ios::out);
		switch (settings) {
		case 0:
			settingsF << "FPS: 60\n";
			settingsF << "Sound: ON";
			break;
		case 1:
			settingsF << "FPS: 144\n";
			settingsF << "Sound: ON";
			break;
		case 2:
			settingsF << "FPS: 60\n";
			settingsF << "Sound: OFF";
			break;
		case 3:
			settingsF << "FPS: 144\n";
			settingsF << "Sound: OFF";
			break;
		}
		settingsF.close();
		return Type::Options::Undo;
	}

	else return Type::Options::Miss;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

Credits::Credits() : MenuPlan(){
	open = false;
}

Type::Options Credits::click(Vector2i mousePosition, bool playSound) {

	if (mousePosition.x > field4.leftPosition.x && mousePosition.x < field4.rightPosition.x && mousePosition.y > field4.leftPosition.y && mousePosition.y < field4.rightPosition.y) {
		if (playSound)clickSound->play();
		return Type::Options::Undo;
	}

	else return Type::Options::Miss;
}