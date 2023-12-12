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
	tile_map.Update();

	if (tile_map.getIsExploded() == false)
	{
		bool click_lock = false;
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && click_lock == false) {

				int i = event.mouseButton.x / 40;
				int j = event.mouseButton.y / 40;

				std::cout << i << "-" << j << std::endl;
				tile_map.HideCell(i, j);
				click_lock = true;
			}
		}
		if (event.type == sf::Event::MouseButtonReleased)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && click_lock == false) {
				click_lock = false;
			}
		}

		std::cout << tile_map.getMapElement(10, 0).getInnerText().getPosition().x;
	}

		
			
			

}

void Game::Render() {
	for (int i = 0; i < WINDOW_HEIGTH / TILE_WIDTH; i++)
	{
		for (int j = 0; j < WINDOW_WIDTH / TILE_WIDTH; j++)
		{
			window.draw(tile_map.getMapElement(i, j));

			if (tile_map.getMapElement(i , j).gethidden_state() == true)
			{
				window.draw(tile_map.getMapElement(i, j).getInnerText());
			}
		}
	}


}


void TileMap::Update() {
	
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
		}
	}


}


void TileMap::ClearSpace(int i, int j) {
	
	
	

		if (tile_array[i + 1][j].getnumber() >= 0) {
			HideCell(i + 1, j);
			//ClearSpace(i + 1, j);
		}
		if (tile_array[i][j + 1].getnumber() >= 0) {
			HideCell(i, j + 1);
			//ClearSpace(i, j + 1);
		}
		if (tile_array[i - 1][j].getnumber() >= 0) {
			HideCell(i - 1, j);
			//ClearSpace(i - 1, j);
		}
		if (tile_array[i][j - 1].getnumber() >= 0) {
			HideCell(i, j - 1);
			//ClearSpace(i, j - 1);
		}
		if (tile_array[i + 1][j + 1].getnumber() >= 0) {
			HideCell(i + 1, j + 1);
			//ClearSpace(i + 1, j + 1);
		}
		if (tile_array[i - 1][j + 1].getnumber() >= 0) {
			HideCell(i - 1, j + 1);
			//ClearSpace(i - 1, j + 1);
		}
		if (tile_array[i - 1][j - 1].getnumber() >= 0) {
			HideCell(i - 1, j - 1);
			//ClearSpace(i - 1, j - 1);
		}
		if (tile_array[i + 1][j - 1].getnumber() >= 0) {
			HideCell(i + 1, j - 1);
			//ClearSpace(i + 1, j - 1);
		}
	
		
	
}