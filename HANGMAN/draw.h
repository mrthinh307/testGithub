#include <bits/stdc++.h>
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;
void renderGame(string guessedWord, int badGuessCount, vector<char> v);
void displayFinalResult(bool won, const string& word);
void playAnimation(int badGuessCount, const string& word);
