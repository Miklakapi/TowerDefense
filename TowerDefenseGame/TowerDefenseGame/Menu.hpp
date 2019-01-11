#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "Type.hpp"

using namespace sf;

struct Field {
	Field();
	Field(Vector2i left, Vector2i right);

	Vector2i leftPosition;
	Vector2i rightPosition;
};

class Menu :public RectangleShape{

	Field field1;
	Field field2;
	Field field3;
	Field field4;

public:

	bool open;

	//

	Menu();

	void loadField(Field field1, Field field2, Field field3, Field field4);

	Type::Options click(Vector2i mousePosition);

};

class Options {

};