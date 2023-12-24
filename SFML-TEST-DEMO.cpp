#include <SFML/Graphics.hpp>
#include <cstdlib> 
#include <iostream> 
#include <time.h> 
#include "Game.h"
#include "Tile.h"



int main()
{


	Game Minesweeper;
	Minesweeper.Start();
	Minesweeper.window.setFramerateLimit(60);
	while (Minesweeper.window.isOpen())
	{

		Minesweeper.Update();

		while (Minesweeper.window.pollEvent(Minesweeper.event))
		{
			if (Minesweeper.event.type == sf::Event::Closed)
				Minesweeper.window.close();
		}

		Minesweeper.window.clear();
		Minesweeper.Render();
		Minesweeper.window.display();
	}

	return 0;
}