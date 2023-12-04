#include <SFML/Graphics.hpp>
#include <cstdlib> 
#include <iostream> 
#include <time.h> 

struct Tile_State {
    bool isHidden = false;
    int number; //-1 for bomb
};

//1 = pink
//2 = black
//3 = magenta
//4 = cyan
//5 = purple
//6 = green
//7 = yellow
//8 = blue



int main()
{

    
    srand(time(0));
    const int WINDOW_HEIGTH = 640;
    const int WINDOW_WIDTH =  640;
    const int TILE_WIDTH = 40;

    sf::RenderWindow window(sf::VideoMode(WINDOW_HEIGTH,WINDOW_WIDTH), "SFML works!" , sf::Style::Close);
    

    //TILE MAP
    sf::RectangleShape tile_array[WINDOW_HEIGTH / TILE_WIDTH][WINDOW_WIDTH/ TILE_WIDTH];
    Tile_State tile_state_array[WINDOW_HEIGTH/ TILE_WIDTH][WINDOW_WIDTH / TILE_WIDTH];
    //MINE ARRAY

    int temp_mines_array[9];
    for (int i = 0; i < 9; i++)
    {
        temp_mines_array[i] = (rand() % (100 - 1 + 1)) + 1;
        std::cout << temp_mines_array[i] << std::endl;
    }
    
    
    for (int i = 0; i < WINDOW_HEIGTH / TILE_WIDTH; i++)
    {
        for (int j = 0; j < WINDOW_WIDTH / TILE_WIDTH; j++)
        {

            tile_state_array[i][j].number = 0;

            for (int k = 0; k < 9; k++)
            {
                if (i * j == temp_mines_array[k]) {
                    tile_state_array[i][j].number = -1;
                }
            }

   
            


        }
    }

    for (int i = 0; i < WINDOW_HEIGTH / TILE_WIDTH; i++)
    {
        for (int j = 0; j < WINDOW_WIDTH / TILE_WIDTH; j++)
        {
            if (tile_state_array[i][j].number >= 0) {
                if (tile_state_array[i + 1][j].number == -1) {
                    tile_state_array[i][j].number++;
                }
                if (tile_state_array[i][j + 1].number == -1) {
                    tile_state_array[i][j].number++;
                }
                if (tile_state_array[i - 1][j].number == -1) {
                    tile_state_array[i][j].number++;
                }
                if (tile_state_array[i][j - 1].number == -1) {
                    tile_state_array[i][j].number++;
                }
                if (tile_state_array[i + 1][j + 1].number == -1) {
                    tile_state_array[i][j].number++;
                }
                if (tile_state_array[i - 1][j + 1].number == -1) {
                    tile_state_array[i][j].number++;
                }
                if (tile_state_array[i - 1][j - 1].number == -1) {
                    tile_state_array[i][j].number++;
                }
                if (tile_state_array[i + 1][j - 1].number == -1) {
                    tile_state_array[i][j].number++;
                }
            }

        }
    }

    for (int i = 0; i < WINDOW_HEIGTH / TILE_WIDTH; i++)
    {
        for (int j = 0; j < WINDOW_WIDTH / TILE_WIDTH; j++)
        {
            tile_array[i][j].setSize(sf::Vector2f(TILE_WIDTH - 1,TILE_WIDTH -1));
            tile_array[i][j].setOrigin(sf::Vector2f(0,0));
            tile_array[i][j].setPosition(sf::Vector2f(TILE_WIDTH* i, TILE_WIDTH * j));
           
            if (tile_state_array[i][j].number == -1)
            {
                tile_array[i][j].setFillColor(sf::Color::Red);
            }

            if (tile_state_array[i][j].number == 0)
            {
                tile_array[i][j].setFillColor(sf::Color::Black);
            }

            if (tile_state_array[i][j].number == 1)
            {
                tile_array[i][j].setFillColor(sf::Color::Blue);
            }
            if (tile_state_array[i][j].number == 2)
            {
                tile_array[i][j].setFillColor(sf::Color::Yellow);
            }
            if (tile_state_array[i][j].number == 3)
            {
                tile_array[i][j].setFillColor(sf::Color::Magenta);
            }
           
        }
        
    }

    
    
    while (window.isOpen())
    {
        sf::Event event;
        
        
        
        

  


        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
     
     
        }

        
       

        window.clear();

        //DRAW HERE


        for (int i = 0; i < WINDOW_HEIGTH / TILE_WIDTH; i++)
        {
            for (int j = 0; j < WINDOW_WIDTH / TILE_WIDTH; j++)
            {
                window.draw(tile_array[i][j]);
            }
        }


        


        window.display();
    }

    return 0;
}