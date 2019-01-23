#pragma once
#include <SFML\Audio.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

using namespace sf;

class RangeField : public CircleShape {

	bool on;

public:

	RangeField(Color color);

	void set(Vector2f position, int radius);

	void turnOn();

	void turnOff();

	bool isOn();
};