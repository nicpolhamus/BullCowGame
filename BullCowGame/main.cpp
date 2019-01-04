/**
 * This is the console executable, that makes use of the BullCow class.
 * This acts as the view in a MVC pattern, and is reponsible for all
 * user interaction. For game logic see the FBullCowGame class.
 */

#include <iostream>
#include <string>
#include "FBullCowGame.hpp"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
void PrintGuess(FText &Guess);
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;

int main() {
  /* bool value for game loop */
  bool bWantsToPlayAgain = false;
  do {
    /* print intro */
    PrintIntro();
    /* start the game loop */
    PlayGame();
    /* check if the player wants to play again */
    bWantsToPlayAgain = AskToPlayAgain();
  }
  while(bWantsToPlayAgain);
  return 0;
}

void PlayGame() {
  BCGame.Reset();
  /* number of guesses */
  int32 MaxTries = BCGame.GetMaxTries();
  /* loop through each guess */
  while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) { // TODO: change from FOR to while once validation is in place
    /* get the players guess and print the guess back */
    FText Guess = GetValidGuess();
    
    // submit valid guess to game
    FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

    std::cout << "Bulls: " << BullCowCount.Bulls << std::endl;
    std::cout << "Cows: " << BullCowCount.Cows << "\n\n";
  }
  PrintGameSummary();
}

/* introduce the game */
void PrintIntro() {
  std::cout << std::endl;
  std::cout << "Welcome to Bulls and Cows, a fun word game?" << std::endl;
  std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
  std::cout << " letter isogram I'm thinking of?\n" << std::endl;
  return;
}

/* loop until we get a valid guess from the player */
FText GetValidGuess() {
  FText Guess = "";
  EGuessStatus Status = EGuessStatus::Invalid_Status;
  do {
    std::cout << "Try " << BCGame.GetCurrentTry() << ". ";
    std::cout << "Enter your guess: ";
    getline(std::cin, Guess);
    // validate guess
    Status = BCGame.CheckGuessValidity(Guess);
    // check guess status
    switch (Status) {
      case EGuessStatus::Wrong_Length:
        std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
        break;
      case EGuessStatus::Not_Isogram:
        std::cout << "Please enter a word without repeating letters.\n";
        break;
      case EGuessStatus::Not_Lowercase:
        std::cout << "Please enter guess in lowercase.\n";
        break;
      default:
        break;
    }
  } while (Status != EGuessStatus::OK);
  return Guess;
}

/* output the guess back to the player */
void PrintGuess(FText &Guess) {
  std::cout << "You guessed: " << Guess << std::endl;
}

bool AskToPlayAgain() {
  std::cout << "Do you want to play again? (y/n)";
  FText Response = "";
  getline(std::cin, Response);
  std::cout << std::endl;
  return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary() {
  FText GameSummary = "";
  if (BCGame.IsGameWon()) {
    GameSummary = "Congrats, you won!";
  } else {
    GameSummary = "Sorry, you lost. Try again!";
  }
  std::cout << GameSummary << std::endl;
  return;
}
