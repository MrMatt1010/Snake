#include <iostream>
#include <vector>
#include <algorithm> // for sorting
#include <utility>   // for pair
#include <string>
#include <cstdlib>
#include <ctime>
#include <conio.h>

using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

// Function to update the highscore list
void updateHighscore(vector<pair<string, int>>& highscores, const string& playerName, int score) {
    highscores.push_back(make_pair(playerName, score));
    // Sort the highscores vector in descending order of scores
    sort(highscores.begin(), highscores.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;
    });
}

void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    srand(time(NULL));
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    nTail = 0;
}

void Draw() {
    system("cls");
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                cout << "#";
            if (i == y && j == x)
                cout << "O";
            else if (i == fruitY && j == fruitX)
                cout << "*";
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }
            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
    cout << "Score:" << score << endl;
}

// Function to set the game difficulty level
int SetDifficulty() {
    int dfc, choice;
    cout << "\nSET DIFFICULTY\n1: Easy\n2: Medium\n3: Hard\nChoose difficulty level: ";
    cin >> choice;
    switch (choice) {
    case 1:
        dfc = 150;
        break;
    case 2:
        dfc = 100;
        break;
    case 3:
        dfc = 50;
        break;
    default:
        dfc = 100;
    }
    return dfc;
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir) {
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

    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

int main() {
    string playerName;
    cout << "Enter your name: ";
    cin >> playerName;
    int highscore = 0;
    string highscorePlayer = "";
    vector<pair<string, int>> highscores;

    int dfc = SetDifficulty();
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
 //       Sleep(150);

        // Update highscore list if needed
        updateHighscore(highscores, playerName, score);
    }

    cout << "Game Over!" << endl;
    cout << "Your score: " << score << endl;

    // Displaying highscores
    cout << "\nHIGHSCORES\n";
    cout << "Player Name\tScore\n";
    for (const auto& entry : highscores) {
        cout << entry.first << "\t\t" << entry.second << endl;
    }

    return 0;
}
