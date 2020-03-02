#include<GL/glew.h>
#include <GL/glut.h>
#include <Windows.h>
#include <stdlib.h>
#include "add.h"

#define COLUMNS 60	//making grid with 40 rows and columns
#define ROWS 60
#define FPS 15  //15 boxes in 1 second approx


extern short snake_dir;
bool gameOver = false;

int score=0;

void timer_func(int);
void display_func();
void reshape_func(int,int);
void keyboard_func(int,int,int);

void init()
{
	glClearColor(0.1, 0.8, 0.1, 1.0);
	initGrid(COLUMNS, ROWS);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Snake by Bhusan");
	glutDisplayFunc(display_func);
	glutReshapeFunc(reshape_func);
	glutTimerFunc(0,timer_func,0);
	glutSpecialFunc(keyboard_func);
	init();
	glutMainLoop();
	return 0;
}

void display_func()
{
	glClear(GL_COLOR_BUFFER_BIT);  //clears color and sets the color to specified color
	drawGrid();						//grid will be drawn
	drawSnake();					//snake drwaing function
	drawFood();						//food is drawn
	glutSwapBuffers();				//buffer is swapped at 10 FPS rate

	if (gameOver)					//when gameover is true
	{
		char nscore[10];
		_itoa_s(score, nscore, 10);		//convert intiger to string
		char text[50] = "Game over!! Your score : ";
		strcat_s(text, nscore);			//score is shown with text
		MessageBox(NULL, text,"Good Game",0);		//message box is shown
		exit(0);
	}
} 

void reshape_func(int l, int b)		 //to resize and move
{
	glViewport(0,0,(GLsizei)l,(GLsizei)b);  //starts from 0,0 to the whole window
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, COLUMNS, 0.0, ROWS, -1.0, 1.0); // grid and screen are same
	glMatrixMode(GL_MODELVIEW);
}

void timer_func(int)
{
	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, timer_func, 0);
}

void keyboard_func(int key, int, int)			//keyboard button press functionality
{
	switch (key)
	{
	case GLUT_KEY_UP:
		if (snake_dir != DOWN)
			snake_dir = UP;
		break;
	case GLUT_KEY_DOWN:
		if (snake_dir != UP)
			snake_dir = DOWN;
		break;
	case GLUT_KEY_RIGHT:
		if (snake_dir != LEFT)
			snake_dir = RIGHT;
		break;
	case GLUT_KEY_LEFT:
		if (snake_dir != RIGHT)
			snake_dir = LEFT;
		break;
	}
}