/*****************************************
** File:    proj1.cpp
** Project: Project 1: Hangman
** Author:  Matthew Makila
** Date:    2/21/21
** Section: 10/13
** E-mail:  mmakila1@umbc.edu
**
** Project 1 uses the game of hangman to test basic C++
** input validation, loops, array use, and the use of functions.
** I created 7 unique functions to split the game's operations,
** each employing unique return types and input variables.
***********************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

int importFile();
string chooseWord(string wordArray[], int size);
void displayPuzzle(string word, int lettersRemaining);
char manageGuesses(string word, char guess, char prevGuesses[]);
string editDisplayStr(string gameWord, string displayWord, char guessChar);
int numLettersFound(string gameWord, char guessChar, int lettersLeft);
void resetGame();

const int INCORRECT_GUESSES = 6;
const int PREV_GUESS_MAX = 26;
const char WRONG_GUESS = '0';
const int LOWERCASE_ASCII_MARKER = 97;


int main() {
    srand(time(NULL));
    cout << "Welcome to UMBC Word Guess" << endl;
    int numWords = importFile();
    // if the file was read properly and returned a list of words, continue
    if (numWords > 0){
        string wordArr[numWords];
        string gameWord = chooseWord(wordArr, numWords);
        int wordLength = gameWord.length();
        cout << "Your file was imported!" << endl;
        cout << numWords << " words imported." << endl;
        cout << "Ok. I am thinking of a word with " << wordLength << " letters." << endl;

        // create the comparative display string for the actual word
        string displayWord;
        for (int i = 0; i < wordLength; i++){
            displayWord += "_";
        }

        int guesses = INCORRECT_GUESSES; int lettersLeft = wordLength;
        char previousGuesses[PREV_GUESS_MAX];

        do {
            // display partial game string and how many letters remain
            displayPuzzle(displayWord, lettersLeft);

            char guess;
            cout << "What letter would you like to guess?" << endl;
            cin >> guess;
            guess = manageGuesses(gameWord, guess, previousGuesses);
            // if guess was incorrect, subtract from guesses, but if not, alter the display word and adjust lettersLeft
            if (guess == WRONG_GUESS){
                guesses--;
                cout << "You have " << guesses << " bad guesses left." << endl;
            } else {
                lettersLeft = numLettersFound(gameWord, guess, lettersLeft);
                displayWord = editDisplayStr(gameWord, displayWord, guess);
            }
        } while (guesses > 0 && lettersLeft > 0);

        // if the user guessed incorrectly 6 times, they lose ... else if the loop terminated they must have won
        if (guesses == 0){
            cout << "You lost!" << endl;
        } else {
            cout << "Congrats, you won!" << endl;
        }
        cout << "The correct word was: " << gameWord << endl;
        // reset game if the player chooses 'y'
        char playAgain;
        cout << "Play again? (y/n)" << endl;
        cin >> playAgain;
        if (playAgain == 'y'){
            resetGame();
        }
    } else {
        cout << "Error. Your file could not be imported." << endl;
    }
    return 0;
}

// Function name: importFile
// Pre-condition: There is no argument passed to this function
// Post-condition: The wordCount is returned to determine the size of the array holding the words from a file
int importFile(){
    // initialize variable for current word, make an array for total words, initialize word count to 0
    string currWord;
    int wordCount = 0;
    ifstream wordFile ("words.txt");

    // if file found, find size of file
    if (wordFile.is_open()) {
        while (wordFile >> currWord) {
            wordCount++;
        }
        wordFile.close();
    }
    return wordCount;
}

// Function name: chooseWord
// Pre-condition: This function takes an empty array of strings and a determined int for the size of the file
// Post-condition: the output is returned as one randomly chosen word from the array populated by the file words
string chooseWord(string wordArray[], int size){
    string currWord;
    ifstream wordFile ("words.txt");
    int wordCount = 0;
    // read file to populate myArr with words within the length of the total list of words
    while (wordFile >> currWord)
    {
        wordArray[wordCount] = currWord;
        wordCount++;
    }
    wordFile.close();

    // generate random index to pick from list of words
    int maxNum = size - 1; int minNum = 0;
    int randIndex = rand() % (maxNum - minNum + 1) + minNum;
    // returns the word at the given random index chosen
    return wordArray[randIndex];
}

// Function name: displayPuzzle
// Pre-condition: The display word and the num of letters remaining are input
// Post-condition: The function simply displays the partial game string and the number of letters left
void displayPuzzle(string word, int lettersRemaining){
    int wordLength = word.length();
    cout << lettersRemaining << " letters remain." << endl;
    for (int i = 0; i < wordLength; i++){
        cout << word[i] << " ";
    }
    cout << "\n";
}

// Function name: manageGuesses
// Pre-condition: This function takes the game word, the user's guess and an array with the user's prior guesses
// Post-condition: the output is returned either as a new valid lowercase guess or is returned as a bad guess
char manageGuesses(string word, char guess, char prevGuesses[]) {
    // check ASCII is in range of lowercase characters
    int wordLength = word.length();
    while (guess < 'a' || guess > 'z') {
        cout << "What letter would you like to guess?" << endl;
        cin >> guess;
        cin.clear();
        cin.ignore(256, '\n');
    }
    bool found = false;
    bool alreadyGuessed = false;
    for (int i = 0; i < wordLength; i++) {
        // check if the guess in the word and also not a previous guess
        if (guess == word[i]) {
            found = true;
        }
        if (guess == prevGuesses[int(guess) - LOWERCASE_ASCII_MARKER]){
            alreadyGuessed = true;
        }
    }
    // add current guess to the previous guess array at its respective position (0 - 25) for the alphabet
    prevGuesses[int(guess) - LOWERCASE_ASCII_MARKER] = guess;

    if (!found && !alreadyGuessed) {
        cout << "There are no " << guess << " in the puzzle." << endl;
        return WRONG_GUESS;
    } else if (alreadyGuessed) {
        cout << "You already guessed " << guess << endl;
        return WRONG_GUESS;
    }else {
        return guess;
    }
}

// Function name: editDisplayStr
// Pre-condition: Takes the input of the gameWord, the partial display string, and the valid guess character
// Post-condition: the output is returned as the updated partial display string with the valid guesses filled in
string editDisplayStr(string gameWord, string displayWord, char guessChar){
    int wordLength = gameWord.length();
    for (int i = 0; i < wordLength; i++){
        if (gameWord[i] == guessChar){
            displayWord[i] = guessChar;
        }
    }
    return displayWord;
}

// Function name: numLettersFound
// Pre-condition: Takes in the gameWord, guess character, and the letters left
// Post-condition: Output is amount of letters left after subtracting the num of the guess char's were in the gameWord
int numLettersFound(string gameWord, char guessChar, int lettersLeft){
    int wordLength = gameWord.length();
    for (int i = 0; i < wordLength; i++){
        if (gameWord[i] == guessChar){
            lettersLeft--;
        }
    }
    return lettersLeft;
}

// Function name: resetGame
// Pre-condition: There is no argument passed to this function
// Post-condition: There is no return, merely main() is called again to restart the game.
void resetGame(){
    main();
}