// Snake.cpp :

#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <Windows.h>

bool gameOver;

const int width = 20;
const int height = 20;

int x, y, fruitX, fruitY, score;

int tailX[100], tailY[100];
int nTail;

std::string fruit = "*";

enum eDirections
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

eDirections dir;

void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width + 1;
    fruitY = rand() % height + 1;
    score = 0;
}


int main()
{
    std::cout << "Hello World!\n";
}

