#ifndef CHARA_H
#define CHARA_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Chara {
    private:
        string _name;
        int _strength, _stamina, _wisdom, _pride_points, _age;
        string _advisor;
        vector<string> _chosenAdvisors;
    public:
        Chara();
        Chara(string name, int strength, int stamina, int wisdom, int pride_points,  int age);

        string getName();
        string getAdvisor();
        int getStrength();
        int getStamina();
        int getWisdom();
        int getPridePoints();
        int getAge();
        vector<string> getChosenAdvisors();

        void setName(string name);
        void setStrength(int strength);
        void setStamina(int stamina);
        void setWisdom(int wisdom);
        void setPridePoints(int pride_points);
        void setAge(int age);
        void setAdvisor(string advisor);

        void addStrength(int strength);
        void addStamina(int stamina);
        void addWisdom(int wisdom);
        void addPridePoints(int pride_points);
        void addStats(int amount);

        void takeStrength(int strength);
        void takeStamina(int stamina);
        void takeWisdom(int wisdom);
        void takePridePoints(int pride_points);
        void takeStats(int amount);

        void trainCub(int strength, int stamina, int wisdom);
        void toPrideLands();
        void printStats();
        static void printAdvisorAbilities(int choice);
        static void printCharacterStats(int choice, string characters[5][6]);
        vector<string> chooseAdvisor(vector<string> chosenAdvisors);
};

#endif