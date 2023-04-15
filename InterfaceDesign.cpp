#include "InterfaceDesign.h"


// Draw welcome screen, including: "SIGN IN", "SIGN UP", "EXIT"
void welComeScreen(int selected) {
    // Clear screen
    ClearScreen();

    // Draw logo 1
    gotoXY(2, 0);
    setColor(BLACK, YELLOW);
    cout << R"(
              █▀█ █ █▄▀ ▄▀█ █▀▀ █ █ █ █   █▀█ █▄ █ █▀▀ ▀█▀   █▀▀ █▀█ █▄ █ █▄ █ █▀▀ █▀▀ ▀█▀
              █▀▀ █ █ █ █▀█ █▄▄ █▀█ █▄█   █▄█ █ ▀█ ██▄  █    █▄▄ █▄█ █ ▀█ █ ▀█ ██▄ █▄▄  █)";
    
    // Draw welcome screen
    setColor(BLACK, BRIGHT_WHITE);
    gotoXY(11, 31);
    cout << "╔═════════════════════════════════════════╗";
    gotoXY(12, 31);
    cout << "║     WELCOME TO PIKACHU ONET CONNECT     ║";
    gotoXY(13, 31);
    cout << "╠═════════════════════════════════════════╣";
    for (int i = 0; i < WELCOME_ITEMS_COUNT; i++) {
        gotoXY(14 + i, 31);
        cout << "║";
        if (i == selected)
            cout << "           <<<   " << WELCOME_ITEMS[i] << "   >>>           ║";
        else 
            cout << "                 " << WELCOME_ITEMS[i] << "                 ║";
    }
    gotoXY(17, 31);
    cout << "╚═════════════════════════════════════════╝";
}

// Blinking welcome
void blinkingStar() {
    srand(time(0));
    int count = 0;
    while (count < 50) {
        ClearScreen();
        for (int i = 0; i < 50; i++) {
            int x = rand() % 105;
            int y = rand() % 30;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(SHORT)x, (SHORT)y});
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), rand() % 16);
            cout << ".";
            // SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        }
        gotoXY(2, 0);
        cout  << R"(
                        ██     ██ ███████ ██       ██████  ██████  ███    ███ ███████ 
                        ██     ██ ██      ██      ██      ██    ██ ████  ████ ██      
                        ██  █  ██ █████   ██      ██      ██    ██ ██ ████ ██ █████   
                        ██ ███ ██ ██      ██      ██      ██    ██ ██  ██  ██ ██      
                         ███ ███  ███████ ███████  ██████  ██████  ██      ██ ███████)";
        gotoXY(10, 0);
        cout << R"(
                          _______________                        |*\_/*|________
                         |  ___________  |     .-.     .-.      ||_/-\_|______  |
                         | |           | |    .****. .****.     | |           | |
                         | |   0   0   | |    .*****.*****.     | |   0   0   | |
                         | |     -     | |     .*********.      | |     -     | |
                         | |   \___/   | |      .*******.       | |   \___/   | |
                         | |___     ___| |       .*****.        | |___________| |
                         |_____|\_/|_____|        .***.         |_______________|
                           _|__|/ \|_|_.............*.............._|________|_
                          / ********** \                          / ********** \
                        /  ************  \                      /  ************  \
                       --------------------                    --------------------)";

        Sleep(50);
        count++;
    }
}

// Draw main menu, including: "PLAY", "HELP", "RANKING", "CREDITS", "LOG OUT"
void mainMenu(int selected) {
    // Clear screen
    ClearScreen();
    
    // Draw logo 2
    for (int i = 0; i < 3; i++) 
        cout << endl;
    setColor(BLACK, YELLOW);
    cout  << "\t\t     ██████╗  ██████╗ ██╗  ██╗███████╗███╗   ███╗ ██████╗ ███╗   ██╗\n"
          << "\t\t     ██╔══██╗██╔═══██╗██║ ██╔╝██╔════╝████╗ ████║██╔═══██╗████╗  ██║\n"
          << "\t\t     ██████╔╝██║   ██║█████╔╝ █████╗  ██╔████╔██║██║   ██║██╔██╗ ██║\n"
          << "\t\t     ██╔═══╝ ██║   ██║██╔═██╗ ██╔══╝  ██║╚██╔╝██║██║   ██║██║╚██╗██║\n"
          << "\t\t     ██║     ╚██████╔╝██║  ██╗███████╗██║ ╚═╝ ██║╚██████╔╝██║ ╚████║\n"
          << "\t\t     ╚═╝      ╚═════╝ ╚═╝  ╚═╝╚══════╝╚═╝     ╚═╝ ╚═════╝ ╚═╝  ╚═══╝\n";
    cout  << "\t\t                                       - The Matching Game -\n";

    // Draw main menu
    setColor(BLACK, BRIGHT_WHITE);
    int colOffset = 41;        // value of column offset
    gotoXY(15, colOffset);
    cout << "╔═════════════════════╗";
    gotoXY(16, colOffset);
    cout << "║      GAME MENU      ║";
    gotoXY(17, colOffset);
    cout << "╠═════╦═══════════════╣";
    for (int i = 0; i < MENU_ITEMS_COUNT; i++) {
        gotoXY(18 + i * 2, colOffset);
        cout << "║";
        if (i == selected) 
            cout << "  >  ";
        else 
            cout << "     ";
        cout << "║ " << MENU_ITEMS[i];
        for (int j = 0; j < 14 - MENU_ITEMS[i].size(); j++) 
            cout << " ";
        cout << "║";
        if (i != MENU_ITEMS_COUNT - 1) {
            gotoXY(19 + i * 2, colOffset);
            cout << "╠═════╬═══════════════╣";
        }
    }
    gotoXY(27, colOffset);
    cout << "╚═════╩═══════════════╝";
}

// Draw game mode, including: "EASY", "MEDIUM", "HARD", "CREATIVE MODE", "BACK"
void gameMode(int selected) {
    // Clear screen
    ClearScreen();
    
    // Draw logo 2
    for (int i = 0; i < 3; i++) 
        cout << endl;
    setColor(BLACK, YELLOW);
    cout  << "\t\t     ██████╗  ██████╗ ██╗  ██╗███████╗███╗   ███╗ ██████╗ ███╗   ██╗\n"
          << "\t\t     ██╔══██╗██╔═══██╗██║ ██╔╝██╔════╝████╗ ████║██╔═══██╗████╗  ██║\n"
          << "\t\t     ██████╔╝██║   ██║█████╔╝ █████╗  ██╔████╔██║██║   ██║██╔██╗ ██║\n"
          << "\t\t     ██╔═══╝ ██║   ██║██╔═██╗ ██╔══╝  ██║╚██╔╝██║██║   ██║██║╚██╗██║\n"
          << "\t\t     ██║     ╚██████╔╝██║  ██╗███████╗██║ ╚═╝ ██║╚██████╔╝██║ ╚████║\n"
          << "\t\t     ╚═╝      ╚═════╝ ╚═╝  ╚═╝╚══════╝╚═╝     ╚═╝ ╚═════╝ ╚═╝  ╚═══╝\n";
    cout  << "\t\t                                       - The Matching Game -\n";

    // Draw game mode
    setColor(BLACK, BRIGHT_WHITE);
    int colOffset = 41;        // value of column offset
    gotoXY(15, colOffset);
    cout << "╔═════════════════════╗";
    gotoXY(16, colOffset);
    cout << "║      GAME MODE      ║";
    gotoXY(17, colOffset);
    cout << "╠═════╦═══════════════╣";
    for (int i = 0; i < GAME_MODE_ITEMS_COUNT; i++) {
        gotoXY(18 + i * 2, colOffset);
        cout << "║";
        if (i == selected) 
            cout << "  >  ";
        else 
            cout << "     ";
        cout << "║ " << GAME_MODE_ITEMS[i];
        for (int j = 0; j < 13 - GAME_MODE_ITEMS[i].size(); j++) 
            cout << " ";
        cout << " ║";
        if (i != GAME_MODE_ITEMS_COUNT - 1) {
            gotoXY(19 + i * 2, colOffset);
            cout << "╠═════╬═══════════════╣";
        }
    }
    gotoXY(27, colOffset);
    cout << "╚═════╩═══════════════╝"; 
}

// Draw creative mode, which players can choose the number of rows and columns to play
void creativeMode(int selected, int numRows, int numCols) {
    // Clear screen
    ClearScreen();

    // Draw creative mode screen
    int colOffset = 41;        // value of column offset
    gotoXY(10, colOffset);
    cout << "╔═════════════════════╗";
    gotoXY(11, colOffset);
    cout << "║    CREATIVE MODE    ║";
    gotoXY(12, colOffset);
    cout << "╠════════╦════════════╣";
    if (selected == 0) {
        gotoXY(13, colOffset);
        cout << "║  ROWS  ║   < " << setw(2) << setfill('0') << numRows << " >   ║";
        gotoXY(14, colOffset);
        cout << "╠════════╬════════════╣";
        gotoXY(15, colOffset);
        cout << "║  COLS  ║     " << setw(2) << setfill('0') << numCols << "     ║";
    } else {
        gotoXY(13, colOffset);
        cout << "║  ROWS  ║     " << setw(2) << setfill('0') << numRows << "     ║";
        gotoXY(14, colOffset);
        cout << "╠════════╬════════════╣";
        gotoXY(15, colOffset);
        cout << "║  COLS  ║   < " << setw(2) << setfill('0') << numCols << " >   ║";
    }
    gotoXY(16, colOffset);
    cout << "╚════════╩════════════╝"; 
    gotoXY(17, colOffset - 12);   
    cout << " NOTE: Make sure to choose an even board size.";
    gotoXY(27, 0);
    cout << "Press ENTER or SPACE to continue . . ." << endl;
    cout << "Press B to back to Main Menu Screen . . .";
}

// Draw help screen, including: rule of game, game controls and how to earn points
void help() {
    // Clear screen
    ClearScreen();
    
    // Draw help screen
    for (int i = 0; i < 2; i++)
        cout << endl;
    cout << "\t\t\t    ╔═══════════════════════════════════════════════╗" << endl;
    cout << "\t\t\t    ║                      HELP                     ║" << endl;
    cout << "\t\t\t    ╠══════════════╦════════════════════════════════╣" << endl;
    cout << "\t\t\t    ║              ║  Players match pairs of cells  ║" << endl;
    cout << "\t\t\t    ║              ║containing identical figure that║" << endl;
    cout << "\t\t\t    ║     RULE     ║connect in a specific pattern,  ║" << endl;
    cout << "\t\t\t    ║              ║causing the cells to disappear, ║" << endl;
    cout << "\t\t\t    ║              ║until all pairs are matched and ║" << endl;
    cout << "\t\t\t    ║              ║the game ends.                  ║" << endl;
    cout << "\t\t\t    ╠══════════════╬════════════════════════════════╣" << endl;
    cout << "\t\t\t    ║              ║  UP     : W or UP_ARROW        ║" << endl;
    cout << "\t\t\t    ║     GAME     ║  DOWN   : S or DOWN_ARROW      ║" << endl;
    cout << "\t\t\t    ║   CONTROLS   ║  LEFT   : A or LEFT_ARROR      ║" << endl;
    cout << "\t\t\t    ║              ║  RIGHT  : D or RIGHT_ARROR     ║" << endl;
    cout << "\t\t\t    ║              ║  CHOOSE : ENTER or SPACE       ║" << endl;
    cout << "\t\t\t    ╠══════════════╬════════════════════════════════╣" << endl;
    cout << "\t\t\t    ║              ║  Each success connect :  +1    ║" << endl;
    cout << "\t\t\t    ║              ║  Each fail connect    :  -2    ║" << endl;
    cout << "\t\t\t    ║    POINTS    ║  Each move suggestion :  -3    ║" << endl;
    cout << "\t\t\t    ║              ║  Each shuffle board   :  -3    ║" << endl;
    cout << "\t\t\t    ║              ╠════════════════════════════════╣" << endl;
    cout << "\t\t\t    ║              ║  Total point = point * level   ║" << endl;
    cout << "\t\t\t    ╚══════════════╩════════════════════════════════╝" << endl;
    for (int i = 0; i < 2; i++)
        cout << endl;
}

// Draw credits
void credits() {
    // Clear screen
    ClearScreen();

    // Draw credits screen
    cout << endl;
    cout << "\t\t\t    ╔═══════════════════════════════════════════════╗" << endl;
    cout << "\t\t\t    ║                    CREDITS                    ║" << endl;
    cout << "\t\t\t    ╠═══════════════════════════════════════════════╣" << endl;
    cout << "\t\t\t    ║         UNIVERSITY OF SCIENCE, VNU-HCM        ║" << endl;
    cout << "\t\t\t    ║       FACULTY OF INFORMATION TECHNOLOGY       ║" << endl;
    cout << "\t\t\t    ║                                               ║" << endl;
    cout << "\t\t\t    ║              CSC 10002 - PROJECT              ║" << endl;
    cout << "\t\t\t    ║               THE MATCHING GAME               ║" << endl;
    cout << "\t\t\t    ║                                               ║" << endl;
    cout << "\t\t\t    ║                 ═════════════                 ║" << endl;
    cout << "\t\t\t    ║                                               ║" << endl;
    cout << "\t\t\t    ║                  SUPERVISORS                  ║" << endl;
    cout << "\t\t\t    ║            Mr. Nguyen Thanh Phuong            ║" << endl;
    cout << "\t\t\t    ║              Ms. Nguyen Ngoc Thao             ║" << endl;
    cout << "\t\t\t    ║               Mr. Bui Huy Thong               ║" << endl;
    cout << "\t\t\t    ║                                               ║" << endl;
    cout << "\t\t\t    ║                 ═════════════                 ║" << endl;
    cout << "\t\t\t    ║                                               ║" << endl;
    cout << "\t\t\t    ║                    MEMBERS :                  ║" << endl;
    cout << "\t\t\t    ║          Phan Vo Minh Tue - 22127440          ║" << endl;
    cout << "\t\t\t    ║          Truong Hoai Nam  - 22127287          ║" << endl;
    cout << "\t\t\t    ║                                               ║" << endl;
    cout << "\t\t\t    ║                 ═════════════                 ║" << endl;
    cout << "\t\t\t    ║                                               ║" << endl;
    cout << "\t\t\t    ║                 - April 2023 -                ║" << endl;
    cout << "\t\t\t    ╚═══════════════════════════════════════════════╝" << endl;
}

// Draw pause menu
void pauseMenu(int selected) {
    // Clear screen
    ClearScreen();

    // Draw pause menu
    int colOffset = 38;        // value of column offset
    gotoXY(9, colOffset);
    cout << "╔═══════════════════════════╗";
    gotoXY(10, colOffset);
    cout << "║         - PAUSED -        ║";
    gotoXY(11, colOffset);
    cout << "╠═════╦═══════════════╦═════╣";
    if (selected == 0) {
        gotoXY(12, colOffset);
        cout << "║  >  ║     RESUME    ║  <  ║";
        gotoXY(13, colOffset);
        cout << "╠═════╬═══════════════╬═════╣";
        gotoXY(14, colOffset);
        cout << "║     ║    RESTART    ║     ║";
        gotoXY(15, colOffset);
        cout << "╠═════╬═══════════════╬═════╣";
        gotoXY(16, colOffset);
        cout << "║     ║      EXIT     ║     ║";
    } else if (selected == 1) {
        gotoXY(12, colOffset);
        cout << "║     ║     RESUME    ║     ║";
        gotoXY(13, colOffset);
        cout << "╠═════╬═══════════════╬═════╣";
        gotoXY(14, colOffset);
        cout << "║  >  ║    RESTART    ║  <  ║";
        gotoXY(15, colOffset);
        cout << "╠═════╬═══════════════╬═════╣";
        gotoXY(16, colOffset);
        cout << "║     ║      EXIT     ║     ║";
    } else {
        gotoXY(12, colOffset);
        cout << "║     ║     RESUME    ║     ║";
        gotoXY(13, colOffset);
        cout << "╠═════╬═══════════════╬═════╣";
        gotoXY(14, colOffset);
        cout << "║     ║    RESTART    ║     ║";
        gotoXY(15, colOffset);
        cout << "╠═════╬═══════════════╬═════╣";
        gotoXY(16, colOffset);
        cout << "║  >  ║      EXIT     ║  <  ║";
    }
    gotoXY(17, colOffset);
    cout << "╚═════╩═══════════════╩═════╝";
}

// Draw after game finish, including: continue game or exit
void afterGameOption(int selected) {
    // Clear screen
    ClearScreen();

    // Draw after game menu
    int colOffset = 38;        // value of column offset
    gotoXY(9, colOffset);
    cout << "╔═══════════════════════════╗";
    gotoXY(10, colOffset);
    cout << "║        - COMPLETE -       ║";
    gotoXY(11, colOffset);
    cout << "╠═════╦═══════════════╦═════╣";
    if (selected == 0) {
        gotoXY(12, colOffset);
        cout << "║  >  ║   NEXT LEVEL  ║  <  ║";
        gotoXY(13, colOffset);
        cout << "╠═════╬═══════════════╬═════╣";
        gotoXY(14, colOffset);
        cout << "║     ║    RESTART    ║     ║";
        gotoXY(15, colOffset);
        cout << "╠═════╬═══════════════╬═════╣";
        gotoXY(16, colOffset);
        cout << "║     ║      BACK     ║     ║";
    } else if (selected == 1) {
        gotoXY(12, colOffset);
        cout << "║     ║   NEXT LEVEL  ║     ║";
        gotoXY(13, colOffset);
        cout << "╠═════╬═══════════════╬═════╣";
        gotoXY(14, colOffset);
        cout << "║  >  ║    RESTART    ║  <  ║";
        gotoXY(15, colOffset);
        cout << "╠═════╬═══════════════╬═════╣";
        gotoXY(16, colOffset);
        cout << "║     ║      BACK     ║     ║";
    } else {
        gotoXY(12, colOffset);
        cout << "║     ║   NEXT LEVEL  ║     ║";
        gotoXY(13, colOffset);
        cout << "╠═════╬═══════════════╬═════╣";
        gotoXY(14, colOffset);
        cout << "║     ║    RESTART    ║     ║";
        gotoXY(15, colOffset);
        cout << "╠═════╬═══════════════╬═════╣";
        gotoXY(16, colOffset);
        cout << "║  >  ║      BACK     ║  <  ║";
    }
    gotoXY(17, colOffset);
    cout << "╚═════╩═══════════════╩═════╝";
}

// Draw after game finish, including: continue game or exit
void failGame(int selected) {
    // Clear screen
    ClearScreen();

    // Draw after game menu
    int colOffset = 38;        // value of column offset
    gotoXY(9, colOffset);
    cout << "╔═══════════════════════════╗";
    gotoXY(10, colOffset);
    cout << "║       - INCOMPLETE -      ║";
    gotoXY(11, colOffset);
    cout << "╠═════╦═══════════════╦═════╣";
    if (selected == 0) {
        gotoXY(12, colOffset);
        cout << "║  >  ║    RESTART    ║  <  ║";
        gotoXY(13, colOffset);
        cout << "╠═════╬═══════════════╬═════╣";
        gotoXY(14, colOffset);
        cout << "║     ║      BACK     ║     ║";
    } else {
        gotoXY(12, colOffset);
        cout << "║     ║    RESTART    ║     ║";
        gotoXY(13, colOffset);
        cout << "╠═════╬═══════════════╬═════╣";
        gotoXY(14, colOffset);
        cout << "║  >  ║      BACK     ║  <  ║";
    }
    gotoXY(15, colOffset);
    cout << "╚═════╩═══════════════╩═════╝";
}

// Draw log out confirm screen
void logOutConfirm(int selected) {
    // Clear screen
    ClearScreen();
    
    // Draw exit check screen
    int colOffset = 38;        // value of column offset
    gotoXY(10, colOffset);
    cout << "╔═══════════════════════════╗";
    gotoXY(11, colOffset);
    cout << "║                           ║";
    gotoXY(12, colOffset);
    cout << "║  Do you want to log out?  ║";
    gotoXY(13, colOffset);
    if (selected % 2 == 1)
        cout << "║     [YES]         NO      ║";
    else 
        cout << "║      YES         [NO]     ║";
    gotoXY(14, colOffset);
    cout << "║                           ║";
    gotoXY(15, colOffset);
    cout << "╚═══════════════════════════╝";
}

// Draw exit confirm screen 
void exitConfirm(int selected) {
    // Clear screen
    ClearScreen();
    
    // Draw exit check screen
    int colOffset = 38;        // value of column offset
    gotoXY(10, colOffset);
    cout << "╔═══════════════════════════╗";
    gotoXY(11, colOffset);
    cout << "║                           ║";
    gotoXY(12, colOffset);
    cout << "║ Do you want to quit game? ║";
    gotoXY(13, colOffset);
    if (selected % 2 == 1)
        cout << "║     [YES]         NO      ║";
    else 
        cout << "║      YES         [NO]     ║";
    gotoXY(14, colOffset);
    cout << "║                           ║";
    gotoXY(15, colOffset);
    cout << "╚═══════════════════════════╝";
}

// Draw loading bar
void loadingBar() {
    ClearScreen();
    gotoXY(14, 47);
    cout << "LOADING...";
	
    gotoXY(15, 42);
	for (int i = 0; i < 20; i++) {
        cout << "█";
		Sleep(50);
	}

    ClearScreen();
}