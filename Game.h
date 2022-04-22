// Game.h : This file contains Game class definition.
// Date: 2022-04-21
// Created by: Gülsen Tuna
//
#pragma once
#include <regex>
#include <string>

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

	std::string sourceString;
	std::string searchString;
	std::regex searchRegex;

	bool gameOverStatus;
	bool isSearchWordContainWildCard;

	void BeginGame();
	bool isValidString(std::string str, bool isSource);
	void SearchForMatchingString();
	void ParseInput(std::string);
	void SetupGameParameters();
	void CreateRegexFromSearchString();
	void ResetSearchParameters();

	bool isGameOver() const;
	std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) const;

public:

	Game();
	void Play();

};