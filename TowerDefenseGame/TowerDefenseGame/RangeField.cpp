#include <SFML\Audio.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "RangeField.hpp"

using namespace sf;

RangeField::RangeField(Color color) {
	setFillColor(color);
}

void RangeField::set(Vector2f position, int radius) {
	setPosition(position);
	setRadius(float(radius));
	setOrigin(Vector2f{ float(radius),float(radius) });
}

void RangeField::turnOn() {
	on = true;
}

void RangeField::turnOff() {
	on = false;
}

bool RangeField::isOn() {
	if (on) return true;
	else return false;
}