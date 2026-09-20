#ifndef BOARD_H
#define BOARD_H

#include "Tile.h"
#include <iostream>
#include <vector>

using namespace std;

class Board {
    private:
        static const int _BOARD_SIZE = 52;
        static const int _MAX_PLAYERS = 5; 
        int _player_count;                 
        int _player_position[_MAX_PLAYERS];
        int _previous_position[_MAX_PLAYERS];
        vector<int> _choice;                //dynamic memory allocation for path choice for optimized multiplayer
        Tile _tiles[_MAX_PLAYERS][_BOARD_SIZE]; //array of objects from other class (struct in this case)
        void displayTile(int player_index, int pos);
        void initializeTiles(int player_index);
    public:
        Board();
        Board(int player_count, vector<int> choice);
        void displayTrack(int player_index);
        void initializeBoard();
        void displayBoard();
        bool movePlayer(int player_index);

        int getPlayerPosition(int player_index) const;
        char getColor(int player_index);
        int getChoice(int player_index);

        void sendBack(int player_index);

};

#endif