#include <SFML\Audio.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "Type.hpp"
#include "Square.hpp"
#include "Map.hpp"

Map::Map(RenderWindow* window) {
	this->window = window;
	square = new Square[144];
	int i(0);
	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 16; x++) {
			(square + i)->setPosition(Vector2f(float(x * 80), float(y * 80)));
			(square + i)->setSize(Vector2f{ 80,80 });
			i++;
		}
	}
}

void Map::setTexture(Texture* texture) {
	for (int i = 0; i < 144; i++) {
		(square + i)->setTexture(texture);
	}
}

void Map::loadIntRect(IntRect* rect) {
	for (int i = 0; i < 144; i++) {
		(square + i)->loadIntRect(rect);
	}
}

void Map::drawAll() {
	for (int i = 0; i < 144; i++) {
		window->draw(*(square + i));
	}
}

void Map::setContent(Type::Content content) {
	for (int i = 0; i < 144; i++) {
		(square + i)->setContent(content);
	}
}

void Map::setContent(int nr, Type::Content content) {
	(square + nr)->setContent(content);
}