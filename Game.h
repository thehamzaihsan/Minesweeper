#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib> 
#include <iostream> 
#include <string>
#include <time.h> 
#include "Tile.h"
#include "TILE_MAP.h"

const int WINDOW_HEIGTH = 640;
const int WINDOW_WIDTH = 640;
const int TILE_WIDTH = 40;
const int BOMB_NUMBER = 20;

struct Point {
	int x;
	int y;

	// Define comparison operators
	bool operator<(const Point& other) const {
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
	std::set <Point> SetRandomBombs();

private:
	Tile tile_array[WINDOW_HEIGTH / TILE_WIDTH][WINDOW_WIDTH / TILE_WIDTH];
	bool isExploded;
	std::set<Point> RandomNumbers;
	bool isWin;
};

Game::Game()
{
	window.create(sf::VideoMode(WINDOW_HEIGTH, WINDOW_WIDTH), "SFML works!", sf::Style::Close);
}


void Game::Start() {
	RandomNumbers = SetRandomBombs();
	isExploded = false;
	for (int i = 0; i < WINDOW_HEIGTH / TILE_WIDTH; i++)
	{
		for (int j = 0; j < WINDOW_WIDTH / TILE_WIDTH; j++)
		{
			tile_array[i][j].setFillColor(sf::Color::White);
			tile_array[i][j].setSize(sf::Vector2f(TILE_WIDTH - 1, TILE_WIDTH - 1));
			tile_array[i][j].setOrigin(sf::Vector2f(0, 0));
			tile_array[i][j].setPosition(sf::Vector2f(TILE_WIDTH * i, TILE_WIDTH * j));
			tile_array[i][j].setnumber(0);
			tile_array[i][j].sethidden_state(false);

			for (const auto& value : RandomNumbers) {
				if (value.x == i && value.y == j)
				{
					tile_array[i][j].setnumber(-1);
				}
			}


			if (i == 0 || j == 0 || i == (WINDOW_HEIGTH / TILE_WIDTH) - 1 || j == (WINDOW_WIDTH / TILE_WIDTH) - 1) {
				tile_array[i][j].setnumber(-2);
			}
		}
	}

	setNumberData();

	for (int i = 0; i < WINDOW_HEIGTH / TILE_WIDTH; i++)
	{
		for (int j = 0; j < WINDOW_WIDTH / TILE_WIDTH; j++)
		{


			tile_array[i][j].setTexturePath("./Sprites/TileUnknown.png");
			tile_array[i][j].setsprite();

			if (tile_array[i][j].getnumber() == -2)
			{
				tile_array[i][j].setFillColor(sf::Color::Cyan);
			}

			else
			{
				if (tile_array[i][j].getnumber() != 0)
				{
					tile_array[i][j].setInnerText(std::to_string(tile_array[i][j].getnumber()));
				}

			}




		}

	}


}

void Game::Update() {
	int i = event.mouseButton.x / 40;
	int j = event.mouseButton.y / 40;

	if (!isExploded)
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (i > 0 && j > 0 && i < WINDOW_HEIGTH / TILE_WIDTH - 1 && j < WINDOW_WIDTH / TILE_WIDTH - 1)
			{
				if (event.key.code == sf::Mouse::Left) {


					std::cout << i << "-" << j << std::endl;
					HideCell(i, j);

				}

				if (event.key.code == sf::Mouse::Right) {


					std::cout << i << "-" << j << std::endl;
					tile_array[i][j].setIsFlagged(true);

				}
				if (event.key.code == sf::Mouse::Middle) {


					std::cout << i << "-" << j << std::endl;
					tile_array[i][j].setIsFlagged(false);

				}


			}
		}
	}




	for (int i = 0; i < WINDOW_HEIGTH / TILE_WIDTH; i++)
	{
		for (int j = 0; j < WINDOW_WIDTH / TILE_WIDTH; j++)
		{
			if (tile_array[i][j].gethidden_state() == true && tile_array[i][j].getnumber() == 0)
			{
				tile_array[i][j].setFillColor(sf::Color::Black);

				HideCell(i, j);
				ClearSpace(i, j);
			}

			if (tile_array[i][j].gethidden_state() == true && tile_array[i][j].getnumber() == -1)
			{
				Explode();
				isExploded = true;
			}

			if (tile_array[i][j].gethidden_state() == true)
			{
				tile_array[i][j].setFillColor(sf::Color{ 198 , 198 , 198 , 100 });
			}
			else if (tile_array[i][j].getIsFlagged() == true)
			{
				tile_array[i][j].setFillColor(sf::Color::Green);
			}
			else if (tile_array[i][j].getIsFlagged() == false && tile_array[i][j].getnumber() >= 0) {
				tile_array[i][j].setFillColor(sf::Color::White);
			}




			//SPRITESSSSSS YESSSS
			if (tile_array[i][j].gethidden_state() == false)
			{
				tile_array[i][j].setTexturePath("./Sprites/TileUnknown.png");
			}
			if (tile_array[i][j].gethidden_state() == false && tile_array[i][j].getnumber() == -2)
			{
				tile_array[i][j].setTexturePath("./Sprites/TileBorder.png");
			}
			if (tile_array[i][j].getIsFlagged() == true ) {
				tile_array[i][j].setTexturePath("./Sprites/TileFlag.png");
			}
			if (tile_array[i][j].gethidden_state() == true && tile_array[i][j].getnumber() == 0) {
				tile_array[i][j].setTexturePath("./Sprites/TileEmpty.png");
			}
			if (isExploded == true && tile_array[i][j].getnumber() == -1) {
				tile_array[i][j].setTexturePath("./Sprites/TileExploded.png");
			}
			else if (tile_array[i][j].gethidden_state() == true && tile_array[i][j].getnumber() == 1) {
				tile_array[i][j].setTexturePath("./Sprites/Tile1.png");
			}
			else if (tile_array[i][j].gethidden_state() == true && tile_array[i][j].getnumber() == 2) {
				tile_array[i][j].setTexturePath("./Sprites/Tile2.png");
			}
			else if (tile_array[i][j].gethidden_state() == true && tile_array[i][j].getnumber() == 3) {
				tile_array[i][j].setTexturePath("./Sprites/Tile3.png");
			}
			else if (tile_array[i][j].gethidden_state() == true && tile_array[i][j].getnumber() == 4) {
				tile_array[i][j].setTexturePath("./Sprites/Tile4.png");
			}
			else if (tile_array[i][j].gethidden_state() == true && tile_array[i][j].getnumber() == 5) {
				tile_array[i][j].setTexturePath("./Sprites/Tile5.png");
			}
			else if (tile_array[i][j].gethidden_state() == true && tile_array[i][j].getnumber() == 6) {
				tile_array[i][j].setTexturePath("./Sprites/Tile6.png");
			}
			else if (tile_array[i][j].gethidden_state() == true && tile_array[i][j].getnumber() == 7) {
				tile_array[i][j].setTexturePath("./Sprites/Tile7.png");
			}
			else if (tile_array[i][j].gethidden_state() == true && tile_array[i][j].getnumber() == 8) {
				tile_array[i][j].setTexturePath("./Sprites/Tile8.png");
			}
		
			/*	else if (tile_array[i][j].gethidden_state() == true && tile_array[i][j].getnumber() == 0) {
					tile_array[i][j].setTexturePath("./Sprites/TileEmpty.png");
				}*/
			tile_array[i][j].setsprite();
		}
	}



}

void Game::Render() {
	for (int i = 0; i < WINDOW_HEIGTH / TILE_WIDTH; i++)
	{
		for (int j = 0; j < WINDOW_WIDTH / TILE_WIDTH; j++)
		{
			window.draw(tile_array[i][j]);


			if (tile_array[i][j].gethidden_state() == true)
			{

				if (i > 0 && j > 0 && i < WINDOW_HEIGTH / TILE_WIDTH && j < WINDOW_WIDTH / TILE_WIDTH)
				{
					window.draw(tile_array[i][j].getInnerText());
				}
			}

			window.draw(tile_array[i][j].getSprite());
		}
	}


}



void Game::ClearSpace(int i, int j) {




	if (tile_array[i + 1][j].getnumber() >= 0) {
		HideCell(i + 1, j);
	}
	if (tile_array[i][j + 1].getnumber() >= 0) {
		HideCell(i, j + 1);
	}
	if (tile_array[i - 1][j].getnumber() >= 0) {
		HideCell(i - 1, j);
	}
	if (tile_array[i][j - 1].getnumber() >= 0) {
		HideCell(i, j - 1);
	}
	if (tile_array[i + 1][j + 1].getnumber() >= 0) {
		HideCell(i + 1, j + 1);
	}
	if (tile_array[i - 1][j + 1].getnumber() >= 0) {
		HideCell(i - 1, j + 1);
	}
	if (tile_array[i - 1][j - 1].getnumber() >= 0) {
		HideCell(i - 1, j - 1);
	}
	if (tile_array[i + 1][j - 1].getnumber() >= 0) {
		HideCell(i + 1, j - 1);
	}



}

void Game::setNumberData() {
	for (int i = 0; i < WINDOW_HEIGTH / TILE_WIDTH - 1; i++)
	{
		for (int j = 0; j < WINDOW_WIDTH / TILE_WIDTH - 1; j++)
		{
			if (tile_array[i][j].getnumber() >= 0) {
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
	}

}
std::set <Point> Game::SetRandomBombs() {
	std::set<Point> uniquePoints;
	std::srand(std::time(0));  // Seed for random number generation

	while (uniquePoints.size() < BOMB_NUMBER) {
		Point p;
		p.x = std::rand() % (WINDOW_HEIGTH / TILE_WIDTH - 2) + 1; // Range: 1 to 15
		p.y = std::rand() % (WINDOW_WIDTH / TILE_WIDTH - 2) + 1; // Range: 1 to 15

		// Ensure the point is unique
		if (uniquePoints.find(p) == uniquePoints.end())
		{
			uniquePoints.insert(p);
		}
	}

	return uniquePoints;
}




void Game::Explode() {
	for (int i = 0; i < WINDOW_HEIGTH / TILE_WIDTH; i++)
	{
		for (int j = 0; j < WINDOW_WIDTH / TILE_WIDTH; j++)
		{


			if (tile_array[i][j].getnumber() == -1)
			{
				tile_array[i][j].setFillColor(sf::Color::Red);
				tile_array[i][j].sethidden_state(false);


			}



		}
	}





}

void Game::HideCell(int i, int j) {
	if (tile_array[i][j].getIsFlagged() == false)
	{
		tile_array[i][j].sethidden_state(true);
	}
}
