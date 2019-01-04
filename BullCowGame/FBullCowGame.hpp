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
  /* constructor */
  FBullCowGame();
  /* getters */
  int32 GetMaxTries() const;
  int32 GetCurrentTry() const;
  int32 GetHiddenWordLength() const;
  bool IsGameWon() const;
  EGuessStatus CheckGuessValidity(FString) const;
  bool IsPlaying() const;
  
  void Reset(); // TODO: make this have a richer return value
  void Start();
  void Stop();
  FBullCowCount SubmitValidGuess(FString);
    
private:
  int32 MyCurrentTry;
  int32 MyMaxTries;
  FString HiddenWord;
  bool bGameIsWon;
};

#endif /* FBullCowGame_hpp */
