//This is a simple 'higher, lower or equal' game
//The computer will begin each round by drawing a 'card' between 1 and 10
//It will then ask the player to predict whether the next card will be higher, lower or equal to the previous draw
//If the player is correct, the player gets a point. If the player is incorrect, the computer gets a point
//First one to 5 points wins. If the player correctly guesses that the card will be equal to the previous one, they automatically win


#include <iostream>
#include <random>
#include <string>

#ifdef _WIN32
    #define CLEAR "cls"  
#else
    #define CLEAR "clear" 
#endif



int main() {
    //mersene twister is used to generate a random integer between 1 and 10
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<int> dist(1,10);

    //'continue_game and play_again work as switches to regulate the game loop'
    bool continue_game = true;
    std::string play_again;

    int player_score = 0;
    int computer_score = 0;
    int cycles = 0;
    std::string clear_terminal;

    while (continue_game) {
        cycles += 1;
        while (cycles >= 4) {
            
            std::cout << "\nYour terminal is looking a little crowded, would you like to clear it? ";
            std::cin >> clear_terminal;
            //the game offers to clear the terminal for the player after the first four rounds
            //if the player declines, it offers again with every subsequent round
            if (clear_terminal == "yes" || clear_terminal == "Yes") {
                system(CLEAR);
                cycles = 0;
            }

            else if (clear_terminal == "no" || clear_terminal == "No") {
                std::cout << "\nGot it, we'll leave it as it is for now\n";
                cycles -=1;
            }

            else {
                
                    std::cout << "\nYou must answer 'yes' or 'no' ";

                }

            }
            
        
        
        
        

        

     
     std::string guess;
    
     int num = dist(gen);
     std::cout << "\n";
     std::cout << "A card is drawn....the number " << num << ".\n";

     std::cout << "\n";
     std::cout << "Do you think the next draw will be higher, lower, or equal? ";
     std::cin >> guess;

     int num2 = dist(gen);

     //conditions for handling the player's guess and comparing it to the drawn cards

     if (guess == "higher" || guess == "Higher") {

            if (num2 > num) {
                player_score += 1;
                std::cout << "\nYES! The number " << num2 << " card was drawn, which is higher than " << num << ".\n";
                if (player_score < 5) {
                std::cout << "\nThe score is Player: " << player_score << ", Computer: " << computer_score << ".\n";
                }
            }

            else if (num2 < num) {
                computer_score +=1;
                std::cout << "\nSorry :( The number " << num2 << " card was drawn, which is lower than " << num << ".\n";
                if (computer_score < 5) {
                std::cout << "\nThe score is Player: " << player_score << ", Computer: " << computer_score << ".\n";
                }
                
            }

            else {
                computer_score +=1;
                std::cout << "\nSorry :( The number " << num2 << " card was drawn, which is equal to " << num << ".\n";
                if (computer_score < 5) {
                std::cout << "\nThe score is Player: " << player_score << ", Computer: " << computer_score << ".\n";
                }
            }

     }
     
     else if (guess == "lower" || guess == "Lower") {

        if (num2 < num) {
                player_score += 1;
                std::cout << "\nYES! The number " << num2 << " card was drawn, which is lower than " << num << ".\n";
                if (player_score < 5) {
                std::cout << "\nThe score is Player: " << player_score << ", Computer: " << computer_score << ".\n";
                }
            }

            else if (num2 > num) {
                computer_score +=1;
                std::cout << "\nSorry :( The number " << num2 << " card was drawn, which is higher than " << num << ".\n";
                if (computer_score < 5) {
                std::cout << "\nThe score is Player: " << player_score << ", Computer: " << computer_score << ".\n";
                }
            }

            else {
                computer_score +=1;
                std::cout << "\nSorry :( The number " << num2 << " card was drawn, which is equal to " << num << ".\n";
                if (computer_score < 5) {
                std::cout << "\nThe score is Player: " << player_score << ", Computer: " << computer_score << ".\n";
                }
            }



     }

     else if (guess == "equal" || guess == "Equal"){

        if (num2 == num) {

            std::cout << "The " << num2 << " card was drawn, which is equal to the previous card. You won the game!\n";
            std::cout << "\nThe final score is Player: " << player_score << ", Computer: " << computer_score << ".\n";
            std::cout << "\n";
            std::cout << "Would you like to play another round? ";
            std::cin >> play_again;

            if (play_again == "yes" || play_again == "Yes") {
                
                continue_game = true;
                player_score = 0;
                computer_score = 0;

            }

            else if (play_again == "no" || play_again == "No") {
                 continue_game = false;
                 std::cout << "\nGot it, thanks for playing :) See you next time!";
                 std::cout << "\nPress Enter to exit...";
                 std::cin.ignore();
                 std::cin.get();

                 break;
            }

            else {
                std::cout << "\nsince you obviously can't spell, lets just end the game here.";
                continue_game = false;
                std::cout << "\nPress Enter to exit...";
                std::cin.ignore();
                std::cin.get();

                break;
            }

            
           
        }

        else if (num2 != num) {
                computer_score += 1;
                std::cout << "\nSorry, the " << num2 << " card was drawn, which is not eqal to " << num << ".\n";
                if (computer_score < 5) {
                std::cout << "\nThe score is Player: " << player_score << ", Computer: " << computer_score << ".\n";
                }
        }


     }

     else {

        std::cout << "\nYou must answer with 'higher', 'lower', or 'equal'.";
     }





     if (player_score == 5) {

        std::cout << "\nCongratulations! You won the game!\n";
        std::cout << "\nThe final score is Player: " << player_score << ", Computer: " << computer_score << ".\n";
        std::cout << "\nWould you like to play another round? ";
        std::cin >> play_again;

            if (play_again == "yes" || play_again == "Yes") {
                
                continue_game = true;
                player_score = 0;
                computer_score = 0;

            }

            else if (play_again == "no" || play_again == "No") {
                 continue_game = false;
                 std::cout << "\nGot it, thanks for playing :) See you next time!";
                 std::cout << "\nPress Enter to exit...";
                 std::cin.ignore();
                 std::cin.get();

                 break;
            }

            else {
                std::cout << "\nsince you obviously can't spell, lets just end the game here.";
                continue_game = false;
                std::cout << "\nPress Enter to exit...";
                std::cin.ignore();
                std::cin.get();

                break;
            }

     }
        //conditions for the game ending. Player is prompted to play another game or exit the program
     else if (computer_score == 5) {

        std::cout << "\nSorry, you've lost this game :(\n";
        std::cout << "\nThe final score is Player: " << player_score << ", Computer: " << computer_score << ".\n";
        std::cout << "\nWould you like to play another round? ";
        std::cin >> play_again;

            if (play_again == "yes" || play_again == "Yes") {
                
                continue_game = true;
            

            }

            else if (play_again == "no" || play_again == "No") {
                 continue_game = false;
                 std::cout << "\nGot it, thanks for playing :) See you next time!";
                 std::cout << "\nPress Enter to exit...";
                 std::cin.ignore();
                 std::cin.get();

                 break;
            }

            else {
                std::cout << "\nsince you obviously can't spell, lets just end the game here.";
                continue_game = false;
                std::cout << "\nPress Enter to exit...";
                std::cin.ignore();
                std::cin.get();

                break;
            }



     }



    
     

     

         
    }

}