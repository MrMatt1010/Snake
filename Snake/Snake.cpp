#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <string>

using namespace std;
using namespace std::chrono;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

struct Highscore {
    string name;
    int score;
};

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
    system("cls");  // Clear the screen (for Linux/Unix, use "cls" for Windows)
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
    if (cin.peek() != EOF) {
        switch (cin.get()) {
            case 'a':
                if (dir != RIGHT) dir = LEFT;
                break;
            case 'd':
                if (dir != LEFT) dir = RIGHT;
                break;
            case 'w':
                if (dir != DOWN) dir = UP;
                break;
            case 's':
                if (dir != UP) dir = DOWN;
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

bool CompareScores(const Highscore& a, const Highscore& b) {
    return a.score > b.score;
}

void DisplayHighscores(const vector<Highscore>& highscores) {
    cout << "Highscores:" << endl;
    for (const auto& entry : highscores) {
        cout << entry.name << ": " << entry.score << endl;
    }
}
//This is the maun  function where the game is played
int main() {
    vector<Highscore> highscores;
    
    do {
        Setup();
        string playerName;
        cout << "Enter your name: ";
        cin >> playerName;

        int dfc = SetDifficulty();
        while (!gameOver) {
            Draw();
            Input();
            Logic();
            this_thread::sleep_for(milliseconds(dfc));
        }

        cout << "Game Over!" << endl;
        cout << "Your score: " << score << endl;

        Highscore currentScore = {playerName, score};
        highscores.push_back(currentScore);

        // Sort the highscores
        sort(highscores.begin(), highscores.end(), CompareScores);

        // Display highscores
        DisplayHighscores(highscores);

        // Prompt the user to play again or exit
        cout << "Do you want to play again? (y/n): ";
        char choice;
        cin >> choice;
        if (choice != 'y' && choice != 'Y')
            break; // Exit the loop if not 'y' or 'Y'
        else {
            // Reset game variables
            score = 0;
            gameOver = false;
        }
    } while (true); // Loop until the user chooses to exit

    cout << "Thank you for playing!" << endl;
    cout << "Press any key to exit...";
    cin.ignore(); // Ignore any previous input
    cin.get();    // Wait for a key press

    return 0;
}
