// StringMatching.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <iostream>
#include <regex>
#include <string>
using namespace std;

enum class UserChoice {
	EMODESOURCE,
	EMODESEARCH,
	EMODEEXIT,
	EMODEINVALID,
	EMODENONE
};

class Game {

private:

	UserChoice userChoice;

	string sourceString;
	string searchString;
	regex searchRegex;

	bool gameOverStatus;
	bool isSearchWordContainWildCard;

	void BeginGame();
	bool isValidString(string str, bool isSource);
	void SearchForMatchingString();
	void ParseInput(string);
	void SetupGameParameters();
	void CreateRegexFromSearchString();
	void ResetSearchParameters();

	bool isGameOver() const;
	string ReplaceAll(std::string str, const std::string& from, const std::string& to) const;

public:

	Game();
	void Play();

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

Game::Game()
{
	gameOverStatus = false;
	userChoice = UserChoice::EMODENONE;
	sourceString = "";

	ResetSearchParameters();

	BeginGame();
}

void Game::SearchForMatchingString()
{


	std::regex re("(?=([a-z](i)[a-z]))."); // <-- PATTERN MODIFICATION

	regex_iterator<string::const_iterator> next = std::sregex_iterator(
		sourceString.begin(),
		sourceString.end(),
		searchRegex);

	std::sregex_iterator end;
	auto words_end = std::sregex_iterator();
	int occurrenceCount = std::distance(next, words_end);

	cout << "For the source word \"" << sourceString << "\" and search word \"" << searchString << "\",";


	if (occurrenceCount == 0)
	{
		cout << " no match has been found." << endl;
	}
	else
	{
		cout << endl;
		while (next != end)
		{
			std::smatch match = *next;
			std::cout << "\"" << match.str(1) << "\" has been found at index " << match.position() << '\n';
			next++;
		}
	}





	/*


	vector<int> index_matches; // result indexes saved here

	for (auto it =match_results;
		it != std::sregex_iterator();
		++it)
	{
		index_matches.push_back(it->position());
	}





	if (occurrenceCount > 0)
	{
		std::cout << endl;
		int index = 0;
		for (std::sregex_iterator i = match_results; i != words_end; ++i) {

			std::smatch match = *i;
			std::string match_str = match.str();

			std::cout << "\"" << match_str << "\" has been found at index " << index_matches[index] << '\n';

			index++;
		}
	}
	else
	{

	}
	*/


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
				isSearchWordContainWildCard = true;
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
			ResetSearchParameters();
		}
	}
	else if (choice == "2")
	{
		isSearchWordContainWildCard = false;
		if (sourceString.length() != 0
			&& sourceString.length() >= word.length()
			&& isValidString(word, false)
			)
		{
			isInputStrValid = true;
			userChoice = UserChoice::EMODESEARCH;
			searchString = word;
			CreateRegexFromSearchString();
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
		return;
	}

}

void Game::SetupGameParameters()
{
	string input;

	cout << endl << "Enter your choice and string: ";
	getline(cin, input);

	userChoice = UserChoice::EMODENONE;

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
		ResetSearchParameters();
		break;
	}
	case UserChoice::EMODEEXIT:
	{
		cout << "See you!" << endl;
		gameOverStatus = true;
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

bool Game::isGameOver() const
{
	return gameOverStatus;
}

void Game::Play()
{
	while (!isGameOver())
	{
		SetupGameParameters();
	}
}

std::string Game::ReplaceAll(std::string str, const std::string& from, const std::string& to) const
{
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
	}
	return str;
}

void Game::CreateRegexFromSearchString()
{
	if (isSearchWordContainWildCard)
	{
		string temp = "";

#pragma region PATTERN_MODIFICATION
		// add pharantesis to all letters
		for (char c : searchString)
		{
			temp += '(';
			temp += c;
			temp += ')';
		}

		// replace all '?' with '[a-z]'
		temp = ReplaceAll(temp, "?", "[a-z]");
		temp = "(?=(" + temp + ")).";
#pragma endregion

		searchRegex = regex(temp);
	}
	else
	{
		searchRegex = regex("(?=(" + searchString + ")).");
	}
}

void Game::ResetSearchParameters()
{
	searchString = "";
	searchRegex = regex("");
	isSearchWordContainWildCard = false;
}

int main()
{
	Game game = Game();
	game.Play();

	return 0;
}