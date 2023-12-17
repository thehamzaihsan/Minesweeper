#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib> 
#include <iostream> 
#include <time.h> 
#include <string>
#include <set>
#include "Game.h"
#include "Tile.h"



class TileMap {
private:
public:
	void Update();
	void ClearSpace(int i, int j);
};
