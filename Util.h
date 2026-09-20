#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Util { //structure for functions that are needed in multiple files but don't fit with other classes
    static int split(string input_string, char separator, string arr[], const int ARR_SIZE) //used in several files for file parsing
    {
        string str = input_string;
        int marker = 0;
        int count = 0;
        int length = str.size();

        if (str == "") {
            return 0;
        }

        for (int i = 0; i <= length; i++) {
            if (str[i] == separator || str[i] == '\0') {
                if (count < ARR_SIZE) {
                    string cut;

                    for (int j = marker; j < i; j++) 
                    {
                        cut += str[j]; 
                    }
                    arr[count] = cut;
                    count++;
                    marker = i + 1;
                } else {
                    return -1;
                }
            }
        }
        return count;
    }

    static int advisorComp (string advisor)  //used frequently to accomodate for the fact that vector members are added from the back (keep numbers consistent). didn't fit elsewhere
    {
        if (advisor == "Heavenly Lightning Blade Namgoong Hyun") {
            return 0;
        } else if (advisor == "Heavenly Demon Cheon Baek") {
            return 1;
        } else if (advisor == "Wise Dragon Jaegal Sung") {
            return 2;
        } else if (advisor == "Green Forest Chief Yoojin Kan") {
            return 3;
        }else if (advisor == "Shaolin Fist Dong-Hyeon Noe") {
            return 4;
        } else {
            return 5;
        }
    }   
};

#endif