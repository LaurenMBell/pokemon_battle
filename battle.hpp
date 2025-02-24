/*
Author: Lauren Bell
Description: battle class prototyping with private member variables and functions to 
            support encapsulation, and public functions for other tasks
*/


#ifndef BATTLE_HPP
#define BATTLE_HPP

#include <string>
#include "pokemon.hpp"

class battle{
private:
    pokemon* train1_poke1;
    pokemon* train2_poke1;
    bool train1_has_potion;
    bool train2_has_potion;
    int current_turn;

    double calc_type_interaction(const std::string& move_type, const std::string& defender_type);
    int calc_pokedamage(pokemon& atacker, pokemon& defender, move& move);
    void display_battle_status();
    void pokebattle_move(pokemon& attacker, pokemon& defender);
    bool pokebattle_heal(pokemon& pokemon, bool& has_potion);
    int trainer_choice(int min, int max);
    int move_choice(pokemon& pokemon);

public:
    battle(pokemon& train1_poke1, pokemon& train2_poke1);

    void start();
    bool is_pokeover() const;
    void display_pokewinner() const;
};

#endif