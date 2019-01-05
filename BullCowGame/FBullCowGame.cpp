/**
* FBullCowGame.cpp
*  BullCowGame
*
*  Created by Nicolas on 1/3/19.
*  Copyright © 2019 Nicolas Polhamus. All rights reserved.
*
*  Future improvements:
*  - give players a "difficulty" option
*    - difficulty is based on word length
*  - utilize a word "dictionary"
*/
#pragma once
#include "FBullCowGame.hpp"

/* constructor */
FBullCowGame::FBullCowGame() { Reset(); }
/* getters */
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return HiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }
bool FBullCowGame::IsPlaying() const { return false; }

int32 FBullCowGame::GetMaxTries() const {
  TMap<int32, int32> WordLengthToMaxTries = { {3,5}, {4,7}, {5,9}, {6,11}, {7,13} };
  return WordLengthToMaxTries[HiddenWord.length()];
}

bool FBullCowGame::IsIsogram(FString Word) const {
  /* 0 and 1 word guesses are isograms */
  if (Word.length() <= 1) { return true; }
  /* letters we have seen */
  TMap<char, bool> LetterSeen;
  /* iterate through guess */
  for (auto Letter : Word) {
    /* makes checking case agnostic */
    Letter = tolower(Letter);
    /* check if the letter has been seen */
    if (LetterSeen[Letter]) {
      /* if the letter has been seen break out of loop and return false */
      return false;
    } else {
      /* if the letter hasn't been seen set the seen value in the map to true, continue iterating */
      LetterSeen[Letter] = true;
    }
  }
  /* the guess is an isogram, so return true */
  return true;
}

bool FBullCowGame::IsLowercase(FString Word) const {
  /* iterate through the word */
  for (auto Letter : Word) {
    /* check if the letter is lowercase */
    if (!islower(Letter)) {
      /* return false if we get a capital letter */
      return false;
    }
  }
  /* there were no capital letters in the word, return true */
  return true;
}

// counts bulls and cows, and incrementing turn number assuming valid guess
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {
  // increment turn value
  MyCurrentTry++;
  // setup return value
  FBullCowCount BullCowCount;
  // loop through all the values in the guess
  int32 HiddenWordLength = HiddenWord.length();
  for (int32 hiddenWordChar = 0; hiddenWordChar < HiddenWordLength; hiddenWordChar++) {
    for (int32 guessChar = 0; guessChar < HiddenWordLength; guessChar++) {
      if (Guess[guessChar] == HiddenWord[hiddenWordChar]) {
        if (hiddenWordChar == guessChar) {
          BullCowCount.Bulls++;
        }
        else {
          BullCowCount.Cows++;
        }
      }
    }
  }
  /* check if the bull count equals the hidden word length */
  if (BullCowCount.Bulls == GetHiddenWordLength()) {
    bGameIsWon = true;
  }
  
  return BullCowCount;
}

void FBullCowGame::Reset() {
  /* use constexpr for the magic number MAX_TRIES */
  constexpr int32 MAX_TRIES = 8;
  /* set the max tries for the game */
  MyMaxTries = MAX_TRIES;
  /* init the hidden word */
  const FString HIDDEN_WORD = "planet";
  /* set the hidden word*/
  HiddenWord = HIDDEN_WORD;
  /* init the current try */
  MyCurrentTry = 1;
  /* init Game status */
  bGameIsWon = false;
  return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const {
  // checking if the guess is an isogram
  if (!IsIsogram(Guess)) {
    return EGuessStatus::Not_Isogram;
  }
  // checking if guess is lowercase
  if (!IsLowercase(Guess)) {
    return EGuessStatus::Not_Lowercase;
  }
  if (Guess.length() != GetHiddenWordLength()) {
    return EGuessStatus::Wrong_Length;
  }
  return EGuessStatus::OK;
}
