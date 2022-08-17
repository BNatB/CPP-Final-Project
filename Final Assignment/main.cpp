#include <iostream>
#include <cstring>
#include <string>
#include <math.h>
#include <fstream>
#include <stack>
using namespace std;

class Entity
{
public:
    int health;
    int damageMod;
    int armour;
    string name;
    bool isBlocking;
    bool isDodging;
};

// literally just to hold data when returning from chosenCombatAction()
class Holder
{
public:
    Entity first;
    Entity second;
};

Holder chosenCombatAction(int userInput, Entity user, Entity target)
{
    // if user chose to attack
    if (userInput == 1)
    {
        cout << "\n"
             << user.name << " chose to attack " << target.name << endl;

        if (target.isBlocking == false)
        {
            int roll;
            // get the user's hit value taking in consideration if the target is dodging or blocking
            if (target.isDodging == true)
            {
                // roll twice, take lowest number
                int roll1 = rand() % 20 + 1;
                int roll2 = rand() % 20 + 1;

                if (roll1 < roll2)
                {
                    roll = roll1;
                }
                else
                {
                    roll = roll2;
                }
            }
            else
            {
                // just normal roll if the target is not dodging or blocking
                roll = rand() % 20 + 1;
            }

            // if target not blocking, only need 10 to hit
            if (roll >= 10)
            {
                cout << user.name << " lands a blow on " << target.name << "!" << endl;
                int damageRoll = rand() % 6 + 1 + user.damageMod; // roll damage
                cout << user.name << " dealt " << damageRoll << " damage to " << target.name << "!" << endl;
                target.health -= damageRoll; // subtract from health
            }
            // if the roll is not high enough
            else
            {
                cout << user.name << " misses!" << endl;
            }
        }
        // if target is blocking
        else
        {
            int roll;
            // get the user's hit value taking in consideration if the target is dodging or blocking
            if (target.isDodging == true)
            {
                // roll twice, take lowest number
                int roll1 = rand() % 20 + 1;
                int roll2 = rand() % 20 + 1;

                // assigns lowest roll
                if (roll1 < roll2)
                {
                    roll = roll1;
                }
                else
                {
                    roll = roll2;
                }
            }
            else
            {
                // normal roll if target is not blocking or dodging
                roll = rand() % 20 + 1;
            }

            // if target is blocking, must get above or equal to armour
            if (roll >= target.armour)
            {
                cout << user.name << " lands a blow on " << target.name << "!" << endl;
                int damageRoll = rand() % 6 + 1 + user.damageMod; // damage
                cout << user.name << " dealt " << damageRoll << " damage to " << target.name << "!" << endl;
                target.health -= damageRoll; // subtract from health
            }
            else
            {
                cout << user.name << " misses!" << endl;
            }
        }
        // set blocking and dodging to false to reset target
        target.isBlocking = false;
        target.isDodging = false;
        // ensures player can't do two things
        user.isBlocking = false;
        user.isDodging = false;
    }
    else if (userInput == 2)
    {
        cout << "\n"
             << user.name << " chose to block." << endl;
        user.isBlocking = true; // set blocking to true
    }
    else if (userInput == 3)
    {
        cout << "\n"
             << user.name << " chose to dodge." << endl;
        user.isDodging = true; // set dodging to true
    }

    // the holder is just to return two Entity objects
    Holder justToHoldData;
    justToHoldData.first = user;
    justToHoldData.second = target;

    return justToHoldData;
}

int main()
{
    cout << "Welcome to Nathaniel's Text-Combat-Game" << endl;
    string playerName;
    cout << "Enter your name: " << endl;
    cin >> playerName;

    cout << "Welcome " << playerName << ". Prepare for combat!" << endl;

    // create player object
    Entity player;
    player.health = 10;
    player.damageMod = 2;
    player.name = playerName;
    player.armour = 14;
    player.isBlocking = false;
    player.isDodging = false;

    // create first enemy. Meant to be easy
    Entity firstEnemy;
    firstEnemy.health = 10;
    firstEnemy.damageMod = 2;
    firstEnemy.name = "Small Goblin";
    firstEnemy.armour = 10;
    firstEnemy.isBlocking = false;
    firstEnemy.isDodging = false;

    cout << "\nBefore you stands a " << firstEnemy.name << "." << endl;

    // while both are not dead
    while (player.health > 0 && firstEnemy.health > 0)
    {
        // prompt user
        cout << "\nWhat would you like to do?" << endl;
        cout << "Type \'1\' to attack the " << firstEnemy.name << "." << endl;
        cout << "Type \'2\' to block." << endl;
        cout << "Type \'3\' to dodge." << endl;

        // record input
        int userInput;
        cin >> userInput;

        Holder playerHolder = chosenCombatAction(userInput, player, firstEnemy);
        player = playerHolder.first;
        firstEnemy = playerHolder.second;

        //make sure they can't do anything if they are dead
        if (firstEnemy.health > 0)
        {
            int enemyChoice = rand() % 3 + 1; // enemy make a choice
            Holder enemyHolder = chosenCombatAction(enemyChoice, firstEnemy, player);
            firstEnemy = enemyHolder.first;
            player = enemyHolder.second;
        }

        cout << "---------------------------------------------------------------------" << endl;
        cout << player.name << "'s health: " << player.health << endl;
        cout << firstEnemy.name << "'s health: " << firstEnemy.health << endl;
        cout << "---------------------------------------------------------------------" << endl;

        // if player dies
        if (player.health <= 0)
        {
            cout << player.name << " has been slain by " << firstEnemy.name << "!" << endl;
            cout << "GAME OVER" << endl;
            cout << "---------------------------------------------------------------------" << endl;
        }
        // if enemy dies
        else if (firstEnemy.health <= 0)
        {
            cout << firstEnemy.name << " has been slain by " << player.name << "!" << endl;
            cout << "Congratulations, you win!" << endl;
            cout << "---------------------------------------------------------------------" << endl;
        }
    }
    return 0;
}