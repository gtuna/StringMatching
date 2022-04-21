// StringMatching.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
using namespace std;

enum class UserChoice {
	EMODESOURCE,
	EMODESEARCH,
	EMODEEXIT,
	EMODEINVALID
};

class Game {

public:

	Game();

	bool isGameOver;
	bool isSearchWordContainsWildCard;
	UserChoice userChoice;
	string sourceString;
	string searchString;

	void BeginGame();
	void SetupGameParameters();
	void SearchForMatchingString();
	bool isValidString(string str, bool isSource);
	void ParseInput(string);

};




void Game::BeginGame()
{
	cout << "This program searches a search string in a source string with the option of wildcards." << endl;
	cout << endl;
	cout << "Example inputs with their meaning in parentheses :" << endl;
	cout << "1 thislectureisawesome(to enter a new source string)" << endl;
	cout << "2 lecture(to enter a new search string)" << endl;
	cout << "2 t?r? (to enter a search string with wildcards)" << endl;
	cout << "3 (to exit the program)" << endl;
	cout << endl;
}

Game::Game() {
	isGameOver = false;
	userChoice = UserChoice::EMODEINVALID;
	sourceString = "";
	searchString = "";
	isSearchWordContainsWildCard = false;
	BeginGame();

}

void Game::SearchForMatchingString()
{




	cout << "For the source word \"" << sourceString << "\" and search word \"" << searchString << "\"," << endl;

}

bool Game::isValidString(string str, bool isSource) {
	if (str.length() == 0) {
		return false;
	}

	// return false if only contains '?'
	if (str.find_first_not_of('?') == string::npos) {
		return false;
	}

	for (char i : str)
	{
		if (i < 'a' || i > 'z') {
			if (!isSource && i == '?') {
				continue;
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}


void Game::ParseInput(string str)
{
	bool isInputStrValid = false;

	// split string into two parts by space
	std::string delimiter = " ";
	std::string choice = str.substr(0, str.find(delimiter)); // first part
	std::string word = str.substr(str.find(delimiter) + 1); // second part

	if (choice == "1")
	{
		if (isValidString(word, true))
		{
			isInputStrValid = true;
			userChoice = UserChoice::EMODESOURCE;
			sourceString = word;
		}
	}
	else if (choice == "2")
	{

		if (sourceString.length() != 0
			&& sourceString.length() >= word.length()
			&& isValidString(word, false)
			)
		{
			isInputStrValid = true;
			userChoice = UserChoice::EMODESEARCH;
			searchString = word;
		}
	}
	else if (choice == "3")
	{
		isInputStrValid = true;
		userChoice = UserChoice::EMODEEXIT;
	}
	else
	{
		isInputStrValid = true; //here is a little bit tricky, input string is valid, but user choice is invalid
		userChoice = UserChoice::EMODEINVALID;
	}

	if (!isInputStrValid)
	{
		cout << "Wrong input format! Try again." << endl;
	}

}

void Game::SetupGameParameters()
{
	string input;

	cout << endl << "Enter your choice and string: ";
	getline(cin, input);

	ParseInput(input);


	switch (userChoice)
	{
	case UserChoice::EMODESOURCE:
	{
		cout << "Source word has been changed to \"" << sourceString << "\"" << endl;
		break;
	}
	case UserChoice::EMODESEARCH:
	{
		SearchForMatchingString();
		break;
	}
	case UserChoice::EMODEEXIT:
	{
		cout << "See you!" << endl;
		isGameOver = true;
		break;
	}
	case UserChoice::EMODEINVALID:
	{
		cout << "Choice can be 1, 2 or 3! Try again.\n";
		break;
	}
	default:
		break;
	}
}


int main()
{

	Game game = Game();


	do
	{
		game.SetupGameParameters();

	} while (!game.isGameOver);

	return 0;
}