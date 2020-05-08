// Simple Snake Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <vector>


bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail; //specifies the length of the tail
enum eDirection{STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void save_score()
{
	int high_score = 0;

	std::ifstream input("high_score.txt");
	if (!input.is_open())
	{
		std::cout << "Can't read file\n";
	}
	else
	{
		input >> high_score;
	}

	std::ofstream output("high_score.txt");
	if (!output.is_open())
	{
		std::cout << "Unable to read file\n";
		return;
	}

	if (score > high_score)
	{
		output << score;
	}
	else
	{
		output << high_score;
	}
}

void print_vector(std::vector<int> vector)
{
	for (int i = 0; i < vector.size(); i++)
	{
		std::cout << vector[i] << "\t";
	}
	std::cout << "\n";
}

void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void Draw()
{
    system("CLS");
    for (int i = 0; i < width + 2; i++)
        std::cout << "\xDC";

    std::cout << std::endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                std::cout << "\xDC";
          
            if (i == y && j == x)
                std::cout << "O";
            else if (i == fruitY && j == fruitX)
                std::cout << "\xE0"; 
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        std::cout << "o";
                        print = true; 
                    }
                }
				if (!print)
					std::cout << " ";
            }      

			if (j == width - 1)
				std::cout << "\xDC";
        }
        std::cout << std::endl;
    }

	for (int i = 0; i < width + 2; i++)
		std::cout << "\xDC";
    std::cout << std::endl;
    std::cout << "Score: " << score << std::endl;
}

// using W, A, S, D keys to move the snake
void Input()
{
    if (_kbhit()) //function to check if keyboard button was pressed
    {
        switch (_getch()) // will return the ASCII value of the character that was pressed
        {
        case 'a':
            if (dir != RIGHT)
                dir = LEFT;
            break;
		case 'd':
            if (dir != LEFT)
			    dir = RIGHT;
			break;
		case 'w':
            if (dir != DOWN)
			    dir = UP;
			break;
        case 's':
            if (dir != UP)
                dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }

}

void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch(dir)
	{
    case LEFT:
        x--;
		break;
    case RIGHT:
        x++;
		break;
    case UP:
        y--;
		break;
    case DOWN:
        y++;
        break;
    default:
        break;
	}

    //if (x > width || x < 0 || y > height || y < 0) //if the snake goes off the screen, game terminates
    //    gameOver = true;

    if (x >= width) 
        x = 0; 
    else if (x < 0)
        x = width - 1;

	if (y >= height)
		y = 0;
	else if (y < 0)
		y = height - 1;

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    if (x == fruitX && y == fruitY)
    {
        score += 10;
        // places fruit at a random spot in the game board
		fruitX = rand() % width; 
		fruitY = rand() % height;
        nTail++;
    }
}

int main()
{

    Setup();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
        Sleep(10); // this sleep function can slow the game speed; 10 represents 10 ms
 
    }
    save_score();
    system("pause");
    return 0;
}
