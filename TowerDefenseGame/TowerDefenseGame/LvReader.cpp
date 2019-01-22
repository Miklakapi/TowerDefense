#include <SFML\Audio.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <fstream>
#include "Type.hpp"
#include "Map.hpp"
#include "LvReader.hpp"

using namespace sf;
using namespace std;

LvReader::LvReader(Map* map) {
	this->map = map;
}

void LvReader::setFile(string file) {

	fstream stream;
	stream.open(file, ios::in);
	if (!stream.is_open()) {
		exit(0);
	}
	int i = 0;
	string line;
	for (int y = 0; y < 9; y++) {
		getline(stream, line);
		for (int x = 0; x < 16; x++) {
			Type::Content content;
			switch (line.at(x)) {
			case '#':
				content = Type::Content::Grass;
				break;
			case '.':
				content = Type::Content::Rock;
				break;
			case '-':
				content = Type::Content::RoadEW;
				break;
			case '|':
				content = Type::Content::RoadNS;
				break;
			case 'L':
				content = Type::Content::RoadNE;
				break;
			case 'l':
				content = Type::Content::RoadWN;
				break;
			case 'T':
				content = Type::Content::RoadES;
				break;
			case 't':
				content = Type::Content::RoadSW;
				break;
			case 'S':
				content = Type::Content::RoadEW;
				startPosition = Vector2f{ float((((x + 1) * 80) + 40)),float(((y * 80) + 40)) };
				break;
			default:
				system("pause");
				break;
			}
			map->setContent(i,content);
			i++;
		}
	}
	getline(stream, line);
	moveNumber = stoi(line);
	direct = new Type::Direct [moveNumber];
	for (int a = 0; a < moveNumber; a++) {
		getline(stream, line);
		if (line == "Right") *(direct + a) = Type::Direct::Right;
		else if (line == "Bottom") *(direct + a) = Type::Direct::Bottom;
		else if (line == "Top") *(direct + a) = Type::Direct::Top;
		else if (line == "Left")*(direct + a) = Type::Direct::Left;
		else if (line == "EN") *(direct + a) = Type::Direct::EN;
		else if (line == "NE") *(direct + a) = Type::Direct::NE;
		else if (line == "ES") *(direct + a) = Type::Direct::ES;
		else if (line == "SE") *(direct + a) = Type::Direct::SE;
		else if (line == "SW") *(direct + a) = Type::Direct::SW;
		else if (line == "WS") *(direct + a) = Type::Direct::WS;
		else if (line == "NW") *(direct + a) = Type::Direct::NW;
		else if (line == "WN") *(direct + a) = Type::Direct::WN;
	}
	getline(stream, line);
	mobNumber = stoi(line);

	stream.close();
}

Type::Direct* LvReader::getDirect() {
	return direct;
}

int LvReader::getMoveNumber() {
	return moveNumber;
}

int LvReader::getMobNumber() {
	return mobNumber;
}

Vector2f LvReader::getStartPosition() {
	return startPosition;
}