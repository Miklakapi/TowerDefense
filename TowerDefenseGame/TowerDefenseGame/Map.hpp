#pragma once
#include <SFML\Audio.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "Type.hpp"
#include "Square.hpp"

using namespace sf;

class Map {

	RenderWindow* window;

	Square* square;

public:

	Map(RenderWindow* window);

	void setTexture(Texture* texture);

	void loadIntRect(IntRect* rect);

	void drawAll();

	void setContent(Type::Content content);

};