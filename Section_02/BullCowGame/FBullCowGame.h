#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Satus,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};


class FBullCowGame 
{
public:
	FBullCowGame();

	void Reset(); //TODO make a more rich return value
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	bool IsGameWon() const;
	int32 GetHiddenWordLength() const;
	EGuessStatus CheckGuessValidity(FString) const;//TODO make a more rich return value
	
    //count bulls & cows, and increases try # assuming valid guess
	FBullCowCount SubmitValidGuess(FString);

private:
	int32 MyCurrentTry;//constructor
	int32 MyMaxTries;//constructor
	FString MyHiddenWord;
	bool bGameIsWon;
};
