#include "Tile.h"
#include "Board.h"
#include "Character.h"
#include "Util.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>

using namespace std;

vector<Chara> chooseChara(int player_count) 
{
    ifstream file_in("characters.txt");
    const int MAX_SIZE = 5;
    string characters[MAX_SIZE][6];
    bool characterAvailable[MAX_SIZE] = {true, true, true, true, true};
    string line;
    int line_count = 0;
    int choice = 0;
    bool chosen = false;

    if (player_count < 2 || player_count > 5) {
        cout << "Invalid number of players. Must be between 1 and 5." << endl;
        exit(1);
    }

    if (file_in.fail()) {
        cout << "Could not open the character file." << endl;
        exit(1);
    }

    getline(file_in, line);

    while (getline(file_in, line)) {
        if (line.empty()) continue;  // Skip empty lines
        string temp[6];  // Array to store the split character data
        int parts = Util::split(line, '|', temp, 6);

        //if the split was successful, store the data
        if (parts == 6) {
            for (int i = 0; i < 6; i++) {
                characters[line_count][i] = temp[i];
            }
            line_count++;
        }
    }
    file_in.close();

    vector<Chara> players;

        for (int i = 0; i < player_count; i++) 
        {
            do {
                cout << "Player " << (i + 1) << ", choose your character: " << endl;

                //display available characters
                for (int j = 0; j < line_count; j++) {
                    if (characterAvailable[j]) {
                        cout << j + 1 << ": " << characters[j][0] << endl;
                    }
                }

                cout << "Enter the number of your choice: ";
                cin >> choice;
                if (choice >= 1 && choice <= 5) {
                    choice--;  //adjust to zero based index
                } else {
                    cout << "invalid input" << endl;
                    chosen = false;
                }
                

                //check if the character is available
                if (choice < 0 || choice >= line_count || !characterAvailable[choice]) {
                    cout << "Invalid choice or character already selected. Please try again." << endl;
                    i--;
                    continue;
                }

                Chara::printCharacterStats(choice, characters);
                cout << "Choose this character? Y/N" << endl;
                char choice2;
                cin >> choice2;
                if (choice2 == 'Y' || choice2 == 'y') {
                    //convert data types to usable values
                    string name = characters[choice][0];
                    int age = stoi(characters[choice][1]);
                    int strength = stoi(characters[choice][2]);
                    int stamina = stoi(characters[choice][3]);
                    int wisdom = stoi(characters[choice][4]);
                    int pride_points = stoi(characters[choice][5]);
                    

                    //create object
                    players.push_back(Chara(name, strength, stamina, wisdom, pride_points, age));

                    //character is chosen
                    characterAvailable[choice] = false;
                    chosen = true;
                } else if (choice2 == 'N' || choice2 == 'n') {
                    chosen = false;
                } else {
                    cout << "Invalid choice. Please try again." << endl;
                    continue;
                }
            } while (chosen == false);
        }
    file_in.close();

    return players;
}

int choosePath() 
{
    int choicePath = 0;

    do {
        cout << "You have two options to begin your martial journey:" << endl;
        cout << "1. Enter the Jianghu to search for a renowned master to teach you. Beware, the martial world is rarely kind to the unaquainted" << endl; //path 1 (or 0 in 0-base index) - top lane
        cout << "2. Remain at home and build up your marial arts foundation with the resurces available to you. This option is safer, but you will not have as strong of a reputation" << endl; // path 2 (or 1 in 0-base index) - bottom lane
        cin >> choicePath;
        if (choicePath < 1 || choicePath > 2) {
            cout << "Invalid" << endl;
            continue;
        }
    } while (choicePath < 1 || choicePath > 2);

    return choicePath - 1;
}

Board mainMenu (vector<Chara> players, Board board, int player_count, int current_player) {
    //main menu to be brought up every turn to each player
        int ch = 0;
        char choice;
        string advisor = players[current_player].getAdvisor();
        int adv_int = Util::advisorComp(advisor);
        do {
            cout << "        Main Menu" << endl;
            cout << "============================" << endl;
            cout << "1. Check Reputation" << endl;
            cout << "----------------------------" << endl;
            cout << "2. Review Character" << endl;
            cout << "----------------------------" << endl;
            cout << "3. View Position" << endl;
            cout << "----------------------------" << endl;
            cout << "4. Review your Advisor" << endl;
            cout << "----------------------------" << endl;
            cout << "5. Move Forward" << endl;
            cout << "----------------------------" << endl;
            cin >> ch;
            if (ch < 1 || ch > 5) {
                cout << "Invalid choice" << endl;
                continue;
            }
            switch (ch) {
                case 1:
                    cout << "Current reputation: " << players[current_player].getPridePoints() << endl;
                    break;
                case 2:
                    players[current_player].printStats();
                    cout << "Would you like to view the your maximum possible reputation (a function of other stats + current reputation)? Y/N" << endl; //same function as victory calc. also submenu 1
                    cin >> choice;
                    if (choice == 'Y' || choice == 'y') {
                        for (int i = 0; i < player_count; i++) 
                        {
                        int strength = players[i].getStrength();
                        int stamina = players[i].getStamina();
                        int wisdom = players[i].getWisdom();
                        int startPride = players[i].getPridePoints();

                        int pride_points = (wisdom * 10) + (stamina * 10) + (strength * 10) + startPride;
                        
                        cout << "Player " << (i + 1) << " max reputation:" << pride_points << endl; 
                        
                        }
                    } else if (choice == 'N' || choice == 'n') {
                        break;
                    } else {
                        continue;
                    }
                    break;
                case 3:
                    cout << "Your current position is: " << board.getPlayerPosition(current_player) << "/52." << endl;
                    cout << "You are on a " << board.getColor(current_player) << " tile" << endl; //make it print full color name
                    break;
                case 4:
                    do {
                        cout << "Your current advisor is: " << advisor << endl;
                        cout << "Would you like to review this advisor's ability? Y/N" << endl; //submenu 2
                        cin >> choice;
                        if (choice == 'Y' || choice == 'y') {
                            Chara::printAdvisorAbilities(adv_int);
                        } else if (choice == 'N' || choice == 'n') {
                            break;
                        } else {
                            cout << "Invalid Choice. Please try again." << endl;
                            continue;
                        }
                    } while (choice != 'Y' || choice != 'y' || choice != 'N' || choice != 'n');
                    break;
                case 5:
                    board.movePlayer(current_player);
                    break;
            }
        } while (ch != 5);
    return board;
}

int endCheck(int player_count, vector<Chara> players, int endCount) //victory checking, printing, and file writing
{
    vector<int> finalPride;
    int highest = 0;
    int winner = 0;
    ofstream winner_out("winner.txt");

    if (endCount == player_count) {
        for (int i = 0; i < player_count; i++) {
            int strength = players[i].getStrength();
            int stamina = players[i].getStamina();
            int wisdom = players[i].getWisdom();
            int startPride = players[i].getPridePoints();

            int pride_points = (wisdom * 10) + (stamina * 10) + (strength * 10) + startPride;
            finalPride.push_back(pride_points);
            winner_out << "Player " << (i + 1) << ": " << strength << " " << stamina << " " << wisdom << " " << pride_points << endl;
            
            cout << "Player " << (i + 1) << ": " << strength << " " << stamina << " " << wisdom << " " << pride_points << endl; 
            
        }
    }
    for (int i = 0; i < finalPride.size(); i++) 
    {
        if (finalPride[i] > highest) {
            highest  = finalPride[i];
            winner = i;
        }
    }
    winner_out << "Player " << (winner + 1) << " Wins!" << endl;
    return winner;
}

int main () // ** MAIN ** //
{ //game setup
    int player_count = 0;
    do {
        cout << "How many people are playing? (Max 5)" << endl;
        cin >> player_count;
        if (player_count < 2 || player_count > 5) {
            cout << "Invalid number of players" << endl;
            continue;
        }
    } while (player_count < 2 || player_count > 5);

    vector<Chara> players = chooseChara(player_count);
    vector<int> choice(player_count);
    vector<string> chosenAdvisors;

    for (int i = 0; i < player_count; i++) //adjustment for path type
    {
        int path = choosePath();
        choice.at(i) = path;
        if (path == 0) {
            players[i].addPridePoints(5000);
            players[i].addStats(200);
        } else if (path == 1) {
            players[i].takePridePoints(5000);
            players[i].addStats(500);
            players[i].addWisdom(500);
        }
    }
    for (int i = 0; i < player_count; i++) {
        if (choice.at(i) == 1) {
            chosenAdvisors = players[i].chooseAdvisor(chosenAdvisors);
        }
    }
    
    srand(time(0));
    Board board(player_count, choice);

    bool gameWon = false;

    board.displayBoard();
//end game setup
    do { //main game loop
        for (int i = 0; i < player_count; i++) 
        {
            if (board.getPlayerPosition(i) == 51) {
                continue;
            }
            cout << "Player " << (i + 1) << "'s turn" << endl;

            board = mainMenu(players, board, player_count, i);
            char current_color = board.getColor(i);
            int choice = board.getChoice(i);
            string advisor = players[i].getAdvisor();
            int advisor_num = Util::advisorComp(advisor);
            pair<vector<Chara>, vector<string>> result;

            switch (current_color) {
                case 'G':
                    players = Tile::green(players, i, choice, advisor_num);
                    break;
                case 'B':
                    cout << "You found a safe space to circulate your qi! you gain 200 strength, stamina, and wisdom" << endl;
                    players[i].addStats(200); 
                    break;
                case 'P':
                    result = Tile::pink(players, i, chosenAdvisors);
                    players = result.first;
                    chosenAdvisors = result.second;
                    players[i].addWisdom(300);
                    break;
                case 'R':
                    cout << "You are attacked by Jiangshi at night. You lose 100 of each stat fighting them before retreating" << endl; 
                    players[i].takeStats(100);
                    board.sendBack(i);
                    break;
                case 'N':
                    cout << "You encounter a rogue criminal. You expend 300 stamina fighting them before retreating to your previous location." << endl;
                    players[i].takeStamina(300);
                    board.sendBack(i);
                    break;
                case 'U':
                    players = Tile::purple(players, i);
                    break;
            }
            board.displayBoard();
                                    //victory checking
            vector<int> atEnd;
            int endCount = 0;
            int winner;

            for (int i = 0; i < player_count; i++) 
            {
                int end = board.getPlayerPosition(i);
                atEnd.push_back(end);
            }

            for (int i = 0; i < atEnd.size(); i++) 
            {
                if (atEnd.at(i) == 51)
                endCount++;
            }

            if (endCount == player_count) {
                winner = endCheck(player_count, players, endCount);
                gameWon = true;
            }

            if (gameWon) {
                cout << "Player " << (winner + 1) << " wins!" << endl;
                break;
            }
        }
    } while(!gameWon);
    return 0;
}