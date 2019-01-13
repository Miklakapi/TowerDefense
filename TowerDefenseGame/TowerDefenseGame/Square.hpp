#pragma once
#include <SFML\Audio.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "Type.hpp"

using namespace sf;

class Square :public RectangleShape{

	

	Type::Content content;

public:

	static IntRect* rect;

	Square();

	void loadIntRect(IntRect* rect);

	void setContent(Type::Content content);

	void reset();
};