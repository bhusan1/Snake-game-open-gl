#include<GL/glew.h>
#include <GL/glut.h>
#include <ctime>
#include "add.h"

extern int score;

int gridX, gridY;
int snake_length = 5;
bool food = true;
int foodX, foodY;
short snake_dir = RIGHT;
extern bool gameOver;

int headX[60] = { 20,20,20,20,20 }, headY[60] = { 20,19,18,17,16 };		//position of head and following body

void initGrid(int x, int y)
{
	gridX = x;
	gridY = y;
}

void unit(int x, int y);

void drawGrid()			//this function draws grid
{
	for (int x = 0; x < gridX; x++)
	{
		for (int y = 0; y < gridY; y++)
		{
			unit(x, y);
		}
	}
}

void unit( int x ,int y)		//unit function makes a box in a grid
{
	if((x ==0) || (y ==0) || (x == gridX-1) || (y == gridY -1))		//border is painted red
	{
		glLineWidth(3.0);
		glColor3f(0.3, 1.0, 0.3);
	}
	else				//other grid is colored different
	{
		glLineWidth(1.0);
		glColor3f(0.1, 0.8, 0.1);
	}

	
	glBegin(GL_LINE_LOOP);		//line loop function is used to draw grid
		glVertex2f(x, y);
		glVertex2f(x + 1, y);
		glVertex2f(x + 1, y+1);
		glVertex2f(x , y+1);

	glEnd();
}

void drawFood()			//function draws food
{
	if (food)
		random(foodX, foodY); //this draws food in random position
	food = false;
	glColor3f(1.0, 0.0, 0.0);
	glRectf(foodX, foodY, foodX + 1, foodY + 1);	//gives square shape to food
}

void drawSnake()			//this function draws snake as it grows
{
	for (int i = snake_length - 1;i>0;i--)		//tell snake follows the previous body as it grows 
	{
		headX[i] = headX[i - 1];
		headY[i] = headY[i - 1];
	}

	if (snake_dir == UP)		//according to direction of snake position is changed
		headY[0]++;
	else if (snake_dir == DOWN)
		headY[0]--;
	else if (snake_dir == LEFT)
		headX[0]--;
	else if (snake_dir == RIGHT)
		headX[0]++;

	for (int i = 0; i < snake_length; i++)
	{
		if (i == 0)			//coloring head different
			glColor3f(1.0, 1.0, 1.0);
		else				//color of following body
			glColor3f(1.0, 1.0, 0.0);
		glRectd(headX[i], headY[i], headX[i] + 1, headY[i] + 1);
	}

	
	if ((headX[0] == 0) || (headX[0] == gridX - 1) || (headY[0] == 0) || (headY[0] == gridY - 1))  //dies if touches border
		gameOver = true;
	
	
	for (int j = 1; j < snake_length; j++)		//if the snake touches itself game over
	{
		if (headX[j] == headX[0] && headY[j] == headY[0])
			gameOver = true;
	}

	if (headX[0] == foodX && headY[0] == foodY)		//when snake eats food from head
	{
		score++;
		snake_length++;
		if (snake_length > MAX)
			snake_length = MAX;
		food = true;
	}
	
}



void random(int &x, int &y)		//generates random number for food location
{
	int _maxX = gridX - 2;
	int _maxY = gridY - 2;
	int _min = 1;
	srand(time(NULL));
	x = _min + rand() % (_maxX - _min);
	y = _min + rand() % (_maxY - _min);

}