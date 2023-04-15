#include "console.h"

// Function to clear the entire console screen
void ClearScreen(){
    HANDLE                     hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      count;
    DWORD                      cellCount;
    COORD                      homeCoords = { 0, 0 };

    hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    /* Get the number of cells in the current buffer */
    if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
    cellCount = csbi.dwSize.X *csbi.dwSize.Y;

    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(
        hStdOut,
        (TCHAR) ' ',
        cellCount,
        homeCoords,
        &count
    )) return;

    /* Fill the entire buffer with the current colors and attributes */
    if (!FillConsoleOutputAttribute(
        hStdOut,
        csbi.wAttributes,
        cellCount,
        homeCoords,
        &count
    )) return;

    /* Move the cursor home */
    SetConsoleCursorPosition( hStdOut, homeCoords );
}

// Resize window console
void ResizeWindow(int posX, int posY, int width, int height) {
    RECT rectClient, rectWindow;
    HWND hWnd = GetConsoleWindow();
    GetClientRect(hWnd, &rectClient);
    GetWindowRect(hWnd, &rectWindow);
    MoveWindow(hWnd, posX, posY, width, height, TRUE);
}

// Disable the resizing of the console window
void DisableResizeWindow() {
    HWND hWnd = GetConsoleWindow();
    SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_SIZEBOX);
}

// Move the console cursor to the specific position
void gotoXY(SHORT x, SHORT y) {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD position;
    position.Y = x;
    position.X = y;

    SetConsoleCursorPosition(console, position);
}

// Turn the cursor on or off in the console
void OnOffCursor(bool OnOff) {
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = OnOff;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

// Set background color and text color
void setColor(int backgound_color, int text_color) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    int color_code = backgound_color * 16 + text_color;
    SetConsoleTextAttribute(hStdout, color_code);
}

// Synthesize functions to set up console
void SetUpGameConsole() {
    // system("MODE 114, 29");
    SetConsoleTitle(TEXT("Pikachu Onet Connect"));
    ResizeWindow(420, 150, 768, 536);
    SetConsoleOutputCP(65001);
    OnOffCursor(false);
	DisableResizeWindow();
}