#include <iostream>
#include <cstdlib> // Required for rand() and srand()
#include <ctime>   // Required for time()
#include <limits>  // Required for input validation

using namespace std;

int main() {
    // 1. Seed the random number generator using the current system time
    // This ensures a different number is generated every time you run the program
    srand(static_cast<unsigned int>(time(0)));

    // 2. Generate a random number between 1 and 100
    int randomNumber = rand() % 100 + 1;
    int userGuess = 0;
    int attempts = 0;

    cout << "==============================\n";
    cout << "   NUMBER GUESSING GAME\n";
    cout << "==============================\n";
    cout << "I have selected a number between 1 and 100.\n";
    cout << "Can you guess what it is?\n\n";

    // 3. Game Loop
    while (userGuess != randomNumber) {
        cout << "Enter your guess: ";
        cin >> userGuess;

        // Input Validation: Check if the user entered a non-numeric value
        if (cin.fail()) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard bad input
            cout << "Invalid input. Please enter a whole number.\n";
            continue;
        }

        attempts++;

        // 4. Provide Feedback
        if (userGuess > randomNumber) {
            cout << "Too high! Try again.\n";
        } else if (userGuess < randomNumber) {
            cout << "Too low! Try again.\n";
        } else {
            cout << "\nCongratulations! You guessed the correct number: " << randomNumber << "\n";
            cout << "It took you " << attempts << " attempts.\n";
        }
    }

    return 0;
}
