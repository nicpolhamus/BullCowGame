/**
*  FBullCowGame.hpp
*  BullCowGame
*
*  Created by Nicolas on 1/3/19.
*  Copyright © 2019 Nicolas Polhamus. All rights reserved.
*/

#ifndef FBullCowGame_hpp
#define FBullCowGame_hpp

#pragma once
#include <string>
#include <map>
#define TMap std::map
/* For Unreal Engine parity */
using FString = std::string;
using int32 = int;
/* Structure for counting bulls and cows in guess */
struct FBullCowCount {
  int32 Bulls = 0;
  int32 Cows = 0;
};
/* Guess statuses */
enum class EGuessStatus {
  Invalid_Status,
  OK,
  Not_Isogram,
  Wrong_Length,
  Not_Lowercase
};
/**
 * FBullCowGame
 * @class
 */
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
  
  void Reset();
  FBullCowCount SubmitValidGuess(FString);
    
private:
  int32 MyCurrentTry;
  FString HiddenWord;
  bool bGameIsWon;
  
  bool IsIsogram(FString) const;
  bool IsLowercase(FString) const;
};

#endif /* FBullCowGame_hpp */
