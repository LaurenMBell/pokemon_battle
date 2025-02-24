/*
Author: Lauren Bell
Description: Meat of the program, handles trainer choice, pokemon construction, 
and basic error handling
*/

#include <iostream>

#include "battle.hpp"
#include "pokemon.hpp"

//function prototypes
pokemon create_charmander();
pokemon create_squirtle();
pokemon create_bulbasaur();
pokemon create_pidgey();
pokemon create_pikachu();

pokemon choose_pokemon(int trainer_num, bool exclude_pokemon = false, std::string excluded_name = "");

/*
Function: main
Description: entry point to the program, handles pokemon selection before the battle starts
Parameters: n/a
Returns: 0 at the end of the program
*/
int main() {
    //trainer 1 choice
    std::cout << "-------------------------------" << std::endl;
    std::cout << "Trainer 1: which pokemon do you choose?" << std::endl;
    std::cout << "1. Charmander!" << std::endl;
    std::cout << "2. Squirtle!" << std::endl;
    std::cout << "3. Bulbasaur!" << std::endl;
    std::cout << "4. Pidgey!" << std::endl;
    std::cout << "5. Pikachu!" << std::endl;
    pokemon train1_poke1 = choose_pokemon(1);
    std::cout << "-------------------------------" << std::endl;

    //trainer 2 choice depending on trainer 1 pokemon
    std::cout << "Trainer 2: Which pokemon do you choose?" << std::endl;
    if (train1_poke1.get_name() == "Charmander") {
        //if t1 chose charmander
        std::cout << "1. Squirtle!" << std::endl;
        std::cout << "2. Bulbasaur!" << std::endl;
        std::cout <<  "3. Pidgey!" << std::endl;
        std::cout <<  "4. Pikachu!" << std::endl;
    } else if (train1_poke1.get_name() == "Squirtle") {
        //if t1 chose squirtle
        std::cout << "1. Charmander!" << std::endl;
        std::cout << "2. Bulbasaur!" << std::endl;
        std::cout << "3. Pidgey!" << std::endl;
        std::cout << "4. Pikachu!" << std::endl;
    } else if (train1_poke1.get_name() == "Bulbasaur") {
        //if t1 chose bulbasaur
        std::cout << "1. Charmander!" << std::endl;
        std::cout << "2. Squirtle!" << std::endl;
        std::cout << "3. Pidgey!" << std::endl;
        std::cout << "4. Pikachu!" << std::endl;
    } else if (train1_poke1.get_name() == "Pidgey") {
        //if t1 chose pidgey
        std::cout << "1. Charmander!" << std::endl;
        std::cout << "2. Squirtle!" << std::endl;
        std::cout << "3. Bulbasaur!" << std::endl;
        std::cout << "4. Pikachu!" << std::endl;
    } else {
        //if t1 chose pikachu
        std::cout << "1. Charmander!" << std::endl;
        std::cout << "2. Squirtle!" << std::endl;
        std::cout << "3. Bulbasaur!" << std::endl;
        std::cout << "4. Pidgey!" << std::endl;
    }
    pokemon train2_poke1 = choose_pokemon(2, true, train1_poke1.get_name());
    std::cout << "-------------------------------" << std::endl;

    //make the battle object and start it!
    battle battle(train1_poke1, train2_poke1);
    battle.start();

    return 0;
}

/*
Function: create_charmander
Description: makes a charmander and adds its moves
Parameters: n/a
Returns: n/a
*/
pokemon create_charmander() {
    pokemon charmander("Charmander", "fire", 18, 18, 4, 6, nullptr, 0);
    charmander.add_pokemove(move::make_move("Ember", "fire", 5, 15, 15));
    return charmander;

}

/*
Function: create_squirtle
Description: creates a squirtle and adds its moves
Parameters: n/a
Returns: n/a
*/
pokemon create_squirtle(){
    pokemon squirtle("Squirtle", "water", 22, 22, 6, 4, nullptr, 0);
    squirtle.add_pokemove(move::make_move("Tackle", "normal", 3, 10000, 10000));
    squirtle.add_pokemove(move::make_move("Water Gun", "water", 5, 3, 3));
    return squirtle;
}

/*
Function: create_bulbasaur
Description: creates a bulbasaur and adds its moves
Parameters: n/a
Returns: n/a
*/
pokemon create_bulbasaur() {
    pokemon bulbasaur("Bulbasaur", "grass", 20, 20, 5, 5, nullptr, 0);
    bulbasaur.add_pokemove(move::make_move("Tackle", "normal", 3, 10000, 10000));
    bulbasaur.add_pokemove(move::make_move("Vine Whip", "grass", 5, 3, 3));
    return bulbasaur;
}

/*
Function: create_pidgey
Description: creates a pidgey and adds its moves
Parameters: n/a
Returns: n/a
*/
pokemon create_pidgey() {
    pokemon pidgey("Pidgey", "flying", 18, 18, 4, 4, nullptr, 0);
    pidgey.add_pokemove(move::make_move("Tackle", "normal", 3, 10000, 10000));
    pidgey.add_pokemove(move::make_move("Wing Attack", "flying",5 , 3, 3));
    return pidgey;
}

/*
Function: create_pikachu
Description: creates a pikachu and adds its moves
Parameters: n/a
Returns: n/a
*/
pokemon create_pikachu() {
    pokemon pikachu("Pikachu", "electric", 19, 19, 5, 5, nullptr, 0);
    pikachu.add_pokemove(move::make_move("Static", "normal", 3, 10000, 10000));
    pikachu.add_pokemove(move::make_move("Thunderbolt", "electric", 5, 3, 3));
    return pikachu;
}

/*
Function: choose_pokemon
Description: handles the trainer pokemon selection process
Parameters: trainer_num - 1 for trainer 1, 2 for trainer 2
            excluded_pokemon - true if theres one you can't choose, false if not
            excluded_name - excluded pokemon name
Returns: a newly_created pokemon object
*/
pokemon choose_pokemon(int trainer_num, bool excluded_pokemon, std::string excluded_name) {
    int choice;
    std::cout << "Your choice: ";
    std::cin >> choice;

    //t2 selection
    if (excluded_pokemon) {
        while (choice < 1 || choice > 4) {  
            std::cout << "Uh-oh: invalid poke-choice!" << std::endl;
            std::cout << "Your choice: ";
            std::cin >> choice;
        }

        if (excluded_name == "Charmander") {
            return (choice == 1) ? create_squirtle() :
                   (choice == 2) ? create_bulbasaur() :
                   (choice == 3) ? create_pidgey() :
                                   create_pikachu();  
        } else if (excluded_name == "Squirtle") {
            return (choice == 1) ? create_charmander() :
                   (choice == 2) ? create_bulbasaur() :
                   (choice == 3) ? create_pidgey() :
                                   create_pikachu();
        } else if (excluded_name == "Bulbasaur") {
            return (choice == 1) ? create_charmander() :
                   (choice == 2) ? create_squirtle() :
                   (choice == 3) ? create_pidgey() :
                                   create_pikachu();
        } else if (excluded_name == "Pidgey") {
            return (choice == 1) ? create_charmander() :
                   (choice == 2) ? create_squirtle() :
                   (choice == 3) ? create_bulbasaur() :
                                   create_pikachu();
        } else {
            return (choice == 1) ? create_charmander() :
                   (choice == 2) ? create_squirtle() :
                   (choice == 3) ? create_bulbasaur() :
                                   create_pidgey();
        }
    } else {
        //t1 selection
        while (choice < 1 || choice > 5) { 
            std::cout << "Uh-oh: invalid poke-choice!" << std::endl;
            std::cout << "Your choice: ";
            std::cin >> choice;
        }

        switch(choice) {
            case 1: return create_charmander();
            case 2: return create_squirtle();
            case 3: return create_bulbasaur();
            case 4: return create_pidgey();
            case 5: return create_pikachu(); 
            default: return create_pidgey();
        }
    }
}
