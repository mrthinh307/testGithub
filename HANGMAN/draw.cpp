#include <bits/stdc++.h>
#include <thread>
#include <chrono>
using namespace std;

const string FIGURE[] =
{
 "   -------------\n"
 "   |                \n"
 "   |                \n"
 "   |                \n"
 "   |                \n"
 "   |     \n"
 " -----\n",
 "   -------------\n"
 "   |           |    \n"
 "   |                \n"
 "   |                \n"
 "   |                \n"
 "   |     \n"
 " -----\n",
 "   -------------\n"
 "   |           |    \n"
 "   |           O    \n"
 "   |                \n"
 "   |                \n"
 "   |     \n"
 " -----\n",
 "   -------------\n"
 "   |           |    \n"
 "   |           O    \n"
 "   |           |    \n"
 "   |                \n"
 "   |     \n"
 " -----\n",
 "   -------------\n"
 "   |           |    \n"
 "   |           O    \n"
 "   |          /|    \n"
 "   |                \n"
 "   |     \n"
 " -----\n",
 "   -------------\n"
 "   |           |    \n"
 "   |           O    \n"
 "   |          /|\\  \n"
 "   |                \n"
 "   |     \n"
 " -----\n",
"   -------------\n"
 "   |           |    \n"
 "   |           O    \n"
 "   |          /|\\  \n"
 "   |          /     \n"
 "   |     \n"
 " -----\n",
// "   -------------\n"
// "   |           |    \n"
// "   |           O    \n"
// "   |          /|\\  \n"
// "   |          / \\  \n"
// "   |     \n"
// " -----\n"
 };

void renderGame(string guessedWord, int badGuessCount, vector<char> v){
    cout << FIGURE[badGuessCount] << endl;
    cout << guessedWord << endl;
    cout << "Number of wrong guesses: " << badGuessCount << endl;
    cout << "Words guessed worng: ";
    for(auto& x : v) cout << x << " ";
    cout << endl;
}

const string& getNextHangMan(){
    const static string figure[]{
 "   ------------+    \n"
 "   |    /           \n"
 "   |    O           \n"
 "   |   /|\\         \n"
 "   |   / \\         \n"
 "   |                \n"
 " -----\n",
 "   ------------+    \n"
 "   |     |          \n"
 "   |     O          \n"
 "   |    /|\\        \n"
 "   |    / \\        \n"
 "   |                \n"
 " -----\n",
 "   ------------+    \n"
 "   |      \\        \n"
 "   |      O         \n"
 "   |     /|\\       \n"
 "   |     / \\       \n"
 "   |                \n"
 " -----\n",
 "   ------------+     \n"
 "   |     |           \n"
 "   |     O           \n"
 "   |    /|\\         \n"
 "   |    / \\         \n"
 "   |                 \n"
 " -----\n"
    };
    const int NUMBER_OF_FIGURES = sizeof(figure) / sizeof(string);
    static int currentFigure = 0;
    return figure[(currentFigure++) % NUMBER_OF_FIGURES];
}

const string& getNextDancingMan(){
    const static string figure[]{
        "     O    \n"
        "    /|\\  \n"
        "    | |   \n",

        "     O    \n"
        "    /|\\  \n"
        "    / \\  \n",

        "    \\O/   \n"
        "     |    \n"
        "    / \\  \n",

        "   __O__  \n"
        "     |    \n"
        "    / \\  \n",

        "     O    \n"
        "    /|\\  \n"
        "    / \\  \n" ,

        "    O     \n"
        "    /|\\  \n"
        "    / \\  \n" ,

        "     O    \n"
        "    /|\\  \n"
        "    / \\  \n" ,

        "      O   \n"
        "    /|\\  \n"
        "    / \\  \n" ,

        "     O    \n"
        "    /|\\  \n"
        "    / \\  \n"

    };
    const int NUMBER_OF_FIGURES = sizeof(figure) / sizeof(string);
    static int currentFigure = 0;
    return figure[(currentFigure++) % NUMBER_OF_FIGURES];
}


void displayFinalResult(bool won, const string& word){       
        if(won){
            cout << "Congratulations! You win!\n\n";
        }
        else    cout << "You lost! The correct word is : " << word << endl << endl;

        cout << (won ? getNextDancingMan() : getNextHangMan());
        this_thread :: sleep_for(chrono :: milliseconds(500));
}

void playAnimation(int badGuessCount, const string& word) {
    auto startTime = chrono::steady_clock::now();

    while (chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - startTime).count() < 10) {
        displayFinalResult(badGuessCount < 7, word);

        this_thread::sleep_for(chrono::milliseconds(500));

        system("cls");
    }
}


