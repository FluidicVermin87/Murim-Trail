#include "Board.h"
#include "Tile.h"

#define RED "\033[48;2;230;10;10m"
#define GREEN "\033[48;2;34;139;34m"
#define BLUE "\033[48;2;10;10;230m"
#define PINK "\033[48;2;255;105;180m"
#define BROWN "\033[48;2;139;69;19m"
#define PURPLE "\033[48;2;128;0;128m"
#define ORANGE "\033[48;2;230;115;0m"
#define GREY "\033[48;2;128;128;128m"
#define RESET "\033[0m"

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

void Board::initializeBoard() //two lane board
{
    for (int i = 0; i < 2; i++)
    {
        initializeTiles(i);
    }
}

void Board::initializeTiles(int player_index) //generation rules by color, track, and board half
{
    Tile temp;
    int green_count = 0;
    int total_tiles = _BOARD_SIZE;

    int track = player_index;  // Track choice for the current player

    while (green_count < 30) {
        int rand_index = rand() % (total_tiles - 2) + 1;
        if (_tiles[player_index][rand_index].color != 'G') {
            _tiles[player_index][rand_index].color = 'G';
            green_count++;
        }
    }

    if (track == 0) {  // path 0 (murim) generation rules
        for (int i = 0; i < total_tiles; i++) {
            if (_tiles[player_index][i].color == 'G') {
                continue;  //skip if it's a green tile
            }

            int randNum = rand() % 100; //players have a good chance of finding a master but also encountering trials

            if (i < total_tiles / 2) {
                if (randNum < 15) {
                    temp.color = 'B';  // Blue
                } else if (randNum < 40) {
                    temp.color = 'P';  // Pink
                } else if (randNum < 60) {
                    temp.color = 'N';  // Brown
                } else if (randNum < 70) {
                    temp.color = 'R';  // Red
                } else if (randNum < 100) {
                    temp.color = 'U';  // Purple
                } else {
                    temp.color = ' ';  // Empty tile
                }
            } else {  // Second half of the board. Characters have gained much wisdom and know what places to avoid
                if (randNum < 35) {
                    temp.color = 'B';
                } else if (randNum < 50) {
                    temp.color = 'P';
                } else if (randNum < 60) {
                    temp.color = 'N';
                } else if (randNum < 70) {
                    temp.color = 'R';
                } else if (randNum < 100) {
                    temp.color = 'U';
                } else {
                    temp.color = ' ';
                }
            }

            if (i == 0) {
                temp.color = 'Y';  //first tile is always grey
            } else if (i == total_tiles - 1) {
                temp.color = 'O';  //last tile is always orange
            }

            _tiles[player_index][i] = temp;  //store tile for player
        }
    } else if (track == 1) {  //path 1 Generation Rules (train at home)
        for (int i = 0; i < total_tiles; i++) {
            if (_tiles[player_index][i].color == 'G') {
                continue;  // Skip if it's a green tile
            }

            int randNum = rand() % 100; //few trials and much opportunity to learn safely

            if (i < total_tiles / 2) {
                if (randNum < 30) {
                    temp.color = 'B';  // Blue
                } else if (randNum < 60) {
                    temp.color = 'P';  // Pink
                } else if (randNum < 70) {
                    temp.color = 'N';  // Brown
                } else if (randNum < 80) {
                    temp.color = 'R';  // Red
                } else if (randNum < 100) {
                    temp.color = 'U';  // Purple
                } else {
                    temp.color = ' ';  // Empty tile
                }
            } else {  // Second half of the board. A lack of experience makes navigating the real world more difficult
                if (randNum < 10) {
                    temp.color = 'B';
                } else if (randNum < 30) {
                    temp.color = 'P';
                } else if (randNum < 60) {
                    temp.color = 'N';
                } else if (randNum < 90) {
                    temp.color = 'R';
                } else if (randNum < 100) {
                    temp.color = 'U';
                } else {
                    temp.color = ' ';
                }
            }
            if (i == 0) {
                temp.color = 'Y';  // First tile is always grey
            } else if (i == total_tiles - 1) {
                temp.color = 'O';  // Last tile is always orange
            }

            _tiles[player_index][i] = temp;  //store tile for player
        }
    }
}

Board::Board() //default constructor
{
    _player_count = 1;
    _player_position[0] = 0;
    initializeTiles(0);
}

Board::Board(int player_count, vector<int> choice) //parameterized constructor
{
    if (player_count > _MAX_PLAYERS)
    {
        _player_count = _MAX_PLAYERS;
    } else {
        _player_count = player_count;
    }

    _choice.resize(_player_count);

    for (int i = 0; i < _player_count; i++)
    {
        _player_position[i] = 0;
        _previous_position[i] = 0;
    }

    for (int i = 0; i < _player_count; i++) 
    {
        _choice[i] = choice[i];
    }

    initializeBoard();
}

void Board::displayTile(int player_index, int pos) //color assignment for each tile, also character printing
{
    string color = "";

    switch (_tiles[player_index][pos].color) {
        case 'R': color = RED; break;
        case 'G': color = GREEN; break;
        case 'B': color = BLUE; break;
        case 'U': color = PURPLE; break;
        case 'N': color = BROWN; break;
        case 'P': color = PINK; break;
        case 'O': color = ORANGE; break;
        case 'Y': color = GREY; break;
        default: color = RESET; break;
    }

    cout << color << "|"; //start with the opening delimiter

    bool printed = false; //check if any player was printed for this tile

    for (int i = 0; i < _player_count; i++) {
        bool isOnTile = (_player_position[i] == pos && _choice[i] == player_index);

        if (isOnTile) {
            if (printed) {
                //if a player is already printed, add an ampersand before the next player
                cout << "&" << (i + 1);
            } else {
                //if first player, just print the number
                cout << (i + 1);
                printed = true;
            }
        }
    }

    if (!printed) {
        cout << " "; //empty space for unoccupied tiles
    }

    //closing delimiter
    cout << "|";
    cout << RESET;
}

void Board::displayTrack(int player_index) //display all tiles in a row
{
    for (int i = 0; i < _BOARD_SIZE; i++)
    {
        displayTile(player_index, i);
    }
    cout << endl;
}

void Board::displayBoard() //display both tracks
{
    for (int i = 0; i < 2; i++)
    {
        displayTrack(i);

        if (i == 0) {
            cout << endl;
        }
    }
}

bool Board::movePlayer(int player_index) //player by a random number between 1 and 6
{
    int mov = rand() % 6 + 1;
    cout << "You rolled a " << mov << "!" << endl; //printed random output
    int newpos = _player_position[player_index] + mov;
    _previous_position[player_index] = _player_position[player_index]; //preserve previous position for red/brown tiles

    if (newpos >= _BOARD_SIZE) { //ensures player stops at last tile
        newpos = _BOARD_SIZE - 1; 
    }

    _player_position[player_index] = newpos; //update position

    if (_player_position[player_index] == _BOARD_SIZE - 1) { //true if at end
        return true;
    }
    return false;
}

// getters

int Board::getPlayerPosition(int player_index) const //const so as not to change
{
    if (player_index >= 0 && player_index <= _player_count) 
    {
        return _player_position[player_index];
    }
    return -1;
}

char Board::getColor(int player_index) 
{
    int track = _choice[player_index];
    return _tiles[track][_player_position[player_index]].color;
}

int Board::getChoice(int player_index)
{
    return _choice[player_index];
}

//red/brown tile function

void Board::sendBack(int player_index)
{
    if (getColor(player_index) == 'R') {
        int newpos = _player_position[player_index] -= 10;
        if (newpos < 0) {
            newpos = 0;
        }
        _player_position[player_index] = newpos;
    } else if (getColor(player_index) == 'N') {
        _player_position[player_index] = _previous_position[player_index];
    }
}
