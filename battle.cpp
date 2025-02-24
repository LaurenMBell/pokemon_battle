/*
Author: Lauren Bell
Description: battle class implementation that handles pokemon battle functions 
*/

#include "battle.hpp"

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

/*
Function: print_type_interaction
Description: prints the type_interaction result to terminal with the multiplier
Parameters: type_interaction - multiplier from calc_type_interaction
Returns: n/a
*/
void print_type_interaction(double type_interaction) {
    if (type_interaction == 2.0) {
        std::cout << "TYPE ADVANTAGE: 2X DAMAGE!" << std::endl;
    } 
    else if (type_interaction == 0.5) {
        std::cout << "Type disadvantage: 1/2X damage" << std::endl;
    } else {
        std::cout << "No advantage: normal damage" << std::endl;
    }
}

/*
Function:  print_random_critical
Description: prints the critical hit message to the terminal 
Parameters: random_critical - random int with a 10% of being 3 and 90% chance of being 1
Returns: n/a
*/
void print_random_critical(int random_critical) {
    if (random_critical == 3) {
        std::cout << "CRITICAL HIT! 3X DAMAGE!" << std::endl;
    } else {
        std::cout << "Hit!" << std::endl;
    }
}

/*
Function: calc_type_interaction
Description: calculates the type interaction mutliplier based on the attackers move type 
            and the defenders type
Parameters: move_type - the type of the move object selected
            defender_type - the type of the defending pokemon
Returns: multiplier value for the damage calculation equation
*/
double battle::calc_type_interaction(const std::string& move_type, const std::string& defender_type) {
    if (move_type == "fire") {
        //if the move is fire
        if (defender_type == "grass") return 2.0;
        if (defender_type == "water") return 0.5;
    } else if (move_type == "water") {
        //if the move is water
        if (defender_type == "fire") return 2.0;
        if (defender_type == "grass") return 0.5;
        if (defender_type == "electric") return 0.5;
    } else if (move_type == "grass") {
        //if the move is grass
        if (defender_type == "water") return 2.0;
        if (defender_type == "fire") return 0.5;
        if (defender_type == "flying") return 0.5;
    } else if (move_type == "flying") {
        //if the move is flying
        if (defender_type == "grass") return 2.0;
        if (defender_type == "electric") return 2.0;
    } else if (move_type == "electric") {
        //if the move is electric
        if (defender_type == "flying") return 0.5;
        if (defender_type == "water") return 2.0;
    }
    //if the move is normal
    return 1.0;
}

/*
Function: battle
Description: constructor for the battle class, makes a new battle between two pokemon
Parameters: train1_poke1 - trainer 1's pokemon, note:the variable names were made when I thought
                            I was doing the multiple pokemon extra credit :( I didn't want to 
                            change every reference
            train2_poke1 - trainer 2's pokemon
Returns: n/a
*/
battle::battle(pokemon& train1_poke1, pokemon& train2_poke1) : 
    train1_poke1(&train1_poke1), train2_poke1(&train2_poke1), train1_has_potion(true), 
    train2_has_potion(true), current_turn(1) {}

/*
Function: calc_pokedamage
Description: calculates the damage according to the formula in the assignment instructions
Parameters: attacker - the attacking pokemon passed in by reference
            defencer - defending pokemon passed in by reference
            move - the selected move of the attacking pokemon (passed in by reference)
Returns: damage - int representing the result of the damage calculation
*/
int battle::calc_pokedamage(pokemon& attacker, pokemon& defender, move& move) {
    double type_interaction = calc_type_interaction(move.type, defender.get_type());
    //print the type multiplier
    print_type_interaction(type_interaction);

    int random_critical = (rand() % 10 == 0) ? 3 : 1;
    //print the critical hit multiplier
    print_random_critical(random_critical);

    //calculate damage
    double damage_float = (static_cast<double>(attacker.get_attack()) / defender.get_defense()) *
                            type_interaction * move.base_damage * random_critical;
    
    int damage = static_cast<int>(std::ceil(damage_float));
    
    //print damage to terminal
    std::cout << "TOTAL DAMAGE: " << damage << "!" << std::endl;
    std::cout << "-------------------------------" << std::endl;
    
    return damage;
}

/*
Function: display_battle_status
Description: shows the current HP of the battling pokemon and whos turn it is
Parameters: n/a
Returns: n/a
*/
void battle::display_battle_status() {
    std::cout << "Trainer " << ((current_turn % 2 == 1) ? 1 : 2)  << "'s turn!" << std::endl;
    std::cout << train1_poke1->get_name() << " has " << train1_poke1->get_current_hp() 
                << "/" << train1_poke1->get_max_hp() << " HP remaining" << std::endl;
    std::cout << train2_poke1->get_name() << " has " << train2_poke1->get_current_hp() 
                << "/" << train2_poke1->get_max_hp() << " HP remaining" << std::endl;
}

/*
Function: trainer_choice
Description: takes in the user-given choice from the menu printed in the 
             start() function
Parameters: min/max - values representing the # of options in the pokemon selection 
            menu 
Returns: choice - int representing the choice
*/
int battle::trainer_choice(int min, int max) {
    int choice;
    std::cout << "Your choice: ";
    std::cin >> choice;

    while (choice< min || choice > max) {
        //error handling for out of range input
        std::cout << "That's an invalid poke-choice!" << std::endl;
        std::cout << "Your choice: ";
        std::cin >> choice;
    }

    return choice;
}

/*
Function: move_choice
Description: takes in the move selection and makes sure theres uses left for it
Parameters: pokemon - pokemon object with the selected move
Returns: choice - index of the user-given move
*/
int battle::move_choice(pokemon& pokemon) {
    std::cout << "Which move would you like to use?" << std::endl;
    pokemon.display_moves();

    int choice = trainer_choice(1, pokemon.get_num_moves());
    std::cout << "-------------------------------" << std::endl;

    while (pokemon.get_move(choice - 1).uses_left <= 0) {
        //error handling for when there aren't any uses left
        std::cout << pokemon.get_move(choice - 1).name << " has no uses remaining..." << std::endl;
        std::cout << "-------------------------------" << std::endl;
        std::cout << "Which move would you like to use?" << std::endl;
        pokemon.display_moves();
        choice = trainer_choice(1, pokemon.get_num_moves());
    }
    return choice;
}

/*
Function: pokebattle_move
Description: handles the whole 'attack' choice 
Parameters: attacker - attacking pokemon passed in by reference
            defender - defender pokemon passed in by reference
Returns: n/a
*/
void battle::pokebattle_move(pokemon& attacker, pokemon& defender) {
    //choose the move
    int move_index = move_choice(attacker) - 1;
    move& selected_move = attacker.get_move(move_index);

    //calculate and defending pokemon take damage
    int damage = calc_pokedamage(attacker, defender, selected_move);
    defender.take_pokedamage(damage);

    //selected move loses 1 use
    selected_move.uses_left--;

    //if the pokemon is out of health, then its fainted and the match is over
    if (defender.is_pokefainted()) {
        std::cout << defender.get_name() << " has fainted..." << std::endl;
        std::cout << "-------------------------------" << std::endl;
    }
}

/*
Function: pokebattle_heal
Description: handles the healing choice and healing the pokemon vs not having a potion
Parameters: pokemon - chosen pokemon object thats being healed
            has_potion - if the trainer still has a healing potion
Returns: n/a
*/
bool battle::pokebattle_heal(pokemon& pokemon, bool& has_potion) {
    if (has_potion) {
        //healing the pokemon and making sure it doesn't go over the max hp
        int initial_hp = pokemon.get_current_hp();
        pokemon.heal_pokepotion(10);
        int healed_amount = pokemon.get_current_hp() - initial_hp;

        std::cout << pokemon.get_name() << " has been healed with a potion!" << std::endl;
        std::cout << "-------------------------------" << std::endl;
        //no more potion
        has_potion = false;
        return true;
    } else{
        //if user chooses 'heal' but doesn't have a potion
        std::cout << "Uh-oh: you don't have any healing potions left!" << std::endl;
        std::cout << "-------------------------------" << std::endl;
        return false;
    }
}

/*
Function: start
Description: takes over each turn and the decision making needs, calling 
            functions depending on the choice and who's turn it is
Parameters: n/a
Returns: n/a
*/
void battle::start() {
    srand(static_cast<unsigned int>(time(nullptr)));  
    //seed for the random critical value

    while (not is_pokeover()) {
        //print the current pokemon HP and whos turn it is
        display_battle_status();

        //menu options
        std::cout << "Would you like to 1) use a move, or 2) heal?: ";
        int choice;
        std::cin >> choice;

        while (choice != 1 && choice != 2) {
            //error handling for out of range choices
            std::cout << "Uh-oh, that's an invalid poke-choice!" << std::endl;
            std::cout << "Would you like to 1) use a move, or 2) heal?: ";
            std::cin >> choice;
        }

        if (current_turn%2 == 1) {
            //player 1's turn
            if (choice == 1) {
                pokebattle_move(*train1_poke1, *train2_poke1);
            } else {
                if (not pokebattle_heal(*train1_poke1, train1_has_potion)) {
                    std::cout << "Please select a move." << std::endl;
                    pokebattle_move(*train1_poke1, *train2_poke1);
                }
            }
        } else {
            //player 2's turn
            if (choice == 1) {
                pokebattle_move(*train2_poke1, *train1_poke1);
            } else {
                if (not pokebattle_heal(*train2_poke1, train2_has_potion)) {
                    std::cout << "Please select a move." << std::endl;
                    pokebattle_move(*train2_poke1, *train1_poke1);
                }           
            }
        }
        current_turn++;
    }
    //print the winner and end the program
    display_pokewinner();
}

/*
Function: is_pokeover
Description: returns a bool value if either pokemon is fainted
Parameters: n/a
Returns: n/a
*/
bool battle::is_pokeover() const {
    return train1_poke1->is_pokefainted() || train2_poke1->is_pokefainted();
}

/*
Function: display_pokewinner
Description: print the winning trainer if the other is fainted!!
Parameters: n/a
Returns: n/a
*/
void battle::display_pokewinner() const {
    if (train1_poke1->is_pokefainted()) {
        std::cout << "TRAINER 2 WINS!" << std::endl;
        std::cout << "-------------------------------" << std::endl;
    } else {
        std::cout << "TRAINER 1 WINS!" << std::endl;
        std::cout << "-------------------------------" << std::endl;
    }
}