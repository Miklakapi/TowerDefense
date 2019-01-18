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

	Texture* texture;

public:

	Map(RenderWindow* window, Texture* texture, IntRect* rect);

	void drawAll();

	void setContent(Type::Content content);

	void setContent(int nr, Type::Content content);

	void setLv(int lv);

	Type::Content getElement(int nr);

	~Map();
};