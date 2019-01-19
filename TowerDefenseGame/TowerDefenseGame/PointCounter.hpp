#pragma once
#include <SFML\Audio.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

using namespace sf;

class PointCounter : public Text{

	int points;

public:

	PointCounter(Font& font);

	void setPoints(int points);

	int getPoints();

	void reset();
};