/*
Author: Lauren Bell
Description: Header file w/ declaration of move structure with member variables
*/

#ifndef MOVE_HPP
#define MOVE_HPP

#include <string>

struct move {
    std::string name;
    std::string type;
    int base_damage;
    int max_uses;
    int uses_left;

    static move make_move(std::string move_name, std::string move_type, int damage, int max, int left) {
        move new_move;
        new_move.name = move_name;
        new_move.type = move_type;
        new_move.base_damage = damage;
        new_move.max_uses = max;
        new_move.uses_left = left;
        return new_move;
    }
};

#endif
