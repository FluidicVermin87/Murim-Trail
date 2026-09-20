#ifndef TILE_H
#define TILE_H

#include "Character.h"

#include <vector>

struct Tile {
    char color; //static functions as none use Tile data members + readability

    static vector<Chara> green(vector<Chara> players, int current_player, int choice, int chosen_advisor);
    static pair<vector<Chara>, vector<string>> pink(vector<Chara> players, int current_player, vector<string> chosenAdvisors);
    static vector<Chara> purple(vector<Chara> players, int current_player);
};

#endif