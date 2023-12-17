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
	window.setFramerateLimit(10000);
}


void Game::Start() {

}

void Game::Update() {


	if (!tile_map.getIsExploded())
	{
		sf::Vector2i pos = sf::Mouse::getPosition(window);
		int x = pos.x / TILE_WIDTH;
		int y = pos.y / TILE_WIDTH;

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.key.code == sf::Mouse::Left)
			{

				Tile tile_d = tile_map.getMapElement(x, y);
				if (tile_d.getFlaggedStatus() == false && tile_d.getnumber() >= -1 && tile_d.gethidden_state() == true)
				{
					tile_map.ShowCell(x, y);
				

				}

			}
		}
		/*		bool click_lock = false;
		if (event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left) && click_lock == false )
		{
			std::cout << "Pressed";


				int i = event.mouseButton.x / 40;
				int j = event.mouseButton.y / 40;

				Tile tile_d = tile_map.getMapElement(i, j);
				if (tile_d.getFlaggedStatus() == false && tile_d.getnumber() >= -1 && tile_d.gethidden_state() == true )
				{
					tile_map.ShowCell(i, j);
					click_lock = true;

				}

		}

		if (event.type == sf::Event::MouseButtonReleased)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && click_lock == true) {
				click_lock = false;
			}
		}*/

		tile_map.Update();

		bool click_lock_right = false;
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && click_lock_right == false) {

				int i = event.mouseButton.x / 40;
				int j = event.mouseButton.y / 40;

				if (tile_map.getMapElement(i, j).getFlaggedStatus() == false && click_lock_right == false)
				{
					tile_map.setFlagged(i, j, true);
					click_lock_right = true;

				}
				else if (tile_map.getMapElement(i, j).getFlaggedStatus() == true && click_lock_right == false)
				{
					tile_map.setFlagged(i, j, false);
					click_lock_right = true;

				}

			}
		}
		else if (event.type == sf::Event::MouseButtonReleased)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && click_lock_right == true) {
				click_lock_right = false;
			}
		}


	}





}

void Game::Render() {
	for (int i = 0; i < WINDOW_HEIGTH / TILE_WIDTH; i++)
	{
		for (int j = 0; j < WINDOW_WIDTH / TILE_WIDTH; j++)
		{
			window.draw(tile_map.getMapElement(i, j));

			if (tile_map.getMapElement(i, j).gethidden_state() == true)
			{
				window.draw(tile_map.getMapElement(i, j).getInnerText());
			}

			window.draw(tile_map.getMapElement(i, j).getSprite());
		}
	}


}


