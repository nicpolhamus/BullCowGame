/**
 * This is the console executable, that makes use of the BullCow class.
 * This acts as the view in a MVC pattern, and is reponsible for all
 * user interaction. For game logic see the FBullCowGame class.
 */

#include <iostream>
#include <string>
#include "FBullCowGame.hpp"
/* These are for Unreal Engine parity */
using FText = std::string;
using int32 = int;
/* Prototypes! */
void PrintIntro();
void PlayGame();
FText GetValidGuess();
void PrintGuess(FText &Guess);
bool AskToPlayAgain();
void PrintGameSummary();
FText AskForDifficulty();

/* Game object */
FBullCowGame BCGame;

/* entry point for game */
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

/* Plays a single round of Bulls and Cows */
void PlayGame() {
  BCGame.Reset();
  /* Ask player to set difficulty */
  FText Difficulty = AskForDifficulty();
  /* set the difficulty, which sets the hidden word for the game */
  BCGame.SetDifficulty(Difficulty);
  /* number of guesses */
  int32 MaxTries = BCGame.GetMaxTries();
  /* loop through each guess */
  while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
    /* get the players guess and print the guess back */
    FText Guess = GetValidGuess();
    
    /* submit valid guess to game */
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
  return;
}

/* loop until we get a valid guess from the player */
FText GetValidGuess() {
  FText Guess = "";
  EGuessStatus Status = EGuessStatus::Invalid_Status;
  do {
    std::cout << "Try " << BCGame.GetCurrentTry() << " of " << BCGame.GetMaxTries() << ". ";
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

/* Asks user if they want to play again */
bool AskToPlayAgain() {
  std::cout << "Do you want to play again? (y/n) ";
  FText Response = "";
  getline(std::cin, Response);
  std::cout << std::endl;
  return (Response[0] == 'y') || (Response[0] == 'Y');
}

/* Prints a win/lose statement based on if the player won or lost */
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

FText AskForDifficulty() {
  std::cout << "Please choose a difficulty:\n";
  std::cout << "e for easy\n";
  std::cout << "s for simple\n";
  std::cout << "m for medium\n";
  std::cout << "h for hard\n";
  std::cout << "vh for very hard\n";
  std::cout << "Please enter your chosen difficulty: ";
  FText ChosenDifficulty = "";
  /* loop until we get a valid difficulty */
  do {
    getline(std::cin, ChosenDifficulty);
    if (!BCGame.IsADifficulty(ChosenDifficulty)) {
      std::cout << "Please enter a valid difficulty: ";
    }
  } while (!BCGame.IsADifficulty(ChosenDifficulty));
  std::cout << std::endl;
  return ChosenDifficulty;
}
