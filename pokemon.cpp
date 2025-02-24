/*
Author: Lauren Bell
Description: implements all the pokemon member functions
*/

#include "pokemon.hpp"

#include <iostream>

/*
Function: pokemon 
Description: constructor for a pokemon object with all the member variables
Parameters: name - pokemon's name
            type - pokemon's type
            max_hp - the highest hp (and init. hp)
            current_hp - current hp (starts equal to max_hp)
            defense - defense stat
            attack - attack stat
            moves - move array
            num_moves - the number of moves a pokemon has
Returns: n/a
*/
pokemon::pokemon(std::string name, std::string type, int max_hp, int current_hp, int defense, 
    int attack, move* moves, int num_moves) : name(name), type(type), max_hp(max_hp),
    current_hp(current_hp), defense(defense), attack(attack), 
    moves(nullptr), num_moves(num_moves) {

        //makes all the moves
        if (moves != nullptr && num_moves > 0) {
            this->moves = new move[num_moves];
            for (int i = 0; i < num_moves; i++) {
                this->moves[i] = moves[i];
            }
        }
}

/*
Function: ~pokemon
Description: pokemon desctructor, deletes the array then the moves and cleans up 
            dynamically allocated memory 
Parameters: n/a
Returns: n/a
*/
pokemon::~pokemon() {
    delete[] moves;
}

/*
Function: get_name
Description: constant name getter to print the name to terminal among other things
Justification: theres no way to alter the objects name using this function, and 
                supports encapsulation by not altering or making a private member public
Parameters: n/a
Returns: name - pokemon object's name
*/
std::string pokemon::get_name() const {
    return name;
}

/*
Function: get_type
Description: constant type getter to calcualte the type interaction
Justification: theres no way to alter the objects type using this function, and 
                supports encapsulation by not altering or making a private member public
Parameters: n/a
Returns: type - pokemon object's type
*/
std::string pokemon::get_type() const {
    return type;
}

/*
Function: get_current_hp
Description: gets the pokemon objects current hp for print to terminal 
Justification: theres no way to alter the objects current_hp using this function, and 
                supports encapsulation by not altering or making a private member public
Parameters: n/a
Returns: current_hp - pokemon objects current hp
*/
int pokemon::get_current_hp() const {
    return current_hp;
}

/*
Function: get_max_hp
Description: get the pokemons max hp to make sure healing potions don't go over 
            the max
Justification: theres no way to alter the objects cmax_hp using this function, and 
                supports encapsulation by not altering or making a private member public
Parameters: n/a
Returns: max_hp - pokemon objects max hp
*/
int pokemon::get_max_hp() const {
    return max_hp;
}

/*
Function: add_pokemove
Description: makes a new move for a pokemon, is used when constructing the pokemon
            at the beginning of the battle
Parameters: new_move - new move to add
Returns: n/a
*/
void pokemon::add_pokemove(const move& new_move) {
    move* new_moves = new move[num_moves + 1];

    for (int i = 0; i < num_moves; i++) {
        new_moves[i] = moves[i];
    }

    new_moves[num_moves] = new_move;
    //making the new moves

    delete[] moves;
    moves = new_moves;
    num_moves++;
}

/*
Function: take_pokedamage
Description: alter the current_hp by the damage variable calculated by the formula
Parameters: damage - calculated damage from the formula
Returns: n/a
*/
void pokemon::take_pokedamage(int damage) {
    current_hp -= damage;
    if (current_hp < 0) {
        current_hp = 0;
    }
}

/*
Function: heal_pokepotion
Description: increases the pokemons hp by 10 unless that goes higher than its max_hp
Parameters: amt = 10
Returns: n/a
*/
void pokemon::heal_pokepotion(int amt = 10) {
    current_hp += amt;
    if (current_hp > max_hp) { 
        current_hp = max_hp;
    }
}

/*
Function: is_pokefainted
Description: if the pokemons hp is <= 0 then the
             pokemon is fainted and the func returns true
Parameters: n/a
Returns: true if hp is <= 0, false is > 0
*/
bool pokemon::is_pokefainted() const {
    if (current_hp <= 0) {
        return true;
    }
    return false;
}

/*
Function: get_num_moves
Description: getter for the number of moves
Justification: theres no way to alter the objects num_moves using this function, and 
                supports encapsulation by not altering or making a private member public
Parameters: n/a
Returns: num_moves - pokemon objects move
*/
int pokemon::get_num_moves() const {
    return (num_moves);
}

/*
Function: get_move
Description: gets the selected move using the index of the move, with
            basic error handling if I screw up the indexing
Parameters: index - ondex of the selected move
Returns: the selected move
*/
move& pokemon::get_move(int index) {
    if (index >= 0 && index < num_moves) {
        return moves[index];
    } else {
        return moves[0];
    }
}

/*
Function: get_attack
Description: getter for the attack variable
Justification: theres no way to alter the objects attack stat using this function, and 
                supports encapsulation by not altering or making a private member public
Parameters: n/a
Returns: attack - pokemon object attack variable
*/
int pokemon::get_attack() const {
    return attack;
}

/*
Function: get_defense
Description: getter for the defense variable
Justification: theres no way to alter the objects defense stat using this function, and 
                supports encapsulation by not altering or making a private member public
Parameters: n/a
Returns: defense - pokemon object defense variable
*/
int pokemon::get_defense() const {
    return defense;
}

/*
Function: display_moves
Description: prints the moves and the number of uses left to the terminal
Parameters: n/a
Returns: n/a
*/
void pokemon::display_moves() const {
    for (int i = 0; i < num_moves; i++ ) { 
        if (moves[i].uses_left > 0) {
            std::cout << (i + 1) << ". " << moves[i].name <<
            " (" << moves[i].uses_left << " uses left)" << std::endl;
                    
        } else {
            std::cout << (i + 1) << ". " << moves[i].name 
                    << " (0 uses remaining)" << std::endl;
        }
    }
}