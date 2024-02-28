#include <time.h>
#include <windows.h>
#include <bits/stdc++.h>

#include "draw.h"

using namespace std;

long long numberOfWords(){
    ifstream file;
    file.open("dictionary.txt");
    if(file.fail()){
        cout << "Cannot open file!" << endl;
        return 0;
    }
    string line;
    long long cnt = 0;
    while(getline(file, line)){
        ++cnt;
    }
    return cnt;
}
string chooseWord(){
    ifstream file;
    file.open("dictionary.txt");
    if(file.fail()){
        cout << "Cannot open file!" << endl;
        return "";
    }
    int l = rand() % numberOfWords() + 1;
    string line;
    for(int i = 1; i < l; i++){
        getline(file, line);
    }
    string word; getline(file, word);
    stringstream ss(word);
    string token; int count = 0;
    while(ss >> token){
        ++count;
        if(count == 2) word = token;
    }
    return word;
}

char readAGuess(){
    char guess;
    cout << "Enter your guess: "; cin >> guess;
    return guess;
}

bool contains(string secretWord, char guess){
    if(secretWord.find(guess) != string::npos)
        return true;
    else return false;
}

bool checkContinuePlaying(){
    char choice;
    cout << "\nDo you want to continue playing? (y/n): ";
    cin >> choice;
    return (choice == 'y');
}

void update(string &guessedWord, const string& secretWord, char guess){
    for(int i = 0; i < secretWord.size(); i++){
        if(guess == secretWord[i]){
            replace(guessedWord.begin() + i, guessedWord.begin() + i + 1,'-', secretWord[i]);
        }
    }
}



void standardization(char& word){
    word = tolower(word);
}


int main(){
    srand(time(NULL));
    int round = 0;

    do{
        cout << "-------- ROUND " << ++round << " --------" << endl;
        system("pause");
        string secretWord = chooseWord();
        string guessedWord = string(secretWord.length(), '-');
        int badGuessCount = 0;
        vector<char> wrongWord;

        do{

            system("cls");
            renderGame(guessedWord, badGuessCount, wrongWord);

            char guess = readAGuess();
            standardization(guess);
            for(char it : wrongWord){
                if(it == guess){
                    --badGuessCount;
                    break;
                }
            }
            if(contains(secretWord, guess)){
                update(guessedWord, secretWord, guess);
            }
            else{
                ++badGuessCount;
                wrongWord.push_back(guess);
            }
        }while(badGuessCount < 7 && guessedWord != secretWord);

        system("cls");
        playAnimation(badGuessCount, secretWord);

    }while(checkContinuePlaying());

    return 0;
}
