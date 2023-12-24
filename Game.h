#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include <time.h>
#include "Tile.h"
#include <set>
#include "ScoreWindow.h"


//DONOT CHANGE TILE_WIDTH  it breaks everything and there is not time to debug.
const int WINDOW_HEIGTH = 640;
const int WINDOW_WIDTH = 640;
const int TILE_WIDTH = 40;
const int BOMB_NUMBER = 25;

struct Point
{
	int x;
	int y;

	// Define comparison operators
	bool operator<(const Point& other) const
	{
		return x < other.x || (x == other.x && y < other.y);
	}

	// Add other operators if needed
};

class Game
{
public:
	sf::RenderWindow window;
	sf::Event event;

	Game();
	void Start();
	void Update();
	void Render();
	void ClearSpace(int, int);
	void Explode();
	void setNumberData();
	void HideCell(int, int);
	std::set<Point> SetRandomBombs(int, int);
	void Checkwin();
	void setBombs();
private:
	bool FirstMove;
	Tile tile_array[WINDOW_HEIGTH / TILE_WIDTH][WINDOW_WIDTH / TILE_WIDTH];
	bool isExploded;
	std::set<Point> RandomNumbers;
	bool isWin;
	int removedBlocks;
	bool DEBUG;
	ScoreWindow scoreWindow;
};

