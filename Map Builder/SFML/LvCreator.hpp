#pragma once
#include <iostream>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <string.h>
#include <fstream>

using namespace sf;

class LvCreator
{
	RectangleShape background[144];
	RectangleShape *wsk = background;
	RectangleShape background2[2];
	RectangleShape lvelements[10];
	RectangleShape choiceelement;
	RectangleShape save;
	RectangleShape arrowstextures[2], arrowsmonster[2];
	RectangleShape lvtexture, monsters, starther;


	Texture texture[10], savetx, arrows, monstertx, leveltx[3],starthere;

	Font font;
	Text text,text2;

	std::fstream plik;
	std::string map,map1,map2,map3,map4,map5,map6,map7,map8,map9;

	bool savetrue = true;
	int nr_mon = 0;
	int nr_tx = 0;
	int nr_ln = 0;
	int start;

	enum Dir {
		Up,
		Down,
		Left,
		Right,
		NE,
		ES,
		SW,
		WN,
		NW,
		WS,
		SE,
		EN
	};

public:

	LvCreator();
	void loadScreen(RenderWindow*app);
	void choicedelement(RenderWindow*app);
	void change(RenderWindow*app);
	int check();
	bool check2();
	bool check3();
	bool check4();
	void saves(RenderWindow*app);
	std::string movement();
	void monster_add(RenderWindow*app);
	void texture_change(RenderWindow*app);
	~LvCreator();
};

