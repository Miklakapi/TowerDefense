#include <SFML\Audio.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "Menu.hpp"
#include "Type.hpp"

using namespace sf;

Field::Field() {};

Field::Field(Vector2i left, Vector2i right) {
	leftPosition = left;
	rightPosition = right;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

MenuPlan::MenuPlan() : RectangleShape() {};

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

Options::Options() : MenuPlan(){
	open = false;
}

Type::Options Options::click(Vector2i mousePosition, bool playSound) {

	if (mousePosition.x > field1.leftPosition.x && mousePosition.x < field1.rightPosition.x && mousePosition.y > field1.leftPosition.y && mousePosition.y < field1.rightPosition.y) {
		if (playSound)clickSound->play();
		return Type::Options::FPS;
	}

	else if (mousePosition.x > field2.leftPosition.x && mousePosition.x < field2.rightPosition.x && mousePosition.y > field2.leftPosition.y && mousePosition.y < field2.rightPosition.y) {
		if (playSound)clickSound->play();
		return Type::Options::Volume;
	}

	else if (mousePosition.x > field4.leftPosition.x && mousePosition.x < field4.rightPosition.x && mousePosition.y > field4.leftPosition.y && mousePosition.y < field4.rightPosition.y) {
		if (playSound)clickSound->play();
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