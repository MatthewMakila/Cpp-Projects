/*****************************************
** File:    Game.cpp
** Project: Project 2: No Man's Alchemy
** Author:  Matthew Makila
** Date:    3/9/21
** Section: 10/13
** E-mail:  mmakila1@umbc.edu
**
** This file executes the functionality for the game by implementing
 * its class methods. The Game Constructor is called to set up a game (creating a
 * player's ship), the game starts
 * and then loops through the various options 1 - 5 until the user quits
 * or wins by crafting 4 unique items with the CombineMaterials method.
***********************************************/

#include "Game.h"

/* Name: Game() Default Constructor
  // Desc - Builds a new game by:
  // 1. Loads all materials and their recipes into m_materials
  // 2. Asks user for their Ship's name (store in m_myShip as m_myName)
  // 3. Copies all materials from m_materials into the Ship's material array
  // Preconditions - None
  // Postconditions - m_materials is populated
  */
Game::Game(){
    // call the method to load materials
    GameTitle();
    LoadMaterials();
    // initialize the user's ship
    string m_myName;
    cout << "What is the name of your ship?" << endl;
    getline(cin, m_myName);
    m_myShip = Ship(m_myName);

    // POPULATE SHIP's MATERIALS!
    for (int i = 0; i < PROJ2_SIZE; i++){
        m_myShip.AddMaterial(m_materials[i]);
    }
}

// Name: LoadMaterials
// Desc - Loads each material into m_materials from file
// Preconditions - Requires file with valid material data
// Postconditions - m_material is populated with material structs
void Game::LoadMaterials(){
    ifstream materialFile(PROJ2_DATA);
    if (materialFile.is_open()){
        int count = 0;
        for (int i = 0; i < PROJ2_SIZE; i++){
            // implement getline to take in the file input and separate data by commas using the ',' delimiter.
            string name; string type; string material1; string material2;
            getline(materialFile, name,',');
            getline(materialFile, type,',');
            getline(materialFile, material1,',');
            getline(materialFile, material2);
            // create material object and add to the m_materials array
            Material myMaterial(name, type, material1, material2, 0);
            m_materials[i] = myMaterial;
            count++;
        }
        materialFile.close();
        cout << count << " Materials loaded." << endl;
    }
}

// Name: StartGame()
// Desc - Manages the game itself including win conditions continually
//         calling the main menu
// Preconditions - Player is placed in game
// Postconditions - Continually checks to see if player has entered 5
void Game::StartGame() {
    // prompt the main menu and utilize the player's option
    /**
     * Huge but smallish issue for OH: Fix the extra loop glitch...
     */
    int playerChoice = 0;
    // Continue the game if the user does not quit or win
    while(playerChoice != QUIT && m_myShip.GetRank() != WIN_RANK){
        playerChoice = MainMenu();
    }
    cout << "Good-bye!" << endl;
    if (m_myShip.GetRank() == WIN_RANK){
        cout << " Congrats! You escaped!" << endl;
    }
}


// Name: DisplayMyMaterials()
// Desc - Displays the Ship's materials (Uses GetMaterial)
// Preconditions - Player's Ship has materials
// Postconditions - Displays a numbered list of materials
void Game::DisplayMaterials(){
    // Menu Option 1, lists out every material and its quantity
    for (int i = 0; i < PROJ2_SIZE; i++){
        cout << i + 1 << ". " << m_myShip.GetMaterial(i).m_name << " " << m_myShip.GetMaterial(i).m_quantity << endl;
    }
}

// Name: MainMenu()
// Desc - Displays and manages menu. Also checks win condition (Ship reaches S rank).
// Preconditions - Player has a Ship
// Postconditions - Returns number including exit
int Game::MainMenu(){
    int choice;
    // prompts the user for a number 1 - 5
    do {
        cout << "\nWhat would you like to do?\n1. Display your Ship's Materials\n"
                "2. Search for Raw Materials\n3. Attempt to Merge Materials\n"
                "4. See Score\n5. Quit\n" << endl;
        cin >> choice;
    } while (choice < DISPLAY || choice > QUIT);
    // chooses path based on choice
    switch (choice){
        case DISPLAY:
            DisplayMaterials(); // works!
            break;
        case SEARCH:
            SearchMaterials(); // works!
            break;
        case COMBINE:
            CombineMaterials(); // works!
            break;
        case SCORE:
            CalcScore(); // works!
            break;
    }
    // checks win condition and returns quit or simply returns user choice
    if (m_myShip.GetRank() == WIN_RANK){
        return QUIT;
    } else {
        return choice;
    }
}

// Name: SearchMaterials()
// Desc - Attempts to search for raw materials (must be type "raw")
// Preconditions - Raw materials loaded
// Postconditions - Increases quantity in Ship's possession of materials
void Game::SearchMaterials(){
    // Menu Option 2
    int maxNum = PROJ2_SIZE - 1; int minNum = 0;
    bool notFound = true;
    while (notFound){
        // produce rand index in range but only "find" element if raw. Search until raw element is found
        int randIndex = rand() % (maxNum - minNum + 1) + minNum;
        if (m_myShip.GetMaterial(randIndex).m_type == "raw"){
            notFound = false;
            // increases quantity of item "found"
            m_myShip.IncrementQuantity(m_myShip.GetMaterial(randIndex));
            cout << m_myShip.GetMaterial(randIndex).m_name << " Found!" << endl;
        }
    }
}

// Name: CombineMaterials()
// Desc - Attempts to combine known materials. If combined, quantity of material decreased
// Preconditions - Ship is populated with materials
// Postconditions - Increments quantity of item "made", decreases quantity of source items
void Game::CombineMaterials(){
    int m1_idx;
    int m2_idx;
    // initializes the user-entered material indices for both materials
    for (int i = 0; i < 2; i++){
        int choice;
        RequestMaterial(choice);
        if (i == 0){
            m1_idx = choice - 1;
        } else if (i == 1){
            m2_idx = choice - 1;
        }
    }
    // checks if there are at least one of each material to combine
    if (!(m_myShip.CheckQuantity(m_myShip.GetMaterial(m1_idx), m_myShip.GetMaterial(m2_idx)))){
        // check if two items even had valid recipe
        int checkMergePossibility = SearchRecipes(m_myShip.GetMaterial(m1_idx).m_name,
                                                  m_myShip.GetMaterial(m2_idx).m_name);
        if (checkMergePossibility == -1){
            cout << "That merge could not be attempted!" << endl;
        // if recipe was valid, simply tell user not enough items
        } else {
            cout << "You do not have enough " << m_myShip.GetMaterial(m1_idx).m_name << " or " <<
            m_myShip.GetMaterial(m2_idx).m_name << " to attempt that merge" << endl;
        }
    // if enough of each, attempts to merge
    } else {
        // once quantities confirmed: check which element in the material list uses the given materials to be created
        int productItem;
        productItem = SearchRecipes(m_myShip.GetMaterial(m1_idx).m_name,
                                    m_myShip.GetMaterial(m2_idx).m_name);
        // if you returned -1, that means the merge could not be identified or you are trying to make more than 1 unique
        if (productItem == -1 || (m_myShip.GetMaterial(productItem).m_quantity > 1 &&
        m_myShip.GetMaterial(productItem).m_type == "unique")){
            cout << "That merge could not be attempted!" << endl;
        } else {
            // call the ship increment (for item made) and decrement (for items used) functions
            m_myShip.IncrementQuantity(m_myShip.GetMaterial(productItem));
            m_myShip.DecrementQuantity(m_myShip.GetMaterial(m1_idx));
            m_myShip.DecrementQuantity(m_myShip.GetMaterial(m2_idx));
            cout << m_myShip.GetMaterial(m1_idx).m_name << " combined with " << m_myShip.GetMaterial(m2_idx).m_name
            << " to produce " << m_myShip.GetMaterial(productItem).m_name << endl;
            cout << "You have built " << m_myShip.GetMaterial(productItem).m_name << " for your ship." << endl;
            // increase ship rank if unique item was formed
            if (string(m_myShip.GetMaterial(productItem).m_type) == "unique"){
                m_myShip.IncRank();
            }
        }
    }
}

// Name: RequestMaterial()
// Desc - Requests material to use to merge
// Preconditions - Ship has materials to try and merge
// Postconditions - Returns integer of item selected by user
void Game::RequestMaterial(int &choice){
    do {
        // ask user for a material to merge. If they enter -1, display known materials and wait for their choice
        cout << "What materials would you like to merge?\nTo list known materials, enter -1" << endl;
        cin >> choice;
        if (choice == -1){
            DisplayMaterials();
        }
    } while (choice < 0 || choice > PROJ2_SIZE);
}

// Name: SearchRecipes()
// Desc - Searches recipes for two strings (name of item)
// Preconditions - m_materials is populated
// Postconditions - Returns int index of matching recipe
int Game::SearchRecipes(string item1, string item2){
    for (int i = 0; i < PROJ2_SIZE; i++){
        // check if any element's required materials (in any order user enters) matches the user-given elements
        if ((string(m_materials[i].m_material1) == item1 && string(m_materials[i].m_material2) == item2)
        || (string(m_materials[i].m_material1) == item2 && string(m_materials[i].m_material2) == item1)){
            return i;  // int index of matching recipe
        }
    }
    return -1;
}

// Name: CalcScore()
// Desc - Displays current score for Ship
// Preconditions - Ship is populated with materials
// Postconditions - Displays total
void Game::CalcScore(){
    // Menu Option 4, receives the rank of the ship
    cout << "The Great Ship " << m_myShip.GetName() << endl;
    cout << "Ship Rank: " << m_myShip.GetRank() << endl;
}
