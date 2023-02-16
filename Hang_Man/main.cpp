#include<iostream>
#include<ctime>
#include<string>
#include<cctype>

using namespace std;

const string DICTIONARY[] = {
       "angle", "ant", "apple", "arch", "arm", "army",
"baby", "bag", "ball", "band", "basin", "basket", "bath", "bed", "bee", "bell", "berry",
"bird", "blade", "board", "boat", "bone", "book", "boot", "bottle", "box", "boy",
"brain", "brake", "branch", "brick", "bridge", "brush", "bucket", "bulb", "button",
"cake", "camera", "card", "cart", "carriage", "cat", "chain", "cheese", "chest",
"chin", "church", "circle", "clock", "cloud", "coat", "collar", "comb", "cord",
"cow", "cup", "curtain", "cushion",
"dog", "door", "drain", "drawer", "dress", "drop", "ear", "egg", "engine", "eye",
"face", "farm", "feather", "finger", "fish", "flag", "floor", "fly",
"foot", "fork", "fowl", "frame", "garden", "girl", "glove", "goat", "gun",
"hair", "hammer", "hand", "hat", "head", "heart", "hook", "horn", "horse",
"hospital", "house", "island", "jewel", "kettle", "key", "knee", "knife", "knot",
"leaf", "leg", "library", "line", "lip", "lock",
"map", "match", "monkey", "moon", "mouth", "muscle",
"nail", "neck", "needle", "nerve", "net", "nose", "nut",
"office", "orange", "oven", "parcel", "pen", "pencil", "picture", "pig", "pin",
"pipe", "plane", "plate", "plow", "pocket", "pot", "potato", "prison", "pump",
"rail", "rat", "receipt", "ring", "rod", "roof", "root",
"sail", "school", "scissors", "screw", "seed", "sheep", "shelf", "ship", "shirt",
"shoe", "skin", "skirt", "snake", "sock", "spade", "sponge", "spoon", "spring",
"square", "stamp", "star", "station", "stem", "stick", "stocking", "stomach",
"store", "street", "sun", "table", "tail", "thread", "throat", "thumb", "ticket",
"toe", "tongue", "tooth", "town", "train", "tray", "tree", "trousers", "umbrella",
"wall", "watch", "wheel", "whip", "whistle", "window", "wire", "wing", "worm",
       };
const int WORD_COUNT = sizeof(DICTIONARY) / sizeof(string);
const int MAX_BAD_GUESS_COUNT = 7;

const string FIGURE[] = {
" ------------- \n"
" | \n"
" | \n"
" | \n"
" | \n"
" | \n"
" ----- \n",
" ------------- \n"
" | | \n"
" | \n"
" | \n"
" | \n"
" | \n"
" ----- \n",
" ------------- \n"
" | | \n"
" | O \n"
" | \n"
" | \n"
" | \n"
" ----- \n",
" ------------- \n"
" | | \n"
" | O \n"
" | | \n"
" | \n"
" | \n"
" ----- \n",
" ------------- \n"
" | | \n"
" | O \n"
" | /| \n"
" | \n"
" | \n"
" ----- \n",
" ------------- \n"
" | | \n"
" | O \n"
" | /|\\ \n"
" | \n"
" | \n"
" ----- \n",
" ------------- \n"
" | | \n"
" | O \n"
" | /|\\ \n"
" | / \n"
" | \n"
" ----- \n",
" ------------- \n"
" | | \n"
" | O \n"
" | /|\\ \n"
" | / \\ \n"
" | \n"
" ----- \n",
};
void renderGame(const string& GuessedWord, const int &badGuess){
       cout << FIGURE[badGuess];
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
