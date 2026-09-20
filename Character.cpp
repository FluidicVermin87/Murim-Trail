#include "Character.h"
#include "Util.h"

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

//constructors

Chara::Chara() : _name(""), _strength(100), _stamina(100), _wisdom(100), _pride_points(0), _age(1){

}

Chara::Chara(string name, int strength, int stamina, int wisdom, int pride_points,  int age) : _name(name), _strength(strength), _stamina(stamina), _wisdom(wisdom), _pride_points(20000), _age(age) {
    if (strength < 100) {
        _strength = 100;
    }
    if (stamina < 100) {
        _stamina = 100;
    }
    if (wisdom < 100) {
        _wisdom = 100;
    }
}

//getters

string Chara::getName() 
{
    return _name;
}

string Chara::getAdvisor()
{
    return _advisor;
}

int Chara::getStrength() 
{
    return _strength;
}

int Chara::getStamina() 
{
    return _stamina;
}

int Chara::getWisdom() 
{
    return _wisdom;
}

int Chara::getPridePoints() 
{
    return _pride_points;
}

int Chara::getAge() 
{
    return _age;
}

vector<string> Chara::getChosenAdvisors()
{
    return _chosenAdvisors;
}

//setters

void Chara::setName(string name) 
{
    _name = name;
}

void Chara::setStrength(int strength) 
{
    _strength = strength;
}

void Chara::setStamina(int stamina) 
{
    _stamina = stamina;
}

void Chara::setWisdom(int wisdom) 
{
    _wisdom = wisdom;
}

void Chara::setPridePoints(int pride_points) 
{
    _pride_points = pride_points;
}

void Chara::setAge(int age) 
{
    _age = age;
}

void Chara::setAdvisor(string advisor) 
{
    _advisor = advisor;
}

//adders

void Chara::addStrength(int strength)
{
    _strength = _strength + strength;
}

void Chara::addStamina(int stamina)
{
    _stamina = _stamina + stamina;
}

void Chara::addWisdom(int wisdom)
{
    _wisdom = _wisdom + wisdom;
}

void Chara::addPridePoints(int pride_points)
{
    _pride_points = _pride_points + pride_points;
}

void Chara::addStats(int amount)
{
    _strength = _strength + amount;
    _wisdom = _wisdom + amount;
    _stamina = _stamina + amount;
}

//subtractors

void Chara::takeStrength(int strength)
{
    _strength = _strength - strength;
}

void Chara::takeStamina(int stamina)
{
    _stamina = _stamina - stamina;
}

void Chara::takeWisdom(int wisdom)
{
    _wisdom = _wisdom - wisdom;
}

void Chara::takePridePoints(int pride_points)
{
    _pride_points = _pride_points - pride_points;
}

void Chara::takeStats(int amount)
{
    _strength = _strength - amount;
    _wisdom = _wisdom - amount;
    _stamina = _stamina - amount;
}

//other member functions

void Chara::trainCub(int strength, int stamina, int wisdom) 
{
    setStrength(strength);
    setStamina(stamina);
    setWisdom(wisdom);
    setPridePoints(getPridePoints() - 5000);
}

void Chara::toPrideLands() 
{
    setStrength(getStrength() - 2000);
    setStamina(getStamina() - 1000);
    setWisdom(getWisdom() - 2000);
    setPridePoints(getPridePoints() + 5000);
}

void Chara::printStats() //fitting character id
{
    string yinYang = R"(
     _.ooo-._   
   .OOOP   _ '. 
  dOOOO   (_)  \
 OOOOOb         |
 OOOOOOb.       |
 OOOOOOOOb      |
  YOO(_)OOO    /
   'OOOOOY  _.'
     '""""''
    )";
    cout << "=========================================\n";
    cout << "            " << yinYang << "        ";
    cout << "\n=========================================\n";
    cout << "Name: " << _name << "   Age: " << getAge() << "\n";
    cout << "-----------------------------------------\n";
    cout << "Strength: " << _strength << "\n";
    cout << "Stamina:  " << _stamina << "\n";
    cout << "Wisdom:   " << _wisdom << "\n";
    cout << "-----------------------------------------\n";
    cout << "Reputation: " << _pride_points << "\n";
    cout << "=========================================\n";
}

void Chara::printAdvisorAbilities(int choice) //used several times so added as class member function
{
    switch (choice) {
        case 0: // Heavenly Lightning Blade Namgoong Hyun
            cout << "The internal arts of the Namgoong clan are second to none. Never experience fatigue from physical activities." << endl;
            break;
        case 1: // Heavenly Demon Cheon Baek
            cout << "The leader of the Heavenly Demon Divine Cult. As his disciple, you will find yourself unbothered by other cultists." << endl;
            break;
        case 2: // Wise Dragon Jaegal Sung
            cout << "A master of strategems and formations. Inheriting his knowledge will render traps and riddles useless against you." << endl;
            break;
        case 3: // Green Forest Chief Yoojin Kan
            cout << "The leader of the unorthodox faction. As his disciple, you will find yourself unbothered by bandits and other n'er-do-wells." << endl;
            break;
        case 4: // Shaolin Fist Dong-Hyeon Noe
            cout << "The head of the Shaolin temple, his spirit arts are unmatched. Inheriting his techniques will make you invulnerable to mental attacks." << endl;
            break;
        default:
            cout << "Invalid choice, please try again." << endl;
            break;
    }
}

void Chara::printCharacterStats(int choice, string characters[5][6])
{
    if (choice < 0 || choice > 5) {
        cout << "Invalid choice, please try again." << endl;
        return;
    }

    string name = characters[choice][0]; //data type conversions
    int age = stoi(characters[choice][1]);
    int strength = stoi(characters[choice][2]);
    int stamina = stoi(characters[choice][3]);
    int wisdom = stoi(characters[choice][4]);
    int pride_points = stoi(characters[choice][5]);

    cout << "Player: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "Strength: " << strength << endl;
    cout << "Stamina: " << stamina << endl;
    cout << "Wisdom: " << wisdom << endl;
    cout << "Reputation: " << pride_points << endl;
}

vector<string> Chara::chooseAdvisor(vector<string> chosenAdvisors)
{
    vector<string> advisors = {
        "Heavenly Lightning Blade Namgoong Hyun",
        "Heavenly Demon Cheon Baek",
        "Wise Dragon Jaegal Sung",
        "Green Forest Chief Yoojin Kan",
        "Shaolin Fist Dong-Hyeon Noe"
    };

    int choice1 = 0;
    char choice2;
    bool validChoice = false;
        
        while (!validChoice) {
            cout << "Choose an advisor:" << endl;
            for (int i = 0; i < advisors.size(); i++) {
                if (find(chosenAdvisors.begin(), chosenAdvisors.end(), advisors[i]) == chosenAdvisors.end()) {
                    cout << (i + 1) << ". " << advisors[i] << endl;
                }
            }
            cin >> choice1;

            if (cin.fail() || choice1 < 1 || choice1 > advisors.size()) {
                cout << "Invalid choice. Please enter a number between 1 and " << advisors.size() << "." << endl;
                continue;
            }
            
            choice1--;  //adjust for 0-based index
            
            if (find(chosenAdvisors.begin(), chosenAdvisors.end(), advisors[choice1]) != chosenAdvisors.end()) {
                cout << "This advisor has already been chosen. Please choose another advisor." << endl;
                continue;
            }

            // Handle advisor description and selection based on the chosen advisor
            printAdvisorAbilities(choice1);

            // Confirm if the player wants to accept the chosen advisor
            cout << "Accept " << advisors[choice1] << " as your advisor? Y/N: ";
            cin >> choice2;
            
            if (choice2 == 'Y' || choice2 == 'y') {
                // Add the chosen advisor to the chosenAdvisors vector
                chosenAdvisors.push_back(advisors[choice1]);
                _advisor = advisors[choice1];  // Set the character's advisor
                validChoice = true;
            } else if (choice2 == 'N' || choice2 == 'n') {
                cout << "Advisor selection canceled. Please choose another advisor." << endl;
                continue;
            } else {
                cout << "Invalid input. Please try again." << endl;
                continue;
            }
        }
    return chosenAdvisors;
}
   