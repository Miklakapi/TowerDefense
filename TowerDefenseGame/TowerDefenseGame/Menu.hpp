#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

using namespace sf;

class Menu {

public:

	RectangleShape background;
	RectangleShape start;
	RectangleShape opcje;
	RectangleShape autorzy;
	RectangleShape wyjscie;

	Menu();

	void click(Vector2i mousePosition);

	void draw(RenderWindow* window);
};