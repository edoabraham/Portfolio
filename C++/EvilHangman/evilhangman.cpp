// Final Project Evil Hangman (evilhangman.cpp)
// Jesse Z Zhong (jzz119@psu.edu)

#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>
#include <string>

using namespace std;

// Returns String with Blanks of Specified Length
string initializeWord (int wordLength);

// Reads and Stores Strings of a File into Vector Word List; Returns the Number of Words/Strings in List
int readFile(string fileName, vector<string> &wordList);

// The Heart of This Game: XOR Function. If Both Cases are True or Both Cases are False, Return False; If Both Cases Differ, Return True => Use for Comparing Matching Strings
bool xorFunction(bool first, bool second);

// Checks if Two Strings Have a Matching Pattern With the Same Letter (Same Number of that Letter and Same Positions in Both Words/Strings)
bool stringMatchLetter(string str1, string str2, char letter);

// Checks if the String Contains the Character Specified. If It Does, Return True. Else, It Returns False
bool containLetter(string word, char letter);

// I Somehow Created a Similar Function as containLetter() But With the Opposite Returns Without Realizing. Unfortunately, This One Is Relied on Heavily So I Cannot Replace at This Time
bool validLetter(string line, char letter);

// Sorts a Word List into "Word Families" and a Vector of Vectors of Strings (HAHA!) According to the Character Specified.
void assembleFamilyList(vector<string> &wordList, vector<vector<string>> &wordListList, char letter);

// Using the Previous Function, this Function Sorts the Words into Families and Stores the Family List with the Most Word Entries into the Word List; It also Returns the Editted Display String
// According to the Word Family and the Previous Display String
string poolParse(vector<string> &wordList, char letter, string display);

// Sorts Words that Match the Length Specified and Discards Words That Don't Match; Returns True if There Are Matches, Otherwise False
bool sortLength(vector<string> &wordList, unsigned int length);

// If Specified as True, The Total Number of WordList Entries Will be Cout When the Function is Called
void runningTotal(bool yesNo, vector<string> wordList);

// Returns True if Character Specified is Y, y, or 1, Otherwise it Returns False
bool yesNo(char letter);

// Checks if Character is a Letter of the English Alphabet
bool validAlphabet(char letter);

// Converts a String Into a "Unsigned" Integer Number
int stringToInt(string line);

// The Game Loop!! FIND ALL THE WORDS!!
bool gameLoop(vector<string> wordList);

int main() {
	bool play = true;
	string dictionaryName;
	int round = 1;

	// Vector for Dictionary Word List
	vector<string> wordList;
	cout << "What is the name of the dictionary file?" << endl;
	cin >> dictionaryName;
	int numOfWords = readFile(dictionaryName, wordList);

	// Checks Valid Name or Dictionary File (Words in There or Not)
	while(numOfWords == 0) {
		cout << "Cannot open " << dictionaryName << " OR there are no words in this file. \nPlease,"
			 << "try again." << endl;
		cin >> dictionaryName;
		numOfWords = readFile(dictionaryName, wordList);
	}

	cout << "Total words in the dictionary: " << numOfWords << endl;
	while(play) {
		// GRAPHICS!
		cout << "*******************************" << endl
			 << "Round " << round << endl
			 << "*******************************" << endl;
		// end Graphics... *sad*

		// The Game
		gameLoop(wordList);

		// DO YOU?!
		cout << "Do you want to play again? Y(y)/N(n)" << endl;
		string meow;
		cin >> meow;
		play = yesNo(meow[0]);
		round++;
	}
	return 0;
}

bool gameLoop(vector<string> wordList) {
	string input;
	int numberOfGuesses = 0;
	string inputLetter;
	string inputYesOrNo;
	
	cout << "How many letters do you want your word to have?" << endl;
	cin >> input;

	while(!sortLength(wordList, stringToInt(input))) {
		cout << "Sorry, there is no word in the dictionary with the length of " << input 
			 << ". \nPlease try another length." << endl;
		cin >> input;
	}

	string display = initializeWord(stringToInt(input));
	cout << "How many guesses do you want to have?" << endl;
	cin >> input;
	numberOfGuesses = stringToInt(input);
	cout << "Do you want to know the running total of remaining words?(Y(y)/N(n)" << endl;
	cin >> inputYesOrNo;

	cout << "Number of guesses remaining: " << numberOfGuesses << endl;
	runningTotal(yesNo(inputYesOrNo[0]), wordList);

	string guessedLetters;

	// The Loop Bounded By the Number of Guesses
	for(int i = numberOfGuesses - 1; i >= 0; i--) {
		bool counterCounter = false;
		cout << "Letters that have been guessed:" << guessedLetters << endl
			<< display << endl
			<< "What letter?" << endl;
		cin >> inputLetter;

		// Y U NO Use Engrish?! Haha, Just Kidding; Checks for Valid Alphabet Input
		while(!validAlphabet(inputLetter[0])) {
			cout << inputLetter << " is not a letter from A/a to Z/z. Please enter"
				 << "a letter that's in the English Alphabet." << endl;
			cin >> inputLetter;
		}

		// Checks if Letter Has Already Been Used; Will Not Deduct Guesses if Letter is Already Used
		if(validLetter(guessedLetters, inputLetter[0])) {
			string inputCon;
			inputCon.assign(1, inputLetter[0]);
			guessedLetters = guessedLetters + " " + inputCon;
		} else counterCounter = true;

		// Returns the New Display String While Sorting the New List of Words
		display = poolParse(wordList, inputLetter[0], display);
		if(validLetter(display, '_')) {
			cout << "Good job, you guessed the word: " << display << endl;
			// I'm Cheating Here; I'm Cutting Off the Rest of the Code by Returning if the Game is a Win
			return true;
		}

		// Checks if the Letter is In the Family; Will Not Deduct Guesses if True
		if(!validLetter(display, inputLetter[0])) {
			if(!counterCounter) counterCounter = true;
		} else cout << "Sorry, " << inputLetter << " is not in the word." << endl;
		
		// Spits Out Remaining Guesses Remaining
		cout << "Number of guesses remaining: " << i << endl;
		if(counterCounter) i++;

		// If Required and if There is More than One Guess Remaining, Show Number of Words Left
		if(i > 1) runningTotal(yesNo(inputYesOrNo[0]), wordList);
	}
	// Lose
	cout << "Sorry, you are out of guesses, and the word is: " << wordList[0] << endl;
	// Just a Required Return~
	return false;
}

int stringToInt(string line) {
	int result = 0;
	int digitsPlace = 1;
	for(int i = (line.length() - 1); i >= 0; i--) {
		if(line[i] <= '9' && line[i] >= '0') {	
			result = result + (line[i] - '0') * digitsPlace;
			digitsPlace = digitsPlace * 10;
		}
	}
	return result;
}

bool validAlphabet(char letter) {
	if((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z')) return true;
	else return false;
}

bool yesNo(char letter) {
	if(letter == 'y' || letter == 'Y' || letter == '1') return true;
	else return false;
}

void runningTotal(bool yesNo, vector<string> wordList) {
	if(yesNo) cout << "Number of words remaining: " << wordList.size() << endl;
}

bool validLetter(string line, char letter) {
	for(unsigned int i = 0; i < line.length(); i++) {
		if(line[i] == letter) return false;
	}
	return true;
}

bool sortLength(vector<string> &wordList, unsigned int length) {
	vector<string> words;
	for(unsigned int i = 0; i < wordList.size(); i++) {
		if(wordList[i].length() == length) words.push_back(wordList[i]);
	}
	if(words.empty()) return false;
	wordList = words;
	return true;
}

string initializeWord (int wordLength) {
	string word;
	return word.assign(wordLength, '_');
}


int readFile(string fileName, vector<string> &wordList) {
	ifstream myFile(fileName.c_str());
	string word;
	int i = 0;
	while(myFile.is_open() && myFile >> word) {
		wordList.push_back(word);
		i++;
	}
	myFile.close();
	return i;
}


bool xorFunction (bool first, bool second) {
	if(first == second) return false;
	else return true;
}

bool stringMatchLetter(string str1, string str2, char letter) {
	int wordMatch = 0;
	if(str1.length() == str2.length()) {
		for(unsigned int i = 0; i < str1.length(); i++) {
			if(!xorFunction((str1[i] == letter), (str2[i] == letter))) wordMatch++;
		}
		if(wordMatch == str1.length()) return true;
		else return false;
	} else return false;
}

bool containLetter(string word, char letter) {
	bool notDone = true;
	for(unsigned int i = 0; i < word.length() && notDone; i++) {
		if(word[i] == letter) notDone = false;
	}
	return !notDone;
}

// Laziness is Tempting, But I'll Explain
void assembleFamilyList(vector<string> &wordList, vector<vector<string>> &wordListList, char letter) {
	for(unsigned int i = 0; i < wordList.size(); i++) {
		// If There are No Words in the Family List, Put the First Word of the Word List In
		if(wordListList.empty()) {
			vector<string> temp;
			temp.push_back(wordList[i]);
			wordListList.push_back(temp);
		} else {
			// Otherwise, Check Against the First Entry of Each Family if the Next Entry in the
			// Word List Matches the Letter Pattern of that Word
			// If the Word does Match, Stuff that Word into the Family's List
			bool marker = true;
			for(unsigned int j = 0; j < wordListList.size() && marker; j++) {
				if(stringMatchLetter(wordList[i], wordListList[j][0], letter)) {
					marker = false;
					wordListList[j].push_back(wordList[i]);
				}
				else marker = true;
			}
			// Otherwise, Make a New Family List and Stuff the Word in It
			// Neat Huh?
			if(marker) {
				vector<string> temp;
				temp.push_back(wordList[i]);
				wordListList.push_back(temp);
			}
		}
	}
}

// Rubbish... No, I'm Kidding.
string poolParse(vector<string> &wordList, char letter, string display) {
	vector<vector<string>> wordListList;
	unsigned int largestIndex = 0;
	unsigned int largestEntry = 0;
	// Sorts
	assembleFamilyList(wordList, wordListList, letter);

	// Checks Which Family is the LARGEST; If it Turns Out That There are Two
	// Largest of the Same Size, Chose the One that Doesn't Contain The Letter
	for(unsigned int i = 0; i < wordListList.size(); i++) {
		if(largestEntry < wordListList[i].size()) {
			largestEntry = wordListList[i].size();
			largestIndex = i;
		} else if(largestEntry == wordListList[i].size()) {
			if(validLetter(wordListList[i][0], letter)) largestIndex = i;
		}
	}
	// STORE THAT LIST IN THE LIST!!
	wordList = wordListList[largestIndex];
	// Scans Letter Pattern of the First Word of the Family and Imprints it Onto the Display String
	for(unsigned int i = 0; i < wordList[0].size(); i++) {
		if(wordList[0][i] == letter) display[i] = letter;
	}
	return display;
}