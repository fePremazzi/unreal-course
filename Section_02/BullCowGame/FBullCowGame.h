/*The game logic (no view or direct use rinteraction)
The game os a smples guess the word game based on mastermind
*/

#pragma once
#include <string>


//to make syntanx Unreal friendly
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
	FBullCowGame();//constructor

	void Reset(); 
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	bool IsGameWon() const;
	int32 GetHiddenWordLength() const;
	EGuessStatus CheckGuessValidity(FString) const;//TODO make a more rich return value
	
    //count bulls & cows, and increases try # assuming valid guess
	FBullCowCount SubmitValidGuess(FString);

	

private:
	int32 MyCurrentTry;//constructor
	//int32 MyMaxTries;//constructor
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString Word) const;
	bool IsLowerCase(FString Word) const;
};
