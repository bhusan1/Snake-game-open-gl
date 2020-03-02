//#ifndef ADD_H_INCLUDED
//#define ADD_H_INCLUDED
#pragma once

#define UP 1	   //defining constants for direction
#define DOWN -1
#define RIGHT 2
#define LEFT -2

#define MAX 60

void initGrid(int, int);
void drawGrid();
void drawSnake();
void drawFood();
void random(int&, int&);



//#endif