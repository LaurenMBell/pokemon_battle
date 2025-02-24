/*
Author: Lauren Bell
Description: prototyping for the pokemon class with member variables 
            and member functions
*/

#ifndef POKEMON_HPP
#define POKEMON_HPP

#include <string>
#include "move.hpp"

class pokemon {
    std::string name;
    std::string type;
    int max_hp;
    int current_hp;
    int defense;
    int attack;
    move* moves;
    int num_moves;

public:
    //constructor
    pokemon(std::string name, std::string type, int max_hp, int current_hp, int defense, 
            int attack, move* moves, int num_moves);
    //destructor
    ~pokemon();
    
    //getters (I justified them in the block comment implementations :) )
    std::string get_name() const;
    std::string get_type() const;
    int get_current_hp() const;
    int get_max_hp() const;
    
    //pokemon actions
    void add_pokemove(const move& move);
    void take_pokedamage(int damage);
    void heal_pokepotion(int amt);
    bool is_pokefainted() const;

    //battle functions
    int get_num_moves() const;
    move& get_move(int index);
    int get_attack() const;
    int get_defense() const;
    void display_moves() const;
    
};

#endif