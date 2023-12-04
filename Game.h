#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib> 
#include <iostream> 
#include <time.h> 

#include "Tile.h"
#include "TILE_MAP.h"



class Game
{
public:
	sf::RenderWindow window; 
	sf::Event event;
	Game();
	void Start();
	void Update();
	void Render();
private:
	TileMap tile_map;
};

Game::Game()
{
	window.create(sf::VideoMode(WINDOW_HEIGTH, WINDOW_WIDTH), "SFML works!", sf::Style::Close);
}


void Game::Start() {
	
	tile_map.init();
}

void Game::Update() {
	
}

void Game::Render() {
	for (int i = 0; i < WINDOW_HEIGTH / TILE_WIDTH; i++)
	{
		for (int j = 0; j < WINDOW_WIDTH / TILE_WIDTH; j++)
		{
			window.draw(tile_map.getMapElement(i, j));
		}
	}
}
