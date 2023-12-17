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
public:
    Tile(bool h, int n) {
        ishidden = h;
        number = n;


    }
    Tile() {
        std::cout << font.loadFromFile("./GeistMonoVF.ttf");
        text.setFont(font);
        text.setFillColor(sf::Color::Blue);
        text.setCharacterSize(28);
        text.setString('1');
        text.setPosition(this->getPosition());
        text.setStyle(sf::Text::Bold);
    };

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
};