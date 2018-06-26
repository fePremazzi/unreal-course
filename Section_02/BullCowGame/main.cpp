/* This is the console executable, that makes use
   of the BullCowGame class.
   This acts as the view in a MVC pattern, and is responsible
   for all user interaction. For game logic see the FBullCowGame class.

*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

//to make syntax Unreal friendly
using FText = std::string;
using int32 = int;


//FText is generally used for user interaction

//function prototypes as outside class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;// instantiate a new game

int main()
{
	BCGame.Reset();
	bool bPlayAgain = false;
	do
	{
		//introduce the game
		BCGame.Reset();
		PrintIntro();
		PlayGame();
		
		bPlayAgain = AskToPlayAgain();
		
	} while (bPlayAgain);
	return 0; //exit
}

void PlayGame()
{

	int32 MaxTries = BCGame.GetMaxTries();

	//loop for the number of turns asking for guesses	
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();

		//submit valide guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls: " << BullCowCount.Bulls << std::endl;
		std::cout << "Cows :" << BullCowCount.Cows << "\n\n";

	}
	PrintGameSummary();
	return;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon() == true)
	{
		std::cout << "You won the game!!\n";
	}
	else
	{
		std::cout << "Try again!!\n";
	}
	return;
}

void PrintIntro()
{
	//introduce the game
	constexpr int32 WORD_LENGTH = 9;
	std::cout << "Welcome to Bulls and Cows, a word game.\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

//loop continues until the user go to a valid guess
FText GetValidGuess()
{
	FText auxGuess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Satus;
	do
	{
		//get guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		std::getline(std::cin, auxGuess);

		//check the guess and loop
		Status = BCGame.CheckGuessValidity(auxGuess);

		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter ISOGRAM (only different letters).\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter your guess with only lowercase.\n";
			break;
		default:
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK);
	return auxGuess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (y/n) ";
	FText Response = "";
	std::getline(std::cin, Response);
	system("cls");
	return (Response[0] == 'y') || (Response[0] == 'Y');
}
