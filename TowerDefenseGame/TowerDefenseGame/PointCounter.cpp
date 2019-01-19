#include <SFML\Audio.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "PointCounter.hpp"

using namespace sf;
using namespace std;

PointCounter::PointCounter(Font& font) {
	setFont(font);
	reset();
}

void PointCounter::setPoints(int points) {
	this->points = points;
	string i = to_string(points) + " pkt";
	setString(i);
}

int PointCounter::getPoints() {
	return points;
}

void PointCounter::reset() {
	setPoints(100);
	setLetterSpacing(3);
	setCharacterSize(30);
	setStyle(Text::Bold);
	setFillColor(Color::Red);
}