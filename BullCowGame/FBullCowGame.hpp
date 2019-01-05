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
#include <vector>
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
/* Game Difficulties */
enum class EGameDifficulties {
  Easy,
  Simple,
  Medium,
  Hard,
  Very_Hard
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
  bool IsADifficulty(FString) const;
  /* reset game state */
  void Reset();
  void SetDifficulty(FString);
  FBullCowCount SubmitValidGuess(FString);
    
private:
  int32 MyCurrentTry;
  FString HiddenWord;
  int32 DictionaryLength = 6;
  bool bGameIsWon;
  std::vector<FString> EasyHiddenWords = {
    "fun",
    "car",
    "cat",
    "dog",
    "eat",
    "air",
    "ear"
  };
  std::vector<FString> SimpleHiddenWords = {
    "funk",
    "dirt",
    "shoe",
    "cart",
    "myth",
    "wolf",
    "duck"
  };
  std::vector<FString> MediumHiddenWords = {
    "black",
    "white",
    "shirt",
    "pants",
    "light",
    "right",
    "mouse"
  };
  std::vector<FString> HardHiddenWords = {
    "drying",
    "dwarfs",
    "flying",
    "kvetch",
    "skrump",
    "second",
    "minute"
  };
  std::vector<FString> VeryHardHiddenWords = {
    "mucking",
    "thwacks",
    "stumped",
    "zephyrs",
    "flyback",
    "gryphon",
    "hydrant"
  };
  
  bool IsIsogram(FString) const;
  bool IsLowercase(FString) const;
  void SetHiddenWord(EGameDifficulties);
};

#endif /* FBullCowGame_hpp */
