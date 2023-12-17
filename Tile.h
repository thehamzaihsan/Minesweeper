#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib> 
#include <iostream> 
#include <string> 

#include <time.h> 

#include "Game.h"

class Tile :public sf::RectangleShape {
protected:
	bool ishidden;
	int number = 0;
	sf::Text text;
	sf::Font font;
	bool isFlagged;
	sf::Sprite sprite;
	sf::Texture texture;
public:
	Tile(bool h, int n) {
		ishidden = h;
		number = n;


	}
	Tile() {
		font.loadFromFile("./GeistMonoVF.ttf");
		text.setFont(font);
		text.setFillColor(sf::Color::Blue);
		text.setCharacterSize(28);
		text.setPosition(this->getPosition());
		text.setStyle(sf::Text::Bold);


	};

	void setsprite() {
	//	texture.loadFromFile("./Sprites/TileUnknown.png");
		texture.setSmooth(true);
		sprite.setTexture(texture);
		sprite.setPosition(this->getPosition());
		sprite.setScale(sf::Vector2f(2.5, 2.5));

	}

	void setnumber(int n) {
		number = n;
	}

	int getnumber() {
		return number;
	}

	void sethidden_state(bool h) {
		ishidden = h;
	}

	bool gethidden_state() {
		return ishidden;
	}

	void operator++ (int) {
		number++;
	}

	sf::Text getInnerText() {
		return text;
	}

	void setInnerText(std::string s) {
		text.setString(s);
		text.setPosition(this->getPosition());
	}

	bool getIsFlagged() {
		return isFlagged;
	}

	void setIsFlagged(bool b) {
		isFlagged = b;
	}

	void setTexturePath(std::string PATH) {
		texture.loadFromFile(PATH);
	}

	sf::Sprite getSprite() {
		return sprite;
	}
};