#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib> 
#include <iostream> 
#include <time.h> 

#include "Game.h"

class Tile :public sf::RectangleShape {
protected:
    bool ishidden;
    int number = 0;
public:
    Tile(bool h, int n) {
        ishidden = h;
        number = n;
    }
    Tile() {};

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
};
