#include <SFML\Audio.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <fstream>
#include "Type.hpp"
#include "Map.hpp"
#include "LvReader.hpp"

using namespace std;
using namespace sf;

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
			switch (line.at(i)) {
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
				startPosition = Vector2i{ ((x * 80) + 40),((y * 80) + 40) };
				break;
			}
			(map + i)->setContent(content);
			i++;
		}
	}
	getline(stream, line);
	moveNumber = stoi(line);
	direct = new Type::Direct[moveNumber];
	for (int a = 0; a < moveNumber; a++) {
		getline(stream, line);
		if (line == "Right") direct[i] = Type::Direct::Right;
		else if (line == "Bottom") direct[i] = Type::Direct::Bottom;
		else if (line == "Top") direct[i] = Type::Direct::Top;
		else if (line == "Left") direct[i] = Type::Direct::Left;
		else if (line == "EN") direct[i] = Type::Direct::EN;
		else if (line == "NE") direct[i] = Type::Direct::NE;
		else if (line == "ES") direct[i] = Type::Direct::ES;
		else if (line == "SE") direct[i] = Type::Direct::SE;
		else if (line == "SW") direct[i] = Type::Direct::SW;
		else if (line == "WS") direct[i] = Type::Direct::WS;
		else if (line == "NW") direct[i] = Type::Direct::NW;
		else if (line == "WN") direct[i] = Type::Direct::WN;
	}
	stream.close();
}

Type::Direct* LvReader::getDirect() {
	return direct;
}

int LvReader::getMoveNumber() {
	return moveNumber;
}

Vector2i LvReader::getStartPosition() {
	return startPosition;
}