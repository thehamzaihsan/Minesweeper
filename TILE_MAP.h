#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib> 
#include <iostream> 
#include <time.h> 
#include <set>
#include <string>
#include <vector>
#include "Game.h"
#include "Tile.h"


struct Point {
	int x;
	int y;

	// Define comparison operators
	bool operator<(const Point& other) const {
		return x < other.x || (x == other.x && y < other.y);
	}

	// Add other operators if needed
};

class TileMap {
private:
	Tile tile_array[WINDOW_HEIGTH / TILE_WIDTH][WINDOW_WIDTH / TILE_WIDTH];
	bool isExploded;
	std::set<Point> RandomNumbers;
public:
	TileMap() {
		RandomNumbers = SetRandomBombs();
		for (int row = 0; row < 16; row++)
		{
			for (int column = 0; column < 16; column++)
			{
				for (const auto& value : RandomNumbers) {
					if (value.x == row && value.y == column)
					{
						tile_array[row][column].setnumber(-1);
						tile_array[row][column].setFillColor(sf::Color::Red);
					}
				}
				tile_array[row][column].setGridPosition(row, column);
			}
		}

		for (int row = 0; row < 16; row++)
		{
			for (int column = 0; column < 16; column++)
			{
				setNumberData(row, column);
			}
		}
	}

	void setNumberData(int i, int j) {

		if (tile_array[i][j].getnumber() >= 0 && i <= 14 && j <=14 && i >= 1 && j >= 1 ) {
			if (tile_array[i + 1][j].getnumber() == -1) {
				tile_array[i][j]++;
			}
			if (tile_array[i][j + 1].getnumber() == -1) {
				tile_array[i][j]++;
			}
			if (tile_array[i - 1][j].getnumber() == -1) {
				tile_array[i][j]++;
			}
			if (tile_array[i][j - 1].getnumber() == -1) {
				tile_array[i][j]++;
			}
			if (tile_array[i + 1][j + 1].getnumber() == -1) {
				tile_array[i][j]++;
			}
			if (tile_array[i - 1][j + 1].getnumber() == -1) {
				tile_array[i][j]++;
			}
			if (tile_array[i - 1][j - 1].getnumber() == -1) {
				tile_array[i][j]++;
			}
			if (tile_array[i + 1][j - 1].getnumber() == -1) {
				tile_array[i][j]++;
			}
		}
	}

	std::set <Point>  SetRandomBombs() {
		std::set<Point> uniquePoints;
		std::srand(std::time(0));  // Seed for random number generation

		while (uniquePoints.size() < 20) {
			Point p;
			p.x = std::rand() % 14 + 1; // Range: 1 to 15
			p.y = std::rand() % 14 + 1; // Range: 1 to 15

			// Ensure the point is unique
			if (uniquePoints.find(p) == uniquePoints.end())
			{
				uniquePoints.insert(p);
			}
		}

		return uniquePoints;
	}

	void setcolor() {

	}

	void Click();
	void ClearSpace(int i , int j) {
		//if (tile_array[i + 1][j].getnumber() >= 0) {
		//	ShowCell(i + 1, j);
		//	//ClearSpace(i + 1, j);
		//}
		//if (tile_array[i][j + 1].getnumber() >= 0) {
		//	ShowCell(i, j + 1);
		//	//ClearSpace(i, j + 1);
		//}
		//if (tile_array[i - 1][j].getnumber() >= 0) {
		//	ShowCell(i - 1, j);
		//	//ClearSpace(i - 1, j);
		//}
		//if (tile_array[i][j - 1].getnumber() >= 0) {
		//	ShowCell(i, j - 1);
		//	//ClearSpace(i, j - 1);
		//}
		//if (tile_array[i + 1][j + 1].getnumber() >= 0) {
		//	ShowCell(i + 1, j + 1);
		//	//ClearSpace(i + 1, j + 1);
		//}
		//if (tile_array[i - 1][j + 1].getnumber() >= 0) {
		//	ShowCell(i - 1, j + 1);
		//	//ClearSpace(i - 1, j + 1);
		//}
		//if (tile_array[i - 1][j - 1].getnumber() >= 0) {
		//	ShowCell(i - 1, j - 1);
		//	//ClearSpace(i - 1, j - 1);
		//}
		//if (tile_array[i + 1][j - 1].getnumber() >= 0) {
		//	ShowCell(i + 1, j - 1);
		//	//ClearSpace(i + 1, j - 1);
		//}

	}
	void setIsExploded(bool b) {
		isExploded = b;
	}
	bool getIsExploded() {
		return isExploded;
	}
	Tile getMapElement(int i, int j) {
		return tile_array[i][j];
	}

	void DestroyCell() {

	}

	void ShowCell(int i, int j) {
		tile_array[i][j].sethidden_state(false);
		
	}

	void setFlagged(int i, int j, bool b) {
		tile_array[i][j].setFlagged(b);
	}

	void Update() {

		for (int row = 0; row < 16; row++)
		{
			for (int column = 0; column < 16; column++)
			{
				if (tile_array[row][column].gethidden_state() == false) {
					tile_array[row][column].setFillColor(sf::Color::Black);

					if (tile_array[row][column].getnumber() == 0)
					{
						ClearSpace(row, column);
					}
				}
			}
		}
	}

};

