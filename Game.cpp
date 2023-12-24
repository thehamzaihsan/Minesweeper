
#include "Game.h"

Game::Game()
{
	window.create(sf::VideoMode(WINDOW_HEIGTH + 260, WINDOW_WIDTH), "Minesweeper", sf::Style::Close);
	DEBUG = false;
	FirstMove = true;
	isWin = false;
	isExploded = false;
	removedBlocks = 0;
}

void Game::Start()
{

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

			if (i == 0 || j == 0 || i == (WINDOW_HEIGTH / TILE_WIDTH) - 1 || j == (WINDOW_WIDTH / TILE_WIDTH) - 1)
			{
				tile_array[i][j].setnumber(-2);
			}
		}
	}

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

void Game::setBombs()
{

	for (int i = 0; i < WINDOW_HEIGTH / TILE_WIDTH; i++)
	{
		for (int j = 0; j < WINDOW_WIDTH / TILE_WIDTH; j++)
		{
			for (const auto& value : RandomNumbers)
			{
				if (value.x == i && value.y == j)
				{
					tile_array[i][j].setnumber(-1);
				}
			}
		}
	}
}

void Game::Update()
{
	scoreWindow.displayTime(isWin , isExploded , removedBlocks);
	removedBlocks = 0;

	int i = event.mouseButton.x / 40;
	int j = event.mouseButton.y / 40;

	if (!isExploded && !isWin)
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (i > 0 && j > 0 && i < WINDOW_HEIGTH / TILE_WIDTH - 1 && j < WINDOW_WIDTH / TILE_WIDTH - 1)
			{
				if (event.key.code == sf::Mouse::Left)
				{
					if (FirstMove == true)
					{
						RandomNumbers = SetRandomBombs(i, j);
						setBombs();
						setNumberData();
						FirstMove = false;
						HideCell(i, j);
					}
					else if (FirstMove == false)
					{

						HideCell(i, j);
					}
				}

				if (event.key.code == sf::Mouse::Right)
				{

					tile_array[i][j].setIsFlagged(true);
				}
				if (event.key.code == sf::Mouse::Middle)
				{

					tile_array[i][j].setIsFlagged(false);
				}
			}
		}
	}


	Checkwin();

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
				tile_array[i][j].setFillColor(sf::Color{ 198, 198, 198, 100 });
			}
			else if (tile_array[i][j].getIsFlagged() == true)
			{
				tile_array[i][j].setFillColor(sf::Color::Green);
			}
			else if (tile_array[i][j].getIsFlagged() == false && tile_array[i][j].getnumber() >= 0)
			{
				tile_array[i][j].setFillColor(sf::Color::White);
			}

			if (isExploded == true)
			{
				isWin == false;
			}

			// SPRITESSSSSS YESSSS

			if (tile_array[i][j].gethidden_state() == false)
			{
				tile_array[i][j].setTexturePath("./Sprites/TileUnknown.png");
			}
			if (DEBUG == true)
			{
				if (tile_array[i][j].getnumber() == -1)
				{
					tile_array[i][j].setTexturePath("./Sprites/TileExploded.png");
				}
			}
			if (tile_array[i][j].gethidden_state() == false && tile_array[i][j].getnumber() == -2)
			{
				tile_array[i][j].setTexturePath("./Sprites/TileBorder.png");
			}
			if (tile_array[i][j].getIsFlagged() == true)
			{
				tile_array[i][j].setTexturePath("./Sprites/TileFlag.png");
			}
			if (tile_array[i][j].gethidden_state() == true && tile_array[i][j].getnumber() == 0)
			{
				tile_array[i][j].setTexturePath("./Sprites/TileEmpty.png");
			}
			if (isExploded == true && tile_array[i][j].getnumber() == -1)
			{
				tile_array[i][j].setTexturePath("./Sprites/TileExploded.png");
			}
			else if (isExploded == false && isWin == true && tile_array[i][j].getnumber() == -1)
			{
				tile_array[i][j].setTexturePath("./Sprites/TileMine.png");
			}
			else if (tile_array[i][j].gethidden_state() == true && tile_array[i][j].getnumber() == 1)
			{
				tile_array[i][j].setTexturePath("./Sprites/Tile1.png");
			}
			else if (tile_array[i][j].gethidden_state() == true && tile_array[i][j].getnumber() == 2)
			{
				tile_array[i][j].setTexturePath("./Sprites/Tile2.png");
			}
			else if (tile_array[i][j].gethidden_state() == true && tile_array[i][j].getnumber() == 3)
			{
				tile_array[i][j].setTexturePath("./Sprites/Tile3.png");
			}
			else if (tile_array[i][j].gethidden_state() == true && tile_array[i][j].getnumber() == 4)
			{
				tile_array[i][j].setTexturePath("./Sprites/Tile4.png");
			}
			else if (tile_array[i][j].gethidden_state() == true && tile_array[i][j].getnumber() == 5)
			{
				tile_array[i][j].setTexturePath("./Sprites/Tile5.png");
			}
			else if (tile_array[i][j].gethidden_state() == true && tile_array[i][j].getnumber() == 6)
			{
				tile_array[i][j].setTexturePath("./Sprites/Tile6.png");
			}
			else if (tile_array[i][j].gethidden_state() == true && tile_array[i][j].getnumber() == 7)
			{
				tile_array[i][j].setTexturePath("./Sprites/Tile7.png");
			}
			else if (tile_array[i][j].gethidden_state() == true && tile_array[i][j].getnumber() == 8)
			{
				tile_array[i][j].setTexturePath("./Sprites/Tile8.png");
			}

			/*	else if (tile_array[i][j].gethidden_state() == true && tile_array[i][j].getnumber() == 0) {
					tile_array[i][j].setTexturePath("./Sprites/TileEmpty.png");
				}*/
			tile_array[i][j].setsprite();
		}
	}
}

void Game::Render()
{
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

	for (int i = 0; i < 8; i++)
	{
		window.draw(scoreWindow.getText(i));
	}
}

void Game::ClearSpace(int i, int j)
{

	if (tile_array[i + 1][j].getnumber() >= 0)
	{
		HideCell(i + 1, j);
	}
	if (tile_array[i][j + 1].getnumber() >= 0)
	{
		HideCell(i, j + 1);
	}
	if (tile_array[i - 1][j].getnumber() >= 0)
	{
		HideCell(i - 1, j);
	}
	if (tile_array[i][j - 1].getnumber() >= 0)
	{
		HideCell(i, j - 1);
	}
	if (tile_array[i + 1][j + 1].getnumber() >= 0)
	{
		HideCell(i + 1, j + 1);
	}
	if (tile_array[i - 1][j + 1].getnumber() >= 0)
	{
		HideCell(i - 1, j + 1);
	}
	if (tile_array[i - 1][j - 1].getnumber() >= 0)
	{
		HideCell(i - 1, j - 1);
	}
	if (tile_array[i + 1][j - 1].getnumber() >= 0)
	{
		HideCell(i + 1, j - 1);
	}
}

void Game::setNumberData()
{
	for (int i = 0; i < WINDOW_HEIGTH / TILE_WIDTH - 1; i++)
	{
		for (int j = 0; j < WINDOW_WIDTH / TILE_WIDTH - 1; j++)
		{
			if (tile_array[i][j].getnumber() >= 0)
			{
				if (tile_array[i + 1][j].getnumber() == -1)
				{
					tile_array[i][j]++;
				}
				if (tile_array[i][j + 1].getnumber() == -1)
				{
					tile_array[i][j]++;
				}
				if (tile_array[i - 1][j].getnumber() == -1)
				{
					tile_array[i][j]++;
				}
				if (tile_array[i][j - 1].getnumber() == -1)
				{
					tile_array[i][j]++;
				}
				if (tile_array[i + 1][j + 1].getnumber() == -1)
				{
					tile_array[i][j]++;
				}
				if (tile_array[i - 1][j + 1].getnumber() == -1)
				{
					tile_array[i][j]++;
				}
				if (tile_array[i - 1][j - 1].getnumber() == -1)
				{
					tile_array[i][j]++;
				}
				if (tile_array[i + 1][j - 1].getnumber() == -1)
				{
					tile_array[i][j]++;
				}
			}
		}
	}
}
std::set<Point> Game::SetRandomBombs(int i, int j)
{
	std::set<Point> uniquePoints;
	std::srand(std::time(0)); // Seed for random number generation

	while (uniquePoints.size() < BOMB_NUMBER)
	{
		Point p;
		p.x = std::rand() % (WINDOW_HEIGTH / TILE_WIDTH - 2) + 1; // Range: 1 to 15
		p.y = std::rand() % (WINDOW_WIDTH / TILE_WIDTH - 2) + 1;  // Range: 1 to 15


		//all these if blcoks are here to insure that the first click does not have a bomb beside it :)
		if (p.x != i && p.y != j)
		{
			if (p.x != i + 1 && p.y != j)
			{
				if (p.x != i && p.y != j + 1)
				{
					if (p.x != i - 1 && p.y != j)
					{

						if (p.x != i && p.y != j - 1)
						{

							if (p.x != i - 1 && p.y != j - 1)
							{
								if (p.x != i + 1 && p.y != j + 1)
								{

									if (p.x != i - 1 && p.y != j + 1)
									{

										if (p.x != i + 1 && p.y != j - 1)
										{
											// Ensure the point is unique
											if (uniquePoints.find(p) == uniquePoints.end())
											{
												uniquePoints.insert(p);
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	return uniquePoints;
}

void Game::Explode()
{
	for (int i = 0; i < WINDOW_HEIGTH / TILE_WIDTH; i++)
	{
		for (int j = 0; j < WINDOW_WIDTH / TILE_WIDTH; j++)
		{

			if (tile_array[i][j].getnumber() == -1)
			{
				tile_array[i][j].setFillColor(sf::Color::Red);
				tile_array[i][j].sethidden_state(true);
			}
		}
	}
}

void Game::HideCell(int i, int j)
{
	if (tile_array[i][j].getIsFlagged() == false)
	{
		tile_array[i][j].sethidden_state(true);
	}
}

void Game::Checkwin()
{

	for (int i = 0; i < WINDOW_HEIGTH / TILE_WIDTH - 1; i++)
	{
		for (int j = 0; j < WINDOW_WIDTH / TILE_WIDTH - 1; j++)
		{
			if (tile_array[i][j].gethidden_state() == true && tile_array[i][j].getnumber() >= 0)
			{
				removedBlocks++;
			}
		}
	}
	// WIN LOGIC

	if (removedBlocks - 136 - 10 == BOMB_NUMBER)
	{
		isWin = true;
	}

}