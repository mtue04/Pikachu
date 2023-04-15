#include "account.h"

void readData(vector<Player> &listP) {
    ifstream fin("users.dat", ios::binary);

    if(!fin.is_open()) {
        cout << "Cannot open file . . ." << endl;
    } else {
        fin.seekg(0, ios::end);
        int n = fin.tellg() / sizeof(Player); //Number of current player listP;
        fin.seekg(0, ios::beg);

        if (n != 0) {
            for (int i = 0; i < n; i++) {
                Player a;
                fin.read((char *) &a, sizeof(Player));
                listP.push_back(a);
            }
        }
    }

    fin.close();
}

void writeData(vector<Player> &listP) {
    ofstream fout("users.dat", ios::binary);

    for (int i = 0; i < listP.size(); i++)
        fout.write((char *) (&listP[i]), sizeof(Player));

    fout.close();
}

void readSaveFile(vector<Save> &saveG) {
    ifstream fin("save.dat", ios::binary);
    if(!fin.is_open()) {
        cout << "Cannot open file . . ." << endl;
    } else {
        fin.seekg(0, ios::end);
        int n = fin.tellg() / sizeof(Save);
        fin.seekg(0, ios::beg);

        if (n != 0) {
            for (int i = 0; i < n; i++) {
                Save a;
                fin.read((char *) &a, sizeof(Save));
                saveG.push_back(a);
            }
        }
    }

    fin.close();
}

void writeSaveFile(vector<Save> &saveG) {
    ofstream fout("save.dat", ios::binary);

    for (int i = 0; i < saveG.size(); i++)
        fout.write((char *) (&saveG[i]), sizeof(Save));

    fout.close();
}


void updateSaveFile(vector<Save> &saveG, string cur_Player, int score)
{
    bool found = false;
    for (int i = 0; i < saveG.size(); i++)
    {
        if (strcmp(saveG[i].user, cur_Player.c_str()) == 0)
        {
            saveG[i].score = score;
            found = true;
            break;
        }
    }
    if (!found)
    {
        Save temp;
        strcpy(temp.user, cur_Player.c_str());
        temp.score = score;
        saveG.push_back(temp);
    }
    writeSaveFile(saveG);
}

int getCurScore (vector<Save> &saveG, string cur_Player) {
    for (int i = 0; i < saveG.size(); i++) {
        if (strcmp(saveG[i].user, cur_Player.c_str()) == 0) {
            return saveG[i].score;
        }
    }
    return 0;
}

bool isValidUsername(string username) {
    if (isspace(username[0])) {
        return false;
    } else if (username.size() == 0) {
        return false;
    }

    return true;
}

void enterUsername(string &username) {
    char ch;
    int count = 0;
    username = "";
    while (true) {
        ch = _getch();
        if (ch == 13) // Enter key
            break;
        if (ch == 8) { // Backspace key
            if (username.length() > 0) {
                username.pop_back();
                cout << "\b \b";
                count--;
            }
        } else if (ch >= 32 && ch <= 126 && count <= 12) {
            username += ch;
            cout << ch;
            count++;
        }
    }
}

void hidePassword(string &password) {
    char ch;
    int count = 0;
    password = "";
    while (true) {
        ch = _getch();
        if (ch == 13) // Enter key
            break;
        if (ch == 8) { // Backspace key
            if (password.length() > 0) {
                password.pop_back();
                cout << "\b \b";
                count--;
            }
        } else if (ch >= 32 && ch <= 126 && count <= 20) {
            password += ch;
            cout << "*";
            count++;
        }
    }
}

void SignUp(vector<Player> &listP, string &cur_player) {
    // Draw Sign Up screen
    ClearScreen();
    for (int i = 0; i < 8; i++)
        cout << endl;
    cout << "\t\t\t       ╔══════════════════════════════════════════╗" << endl;
    cout << "\t\t\t       ║                  SIGN UP                 ║" << endl;
    cout << "\t\t\t       ╠════════════════╦═════════════════════════╣" << endl;
    cout << "\t\t\t       ║    username    ║                         ║" << endl; // x = 11 ; y = 50
    cout << "\t\t\t       ╠════════════════╬═════════════════════════╣" << endl;
    cout << "\t\t\t       ║    password    ║                         ║" << endl; // x = 13 ; y = 50
    cout << "\t\t\t       ╠════════════════╬═════════════════════════╣" << endl;
    cout << "\t\t\t       ║    confirm     ║                         ║" << endl; // x = 15 ; y = 50
    cout << "\t\t\t       ╚════════════════╩═════════════════════════╝" << endl;
    cout << "\t\t\t  NOTE: Please enter username no more than 12 characters . . ." << endl;

    // 1. username
    Player tempP;
    string username;
    gotoXY(11, 50);
    enterUsername(username);

    // Check if username is valid
    do {
        if (isValidUsername(username) == false) {
            gotoXY(18, 26);
            cout << "Your username is not valid! Please try again . . . " << endl;
            gotoXY(11, 50);
            cout << "                        "; // Clear line
            gotoXY(11, 50);
            enterUsername(username);
        }
    } while (isValidUsername(username) == false);

    strcpy(tempP.username, username.c_str());
    // Check if username exists
    while (true) {
        bool isExisted = false;
        for (int i = 0; i < listP.size(); i++) {
            if (strcmp(tempP.username, listP[i].username) == 0) {
                gotoXY(18, 26);
                cout << "Your username already existed! Please try again . . ." << endl;
                gotoXY(11, 50);
                cout << "                       ";
                gotoXY(11, 50);
                enterUsername(username);
                strcpy(tempP.username ,username.c_str());
                isExisted = true;
                break;
            }
        }
        if (!isExisted)
            break;
        cur_player = tempP.username;
    }

    // 2. password
    string password;
    string re_password;
    gotoXY(13, 50);
    hidePassword(password);


    do {
        gotoXY(15, 50);
        cout << "                        "; // Clear line
        gotoXY(15, 50);
        hidePassword(re_password);

    } while (re_password != password);
    strcpy(tempP.password, password.c_str());

    // 3. Push new date to file
    listP.push_back(tempP);
    ofstream fout("users.dat", ios::binary);
    for (int i = 0; i < listP.size(); i++) {
        fout.write((char *) (&listP[i]), sizeof(Player));
    }
    fout.close();
}

void SignIn(vector<Player> &listP, bool &logInFlag, string &cur_player) {
    // Draw Sign In screen
    ClearScreen();
    for (int i = 0; i < 8; i++)
        cout << endl;
    cout << "\t\t\t       ╔══════════════════════════════════════════╗" << endl;
    cout << "\t\t\t       ║                  SIGN IN                 ║" << endl;
    cout << "\t\t\t       ╠════════════════╦═════════════════════════╣" << endl;
    cout << "\t\t\t       ║    username    ║                         ║" << endl; // x = 11 ; y = 50
    cout << "\t\t\t       ╠════════════════╬═════════════════════════╣" << endl;
    cout << "\t\t\t       ║    password    ║                         ║" << endl; // x = 13 ; y = 50
    cout << "\t\t\t       ╚════════════════╩═════════════════════════╝" << endl;

    string username;
    string password;

    bool usernameFlag = false;  // separate flag for username
    bool passwordFlag = false;  // separate flag for password

    int username_index = 0;     // index for checking password

    // 1. Check username
    gotoXY(11, 50);
    enterUsername(username);
    for (int i = 0; i < listP.size(); i++) {
        if (username == listP[i].username) {
            usernameFlag = true;
            username_index = i;
            break;
        }
    }

    if (usernameFlag == false) {
        // username is incorrect
        int attempt = 5;
        while (attempt > 0) {
            ClearScreen();
            for (int i = 0; i < 8; i++)
                cout << endl;
            cout << "\t\t\t       ╔══════════════════════════════════════════╗" << endl;
            cout << "\t\t\t       ║                  SIGN IN                 ║" << endl;
            cout << "\t\t\t       ╠════════════════╦═════════════════════════╣" << endl;
            cout << "\t\t\t       ║    username    ║                         ║" << endl; // x = 11 ; y = 50
            cout << "\t\t\t       ╠════════════════╬═════════════════════════╣" << endl;
            cout << "\t\t\t       ║    password    ║                         ║" << endl; // x = 13 ; y = 50
            cout << "\t\t\t       ╚════════════════╩═════════════════════════╝" << endl;

            gotoXY(15, 26);
            cout << "Your username is incorrect. Please try again! (" << attempt << " attempts left)" << endl;
            gotoXY(11, 50);
            enterUsername(username);
            for (int i = 0; i < listP.size(); i++) {
                if (username == listP[i].username) {
                    usernameFlag = true;
                    username_index = i;
                    break;
                }
            }

            if (usernameFlag == true)
                break;
            else
                attempt--;
        }

        if (attempt <= 0) {
            logInFlag = false;
            return;
        }
    }

    // 2. Check password
    gotoXY(13, 50);
    hidePassword(password);



    if (password == listP[username_index].password) {
        passwordFlag = true;
    }

    if (passwordFlag == false) {
        // password is incorrect
        int attempt = 5;
        while (attempt > 0) {
            gotoXY(13, 50);
            cout << "                        "; // Clear screen
            gotoXY(15, 26);
            cout << "Your password is incorrect. Please try again! (" << attempt << " attempts left)" << endl;
            gotoXY(13, 50);
            hidePassword(password);

            if (password == listP[username_index].password) {
                passwordFlag = true;
                break;
            }

            attempt--;
        }

        if (attempt <= 0) {
            logInFlag = false;
            return;
        }
    }

    if (passwordFlag == true) {
        logInFlag = true;
        cur_player = username; //Get current player
    }
}

//Used to sort leaderboard
void leaderBoardSorting(vector<Save> &saveG) {
    for (int i = 0; i < saveG.size() - 1; i++)
        for (int j = i + 1; j < saveG.size(); j++)
            if (saveG[i].score < saveG[j].score)
                swap(saveG[i],saveG[j]);
}

void leaderBoardPrinting(vector<Save> &saveG) {
    leaderBoardSorting(saveG);
    // Clear Screen
    ClearScreen();

    // Print leader board
    cout << endl << endl;
    cout << "\t\t\t╔══════════════════════════════════════════════════════════╗" << endl;
    cout << "\t\t\t║                       LEADER BOARD                       ║" << endl;
    cout << "\t\t\t╠══════╦══════════════════════════╦════════════════════════╣" << endl;
    for (int i = 0; i < saveG.size() && i < 10; i++) {
        cout << "\t\t\t║  " << setw(2) << setfill(' ') << i + 1 << "  ║";
        cout << "          " << saveG[i].user;
        for (int j = 0; j < 16 - strlen(saveG[i].user); j++)
            cout << " ";
        cout << "║        " << setw(4) << setfill(' ') << saveG[i].score << "            ║\n";
    }
    cout << "\t\t\t╚══════╩══════════════════════════╩════════════════════════╝" << endl;
    cout << endl << endl;
}
