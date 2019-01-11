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

Menu::Menu() : RectangleShape(){
	open = true;
}

void Menu::loadField(Field field1, Field field2, Field field3, Field field4) {
	this->field1 = field1;
	this->field2 = field2;
	this->field3 = field3;
	this->field4 = field4;
}

Type::Options Menu::click(Vector2i mousePosition) {

	if (mousePosition.x > field1.leftPosition.x && mousePosition.x < field1.rightPosition.x && mousePosition.y > field1.leftPosition.y && mousePosition.y < field1.rightPosition.y) {

		return Type::Options::Start;
	}

	else if (mousePosition.x > field2.leftPosition.x && mousePosition.x < field2.rightPosition.x && mousePosition.y > field2.leftPosition.y && mousePosition.y < field2.rightPosition.y) {

		return Type::Options::Settings;
	}

	else if (mousePosition.x > field3.leftPosition.x && mousePosition.x < field3.rightPosition.x && mousePosition.y > field3.leftPosition.y && mousePosition.y < field3.rightPosition.y) {

		return Type::Options::Credits;
	}

	else if (mousePosition.x > field4.leftPosition.x && mousePosition.x < field4.rightPosition.x && mousePosition.y > field4.leftPosition.y && mousePosition.y < field4.rightPosition.y) {

		return Type::Options::Exit;
	}

	else return Type::Options::Miss;
}