#pragma once
#include <SFML\Audio.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "Type.hpp"

using namespace sf;

class Square :public RectangleShape{

	IntRect* rect;

	Type::Content content;

public:

	Square();

	void loadIntRect(IntRect* rect);

	void setContent(Type::Content content);

	void reset();
};