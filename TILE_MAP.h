#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib> 
#include <iostream> 
#include <time.h> 

#include "Game.h"
#include "Tile.h"

const int WINDOW_HEIGTH = 640;
const int WINDOW_WIDTH = 640;
const int TILE_WIDTH = 40;




class TileMap {
private:
    Tile tile_array[WINDOW_HEIGTH / TILE_WIDTH][WINDOW_WIDTH / TILE_WIDTH];
public:
    void init() {
        srand(time(0));
        int temp_mines_array_i[10];
        int temp_mines_array_j[10];

        for (int i = 0; i < 9; i++)
        {
            int random_value_i = (rand() % 14) + 1;
            int random_value_j = (rand() % 14) + 1;

            temp_mines_array_i[i] = random_value_i;
            temp_mines_array_j[i] = random_value_j;

            /*if (i == 0)
            {

            }
            else {
                for (int j = 0; j < i; j++)
                {

                    if (random_value == temp_mines_array[j])
                    {
                        break;
                    }
                    temp_mines_array[i] = random_value;
                }
            }*/

        }

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

                for (int k = 0; k < 9; k++)
                {
                    if (i == temp_mines_array_i[k] && j == temp_mines_array_j[k])
                    {
                        tile_array[i][j].setnumber(-1);
                    }
                }

                if (i == 0 || j == 0 || i == 15 || j == 15) {
                    tile_array[i][j].setnumber(-2);
                }
            }
        }

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

        for (int i = 0; i < WINDOW_HEIGTH / TILE_WIDTH; i++)
        {
            for (int j = 0; j < WINDOW_WIDTH / TILE_WIDTH; j++)
            {


                if (tile_array[i][j].getnumber() == -1)
                {
                    tile_array[i][j].setFillColor(sf::Color::Red);
                }

                if (tile_array[i][j].getnumber() == -2)
                {
                    tile_array[i][j].setFillColor(sf::Color::Cyan);
                }

                if (tile_array[i][j].getnumber() == 0)
                {
                    tile_array[i][j].setFillColor(sf::Color::Black);
                }

                if (tile_array[i][j].getnumber() == 1)
                {
                    tile_array[i][j].setFillColor(sf::Color::Blue);
                }
                if (tile_array[i][j].getnumber() == 2)
                {
                    tile_array[i][j].setFillColor(sf::Color::Yellow);
                }
                if (tile_array[i][j].getnumber() == 3)
                {
                    tile_array[i][j].setFillColor(sf::Color::Magenta);
                }

            }

        }





    }

    Tile getMapElement(int a, int b) {
        return tile_array[a][b];
    }

};

