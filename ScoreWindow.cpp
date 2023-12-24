#include "ScoreWindow.h"

ScoreWindow::ScoreWindow()
{
	score = 0;
	clock.restart();
	std::cout << "Time Started";

	//TEXT ADD INIT
	font.loadFromFile("./GeistMonoVF.ttf");
	for (int i = 0; i < 8; i++)
	{
		text_array[i].setFont(font);
		text_array[i].setFillColor(sf::Color::White);
		text_array[i].setCharacterSize(28);
		text_array[i].setStyle(sf::Text::Bold);
		text_array[i].setPosition(sf::Vector2f(Primary_Text_Offset, 10.0f));
	}
	text_array[0].setString("Time Elapsed");
	text_array[1].setPosition(sf::Vector2f(Primary_Text_Offset, 40.0f));
	text_array[2].setString("Blocks Broken");
	text_array[2].setPosition(sf::Vector2f(Primary_Text_Offset, 100.0f));
	text_array[3].setPosition(sf::Vector2f(Primary_Text_Offset, 130.0f));
	text_array[4].setPosition(sf::Vector2f(Primary_Text_Offset, 190.0f));
	text_array[4].setString("Total Blocks");
	text_array[5].setPosition(sf::Vector2f(Primary_Text_Offset, 220.0f));
	text_array[6].setPosition(sf::Vector2f(Primary_Text_Offset, 280.0f));
	text_array[6].setString("Score");
	text_array[7].setPosition(sf::Vector2f(Primary_Text_Offset, 310.0f));
   
}

void ScoreWindow::setScore(int s) {
	score = s;
}


int ScoreWindow::getScore() {
	return score;
}

void ScoreWindow::displayTime(bool isWin, bool isExploded, int BlocksBrocken) {

	if (isWin != true && isExploded != true)
	{
		elapsed = clock.getElapsedTime();
		int elapsedTime = elapsed.asSeconds();
		text_array[1].setString((std::to_string(elapsedTime)) + "s");
		text_array[3].setString(std::to_string(BlocksBrocken));
		text_array[5].setString((std::to_string(14 * 14)));
		score = ScoreCalc(BlocksBrocken, 196, elapsedTime);
		text_array[7].setString(std::to_string(score));
	}
}

sf::Text ScoreWindow::getText(int i)
{
	return text_array[i];
}

int ScoreWindow::ScoreCalc(int BlocksBrocken, int totalBlocks, int secondsElapsed) {
	int TimeVariance = (secondsElapsed / 20) * 100;
	if (BlocksBrocken == 0 || secondsElapsed == 0)
	{
		return 0;
	}
	else
	{
		float score_f = (BlocksBrocken * 100 / totalBlocks * 100) - TimeVariance;
		//std::cout << score_f << std::endl;
		return score_f;
	}
}