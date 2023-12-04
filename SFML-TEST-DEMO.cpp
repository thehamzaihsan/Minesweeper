#include <SFML/Graphics.hpp>
#include <cstdlib> 
#include <iostream> 
#include <time.h> 

#include "Game.h"
#include "Tile.h"
#include "TILE_MAP.h"



int main()
{   
    
  
    Game Minesweeper;
    Minesweeper.Start();
    
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