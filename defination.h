//  This file is used to include the necessary libraries, defination, variables for a project

#ifndef _DEFINATION_H           // Header Guard: This ensures that the header file is included only once during compilation.
#define _DEFINATION_H


// LIBRARY USED
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <mmsystem.h>
#pragma (lib, "Winmm.lib")
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

// GAME MODE 
#define EASY 4
#define MEDIUM 6
#define HARD 8

// COLOR CODE DEFINATION
#define BLACK			0
#define BLUE			1
#define GREEN			2
#define AQUA			3
#define RED				4
#define PURPLE			5
#define YELLOW			6
#define WHITE			7
#define GRAY			8
#define LIGHT_BLUE		9
#define LIGHT_GREEN		10
#define LIGHT_AQUA		11
#define LIGHT_RED		12
#define LIGHT_PURPLE	13
#define LIGHT_YELLOW	14
#define BRIGHT_WHITE	15

// MOVEMENT DEFINATION
#define UP_KEY			72
#define DOWN_KEY		80
#define LEFT_KEY		75
#define RIGHT_KEY		77
#define ENTER_KEY		13

char _getCh() {
    char* ch = new char; 
    *ch = _getch();

    switch(*ch) {
        case UP_KEY : case DOWN_KEY : case RIGHT_KEY : case LEFT_KEY :
            return *ch;
        case 'w': case 'W':
            return UP_KEY;
        case 's': case 'S':
            return DOWN_KEY;
        case 'a':  case 'A':
            return LEFT_KEY;
        case 'd': case 'D':
            return RIGHT_KEY;
        case ' ': case '\n':
            return ENTER_KEY;
        default:
            return *ch;
    }
}

// GAME VARIABLES
const int WELCOME_ITEMS_COUNT = 3;
const string WELCOME_ITEMS[WELCOME_ITEMS_COUNT] = {"SIGN IN", "SIGN UP", "EXIT 😢"};
const int MENU_ITEMS_COUNT = 5;
const string MENU_ITEMS[MENU_ITEMS_COUNT] = {"PLAY", "HELP", "RANKING", "CREDITS", "SIGN OUT"};
const int GAME_MODE_ITEMS_COUNT = 5;
const string GAME_MODE_ITEMS[GAME_MODE_ITEMS_COUNT] = {"EASY", "MEDIUM", "HARD", "CREATIVE MODE", "BACK"};

struct Player {
    char username[12] = "";
    char password[20] = "";
};

struct Save {
    char user[12] = "";
    int score = 0;
};

struct GameBoard {
    int rows, cols;
    char** pokemons;
    bool** highlighted;
    string** bg;
};

struct Position {
    int posX, posY;
};


#endif