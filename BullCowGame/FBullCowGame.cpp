//
//  FBullCowGame.cpp
//  BullCowGame
//
//  Created by Nicolas on 1/3/19.
//  Copyright © 2019 Nicolas Polhamus. All rights reserved.
//

#include "FBullCowGame.hpp"

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return HiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return false; }
bool FBullCowGame::IsPlaying() const { return false; }

// counts bulls and cows, and incrementing turn number assuming valid guess
FBullCowCount FBullCowGame::SubmitGuess(FString Guess) {
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
  return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const {
  // checking if the guess is an isogram
  if (false) {
    return EGuessStatus::Not_Isogram;
  }
  // checking if guess is lowercase
  if (false) {
    return EGuessStatus::Not_Lowercase;
  }
  if (Guess.length() != GetHiddenWordLength()) {
    return EGuessStatus::Wrong_Length;
  }
  return EGuessStatus::OK;
}

void FBullCowGame::Start() {
  return;
}

void FBullCowGame::Stop() {
  return;
}
