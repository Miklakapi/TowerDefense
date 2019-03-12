#include "LvCreator.hpp"



LvCreator::LvCreator()
{
	int ii(0);
	for (int y = 0; y != 9; y++) {
		for (int x = 0; x != 16; x++) {
			(wsk + ii)->setSize(Vector2f(60, 60));
			(wsk + ii)->setFillColor(Color(40, 40, 40));
			(wsk + ii)->setOutlineColor(Color(0, 0, 0));
			(wsk + ii)->setOutlineThickness(1);
			(wsk + ii)->setPosition(Vector2f(x * 60, y * 60));
			ii++;
		}
	}

	background2[0].setFillColor(Color(70, 70, 70));
	background2[1].setFillColor(Color(70, 70, 70));
	background2[0].setSize(Vector2f(320, 720));
	background2[1].setSize(Vector2f(960, 180));
	background2[0].setPosition(Vector2f(960, 0));
	background2[1].setPosition(Vector2f(0, 540));

	for (int i = 0; i != 10; i++) {
		lvelements[i].setSize(Vector2f(60, 60));
		int j = i + 1;
		texture[i].loadFromFile("Img/" + std::to_string(j) + ".png");
		lvelements[i].setTexture(&texture[i]);
	}


	choiceelement.setSize(Vector2f(100, 100));
	choiceelement.setPosition(Vector2f(1070, 45));


	lvelements[0].setPosition(Vector2f(1000, 280));
	lvelements[1].setPosition(Vector2f(1090, 280));
	lvelements[2].setPosition(Vector2f(1180, 280));
	lvelements[3].setPosition(Vector2f(1000, 370));
	lvelements[4].setPosition(Vector2f(1090, 370));
	lvelements[5].setPosition(Vector2f(1180, 370));
	lvelements[6].setPosition(Vector2f(1000, 460));
	lvelements[7].setPosition(Vector2f(1090, 460));
	lvelements[8].setPosition(Vector2f(1180, 460));
	lvelements[9].setPosition(Vector2f(1090, 190));


	save.setSize(Vector2f(200, 100));
	savetx.loadFromFile("Img/SAVE.png");
	save.setTexture(&savetx);
	save.setPosition(Vector2f(1020, 580));


	arrows.loadFromFile("Img/arrow.png");
	arrowsmonster[0].setTexture(&arrows);
	arrowsmonster[1].setTexture(&arrows);
	arrowsmonster[1].setScale(1,1);
	arrowsmonster[1].setScale(-1,1);
	arrowsmonster[0].setPosition(Vector2f(10, 610));
	arrowsmonster[1].setPosition(Vector2f(230, 610));
	arrowsmonster[0].setSize(Vector2f(30, 80));
	arrowsmonster[1].setSize(Vector2f(30, 80));
	
	arrowstextures[0].setTexture(&arrows);
	arrowstextures[1].setTexture(&arrows);
	arrowstextures[1].setScale(1, 1);
	arrowstextures[1].setScale(-1, 1);
	arrowstextures[0].setPosition(Vector2f(720, 580));
	arrowstextures[1].setPosition(Vector2f(950, 580));
	arrowstextures[0].setSize(Vector2f(30, 100));
	arrowstextures[1].setSize(Vector2f(30, 100));

	leveltx[0].loadFromFile("Img/lv1.png");
	leveltx[1].loadFromFile("Img/lv2.png");
	leveltx[2].loadFromFile("Img/lv3.png");

	lvtexture.setSize(Vector2f(150, 150));
	lvtexture.setPosition(Vector2f(760, 555));
	

	font.loadFromFile("Fonts/IndieFlower.ttf");
	text.setFont(font);
	text.setPosition(Vector2f(60, 580));
	text.setCharacterSize(100);
	text2.setFont(font);
	text2.setPosition(Vector2f(970, 30));
	text2.setCharacterSize(30);
	text2.setString("Start");

	starther.setPosition(Vector2f(960, 30));
	starthere.loadFromFile("Img/start.png");
	starther.setSize(Vector2f(10, 480));
	starther.setTexture(&starthere);
	

}

void LvCreator::loadScreen(RenderWindow *app) {
	app->draw(background2[0]);
	app->draw(background2[1]);
	for (int i = 0; i != 144; i++) app->draw(*(wsk + i));
	for (int i = 0; i != 10; i++) app->draw(lvelements[i]);
	app->draw(choiceelement);
	app->draw(save);
	app->draw(arrowsmonster[1]);
	app->draw(arrowsmonster[0]);
	app->draw(arrowstextures[0]);
	app->draw(arrowstextures[1]);
	lvtexture.setTexture(&leveltx[nr_tx]);
	app->draw(lvtexture);
	text.setString(std::to_string(nr_mon));
	app->draw(text);
	app->draw(text2);
	app->draw(starther);

}

void LvCreator::choicedelement(RenderWindow*app) {
	if (Mouse::isButtonPressed(Mouse::Left)) {
		for (int i = 0; i != 10; i++) {
			if (lvelements[i].getGlobalBounds().contains(Mouse::getPosition(*app).x, Mouse::getPosition(*app).y)) {
				choiceelement.setTexture(lvelements[i].getTexture());
			}
		}
	}

}

void LvCreator::change(RenderWindow*app) {
	if (Mouse::isButtonPressed(Mouse::Left)) {
		for (int i = 0; i != 144; i++) {
			if ((wsk + i)->getGlobalBounds().contains(Mouse::getPosition(*app).x, Mouse::getPosition(*app).y)) {
				(wsk + i)->setTexture(choiceelement.getTexture());
				(wsk + i)->setFillColor(Color(255, 255, 255));
			}
		}
	}

}


int LvCreator::check() {
	if (check2()) {
		int a = 0;
		for (int i = 0; i != 144; i++) {
			if ((wsk + i)->getTexture() == &texture[0] ||
				(wsk + i)->getTexture() == &texture[1] ||
				(wsk + i)->getTexture() == &texture[2] ||
				(wsk + i)->getTexture() == &texture[3] ||
				(wsk + i)->getTexture() == &texture[4] ||
				(wsk + i)->getTexture() == &texture[5] ||
				(wsk + i)->getTexture() == &texture[6] ||
				(wsk + i)->getTexture() == &texture[7] ||
				(wsk + i)->getTexture() == &texture[8] ||
				(wsk + i)->getTexture() == &texture[9]) {
				a++;
			}
		}
		return a;
	}

}

bool LvCreator::check2() {
	if (check3())
	{
		int a = 0;
		for (int i = 0; i != 144; i++) {
			if ((wsk + i)->getTexture() == &texture[9]) a++;
		}
		if (a > 1) return false;
		else if (a == 0) return false;
		else return true;
	}
}

bool LvCreator::check3() {
	if (check4()) {
		int a = 0;
		for (int i = 0; i != 144; i++) {
			if ((wsk + i)->getTexture() == &texture[8]) a++;
		}
		if (a > 1) return false;
		else if (a == 0) return false;
		else return true;
	}
}
bool LvCreator::check4() {
	if ((wsk + 15)->getTexture() == &texture[9]) return true;
	else if ((wsk + 31)->getTexture() == &texture[9]) return true;
	else if ((wsk + 47)->getTexture() == &texture[9]) return true;
	else if ((wsk + 63)->getTexture() == &texture[9]) return true;
	else if ((wsk + 79)->getTexture() == &texture[9]) return true;
	else if ((wsk + 95)->getTexture() == &texture[9]) return true;
	else if ((wsk + 111)->getTexture() == &texture[9]) return true;
	else if ((wsk + 127)->getTexture() == &texture[9]) return true;
	else if ((wsk + 143)->getTexture() == &texture[9]) return true;
	else return false;
}

void LvCreator::saves(RenderWindow*app) {
	if (savetrue) {
		if (Mouse::isButtonPressed(Mouse::Left)) {
			if (save.getGlobalBounds().contains(Mouse::getPosition(*app).x, Mouse::getPosition(*app).y)) {

				if (check() >= 143) {

					for (int i = 0; i != 144; i++) {

						if ((wsk + i)->getTexture() == &texture[0]) {
							map = map + "T";
						}
						else if ((wsk + i)->getTexture() == &texture[1]) {
							map = map + "-";
						}
						else if ((wsk + i)->getTexture() == &texture[2]) {
							map = map + "t";
						}
						else if ((wsk + i)->getTexture() == &texture[3]) {
							map = map + "|";
						}
						else if ((wsk + i)->getTexture() == &texture[4]) {
							map = map + ".";
						}
						else if ((wsk + i)->getTexture() == &texture[5]) {
							map = map + "#";
						}
						else if ((wsk + i)->getTexture() == &texture[6]) {
							map = map + "L";
						}
						else if ((wsk + i)->getTexture() == &texture[7]) {
							map = map + "l";
						}
						else if ((wsk + i)->getTexture() == &texture[8]) {
							map = map + "B";
						}
						else if ((wsk + i)->getTexture() == &texture[9]) {
							map = map + "S";
						}
					}
					savetrue = false;
					for (int i = 0; i != 144; i++) {
						if (i < 16 && i > -1) {
							map1 = map1 + map[i];
						}
						else if (i > 15 && i < 32) {
							map2 = map2 + map[i];
						}
						else if (i > 31 && i < 16 * 3) {
							map3 = map3 + map[i];
						}
						else if (i > (16 * 3) - 1 && i < 16 * 4) {
							map4 = map4 + map[i];
						}
						else if (i > (16 * 4) - 1 && i < 16 * 5) {
							map5 = map5 + map[i];
						}
						else if (i > (16 * 5) - 1 && i < 16 * 6) {
							map6 = map6 + map[i];
						}
						else if (i > (16 * 6) - 1 && i < 16 * 7) {
							map7 = map7 + map[i];
						}
						else if (i > (16 * 7) - 1 && i < 16 * 8) {
							map8 = map8 + map[i];
						}
						else if (i > (16 * 8) - 1 && i < 16 * 9) {
							map9 = map9 + map[i];
						}
						if (map[i] != '#' && map[i] != '.') { nr_ln++; }
						if (map[i] == 'S') start = i;
					}
					bool first_curve = true;
					plik.open(movement(), std::ios::out);
					plik << map1 << std::endl;
					plik << map2 << std::endl;
					plik << map3 << std::endl;
					plik << map4 << std::endl;
					plik << map5 << std::endl;
					plik << map6 << std::endl;
					plik << map7 << std::endl;
					plik << map8 << std::endl;
					plik << map9 << std::endl;
					plik << nr_ln << std::endl;
					Dir dir;
					int pos = start;
					for (int i = 0; i != nr_ln; i++) {
						if (first_curve) {
							plik << "Left" << std::endl;
							first_curve = false;
						}
						if (map[pos] == 'S') {
							plik << "Left" << std::endl;
							dir = Dir::Left;
						}
						else if (map[pos] == '-') {
							if (dir == Dir::Left) {
								plik << "Left" << std::endl;
							}
							else if (dir == Dir::Right) {
								plik << "Right" << std::endl;
							}
						}
						else if (map[pos] == '|') {
							if (dir == Dir::Up) {
								plik << "Top" << std::endl;
							}
							else if (dir == Dir::Down) {
								plik << "Bottom" << std::endl;
							}
						}
						else if (map[pos] == 'L') {
							if (dir == Dir::Left) {
								plik << "EN" << std::endl;
								dir = Dir::Up;
							}
							else if (dir == Dir::Down) {
								plik << "NE" << std::endl;
								dir = Dir::Right;
							}
						}
						else if (map[pos] == 'l') {
							if (dir == Dir::Right) {
								plik << "WN" << std::endl;
								dir = Dir::Up;
							}
							else if (dir == Dir::Down) {
								plik << "NW" << std::endl;
								dir = Dir::Left;
							}
						}
						else if (map[pos] == 'T') {
							if (dir == Dir::Left) {
								plik << "ES" << std::endl;
								dir = Dir::Down;
							}
							else if (dir == Dir::Up) {
								plik << "SE" << std::endl;
								dir = Dir::Right;
							}
						}
						else if (map[pos] == 't') {
							if (dir == Dir::Right) {
								plik << "WS" << std::endl;
								dir = Dir::Down;
							}
							else if (dir == Dir::Up) {
								plik << "SW" << std::endl;
								dir = Dir::Left;
							}
						}
						if (dir == Dir::Left) {
							pos -= 1;
						}
						else if (dir == Dir::Right) {
							pos += 1;
						}
						else if (dir == Dir::Up) {
							pos -= 16;
						}
						else if (dir == Dir::Down) {
							pos += 16;
						}

					
					
					}
					
					plik << nr_mon << std::endl;
					plik.close();
					exit(0);
				}
			}
		}
	}
}

void LvCreator::monster_add(RenderWindow*app) {

		if (arrowsmonster[1].getGlobalBounds().contains(Mouse::getPosition(*app).x, Mouse::getPosition(*app).y)) {
			nr_mon += 1;
		}
		else if (arrowsmonster[0].getGlobalBounds().contains(Mouse::getPosition(*app).x, Mouse::getPosition(*app).y)) {
			nr_mon -= 1;
		}
		
	if (nr_mon < 0)   nr_mon = 100;
	if (nr_mon > 100) nr_mon = 0;
	
}

void LvCreator::texture_change(RenderWindow*app) {
	if (arrowstextures[1].getGlobalBounds().contains(Mouse::getPosition(*app).x, Mouse::getPosition(*app).y)) {
		nr_tx += 1;
	}
	else if (arrowstextures[0].getGlobalBounds().contains(Mouse::getPosition(*app).x, Mouse::getPosition(*app).y)) {
		nr_tx -= 1;
	}
	if (nr_tx < 0)   nr_tx = 2;
	if (nr_tx > 2) nr_tx = 0;
}

std::string LvCreator::movement() {
	if (lvtexture.getTexture() == &leveltx[0]) return "lv1.txt";
	else if (lvtexture.getTexture() == &leveltx[1]) return "lv2.txt";
	else if (lvtexture.getTexture() == &leveltx[2]) return "lv3.txt";

}

LvCreator::~LvCreator()
{
}
