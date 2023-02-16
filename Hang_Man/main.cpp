#include<iostream>
#include<ctime>
#include<string>
#include<cctype>

using namespace std;

string DICTIONARY[] = {"dog", "cat", "human"};
const int WORD_COUNT = sizeof(DICTIONARY) / sizeof(string);
const int MAX_BAD_GUESS_COUNT = 7;

void renderGame(const string& GuessedWord, const int &badGuess){
       cout << "Current Word: " << GuessedWord << endl << "Number of bad guess left: " << MAX_BAD_GUESS_COUNT - badGuess << endl;
       cout << "-----------------------" << endl;
}

string RandomWord(){
       srand(time(NULL));
       int index = rand() % WORD_COUNT;
       return DICTIONARY[index];
}

bool updateGuessedWord(string &GuessedWord, const string &SecretWord, char guess){
     bool ret = false;
     for(int i = 0; i < (int)SecretWord.size(); i ++){
              if(SecretWord[i] == tolower(guess)){
                     GuessedWord[i] = tolower(guess);
                     ret = true;
              }
     }
     return ret;
}

char Guess_A_Letter(){
       cout << "Guess a letter: " << endl;
       char guess;
       cin >> guess;
       return guess;
}

void Display_Result(const string &SecretWord, const string &GuessedWord, const int &badGuess){
       if(badGuess == MAX_BAD_GUESS_COUNT){
              cout << "You lost the game\nThe secret word is: " << SecretWord << endl;
       }
       else cout << GuessedWord << endl << "Congratulations! You won the game!" << endl;
}

void GamePlay(){
       string SecretWord = RandomWord();
       string GuessedWord(SecretWord.size(), '_');
       int badGuess = 0;
       while(badGuess < MAX_BAD_GUESS_COUNT && SecretWord != GuessedWord){
              renderGame(GuessedWord, badGuess);
              char guess = Guess_A_Letter();
              if(!updateGuessedWord(GuessedWord, SecretWord, guess)) badGuess ++;
       }
       Display_Result(SecretWord, GuessedWord, badGuess);
}

bool playMore(){
       cout << "Do you want to play again? y/n" << endl;
       char res;
       cin >> res;
       return (res == 'y') ? 1 : 0;
}

int main(int argc, char *argv[]){
       do{
              GamePlay();
       }while(playMore());
       return 0;
}
