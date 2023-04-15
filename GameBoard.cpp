#include "GameBoard.h"

//////////////////////////////////////////
/*  PART 1: STAGES DIFFICULTY INCREASE  */
//////////////////////////////////////////

// blocks moving up
void level2(GameBoard &board) { 
    for(int j = 1; j <= board.cols; j++)
        for(int i = 1; i <= board.rows; i++) {
            if(board.pokemons[i][j] == 0)
                for(int key = i; key <= board.rows; key++)
                    board.pokemons[key][j] = board.pokemons[key + 1][j];
            if(board.pokemons[i][j] == 0)
                for(int key = i; key <= board.rows; key++)
                    board.pokemons[key][j] = board.pokemons[key + 1][j];
        }
}

// blocks moving left
void level3(GameBoard &board) {
    for(int i = 1; i <= board.rows; i++)
        for(int j = 1; j <= board.cols; j++){
            if(board.pokemons[i][j] == 0)
                for(int key = j; key <= board.cols; key++)
                    board.pokemons[i][key] = board.pokemons[i][key + 1];
            if(board.pokemons[i][j] == 0)
                for(int key = j; key <= board.cols; key++)
                    board.pokemons[i][key] = board.pokemons[i][key + 1];
        }
}

// blocks moving down
void level4(GameBoard &board) {
    for(int j = 1; j <= board.rows; j++)
        for(int i = board.rows; i >= 1; i--){
            if(board.pokemons[i][j] == 0)
                for(int key = i; key >= 1; key--)
                    board.pokemons[key][j] = board.pokemons[key - 1][j];
            if(board.pokemons[i][j] == 0)
                for(int key = i; key >= 1; key--)
                    board.pokemons[key][j] = board.pokemons[key - 1][j];
        }
}

// blocks moving right
void level5(GameBoard &board) {
    for(int i = 1; i <= board.rows; i++)
        for(int j = board.cols; j >= 1; j--){
            if(board.pokemons[i][j] == 0)
                for(int key = j; key >= 1; key--)
                    board.pokemons[i][key] = board.pokemons[i][key - 1];
            if(board.pokemons[i][j] == 0)
                for(int key = j; key >= 1; key--)
                    board.pokemons[i][key] = board.pokemons[i][key - 1];
        }
}

////////////////////////////////////////////////////////////////////////////////
/*  PART 2: HANDLE GAME BOARD: GENERATE BOARD, PRINT BOARD, FREE MEMORY USED  */
////////////////////////////////////////////////////////////////////////////////

// Generate randomly game board
void generateGameBoard(GameBoard &board) {
    const int maxCount = 4; // Every character does not appear over 4 times
    int count = 0;
    char currentChar = 'A'; 
    
    // Initialize board
    board.pokemons = new char*[board.rows + 2];
    board.highlighted = new bool*[board.rows + 2];
    for (int i = 0; i < board.rows + 2; i++) {
        board.pokemons[i] = new char[board.cols + 2];
        board.highlighted[i] = new bool[board.cols + 2];
        for (int j = 0; j < board.cols + 2; j++) {
            board.pokemons[i][j] = 0;
            board.highlighted[i][j] = false;
        }
    }

    // Generate game board
    srand(time(NULL));
    while(count < board.rows * board.cols) {
        if (currentChar > 'Z') 
            currentChar = 'A';
        if ((currentChar - 'A' + 1) * maxCount < (board.rows * board.cols)) {
            int i = 1;
            while ((i <= maxCount) && (count <= board.rows * board.cols)) {
                int posX = rand() % board.rows + 1;
                int posY = rand() % board.cols + 1;
                if (board.pokemons[posX][posY] == 0) {
                    i++;
                    board.pokemons[posX][posY] = currentChar;
                    count++;
                }
            }
            currentChar++;
        } else {
            for (int i = 1; i <= board.rows; i++)
                for (int j = 1; j <= board.cols; j++)
                    if (board.pokemons[i][j] == 0) {
                        board.pokemons[i][j] = currentChar;
                        count++;
                    }
            currentChar++;
        }
    }

    // Generate background
    board.bg = new string*[board.rows*3];
    ifstream bg;
    if (board.rows == EASY && board.cols == EASY)
        bg.open("resource\\background\\easy.txt");
    else if (board.rows == MEDIUM && board.cols == MEDIUM)
        bg.open("resource\\background\\medium.txt");
    else if (board.rows == HARD && board.cols == HARD)
        bg.open("resource\\background\\hard.txt");
    if (bg.is_open()) {
        string bgFile;
        for (int i = 0; i < board.rows*3; i++) {
            board.bg[i] = new string[board.cols*8];
            getline(bg, bgFile, '\n');
            for (int j = 0; j < board.cols*8; j++) {
                board.bg[i][j] = bgFile[j];
            }
        }
        bg.close();
    }
}

// Print each cell of board to handle independently
void printCell(GameBoard board, int x, int y, int background_color, int text_color) {
    setColor(background_color, text_color);
    gotoXY((SHORT)((x - 1) * 3 + 3), (SHORT)((y - 1) * 8 + 6));
    cout << "┌     ┐";
    gotoXY((SHORT)((x - 1) * 3 + 4), (SHORT)((y - 1) * 8 + 6));
    if (board.pokemons[x][y])
        cout << "   " << board.pokemons[x][y] << "   ";
    else if (background_color == YELLOW && text_color == BLACK) {
        cout << "   ♥️  ";
    } else {
        setColor(BLACK, RED);
        cout << "   ♥️  ";
        setColor(BLACK, BRIGHT_WHITE);
    }
    gotoXY((SHORT)((x - 1) * 3 + 5), (SHORT)((y - 1) * 8 + 6));
    cout << "└     ┘";
    // set to default
    setColor(BLACK, BRIGHT_WHITE);
}

// To ordinary game, draw background into empty cells 
void drawBG(GameBoard board, int x, int y, int background_color, int text_color) {
    int rows_ = (x - 1) * 3;
    int cols_ = (y - 1) * 7;
    
    setColor(background_color, text_color);
    gotoXY((SHORT)((x - 1) * 3 + 3), (SHORT)((y - 1) * 8 + 6));
    for (int y = cols_; y < cols_ + 7; y++) 
        cout << board.bg[rows_][y];
    gotoXY((SHORT)((x - 1) * 3 + 4), (SHORT)((y - 1) * 8 + 6));
    for (int y = cols_; y < cols_ + 7; y++) 
        cout << board.bg[rows_ + 1][y];
    gotoXY((SHORT)((x - 1) * 3 + 5), (SHORT)((y - 1) * 8 + 6));
    for (int y = cols_; y < cols_ + 7; y++) 
        cout << board.bg[rows_ + 2][y];
    // set to default
    setColor(BLACK, BRIGHT_WHITE);
}

// Print border of game board
void printBorder(GameBoard board) {
    setColor(BLACK, BRIGHT_WHITE);

    gotoXY(0, 0);                           // Print top border
    cout << "╔═════";
    gotoXY(0, 6);
    for (int i = 1; i < board.cols; i++)
        cout << "════════";
    cout << "════════════╗";

    gotoXY(5 + 3 * board.rows, 0);          // Print bottom border
    cout << "╚═════";
    gotoXY(5 + 3 * board.rows, 6);
    for (int i = 1; i < board.cols; i++)
        cout << "════════";
    cout << "════════════╝";

    gotoXY(1, 0);                           // Print left border
    cout << "║     ";
    gotoXY(2, 0);
    cout << "║     ";
    for (int i = 0; i < board.rows; i++) {
        gotoXY(i * 3 + 3, 0);
        cout << "║     ";
        gotoXY(i * 3 + 4, 0);
        cout << "║     ";
        gotoXY(i * 3 + 5, 0);
        cout << "║     ";
    }
    gotoXY(3 + 3 * board.rows, 0);
    cout << "║     ";
    gotoXY(4 + 3 * board.rows, 0);
    cout << "║     ";

    gotoXY(1, 13 + 8 * (board.cols - 1));   // Print right border
    cout << "     ║";
    gotoXY(2, 13 + 8 * (board.cols - 1));
    cout << "     ║";
    for (int i = 0; i < board.rows; i++) {
        gotoXY(i * 3 + 3, 13 + 8 * (board.cols - 1));
        cout << "     ║";
        gotoXY(i * 3 + 4, 13 + 8 * (board.cols - 1));
        cout << "     ║";
        gotoXY(i * 3 + 5, 13 + 8 * (board.cols - 1));
        cout << "     ║";
    }
    gotoXY(3 + 3 * board.rows, 13 + 8 * (board.cols - 1));
    cout << "     ║";
    gotoXY(4 + 3 * board.rows, 13 + 8 * (board.cols - 1));
    cout << "     ║";

}

// Print game board (synthesize printCell and drawBG to show game board)
void printGameBoard(GameBoard &board, Position pCurrent, int level) {
    setColor(BLACK, BRIGHT_WHITE);
    switch(level) {
        case 1 :
            break;
        case 2 :
            level2(board);
            break;
        case 3 :
            level3(board);
            break;
        case 4 :
            level4(board);
            break;
        case 5 :
            level5(board);
            break;    
    }
    // Print top space
    for (int i = 1; i <= 2; i++) {
        gotoXY(i, 1);
        cout << "      ";
        gotoXY(i, 6);
        for (int j = 1; j < board.cols; j++)
            cout << "        ";
        cout << "            ";
    }
    // Print bottom space
    for (int i = 3 + 3 * board.rows; i <= 4 + 3 * board.rows; i++) {
        gotoXY(i, 1);
        cout << "      ";
        gotoXY(i, 6);
        for (int j = 1; j < board.cols; j++)
            cout << "        ";
        cout << "            ";
    }
    // Print left space
    gotoXY(1, 1);                           // Print left border
    cout << "     ";
    gotoXY(2, 1);
    cout << "     ";
    for (int i = 0; i < board.rows; i++) {
        gotoXY(i * 3 + 3, 1);
        cout << "     ";
        gotoXY(i * 3 + 4, 1);
        cout << "     ";
        gotoXY(i * 3 + 5, 1);
        cout << "     ";
    }
    gotoXY(3 + 3 * board.rows, 1);
    cout << "     ";
    gotoXY(4+ 3 * board.rows, 1);
    cout << "     ";
    // Print right space
    gotoXY(1, 13 + 8 * (board.cols - 1));   // Print right border
    cout << "     ";
    gotoXY(2, 13 + 8 * (board.cols - 1));
    cout << "     ";
    for (int i = 0; i < board.rows; i++) {
        gotoXY(i * 3 + 3, 13 + 8 * (board.cols - 1));
        cout << "     ";
        gotoXY(i * 3 + 4, 13 + 8 * (board.cols - 1));
        cout << "     ";
        gotoXY(i * 3 + 5, 13 + 8 * (board.cols - 1));
        cout << "     ";
    }
    gotoXY(3 + 3 * board.rows, 13 + 8 * (board.cols - 1));
    cout << "     ";
    gotoXY(4 + 3 * board.rows, 13 + 8 * (board.cols - 1));
    cout << "     ";

    // Print game board
    for (int i = 1; i <= board.rows; i++)
        for (int j = 1; j <= board.cols; j++)
            // Cell that player move cursor to 
            if (i == pCurrent.posX && j == pCurrent.posY) {
                if (board.pokemons[i][j])
                    printCell(board, i, j, YELLOW, BLACK);
                else 
                    if ((board.rows == EASY && board.cols == EASY) || (board.rows == MEDIUM && board.cols == MEDIUM) || (board.rows == HARD && board.cols == HARD))
                        drawBG(board, i, j, YELLOW, BLACK);
                    else 
                        printCell(board, i, j, YELLOW, BLACK);
            // Cell that player chose
            } else if (board.highlighted[i][j]) {
                if (board.pokemons[i][j])
                    printCell(board, i, j, LIGHT_AQUA, BLACK);
                else 
                    if ((board.rows == EASY && board.cols == EASY) || (board.rows == MEDIUM && board.cols == MEDIUM) || (board.rows == HARD && board.cols == HARD))
                        drawBG(board, i, j, BLACK, BRIGHT_WHITE);
                    else 
                        printCell(board, i, j, BLACK, BRIGHT_WHITE);
            // Is not two cases above
            } else {
                if (board.pokemons[i][j])
                    printCell(board, i, j, BLACK, (int)board.pokemons[i][j] % 7 + 9);
                else 
                    if ((board.rows == EASY && board.cols == EASY) || (board.rows == MEDIUM && board.cols == MEDIUM) || (board.rows == HARD && board.cols == HARD))
                        drawBG(board, i, j, BLACK, BRIGHT_WHITE);
                    else 
                        printCell(board, i, j, BLACK, BRIGHT_WHITE);
            }
}

// Free memory of GameBoard.pokemons and GameBoard.highlighted
void freeMemory(GameBoard &board) {
    for (int i = 0; i < board.rows + 2; i++) {
        delete[] board.pokemons[i];
        delete[] board.highlighted[i];
    }
    delete[] board.pokemons;
    delete[] board.highlighted;
}

// Free memory of GameBoard.bg
void freeBG(GameBoard &board) {
    for (int i = 0; i < board.rows * 3; i++)
        delete[] board.bg[i];
    delete[] board.bg;
}

/////////////////////////////////
/*  PART 3: HANDLE GAME LOGIC  */
/////////////////////////////////

// Check if the choice is not NULL
bool isLegalChoice(GameBoard board, Position pCurrent) {
    if (board.pokemons[pCurrent.posX][pCurrent.posY] == 0)
        return false;   // If NULL, then return false
    return true;        // Else return true
}

// Check if game is over
bool isOver(GameBoard board) {
    const int border = 2;

    for (int i = 0; i < board.rows + border; i++)
        for (int j = 0; j < board.cols + border; j++)
            if (board.pokemons[i][j] != 0)
                return false;
    return true;
}

// Horizontal line check
bool checkLineX(GameBoard board, int y1, int y2, int x) {
    // Find point max + min
    int minVal = min(y1, y2);
    int maxVal = max(y1, y2);
    // Run column
    for (int y = minVal + 1; y < maxVal; y++) 
        if (board.pokemons[x][y] != 0) // if see barrier then false
            return false;
    // not false > true
    return true;
}

// Vertical line check
bool checkLineY(GameBoard board, int x1, int x2, int y) {
    // Find point max + min
    int minVal = min(x1, x2);
    int maxVal = max(x1, x2);
    // Run row
    for (int x = minVal + 1; x < maxVal; x++)
        if (board.pokemons[x][y] != 0) // if see barrier then false
            return false;
    // not false > true
    return true;
}

// Check the horizontal rectangle
int checkRectX(GameBoard board, Position p1, Position p2) {
    // Find point have y min and max
    Position pMinY = p1, pMaxY = p2;
    if (p1.posY > p2.posY) {
        pMinY = p2;
        pMaxY = p1;
    }
    // Find line and y begin 
    for (int y = pMinY.posY; y <= pMaxY.posY; y++) {
        if (y > pMinY.posY && board.pokemons[pMinY.posX][y] != 0)
            return -1;

        // Check two lines
        if ((board.pokemons[pMaxY.posX][y] == 0 || y == pMaxY.posY)
                && checkLineY(board, pMinY.posX, pMaxY.posX, y)
                && checkLineX(board, y, pMaxY.posY, pMaxY.posX)) 
            return y;
    }
    // Have a line in 3 line 
    return -1;
}

// Check the vertical rectangle
int checkRectY(GameBoard board, Position p1, Position p2) {
    // Find point have x min and max
    Position pMinX = p1, pMaxX = p2;
    if (p1.posX > p2.posX) {
        pMinX = p2;
        pMaxX = p1;
    }
    // Find line and x begin
    for (int x = pMinX.posX; x <= pMaxX.posX; x++) {
        if (x > pMinX.posX && board.pokemons[x][pMinX.posY] != 0)
            return -1;
        // Check two lines
        if ((board.pokemons[x][pMaxX.posY] == 0 || x == pMaxX.posX)
                && checkLineX(board, pMinX.posY, pMaxX.posY, x)
                && checkLineY(board, x, pMaxX.posX, pMaxX.posY))
            return x;
    }
    // Have a line in 3 line 
    return -1;
}

// Check more horizontal line
int checkMoreLineX(GameBoard board, Position p1, Position p2, int type) {
    // Find point have y min and max
    Position pMinY = p1, pMaxY = p2;
    if (p1.posY > p2.posY) {
        pMinY = p2;
        pMaxY = p1;
    }
    // Find line and y begin + col finish 
    int y = pMaxY.posY + type;
    int row = pMinY.posX;
    int colFinish = pMaxY.posY;
    if (type == -1) {
        colFinish = pMinY.posY;
        y = pMinY.posY + type;
        row = pMaxY.posX;
    }
    // Check more line
    if ((board.pokemons[row][colFinish] == 0 || pMinY.posY == pMaxY.posY)
            && checkLineX(board, pMinY.posY, pMaxY.posY, row)) 
        while (board.pokemons[pMinY.posX][y] == 0
                && board.pokemons[pMaxY.posX][y] == 0) {
            if (checkLineY(board, pMinY.posX, pMaxY.posX, y))
                return y;
            y += type;
        }
    // if do not have line match > false
    return -1;
}

// Check more vertical line
int checkMoreLineY(GameBoard board, Position p1, Position p2, int type) {
    // Find point have x min and max
    Position pMinX = p1, pMaxX = p2;
    if (p1.posX > p2.posX) {
        pMinX = p2;
        pMaxX = p1;
    }
    // Find line and x begin + row finish 
    int x = pMaxX.posX + type;
    int col = pMinX.posY;
    int rowFinish = pMaxX.posX;
    if  (type == -1) {
        rowFinish = pMinX.posX;
        x = pMinX.posX + type;
        col = pMaxX.posY;
    }
    // Check more line
    if ((board.pokemons[rowFinish][col] == 0 || pMinX.posX == pMaxX.posX)
            && checkLineY(board, pMinX.posX, pMaxX.posX, col))
        while (board.pokemons[x][pMinX.posY] == 0
                && board.pokemons[x][pMaxX.posY] == 0) {
            if (checkLineX(board, pMinX.posY, pMaxX.posY, x))
                return x;
            x += type;
        }
    // if do not have line match > false
    return -1;
}

// Check if two pokemons can be connected by below functions
bool canBeConnected(GameBoard board, Position p1, Position p2) {
    // Check if 2 pokemons are same
    if (board.pokemons[p1.posX][p1.posY] == board.pokemons[p2.posX][p2.posY]) {
        // Check Line X
        if (p1.posX == p2.posX)
            if (checkLineX(board, p1.posY, p2.posY, p1.posX)) 
                return true;
            
        // Check Line Y
        if (p1.posY == p2.posY)
            if (checkLineY(board, p1.posX, p2.posX, p1.posY))
                return true;
            
        // Check Rect X
        if (checkRectX(board, p1, p2) != -1)
            return true;
        

        // Check Rect Y
        if (checkRectY(board, p1, p2) != -1)
            return true;
        

        // Check More Left
        if (checkMoreLineX(board, p1, p2, -1) != -1)
            return true;
        

        // Check More Right
        if (checkMoreLineX(board, p1, p2, 1) != -1)
            return true;
        

        // Check More Up
        if (checkMoreLineY(board, p1, p2, -1) != -1)
            return true;
        

        // Check More Down
        if (checkMoreLineY(board, p1, p2, 1) != -1)
            return true;

    } 
    return false;
}

// Count the number of cases that can be connected
int countCheckToShuffle(GameBoard &board) {
    int count = 0;
    
    for (int i = 1; i <= board.rows; i++) {
        for (int j = 1; j <= board.cols; j++) {
            for (int k = i; k <= board.rows; k++) {
                int l_start = (k == i) ? (j+1) : 0;
                for (int l = l_start; l <= board.cols; l++) {
                    if (canBeConnected(board, {i, j}, {k, l}) && isLegalChoice(board, {i, j}) && isLegalChoice(board, {k, l})) 
                        count++;
                }
            }
        }
    }
    return count;
}

// Shuffle board (Called when players enter button or when game cannot continue)
void shuffleBoard(GameBoard &board) {
    srand(time(NULL));
    for (int i = board.rows; i >= 1; i--)
        for (int j = board.cols; j >= 1; j--) {
            int rand_row = rand() % i + 1;
            int rand_col = rand() % j + 1;
            swap(board.pokemons[i][j], board.pokemons[rand_row][rand_col]);
        }
}

// Move suggestion (Called when players enter button)
void moveSuggestion(GameBoard &board) {
    for (int i = 1; i <= board.rows; i++) {
        for (int j = 1; j <= board.cols; j++) {
            for (int k = i; k <= board.rows; k++) {
                int l_start = (k == i) ? (j + 1) : 0;
                for (int l = l_start; l <= board.cols; l++) {
                    if (canBeConnected(board, {i, j}, {k, l}) && isLegalChoice(board, {i, j}) && isLegalChoice(board, {k, l})) {
                        // Change color cell suggested
                        printCell(board, i, j, LIGHT_PURPLE, BRIGHT_WHITE);
                        printCell(board, k, l, LIGHT_PURPLE, BRIGHT_WHITE); 
                        Sleep(1000);    // Sleep 1s for player can see

                        // reset to default color
                        printCell(board, i, j, BLACK, (int)board.pokemons[i][j] % 7 + 9);
                        printCell(board, k, l, BLACK, (int)board.pokemons[k][l] % 7 + 9);

                        return;
                    }
                }
            }
        }
    }
}

//////////////////////////////////////////
/*  PART 4: DRAW LINE (VISUAL EFFECTS)  */
//////////////////////////////////////////

// Draw 🠜
void drawArrowXFrom(GameBoard board, Position p) {
    gotoXY((SHORT)(4 + (p.posX-1) * 3), (SHORT)(9 + (p.posY-1) * 8));
    cout << "🠜";
}

// Draw 🠞
void drawArrowXTo(GameBoard board, Position p) {
    gotoXY((SHORT)(4 + (p.posX-1) * 3), (SHORT)(9 + (p.posY-1) * 8));
    cout << "🠞";
}

// Draw 🠝
void drawArrowYFrom(GameBoard board, Position p) {
    gotoXY((SHORT)(4 + (p.posX-1) * 3), (SHORT)(9 + (p.posY-1) * 8));
    cout << "🠝";
}

// Draw 🠟
void drawArrowYTo(GameBoard board, Position p) {
    gotoXY((SHORT)(4 + (p.posX-1) * 3), (SHORT)(9 + (p.posY-1) * 8));
    cout << "🠟";
}

// Draw horizontal line
void drawLineX(GameBoard board, int y1, int y2, int x) {
    int minVal = min(y1, y2);
    int maxVal = max(y1, y2);
    gotoXY((SHORT)(4 + (x-1) * 3), (SHORT)(10 + (minVal-1) * 8));
    for (int y = minVal; y < maxVal; y++)
        cout << "-------";
}

// Draw vertical line
void drawLineY(GameBoard board, int x1, int x2, int y) {    
    int fromX = 5 + (min(x1, x2) - 1) * 3;
    int toX   = 4 + (max(x1, x2) - 1) * 3;

    for (int x = fromX; x < toX; x++) {
        gotoXY((SHORT)(x), (SHORT)(9 + (y-1) * 8));
        cout << "|";
    }
}

// Synthesize functions to draw line from the first pokemon to the second one
int drawLine(GameBoard board, Position p1, Position p2) {
    setColor(BLACK, BRIGHT_WHITE);
    if (canBeConnected(board, p1, p2)) {
        // Check Line X
        if (p1.posX == p2.posX) {
            if (checkLineX(board, p1.posY, p2.posY, p1.posX)) {
                Position pMinY = p1, pMaxY = p2;
                if (p1.posY > p2.posY) {
                    pMinY = p2;
                    pMaxY = p1;
                }
                drawArrowXFrom(board, pMinY);
                drawArrowXTo(board, pMaxY);
                drawLineX(board, p1.posY, p2.posY, p1.posX);
                Sleep(200);
                return 1;
            }
        }
        // Check Line Y
        if (p1.posY == p2.posY) {
            if (checkLineY(board, p1.posX, p2.posX, p1.posY)) {
                Position pMinX = p1, pMaxX = p2;
                if (p1.posX > p2.posX) {
                    pMinX = p2;
                    pMaxX = p1;
                }
                drawArrowYFrom(board, pMinX);
                drawArrowYTo(board, pMaxX);
                drawLineY(board, p1.posX, p2.posX, p1.posY);
                Sleep(200);
                return 1;
            }
        }
        // Check Rect X
        if (checkRectX(board, p1, p2) != -1) {
            int y = checkRectX(board, p1, p2);
            Position pMinX = p1, pMaxX = p2;
            if (p1.posX > p2.posX) {
                    pMinX = p2;
                    pMaxX = p1;
            }
            int minYUp = min(pMinX.posY, y);
            int maxYUp = max(pMinX.posY, y);
            int minYDown = min(pMaxX.posY, y);
            int maxYDown = max(pMaxX.posY, y);
            
            if (pMinX.posY < pMaxX.posY) {
                if (y == pMaxX.posY) {
                    drawArrowXFrom(board, pMinX);
                    drawArrowYTo(board, pMaxX);
                    // draw horizontal line
                    drawLineX(board, minYUp, maxYUp, pMinX.posX);
                    // draw vertical line
                    drawLineY(board, pMinX.posX, pMaxX.posX, y);
                    Sleep(200);
                    return 2;
                } else if (y == pMinX.posY) {
                    drawArrowYFrom(board, pMinX);
                    drawArrowXTo(board, pMaxX);
                    // draw vertical line
                    drawLineY(board, pMinX.posX, pMaxX.posX, y);
                    // draw horizontal line
                    drawLineX(board, minYDown, maxYDown, pMaxX.posX);
                    Sleep(200);
                    return 2;
                } else {
                    drawArrowXFrom(board, pMinX);
                    drawArrowXTo(board, pMaxX);
                    // draw up-line
                    drawLineX(board, minYUp, maxYUp, pMinX.posX);
                    // draw vertical line
                    drawLineY(board, pMinX.posX, pMaxX.posX, y);
                    // draw down-line
                    drawLineX(board, minYDown, maxYDown, pMaxX.posX);
                    Sleep(200);
                    return 4;
                }
            } else {
                if (y == pMaxX.posY) {
                    drawArrowXTo(board, pMinX);
                    drawArrowYTo(board, pMaxX);
                    // draw horizontal line
                    drawLineX(board, minYUp, maxYUp, pMinX.posX);
                    // draw vertical line
                    drawLineY(board, pMinX.posX, pMaxX.posX, y);
                    Sleep(200);
                    return 2;
                } else if (y == pMinX.posY) {
                    drawArrowYFrom(board, pMinX);
                    drawArrowXFrom(board, pMaxX);
                    // draw vertical line
                    drawLineY(board, pMinX.posX, pMaxX.posX, y);
                    // draw horizontal line
                    drawLineX(board, minYDown, maxYDown, pMaxX.posX);
                    Sleep(200);
                    return 2;
                } else {
                    drawArrowXTo(board, pMinX);
                    drawArrowXFrom(board, pMaxX);
                    // draw up-line
                    drawLineX(board, minYUp, maxYUp, pMinX.posX);
                    // draw vertical line
                    drawLineY(board, pMinX.posX, pMaxX.posX, y);
                    // draw down-line
                    drawLineX(board, minYDown, maxYDown, pMaxX.posX);
                    Sleep(200);
                    return 4;
                }
            }
        }
        // Check Rect Y
        if (checkRectY(board, p1, p2) != -1) {
            int x = checkRectY(board, p1, p2);
            Position pMinY = p1, pMaxY = p2;
            if (p1.posY > p2.posY) {
                pMinY = p2;
                pMaxY = p1;
            }
            int minXLeft = min(pMinY.posX, x);
            int maxXLeft = max(pMinY.posX, x);
            int minXRight = min(pMaxY.posX, x);
            int maxXRight = max(pMaxY.posX, x);
            if (pMinY.posX < pMaxY.posX) {
                drawArrowYFrom(board, pMinY);
                drawArrowYTo(board, pMaxY);
                // draw left-line
                drawLineY(board, minXLeft, maxXLeft, pMinY.posY);
                // draw horizontal line
                drawLineX(board, pMinY.posY, pMaxY.posY, x);
                // draw right-line
                drawLineY(board, minXRight, maxXRight, pMaxY.posY);
                Sleep(200);
                return 4;
            } else {
                drawArrowYFrom(board, pMaxY);
                drawArrowYTo(board, pMinY);
                // draw right-line
                drawLineY(board, minXRight, maxXRight, pMaxY.posY);
                // draw horizontal line
                drawLineX(board, pMinY.posY, pMaxY.posY, x);
                // draw left-line
                drawLineY(board, minXLeft, maxXLeft, pMinY.posY);
                Sleep(200);
                return 4;
            }
        }
        // Check More Left
        if (checkMoreLineX(board, p1, p2, -1) != -1) {
            int y = checkMoreLineX(board, p1, p2, -1);
            Position pMinX = p1, pMaxX = p2;
            if (p1.posX > p2.posX) {
                    pMinX = p2;
                    pMaxX = p1;
            }
            drawArrowXTo(board, pMinX);
            drawArrowXTo(board, pMaxX);
            // draw up-line
            drawLineX(board, y, pMinX.posY, pMinX.posX);
            // draw vertical line
            drawLineY(board, pMinX.posX, pMaxX.posX, y);
            // draw down-line
            drawLineX(board, y, pMaxX.posY, pMaxX.posX);
            Sleep(200);
            return 3;
        }
        // Check More Right
        if (checkMoreLineX(board, p1, p2, 1) != -1){
            int y = checkMoreLineX(board, p1, p2, 1);
            Position pMinX = p1, pMaxX = p2;
            if (p1.posX > p2.posX) {
                    pMinX = p2;
                    pMaxX = p1;
            }
            drawArrowXFrom(board, pMinX);
            drawArrowXFrom(board, pMaxX);
            // draw up-line
            drawLineX(board, y, pMinX.posY, pMinX.posX);
            // draw vertical line
            drawLineY(board, pMinX.posX, pMaxX.posX, y);
            // draw down-line
            drawLineX(board, y, pMaxX.posY, pMaxX.posX);
            Sleep(200);
            return 3;
        }
        // Check More Up
        if (checkMoreLineY(board, p1, p2, -1) != -1){
            int x = checkMoreLineY(board, p1, p2, -1);
            Position pMinY = p1, pMaxY = p2;
            if (p1.posY > p2.posY) {
                pMinY = p2;
                pMaxY = p1;
            }
            drawArrowYTo(board, pMinY);
            drawArrowYTo(board, pMaxY);
            // draw left-line
            drawLineY(board, x, pMinY.posX, pMinY.posY);
            // draw horizontal line
            drawLineX(board, pMinY.posY, pMaxY.posY, x);
            // draw right-line
            drawLineY(board, x, pMaxY.posX, pMaxY.posY);
            Sleep(200);
            return 3;
        }
        // Check More Down
        if (checkMoreLineY(board, p1, p2, 1) != -1){
            int x = checkMoreLineY(board, p1, p2, 1);
            Position pMinY = p1, pMaxY = p2;
            if (p1.posY > p2.posY) {
                pMinY = p2;
                pMaxY = p1;
            }
            drawArrowYFrom(board, pMinY);
            drawArrowYFrom(board, pMaxY);
            // draw left-line
            drawLineY(board, x, pMinY.posX, pMinY.posY);
            // draw horizontal line
            drawLineX(board, pMinY.posY, pMaxY.posY, x);
            // draw right-line
            drawLineY(board, x, pMaxY.posX, pMaxY.posY);
            Sleep(200);
            return 3;
        }
    }
    return 0;
}

/////////////////////////////////////////
/*  PART 5: DRAW AND HANDLE INTERFACE  */
/////////////////////////////////////////

// Update time countdown
void countdown(time_t originalTime, int timeLeft, bool &overTime) {
    time_t nowTime = time(0);
    timeLeft -= difftime(nowTime, originalTime);
    if (timeLeft <= 0)
        overTime = true;
    
    gotoXY(16, 89);                             // Time left
    cout << setw(3) << setfill(' ') << timeLeft << "s";
}

// Draw information board to show player's information, game information, etc.
void drawIn4Board(GameBoard board, string cur_player, vector<Save> saveG, int level) {
    // Draw initial information'
    setColor(BLACK, BRIGHT_WHITE);
    gotoXY(0, 75);
    cout << "║                           ║";
    gotoXY(1, 75);
    cout << "║╔═════════════════════════╗║";
    gotoXY(2, 75);
    cout << "║║   Player's information  ║║";
    gotoXY(3, 75);
    cout << "║╠══════════╦══════════════╣║";
    gotoXY(4, 75);
    cout << "║║ username ║              ║║";
    gotoXY(5, 75);
    cout << "║╠══════════╬══════════════╣║";
    gotoXY(6, 75);
    cout << "║║  score   ║              ║║";
    gotoXY(7, 75);
    cout << "║╚══════════╩══════════════╝║";
    gotoXY(8, 75);
    cout << "║                           ║";
    gotoXY(9, 75);
    cout << "║╔═════════════════════════╗║";
    gotoXY(10, 75);
    cout << "║║     Game information    ║║";
    gotoXY(11, 75);
    cout << "║╠═════════════════════════╣║";
    gotoXY(12, 75);
    cout << "║║                         ║║";
    gotoXY(13, 75);
    cout << "║║                         ║║";
    gotoXY(14, 75);
    cout << "║║                         ║║";
    gotoXY(15, 75);
    cout << "║╠═════════════════════════╣║";
    gotoXY(16, 75);
    cout << "║║  Time :                 ║║";
    gotoXY(17, 75);
    cout << "║╚═════════════════════════╝║";
    gotoXY(18, 75);
    cout << "║                           ║";
    gotoXY(19, 75);
    cout << "║                           ║";
    gotoXY(20, 75);
    cout << "║╔═════════════════════════╗║";
    gotoXY(21, 75);
    cout << "║║   O : Pause             ║║";
    gotoXY(22, 75);
    cout << "║╠═════════════════════════╣║";
    gotoXY(23, 75);
    cout << "║║   U : Help              ║║";
    gotoXY(24, 75);
    cout << "║╠═════════════════════════╣║";
    gotoXY(25, 75);
    cout << "║║   Y : Move Suggestion   ║║";
    gotoXY(26, 75);
    cout << "║╠═════════════════════════╣║";
    gotoXY(27, 75);
    cout << "║║   T : Shuffle Board     ║║";
    gotoXY(28, 75);
    cout << "║╚═════════════════════════╝║";
    gotoXY(29, 75);
    cout << "║                           ║";
    
    gotoXY(4, 89);                              // fill username
    cout << cur_player;
    gotoXY(6, 89);                              // fill total score
    cout << getCurScore(saveG, cur_player);
    gotoXY(12, 86);                             // fill game level
    cout << "level " << level;

}

// Input character and handle event
void handleEvent(GameBoard &board, Position &pCurrent, Position &p1, Position &p2, string cur_player, vector<Save> &saveG, int &pointAtBoard, int level, bool &finished) {
    // Supportive variables
    int selected;
    char *ch = new char;

    // Handle event
    switch(*ch = _getCh()) {
        case UP_KEY :
                if (pCurrent.posX > 1)
                    pCurrent.posX--;
                else 
                    pCurrent.posX = board.rows;
                break;
            
            case DOWN_KEY :
                if (pCurrent.posX < board.rows)
                    pCurrent.posX++;
                else
                    pCurrent.posX = 1;
                break;
            
            case LEFT_KEY :
                if (pCurrent.posY > 1)
                    pCurrent.posY--;
                else 
                    pCurrent.posY = board.cols;
                break;
            
            case RIGHT_KEY :
                if (pCurrent.posY < board.cols)
                    pCurrent.posY++;
                else 
                    pCurrent.posY = 1;
                break;
            
            // Move Suggestion > -3
            case 'Y' : case 'y' :
                moveSuggestion(board);
                gotoXY(13, 77);
                cout << "     Move Suggestion     ";
                gotoXY(14, 77);
                cout << "            -3           ";
                pointAtBoard -= 3;
                break;

            // Pause
            case 'O' : case 'o' :
            {    
                selected = 0;
                bool resume_ = false;
                // Clear screen and print pause menu
                ClearScreen();
                pauseMenu(selected);
                while (!resume_) {
                    *ch = _getCh();
                    switch(*ch) {
                        case UP_KEY :
                            if (selected > 0)
                                selected--;
                            else 
                                selected = 2;
                            break;
                        
                        case DOWN_KEY :
                            if (selected < 2)
                                selected++;
                            else 
                                selected = 0;
                            break;

                        case ENTER_KEY :
                            // Player choose to resume
                            if (selected == 0) 
                                resume_ = true;

                            // Player choose to restart
                            if (selected == 1) {
                                ClearScreen();
                                freeMemory(board);
                                freeBG(board);
                                board.rows = board.rows;
                                board.cols = board.cols;
                                handleGameBoard(board, cur_player, saveG, level, finished);
                            }

                            // Player choose to exit
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
                    // Update screen
                    ClearScreen();
                    pauseMenu(selected);
                    
                }
                ClearScreen();
                printBorder(board);
                drawIn4Board(board, cur_player, saveG, level);
                break;
            }
            
            // Shuffle board > -3
            case 'T' : case 't' :
                // Clear screen and shuffle board
                ClearScreen();
                shuffleSound();
                gotoXY(12, 28);
                cout << "╔══════════════════════════════════════════╗";
                gotoXY(13, 28);
                cout << "║   SHUFFLE GAME BOARD HAS TURNED ON . . . ║";
                gotoXY(14, 28);
                cout << "╚══════════════════════════════════════════╝" << endl;
                Sleep(2000);
                ClearScreen();
                shuffleBoard(board);
                printBorder(board);
                drawIn4Board(board, cur_player, saveG, level);
                gotoXY(13, 77);
                cout << "      Shuffle Board      ";
                gotoXY(14, 77);
                cout << "            -3           ";
                pointAtBoard -= 3;
                break;

            // Help screen
            case 'U' : case 'u' :
                help();
                system("pause");
                ClearScreen();
                printBorder(board);
                drawIn4Board(board, cur_player, saveG, level);
                break;

            case ENTER_KEY :
                if (isLegalChoice(board, pCurrent)) {
                    if (p1.posX == -1 && p1.posX == -1) {
                        p1.posX = pCurrent.posX;
                        p1.posY = pCurrent.posY;
                        board.highlighted[p1.posX][p1.posY] = true;
                        tapSound();
                    } else {
                        p2.posX = pCurrent.posX;
                        p2.posY = pCurrent.posY;
                        board.highlighted[p2.posX][p2.posY] = true;
                        if (p1.posX == p2.posX && p1.posY == p2.posY) {
                            // return default value
                            board.highlighted[p1.posX][p1.posY] = false;
                            board.highlighted[p2.posX][p2.posY] = false;
                            p1.posX = -1; p1.posY = -1; p2.posX = -1; p2.posY = -1;
                        } else {
                            if (canBeConnected(board, p1, p2)) {
                                // Draw line & Update game information
                                successConnectSound();
                                int type = drawLine(board, p1, p2);
                                gotoXY(13, 77);
                                switch (type) {
                                    case 1 :
                                        cout << "        I Matching       ";
                                        gotoXY(14, 77);
                                        cout << "            +1           ";
                                        pointAtBoard += 1;
                                        break;
                                    case 2 :
                                        cout << "        L Matching       ";
                                        gotoXY(14, 77);
                                        cout << "            +1           ";
                                        pointAtBoard += 1;
                                        break;
                                    case 3 :
                                        cout << "        U Matching       ";
                                        gotoXY(14, 77);
                                        cout << "            +1           ";
                                        pointAtBoard += 1;
                                        break;
                                    case 4 :
                                        cout << "        Z Matching       ";
                                        gotoXY(14, 77);
                                        cout << "            +1           ";
                                        pointAtBoard += 1;
                                }

                                // delete cells 
                                board.pokemons[p1.posX][p1.posY] = 0;
                                board.pokemons[p2.posX][p2.posY] = 0;
                            } else {
                                failConnectSound();
                                gotoXY(13, 77);
                                cout << "      Fail Matching      ";
                                gotoXY(14, 77);
                                cout << "            -2           ";
                                pointAtBoard -= 2;
                            }
                            // return default value
                            board.highlighted[p1.posX][p1.posY] = false;
                            board.highlighted[p2.posX][p2.posY] = false;
                            p1.posX = -1; p1.posY = -1; p2.posX = -1; p2.posY = -1;
                        }
                    }
                }
    }
}

// Synthesize two above functions and handle game board
void handleGameBoard(GameBoard &board, string cur_player, vector<Save> &saveG, int level, bool &finished) {
    // Supportive variables
    char* ch = new char;
    time_t originalTime = time(0);
    int timeLeft = ((board.rows * board.cols) / 2) * 5;
    bool overTime = false;
    int cur_point = getCurScore(saveG, cur_player);
    int pointAtBoard = 0;

    // Generate + Print initial board 
    generateGameBoard(board);
    Position pCurrent, p1 , p2;
    pCurrent.posX = (board.rows + 2) / 2;
    pCurrent.posY = (board.cols + 2) / 2;
    p1.posX = -1; p1.posY = -1; p2.posX = -1; p2.posY = -1;

    printBorder(board);
    printGameBoard(board, pCurrent, level);
    drawIn4Board(board, cur_player, saveG, level);

    while (!isOver(board) && !overTime) {
        int count = countCheckToShuffle(board); // Count the number of cases that can be connected
        if (count == 0 && !isOver(board)) {     // Check if count = 0, then call shuffleBoard();
            ClearScreen();
            shuffleSound();
            gotoXY(12, 28);
            cout << "╔═══════════════════════════════════════════════╗";
            gotoXY(13, 28);
            cout << "║   AUTO SHUFFLE GAME BOARD HAS TURNED ON . . . ║";
            gotoXY(14, 28);
            cout << "╚═══════════════════════════════════════════════╝" << endl;
            Sleep(2000);
            ClearScreen();
            shuffleBoard(board);
            printBorder(board);
            drawIn4Board(board, cur_player, saveG, level);
            gotoXY(13, 77);
            cout << "      Shuffle Board      ";
            gotoXY(14, 77);
            cout << "            -3           ";
            pointAtBoard -= 3;
        }
        
        printGameBoard(board, pCurrent, level);
        countdown(originalTime, timeLeft, overTime);
        if (kbhit()) {
            handleEvent(board, pCurrent, p1, p2, cur_player, saveG, pointAtBoard, level, finished);
        }
    }

    // After finish game
    if (isOver(board)) {
        ClearScreen();  // Clear screen
        gotoXY(12, 28);     
        cout << "╔═══════════════════════════════════════════════╗";
        gotoXY(13, 28);
        cout << "║    CONGRATULATIONS! YOU WON THIS GAME . . .   ║";
        gotoXY(14, 28);
        cout << "╚═══════════════════════════════════════════════╝" << endl;
        Sleep(2000);
        finished = true;
        pointAtBoard = pointAtBoard * level;
        cur_point += pointAtBoard;
        updateSaveFile(saveG, cur_player, cur_point);
    } else {
        ClearScreen();  // Clear screen
        gotoXY(12, 28);     
        cout << "╔═══════════════════════════════════════════════╗";
        gotoXY(13, 28);
        cout << "║            GOOD LUCK NEXT TIME . . .          ║";
        gotoXY(14, 28);
        cout << "╚═══════════════════════════════════════════════╝" << endl;
        Sleep(2000);
        finished = false;
    }

    // Free dynamical allocated memory
    freeMemory(board);
    if ((board.rows == 4 && board.cols == 4) || (board.rows == 6 && board.cols == 6) || (board.rows == 8 && board.cols == 8))
        freeBG(board);
    delete ch;
}

// After game board selection, including: next level, restart, back
void afterGame(GameBoard &board, int &level, bool &back_, bool &finished) {
    int selected = 0;
    char* ch = new char;
    bool outLoop = false;

    ClearScreen();
    if (finished == true) {
        afterGameOption(selected);
        while (true) {
            *ch = _getCh();
            ClearScreen();
            switch(*ch) {
                case UP_KEY :
                    if (selected > 0)
                        selected--;
                    else 
                        selected = 2;
                    break;
                
                case DOWN_KEY :
                    if (selected < 2)
                        selected++;
                    else 
                        selected = 0;
                    break;

                case ENTER_KEY :
                    // Player choose to play next level
                    if (selected == 0) {
                        level++;
                    }
                    // Player choose to restart
                    if (selected == 1) {
                        level = level;
                        generateGameBoard(board);
                    }
                    // Player choose to back
                    if (selected == 2)
                        back_ = true;
                    outLoop = true;
            }
            if (outLoop == true)
                break;
            afterGameOption(selected);
        }
    } else {
        failGame(selected);
        while (true) {
            *ch = _getCh();
            ClearScreen();
            switch(*ch) {
                case UP_KEY :
                    if (selected > 0)
                        selected--;
                    else 
                        selected = 2;
                    break;
                
                case DOWN_KEY :
                    if (selected < 2)
                        selected++;
                    else 
                        selected = 0;
                    break;

                case ENTER_KEY :
                    // Player choose to restart
                    if (selected == 0) {
                        level = level;
                    }
                    // Player choose to back
                    if (selected == 1) {
                        back_ = true;
                    }
                    outLoop = true;
            }
            if (outLoop == true)
                break;
            failGame(selected);
        }
    }
    delete ch;
}