/*****************************************
** File:    Farm.cpp
** Project: Project 4: Stardew Valley
** Author:  Matthew Makila
** Date:    4/5/21
** Section: 10/13
** E-mail:  mmakila1@umbc.edu
**
** This file is the implements the Farm class. The methods for constructing a farm
 * displaying the farm status, displaying the menu, choosing items and exiting are all defined here.
 * The most important Tick function is written here to manage the game's time and harvest items.
***********************************************/
#include "Farm.h"

enum {ADD=1, ADD_2=2, SIMULATE=3, STATUS=4, QUIT=5};
enum {ANIMAL=1, VEGETABLE, TREE};


// Name: Farm (Default constructor)
// Desc: Creates a Farm (with 6 food, 0 money, season = 1)
// Preconditions:  None
// Postconditions: A farm is created
Farm::Farm(){
    const int STARTER_FOOD = 6;
    m_food = STARTER_FOOD;
    m_money = 0;
    m_season = 1;

}

// Name: Farm (Destructor)
// Desc: Deallocates everything in the farm
// Preconditions:  None
// Postconditions: The farm is cleared out
Farm::~Farm(){
    // get rid of dynamically created AgItems
    for (unsigned int i = 0; i < m_farm.size(); i++){
        delete m_farm.at(i);
    }
}

// Name: ChooseItem
// Desc: Allows the user to choose either an animal, vegetable, or tree
// Preconditions:  None
// Postconditions: returns 1 (animal), 2 (vegetable), or 3 (tree) (reprompts for anything else)
int Farm::ChooseItem(){
    int type;
    // allow user to choose new item and return its type as an int
    do {
        cout << "Which agricultural item are you interested in?\n"
                "1. Animal\n"
                "2. Vegetable\n"
                "3. Tree" << endl;
        cin >> type;
    } while (type < ANIMAL || type > TREE);
    return type;
}

// Name: AddItem (int type, int quantity)
// Desc: Dynamically allocates new animals, vegetables, or trees and adds to m_farm
// Preconditions:  None
// Postconditions: Adds 1 (animal), 2 (vegetable), or 3 (tree) to m_farm
void Farm::AddItem(int type, int quantity){
    // create new AgItem (allocated)
    for (int i = 0; i < quantity; i++){
        if (type == ANIMAL){
            // dynamically create animal and add to farm
            AgItem* newAnimal = new Animal();
            m_farm.push_back(newAnimal);
            cout << "New Animal added to the farm." << endl;

        } else if (type == VEGETABLE){
            // create veggie and add to farm
            AgItem* newVeggie = new Vegetable();
            m_farm.push_back(newVeggie);
            cout << "New Vegetable added to the farm." << endl;

        } else {
            // create Tree and add to farm
            AgItem* newTree = new Tree();
            m_farm.push_back(newTree);
            cout << "New Tree added to the farm." << endl;
        }
    }
}

// Name: Tick (int season)
// Desc: Simulates a specific number of seasons
// For each season:
//               1. Calls Tick for each item in m_farm
//               2. Tries to harvest mature items (vegetables and fruit add food; animals money)
//               3. Removes anything harvested from m_farm
//               4. Displays the status automatically
// Preconditions:  None
// Postconditions: Time passes
void Farm::Tick(int time){
    const string TYPE_A = "Animal";
    const string TYPE_V = "Vegetable";
    const string TYPE_T = "Tree";
    bool hasFood;
    bool vegMax;
    bool treeHarvestable;

    // run ticks for amount of seasons to simulate
    int tickTime = m_season + time;
    while (m_season < tickTime){
        // create vector of harvested items to delete later
        vector<AgItem*> itemsHarvested;

        // call tick for each item in farm
        for (unsigned int i = 0; i < m_farm.size(); i++){
            // animal tick
            if (m_farm.at(i)->GetType() == TYPE_A){

                // if farm has food, animal gets fed and farm -1 food
                if (m_food > 0){
                    hasFood = true;
                    m_food -= 1;
                } else {
                    hasFood = false;
                }
                // call the animal tick
                m_farm.at(i)->Tick(hasFood); // THE IS-FED VAR

                // check if now harvestable ... harvest if it is

                if (m_farm.at(i)->GetIsHarvestable()){
                    m_money += m_farm.at(i)->Harvest();
                    // add specific index of this item to vector of items to delete
                    itemsHarvested.push_back(m_farm.at(i));
                }

            // veggie tick
            } else if (m_farm.at(i)->GetType() == TYPE_V) {
                vegMax = false;
                // call veggie tick to make it grow
                m_farm.at(i)->Tick(vegMax);

                // if veggie is harvestable, harvest it and add 2 food
                if (m_farm.at(i)->GetIsHarvestable()){
                    m_food += m_farm.at(i)->Harvest();
                    // add to items harvested
                    itemsHarvested.push_back(m_farm.at(i));
                }

            // tree tick
            } else if (m_farm.at(i)->GetType() == TYPE_T){
                treeHarvestable = false;
                m_farm.at(i)->Tick(treeHarvestable);

                // if age of tree is mature and ready to harvest add food for the fruit harvested
                if (m_farm.at(i)->GetIsHarvestable()){
                    int treeHarvest = m_farm.at(i)->Harvest();
                    if (treeHarvest == 0){
                        // tree is old (60) and harvested
                        itemsHarvested.push_back(m_farm.at(i));
                        m_food += 1;
                    } else {
                        // if returned 1, then add 1 food to farm
                        m_food += treeHarvest;
                    }
                }
            }
        }
        // display, then update season to next season
        cout << "SEASON: " << m_season << endl;
        // IF anything harvested, tell the user. use the index of harvested items
        for (unsigned int i = 0; i < itemsHarvested.size(); i++){
            for (unsigned int j = 0; j < m_farm.size(); j++){
                // DELETE and erase harvested items
                if (itemsHarvested.at(i) == m_farm.at(j)){
                    cout << "The " << m_farm.at(j)->GetType() << " was harvested." << endl;
                    delete m_farm.at(j);
                    // erase element at jth position
                    m_farm.erase(m_farm.begin()+j);
                }
            }
        }
        // display status and increment the season
        Status();
        cout << endl;
        m_season += 1;
    }

}

// Name: Menu
// Desc: Displays a menu with the following:
//     1. Add Item to Farm (adds a single item to m_farm)
//     2. Add Two of Each Item to Farm (Adds two of each item to m_farm)
//     3. Simulate Time (Asks the user how many seasons to simulate)
//     4. Farm Status (Displays the status of the farm)
//     5. Quit (Quits the simulation)
// Preconditions:  None
// Postconditions:  If returns 5, quits
int Farm::Menu(){
    const int ADD_2_QUANTITY = 2;
    int choice;
    do {
        cout << "1. Add Item to Farm\n"
                "2. Add Two of Each Item to Farm\n"
                "3. Simulate Time\n"
                "4. Farm Status\n"
                "5. Quit" << endl;
        cin >> choice;
    }while (choice < ADD || choice > QUIT);
    // switch between the options they chose
    switch (choice) {
        case ADD:
            // call choose item to have user choose their item, then add one of that item to farm
            int type;
            type = ChooseItem(); // ER
            AddItem(type, 1);
            break;
        case ADD_2:
            // add 2 of every item to the farm
            AddItem(ANIMAL, ADD_2_QUANTITY);
            AddItem(VEGETABLE, ADD_2_QUANTITY);
            AddItem(TREE, ADD_2_QUANTITY);
            break;
        case SIMULATE:
            // get the user choice for ticks (seasons)
            int tick_choice;
            do {
                cout << "How many seasons would you like to simulate?" << endl;
                cin >> tick_choice;
            } while (tick_choice <= 0);
            Tick(tick_choice); // ER
            break;
        case STATUS:
            Status(); // call display function
            break;
        case QUIT:
            //display exit message
            cout << "Thank you for simulating Stardew Valley!" << endl;
    }
    return choice;
}

// Name: StartSimulation
// Desc: Manages the introduction, menu, and quitting
// Preconditions:  Displays welcome message
// Postconditions: As long as menu doesn't return 5, keeps running
void Farm::StartSimulation(){
    // Instantiate welcome ...
    cout << "Welcome to Stardew Valley Simulator!" << endl;
    // MANAGE MENU
    int choice;
    do{
        // check that the user didn't quit and keep going
        choice = Menu();
    } while (choice != QUIT);
}

// Name: Status
// Desc: Displays farm food, money, season, and each agricultural item
// Preconditions:  None
// Postconditions: Displays farm data
void Farm::Status(){
    // display function
    cout << "**** Farm Status ****\n"
            "Food: " << m_food << "\n"
            "Money: " <<  m_money << "\n"
            "Season: " << m_season << endl;

    cout << "Agricultural Items:" << endl;
    if (m_farm.empty()){
        cout << "None." << endl;
    } else {
        // display all farm items by calling the overloaded operators
        for (unsigned int i = 0; i < m_farm.size(); i++){
            (*m_farm.at(i)) << cout << endl;
        }
    }
}
