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

vector<Chara> Tile::green(vector<Chara> players, int current_player, int choice, int chosen_advisor) //reads from event file and randomly chooses 1. advisors can protect from relevant detriments
{
    cout << "You move through the grasslands! Perhaps something unexpected will occur..." << endl;
    ifstream events_in("random_events.txt");
    vector<string> path0_events;
    vector<string> path1_events;
    string line;
    int randNum = rand() % 100;

    if (!events_in) {
        cout << "Error opening events file!" << endl;
        exit(1);
    }

    getline(events_in, line);
    getline(events_in, line);

    while (getline(events_in, line)) {
        if (line.empty()) continue;  // Skip empty lines
        string temp[4];  // Array to store the split character data
        int parts = Util::split(line, '|', temp, 4);

        if (parts == 4) {
            int path = stoi(temp[1]);

            if (path == 0) {
                path0_events.push_back(line);
            } else if (path == 1) {
                path1_events.push_back(line);
            }
        }
    }
    events_in.close();

    if (randNum <= 50 && randNum > 0 && choice == 0) {
        int randIndex = rand() % path0_events.size();
        string selectedEvent = path0_events[randIndex]; //different events for each path
        string temp[4];
        int parts = Util::split(selectedEvent, '|', temp, 4);

        if (parts == 4) {
            string description = temp[0];
            int advisor = stoi(temp[2]);
            int points_change = stoi(temp[3]);

            cout << description << endl;
            if (chosen_advisor == advisor) {
                cout << "Your advisor's ability protects you from a dangerous fate!" << endl;
            } else {
                if (points_change < 0) {
                    cout << points_change << " reputation" << endl;
                    players[current_player].takePridePoints(points_change);
                } else {
                    cout << "You gain " << points_change << " repuatation" << endl;
                    players[current_player].addPridePoints(points_change);
                }
            }
        }
    } else if (randNum <= 50 && randNum > 0 && choice == 1) {
        int randIndex = rand() % path1_events.size();
        string selectedEvent = path1_events[randIndex]; //ibid
        string temp[4];
        int parts = Util::split(selectedEvent, '|', temp, 4);

        if (parts == 4) {
            string description = temp[0];
            int advisor = stoi(temp[2]);
            int points_change = stoi(temp[3]);

            cout << description << endl;
            if (chosen_advisor == advisor) {
                cout << "Your advisor's ability protects you from a dangerous fate!" << endl;
            } else {
                if (points_change < 0) {
                    cout << points_change << " reputation" << endl;
                    players[current_player].takePridePoints(points_change);
                } else {
                    cout << "You gain " << points_change << " repuatation" << endl;
                    players[current_player].addPridePoints(points_change);
                }
            }
        }
    } else {
        cout << "It appears no strange events will happen to you today!" << endl;
    }
    return players;
}

pair<vector<Chara>, vector<string>> Tile::pink(vector<Chara> players, int current_player, vector<string> chosenAdvisors) //pair container return as this function needs to alter both chosen advisors and the characters' advisors
{
    bool validResponse = false;
    do {
        cout << "You happen upon a gathering of martial masters. You gain 300 wisdom from overhearing their conversation. Perhaps one would be willing to train you..." << endl;
        if (players[current_player].getAdvisor() == "") {
            cout << "You do not have an advisor. Would you like to choose one? (Y/N): ";
        } else {
            cout << "You already have an advisor: " << players[current_player].getAdvisor() << endl;
            cout << "Would you like to change advisors? (Y/N): ";
        }
        char response;
        cin >> response;
        if (response == 'Y' || response == 'y') {
            vector<string> advisors = players[current_player].chooseAdvisor(chosenAdvisors);
            string newAdvisor = advisors.back();
            players[current_player].setAdvisor(newAdvisor);
            validResponse = true;
        } else if (response == 'N' || response == 'n') {
            break;
        } else {
            cout << "Invalid input. Please try again" << endl;
            continue;
        }
    } while (!validResponse);
    return make_pair(players, chosenAdvisors);
}

vector<Chara> Tile::purple(vector<Chara> players, int current_player)
{
    ifstream riddles_in("riddles.txt");
    vector<string> riddle;
    string line;

    if (!riddles_in) {
        cout << "Riddles file failed to open!" << endl;
        exit(1);
    }

    cout << "You find a mysterious riddle while deciphering an ancient martial text. Perhaps solving it will increase your martial understanding..." << endl;
    getline(riddles_in, line);

    while(getline(riddles_in, line)) {
        if (line.empty()) continue;
        string temp[2];
        int parts = Util::split(line, '|', temp, 2);

        if (parts == 2) {
            riddle.push_back(line);
        }
    }
    riddles_in.close();

    srand(time(0));
    string temp2[2];
    int randIndex = rand() % riddle.size();
    string selectedEvent = riddle[randIndex];
    int parts2 = Util::split(selectedEvent, '|', temp2, 2);

    if (parts2 == 2) {
        string text = temp2[0];
        string answer = temp2[1];
        string response;

        cout << text << endl;
        cin.clear();
        cin.sync();
        cin.ignore(); //wait for response
        getline(cin, response);

        if (response == answer) {
            players[current_player].addWisdom(500);
            cout << "You have uncovered a secret! Your wisdom increases by 500." << endl;
        } else {
            cout << "You have failed to understand the profound writing and it's wisdom passes you by." << endl;
        }

    }
    return players;
}
            