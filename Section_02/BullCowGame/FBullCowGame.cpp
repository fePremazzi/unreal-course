#include "FBullCowGame.h"
#include <map>
#define TMap std::map

//FString

FBullCowGame::FBullCowGame() {
	Reset();
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planet";
	constexpr int32 MAX_TRIES = 2;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	MyMaxTries = MAX_TRIES;
	bGameIsWon = false;
}

int32 FBullCowGame::GetMaxTries() const{	return MyMaxTries;}

int32 FBullCowGame::GetCurrentTry() const{	return MyCurrentTry;}

bool FBullCowGame::IsGameWon() const{	return bGameIsWon;}

int FBullCowGame::GetHiddenWordLength() const{	return MyHiddenWord.length();}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (false)//TODO if the guess is not all lowerwcase, 
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength())//if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
	
		
}

//receives a valid guess, increments turn, and return count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	

	//main logic
	for (int32 i = 0; i < MyHiddenWord.length(); i++)
	{
		for (int32 j = 0; j < MyHiddenWord.length(); j++)
		{
			if (MyHiddenWord[i] == Guess[j])
			{
				if (i == j)				
					BullCowCount.Bulls++;				
				else				
					BullCowCount.Cows++;				
			}
		}

	}

	if (BullCowCount.Bulls == GetHiddenWordLength())
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}


	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	//Treat 0 and 1 letter words as isograms
	if (Word.length() <= 1)	
		return true;
	//TMap<char,bool> Name
	//std::map<key, value> Name
	TMap<char, bool> LetterSeen;
	for (auto Letter : Word)
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter])
		{
			return false;
		}
		else
		{
			LetterSeen[Letter] = true;
		}
	}
	
		//if the letter is in the map
			//we do NOT have an isogram
		//otheriwse
			//add that letter to the map
	return true;
}