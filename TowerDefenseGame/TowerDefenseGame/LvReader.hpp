#pragma once
#include <SFML\Audio.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "Type.hpp"
#include "Map.hpp"

using namespace sf;
using namespace std;

class LvReader {

	Map* map;

	Vector2i startPosition;

	int moveNumber;

	Type::Direct* direct;

public:

	LvReader(Map* map);

	void setFile(string file);

	Type::Direct* getDirect();

	int getMoveNumber();

	Vector2i getStartPosition();
};