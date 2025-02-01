//My very first C++ program
//The program will randomly generate two numbers from 1 to 6, add them together, and then ask the user to guess a number
//If the user's guess is incorret, a new random number will be generated and the user will again be prompted for a guess
//The program ends only when the user guesses correctly


#include <iostream>
#include <vector>
#include <string>
#include <random>

int main() {

 //initialize and seed the random device
 std::random_device rd;
 std::mt19937_64 gen(rd());

 //define different random number selections
 //we could have also used 'uniform_real_distribution<double>' if we wanted a random float value
 std::uniform_int_distribution<int> dice1(1,6);
 std::uniform_int_distribution<int> dice2(1,6);
 
 //a boolean switch for controlling the while loop
 bool continue_game = true;

 //while loop continues the game, randomly generating a new number, and prompting the user for a guess, until the user guesses correctly
 while (continue_game) {

 int dice01 = dice1(gen);
 int dice02 = dice2(gen);

 int roll = dice01 + dice02;
 int guess;
 int difference;

 std::cout << "Guess a number between 1 and 12:\n";
 std::cin >> guess;
 

//conditionals for handling user input and comparing it to the random number or, 'roll'
 if (guess > roll) {
    difference = guess - roll;
    std::cout << "Sorry, the correct answer was " << roll << ". Your guess was " << difference << " units too high.\n";
 }
 else if(guess < roll) {

    difference = roll - guess;
    std::cout << "Sorry, the correct answer was " << roll << ". Your guess was " << difference << " units too low.\n";

 }

 else {

    std::cout << "Congratulations! You got it! The correct answer WAS " << roll << "\n";
    continue_game = false;
 }


 }

}
