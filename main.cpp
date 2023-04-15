#include "header.h"

int main() {
    // Set Up Game Console
    SetUpGameConsole();

    // Game variables
    bool isExited = false, signInFlag = false;
    int selected = 0;
    char* ch = new char;
    string cur_player = "";
    vector<Player> listP;
    vector<Save> saveG;
    
    readData(listP);
    readSaveFile(saveG);
    gotoXY(0, 0);
    string text = "Introducing the game created by Phan Vo Minh Tue and Truong Hoai Nam . . .";
    for (int i = 0; i < text.length(); i++) {
        cout << text[i];
        Sleep(50); // tạm dừng trong 50ms trước khi in ký tự tiếp theo
    }
    Sleep(1000);
    bgSound(true);
    while (!isExited) {	
        // Draw Welcome Screen
        ClearScreen();
        welComeScreen(selected);
        *ch = _getCh();
        switch(*ch) {
            case UP_KEY :
                if (selected > 0)
                    selected--;
                else 
                    selected = WELCOME_ITEMS_COUNT - 1;
                break;

            case DOWN_KEY :
                if (selected < WELCOME_ITEMS_COUNT - 1)
                    selected++;
                else
                    selected = 0;
                break;

            case ENTER_KEY :
                // 1. Sign in successfully
                if (selected == 0) {
                    ClearScreen();
                    OnOffCursor(true);
                    SignIn(listP, signInFlag, cur_player);
                    if (signInFlag == true) {
                        // Draw initial menu
                        ClearScreen();
                        OnOffCursor(false);
                        blinkingStar();
                        mainMenu(selected);

                        // Game loop
                        while (signInFlag) {
                            *ch = _getCh();
                            bool isBack = false;
                            switch(*ch) {
                                case UP_KEY :
                                    if (selected > 0)
                                        selected--;
                                    else 
                                        selected = MENU_ITEMS_COUNT - 1;
                                    break;

                                case DOWN_KEY :
                                    if (selected < MENU_ITEMS_COUNT - 1)
                                        selected++;
                                    else
                                        selected = 0;
                                    break;
                        
                                case ENTER_KEY :
                                    // 1. GAME MODE
                                    bgSound(false);
                                    if (selected == 0) {
                                        ClearScreen();
                                        selected = 0;

                                        // Draw game mode screen
                                        gameMode(selected);
                                        while (true) {
                                            *ch = _getCh();
                                            switch(*ch) {
                                                case UP_KEY :
                                                    if (selected > 0)
                                                        selected--;
                                                    else 
                                                        selected = GAME_MODE_ITEMS_COUNT - 1;
                                                    break;

                                                case DOWN_KEY :
                                                    if (selected < GAME_MODE_ITEMS_COUNT - 1)
                                                        selected++;
                                                    else 
                                                        selected = 0;
                                                    break;
                                                
                                                case ENTER_KEY :
                                                    // Mode 1 : EASY
                                                    if (selected == 0) {
                                                        int level = 1;
                                                        bool BackButton = false;
                                                        ClearScreen();
                                                        loadingBar();
                                                        GameBoard board;
                                                        board.rows = EASY;
                                                        board.cols = EASY;
                                                        while (level <= 5 && !BackButton) {
                                                            bool finished = false;
                                                            handleGameBoard(board, cur_player, saveG, level, finished);
                                                            afterGame(board, level, BackButton, finished);
                                                        }
                                                        ClearScreen();                           
                                                    }
                                                    
                                                    // Mode 2 : Medium
                                                    if (selected == 1) {
                                                        int level = 1;
                                                        bool BackButton = false;
                                                        ClearScreen();
                                                        loadingBar();
                                                        GameBoard board;
                                                        board.rows = MEDIUM;
                                                        board.cols = MEDIUM;
                                                        while (level <= 5 && !BackButton) {
                                                            bool finished = false;
                                                            handleGameBoard(board, cur_player, saveG, level, finished);
                                                            afterGame(board, level, BackButton, finished);
                                                        }
                                                        ClearScreen();
                                                    }

                                                    // Mode 3 : HARD
                                                    if (selected == 2) {
                                                        int level = 1;
                                                        bool BackButton = false;
                                                        ClearScreen();
                                                        loadingBar();
                                                        GameBoard board;
                                                        board.rows = HARD;
                                                        board.cols = HARD;
                                                        while (level <= 5 && !BackButton) {
                                                            bool finished = false;
                                                            handleGameBoard(board, cur_player, saveG, level, finished);
                                                            afterGame(board, level, BackButton, finished);
                                                        }
                                                        ClearScreen();      
                                                    }

                                                    // Mode 4 : CREATIVE MODE
                                                    if (selected == 3) {
                                                        int level = 1;
                                                        ClearScreen();
                                                        selected = 0;
                                                        int numRows = 4;
                                                        int numCols = 4;
                                                        bool BackButton = false;
                                                        // Draw selection
                                                        creativeMode(selected, numRows, numCols);
                                                        while(true) {
                                                            *ch = _getCh();
                                                            switch(*ch) {
                                                                case UP_KEY : case DOWN_KEY :
                                                                    if (selected == 0)
                                                                        selected = 1;
                                                                    else 
                                                                        selected = 0;
                                                                    break;

                                                                case LEFT_KEY : 
                                                                    if (selected == 0)
                                                                        numRows--;
                                                                    else 
                                                                        numCols--;
                                                                        
                                                                    if (numRows < 2)
                                                                        numRows = 2;
                                                                    if (numCols < 2)
                                                                        numCols = 2;
                                                                    break;

                                                                case RIGHT_KEY :
                                                                    if (selected == 0)
                                                                        numRows++;
                                                                    else 
                                                                        numCols++;
                                                                    
                                                                    if (numRows > 8)
                                                                        numRows = 8;
                                                                    if (numCols > 8)
                                                                        numCols = 8;
                                                                    break;

                                                                case ENTER_KEY :
                                                                    if (numRows * numCols % 2 == 0) {
                                                                        ClearScreen();
                                                                        loadingBar();
                                                                        GameBoard board;
                                                                        board.rows = numRows;
                                                                        board.cols = numCols;
                                                                        while (level <= 5 && !BackButton) {
                                                                            bool finished = false;
                                                                            handleGameBoard(board, cur_player, saveG, level, finished);
                                                                            afterGame(board, level, BackButton, finished);
                                                                        }
                                                                        ClearScreen();
                                                                    }
                                                                    break;
                                                                
                                                                case 'B' : case 'b' :
                                                                    BackButton = true;
                                                                    
                                                            } 
                                                            if (BackButton) {
                                                                selected = 0;
                                                                ClearScreen();
                                                                break;
                                                            }
                                                            // Update Screen
                                                            creativeMode(selected, numRows, numCols);
                                                        }
                                                    }

                                                    // Back 
                                                    if (selected == 4) 
                                                        isBack = true;                     
                                            }
                                            // Check isBack;
                                            if (isBack == true) {
                                                selected = 0;
                                                break;
                                            }   
                                            // Update screen                 
                                            gameMode(selected);
                                        }
                                    }

                                    // 2. HELP
                                    if (selected == 1) {
                                        help();
                                        system("pause");
                                        ClearScreen();
                                    }

                                    // 3. RANKING
                                    if (selected == 2) {
                                        leaderBoardPrinting(saveG);
                                        system("pause");
                                        ClearScreen();
                                    }

                                    // 4. CREDITS
                                    if (selected == 3) {
                                        credits();
                                        system("pause");
                                        ClearScreen();
                                    }

                                    // 5. LOG OUT
                                    if (selected == 4) {
                                        ClearScreen();
                                        selected = 0;
                                        // Draw log out check screen
                                        logOutConfirm(selected);
                                        while (true) {
                                            *ch = _getCh();
                                            switch(*ch) {
                                                case UP_KEY : case DOWN_KEY : case LEFT_KEY : case RIGHT_KEY :
                                                    // Update screen
                                                    ClearScreen();
                                                    selected++;
                                                    break;
                                                case ENTER_KEY :
                                                    if (selected % 2 == 1)
                                                        signInFlag = false;
                                                    else 
                                                        isBack = true;
                                            }
                                            // after ENTER_KEY 
                                            if (isBack == true || signInFlag == false) {
                                                selected = 0;
                                                ClearScreen();
                                                break;
                                            }
                                            // Update Screen
                                            logOutConfirm(selected);
                                        }       
                                    }
                            }
                            // Update Screen
                            mainMenu(selected);
                        }
                    }
                }

                // 2. Sign up screen
                if (selected == 1) {
                    OnOffCursor(true);
                    SignUp(listP, cur_player);
                    ClearScreen();
                    OnOffCursor(false);
                    welComeScreen(selected);
                }

                // 3. Exit
                if (selected == 2) {
                    ClearScreen();
                    selected = 0;
                    bool noExit = false;
                    // Draw exit check screen
                    exitConfirm(selected);
                    while (true) {
                        *ch = _getCh();
                        switch(*ch) {
                            case UP_KEY : case DOWN_KEY : case LEFT_KEY : case RIGHT_KEY :
                                // Update screen
                                ClearScreen();
                                selected++;
                                break;
                            
                            case ENTER_KEY :
                                if (selected % 2 == 1) {
                                	gotoXY(25, 0);
                                    exit(0);
                                }
                                else 
                                    noExit = true;
                        }
                        if (noExit == true) {
                            selected = 0;
                            ClearScreen();
                            break;
                        }
                        // Update screen
                        exitConfirm(selected);
                    }
                }
        }
        // Update Screen
        welComeScreen(selected);
    }

    // Free dynamical allocated memory 
    delete ch;
}