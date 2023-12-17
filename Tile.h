#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib> 
#include <iostream> 
#include <string> 

#include <time.h> 

#include "Game.h"


const int WINDOW_HEIGTH = 640;
const int WINDOW_WIDTH = 640;
const int TILE_WIDTH = 40;
const int BOMB_NUMBER = 20;


class Tile :public sf::RectangleShape {
protected:
	bool ishidden;
	int number = 0;
	sf::Text text;
	sf::Font font;
	bool isFlagged;
	sf::Texture texture;
	sf::Sprite sprite;

public:
	Tile() {
		font.loadFromFile("./GeistMonoVF.ttf");
		text.setFont(font);
		text.setFillColor(sf::Color::Blue);
		text.setCharacterSize(35);
		text.setString('1');
		text.setOrigin(sf::Vector2f(text.getPosition().x / 2, text.getPosition().y / 2));
		text.setPosition(sf::Vector2f(this->getPosition().x, this->getPosition().y / 2));
		text.setStyle(sf::Text::Bold);
		isFlagged = false;

		this->setFillColor(sf::Color::White);
		this->setSize(sf::Vector2f(TILE_WIDTH - 1, TILE_WIDTH - 1));
		this->setOrigin(sf::Vector2f(0, 0));
		ishidden = true;
		number = 0;
	}


	void setGridPosition(int i, int j) {
		this->setPosition(sf::Vector2f(TILE_WIDTH * i, TILE_WIDTH * j));
	}

	void setnumber(int n) {
		number = n;
	}
	void setSprites() {

		//if (ishidden == false) {
			//texture.loadFromFile("./Sprites/TileUnknown.png");
		//}
		//else if (ishidden == true && number >= 0) {
		//	texture.loadFromFile("./Sprites/TileEmpty.png");
		//}
		//else if (ishidden == true && number == -1)
		//{
		//	texture.loadFromFile("./Sprites/TileExploded.png");
		//}


		texture.setSmooth(true);
		sprite.setTexture(texture);
		sprite.setPosition(this->getPosition());
		sprite.setScale(sf::Vector2f(2.5, 2.5));

	}

	sf::Sprite getSprite() {
		return sprite;
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
	void setFlagged(bool b) {
		isFlagged = b;
	}

	bool getFlaggedStatus() {
		return isFlagged;
	}

	void const debug() {
		std::cout << "Number: " << number << std::endl;
		std::cout << "Is Hidden: " << ishidden << std::endl;
		std::cout << "Is Flagged: " << isFlagged << std::endl;
		std::cout << std::endl;
	}
};
