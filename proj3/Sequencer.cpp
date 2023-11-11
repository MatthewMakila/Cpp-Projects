/*****************************************
** File:    Sequencer.cpp
** Project: Project 3: DNA Sequencing
** Author:  Matthew Makila
** Date:    3/22/21
** Section: 10/13
** E-mail:  mmakila1@umbc.edu
**
** This file contains the sequencer methods and constructor/destructor written out. The
 * methods allow for various DNA methods to be used in order to compare sequences
 * reverse them, and display them. The constructor and destructor are called here
 * to initialize data and then destroy it to prevent leaks.
***********************************************/

#include "Sequencer.h"

// Name: Sequencer (constructor)
// Desc: Creates a Sequencer to hold multiple DNA strands from a file
// Preconditions:  None
// Postconditions: A sequencer created to populate m_suspects and m_evidence
Sequencer::Sequencer(string fileName) {
    // set file name, load strands, then call main menu
    m_fileName = fileName;
    ReadFile();
    MainMenu();
}

// Name:  Sequencer (destructor)
// Desc: Deallocates all dynamic aspects of a Sequencer
// Preconditions: There is an existing DNA strand (linked list)
// Postconditions: All vectors are cleared of DNA strands
Sequencer::~Sequencer() {
    // delete all allocated DNA strands in the sequencer (both suspect and evidence)
    for (unsigned int i = 0; i < m_suspects.size(); i++){
        delete m_suspects[i];
    }
    for (unsigned int i = 0; i < m_evidence.size(); i++){
        delete m_evidence[i];
    }
}

// Name:  DisplayStrands
// Desc: Displays each strand in both m_suspects and m_evidence
// Preconditions: At least one linked list is in either m_suspects or m_evidence
// Postconditions: Displays DNA strand from one of the vectors
void Sequencer::DisplayStrands() {
    // display each vector's strands using overloaded <<
    // print out suspect strand(s)
    for (unsigned int i = 0; i < m_suspects.size(); i++){
        cout << m_suspects[i]->GetName() << "\n" << *m_suspects[i] << endl;
    }
    // print out the evidence DNA strand(s)
    for (unsigned int i = 0; i < m_evidence.size(); i++){
        cout << m_evidence[i]->GetName() << "\n" << *m_evidence[i] << endl;
    }
}

// Name:  ReadFile
// Desc: Reads in a file that has the name on one line then the sequence on the next
//       All sequences will be an indeterminate length. There are an indeterminate number of
//       sequences in a file. Hint: Read in the entire sequence into a string then go char
//       by char until you hit a new line break. Then insert to the correct vector
// Preconditions: Valid file name of characters (Either A, T, G, or C)
// Postconditions: Populates each DNA strand and puts in either m_suspects or m_evidence
void Sequencer::ReadFile() {
    const char SUSPECT = 'S';
    const char EVIDENCE = 'E';
    const char SEPARATOR = ',';
    ifstream dataFile(m_fileName);
    string name;
    string nucleotide;

    if (dataFile.is_open()){
        int count = 0;
        while(dataFile >> name){
            dataFile >> nucleotide;
            // cout << name << endl;
            // cout << nucleotide << endl;

            //create new DNA object
            DNA *strand = new DNA(name);

            if (name[0] == SUSPECT){
                //it's a suspect's strand, separate by commas
                for (int i = 0; i < int(nucleotide.length()); i++){
                    if (nucleotide[i] != SEPARATOR){
                        // create new DNA node
                        strand->InsertEnd(nucleotide[i]);
                    }
                }
                // add to suspect vector
                m_suspects.push_back(strand);
                count++;

            } else if (name[0] == EVIDENCE){
                // it's an evidence strand, sep by commas
                for (int i = 0; i < int(nucleotide.length()); i++){
                    if (nucleotide[i] != SEPARATOR){
                        // create new DNA node
                        strand->InsertEnd(nucleotide[i]);
                    }
                }
                // add to evidence vector
                m_evidence.push_back(strand);
                count++;
            }

        }
        dataFile.close();
        cout << count << " strands loaded." << endl;
    }
}

// Name:  MainMenu
// Desc: Displays the main menu and manages exiting
// Preconditions: Populated m_suspects and m_evidence
// Postconditions: None
void Sequencer::MainMenu() {
    enum choices {
        DISPLAY=1, REVERSE=2, CHECK=3, EXIT=4
    };

    int choice;

    // prompt the user to enter a viable menu choice and choose path based on choice
    do {
        do {
            cout << "What would you like to do?:\n"
                    "1. Display Strand\n"
                    "2. Reverse Sequence\n"
                    "3. Check Suspects\n"
                    "4. Exit" << endl;
            cin >> choice;
        } while(choice < DISPLAY || choice > EXIT);

        // depending on the choice, do something here
        switch (choice){
            case DISPLAY:
                DisplayStrands(); // works!
                break;
            case REVERSE:
                ReverseSequence(); // works!
                break;
            case CHECK:
                CheckSuspects(); // works!
                break;
            case EXIT:
                cout << "DNA removed from memory\n"
                        "Deleting Suspects\n"
                        "Deleting Evidence\n" << endl;
        }
    } while (choice != EXIT);
}

// Name:  CheckSuspects
// Desc: Iterates through each DNA strand in m_suspects to see if there is a match from
//       m_evidence. Displays each suspect strand where the evidence matches
// Preconditions: Populated m_suspects and m_evidence
// Postconditions: Displays each suspect that has a match
void Sequencer::CheckSuspects() {
    cout << "Checking all suspects vs. evidence ..." << endl;
    bool matchChecker;
    int multipleMatch = 0;
    // check all suspects against each evidence (nested for loop to check suspect matches to every evidence)
    for (unsigned int i = 0; i < m_suspects.size(); i++){
        for (unsigned int j = 0; j < m_evidence.size(); j++){
            // compare each suspect to the evidence and call compare sequence from DNA.cpp
            matchChecker = m_suspects[i]->CompareSequence(*m_evidence[j]);
            // if it's a match, let them know
            if (matchChecker) {
                cout << m_suspects[i]->GetName() << " matches " << m_evidence[j]->GetName() << endl;
                multipleMatch++;
            // if it matches no evidence, tell them that
            } else {
                cout << m_suspects[i]->GetName() << " does NOT match " << m_evidence[j]->GetName() << endl;
            }
            // if it matches all evidence, tell them that
            if (multipleMatch == int(m_evidence.size())){
                cout << m_suspects[i]->GetName() << " matches ALL evidence" << endl;
                multipleMatch = 0;
            }
        }
    }
    cout << endl;
}

// Name: ReverseSequence
// Desc: User chooses a sequence from m_suspects or m_evidence and the sequence is reversed
// Preconditions: Populated m_suspects and m_evidence
// Postconditions: Reverses a specific sequence replacing in place
void Sequencer::ReverseSequence() {
    const int SUSPECT = 1, EVIDENCE = 2;
    int choice;
    // prompts user to choose a sequence to reverse from suspects or evidence
    do {
        cout << "Which type of sequence to reverse?\n"
                "1. Suspect\n"
                "2. Evidence" << endl;
        cin >> choice;
    }
    while (choice < SUSPECT || choice > EVIDENCE);
    // based on user choice, prompt user to select a specific strand from the evidence or suspects list
    if (choice == SUSPECT){
        int susChoice;
        // ask which sequence to reverse if more than 1
        if (int(m_suspects.size()) > 1){
            do {
                cout << "Which sequence to reverse?\n"
                        "Choose 1 - " << m_suspects.size() << endl;
                cin >> susChoice;
            }
            while (susChoice < 1 || susChoice > int(m_suspects.size()));
        } else {
            susChoice = 1;
        }

        // loop through until suspect matches user choice
        for (int i = 1; i < int(m_suspects.size()) + 1; i++){
            if (i == susChoice){
                // call reverse sequence and acknowledge reversal
                m_suspects[i - 1]->ReverseSequence();
                cout << "Done reversing " << m_suspects[i - 1]->GetName() << "'s sequence." << endl;
            }
        }
    } else {
        int evidenceChoice;
        // ask which sequence to reverse if more than 1
        if (int(m_evidence.size()) > 1){
            do {
                cout << "Which sequence to reverse?\n"
                        "Choose 1 - " << m_evidence.size() << endl;
                cin >> evidenceChoice;
            }
            while (evidenceChoice < 1 || evidenceChoice > int(m_evidence.size()));
        } else {
            evidenceChoice = 1;
        }
        // loop through until evidence matches user choice
        for (int i = 1; i < int(m_evidence.size()) + 1; i++){
            // call reverse sequence and acknowledge reversal
            if (i == evidenceChoice){
                m_evidence[i - 1]->ReverseSequence();
                cout << "Done reversing " << m_evidence[i - 1]->GetName() << "'s sequence." << endl;
            }
        }
    }
}
