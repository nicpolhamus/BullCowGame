//
//  FBullCowGame.hpp
//  BullCowGame
//
//  Created by Nicolas on 1/3/19.
//  Copyright © 2019 Nicolas Polhamus. All rights reserved.
//

#ifndef FBullCowGame_hpp
#define FBullCowGame_hpp

#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount {
  int32 Bulls = 0;
  int32 Cows = 0;
};

enum class EGuessStatus {
  Invalid_Status,
  OK,
  Not_Isogram,
  Wrong_Length,
  Not_Lowercase
};

class FBullCowGame {
public:
  FBullCowGame();
  void Reset(); // TODO: make this have a richer return value
  int32 GetMaxTries() const;
  int32 GetCurrentTry() const;
  int32 GetHiddenWordLength() const;
  bool IsGameWon() const;
  EGuessStatus CheckGuessValidity(FString) const; // TODO: make this return a richer value
  void Start();
  void Stop();
  bool IsPlaying() const;
  FBullCowCount SubmitGuess(FString);
    
private:
  int32 MyCurrentTry;
  int32 MyMaxTries;
  FString HiddenWord;
};

#endif /* FBullCowGame_hpp */
