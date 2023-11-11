/*****************************************
** File:    DNA.cpp
** Project: Project 3: DNA Sequencing
** Author:  Matthew Makila
** Date:    3/22/21
** Section: 10/13
** E-mail:  mmakila1@umbc.edu
**
** This file contains the methods and constructor/destructor written out for a DNA. The
 * methods allow for the name, data, and size to be retrieved.
 * The methods are used in order to compare sequences to evidence,
 * reverse them node-by-node, and display them with the written friend function.
 * The constructor and destructor are called here
 * to initialize data and then destroy it to prevent leaks.
***********************************************/

#include "DNA.h"

// Name: DNA() - Default Constructor
// Desc: Used to build a new DNA sequence
// Preconditions: None
// Postconditions: Creates a new DNA where m_head and m_tail point to nullptr
DNA::DNA() {
    //m_head and m_tail point to nullptr
    m_head = nullptr;
    m_tail = nullptr;
}

// Name: DNA(string) - Overloaded Constructor
// Desc: Used to build a new DNA sequence with the name passed
// Preconditions: None
// Postconditions: Creates a new DNA where m_head and m_tail point to nullptr and name is passed
DNA::DNA(string name){
    m_head = nullptr;
    m_tail = nullptr;
    m_name = name;
    m_size = 0;
}

// Name: ~DNA() - Destructor
// Desc: Used to destruct a strand of DNA
// Preconditions: There is an existing DNA strand with at least one node
// Postconditions: DNA is deallocated (including all dynamically allocated nodes)
//                 to have no memory leaks!
DNA::~DNA() {
    Node *temp = m_head;
    while(m_head != nullptr){
        temp = m_head->m_next;
        delete m_head;
        m_head = temp;
    }
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}

// Name: InsertEnd
// Preconditions: Takes in a char. Creates new node.
//                Requires a DNA strand
// Postconditions: Adds the new node to the end of the DNA strand.
void DNA::InsertEnd(char data) {
    // create new node with data and a pointer to next node
    Node *temp = new Node();
    temp->m_data = data;
    temp->m_next = nullptr;

    // make node to traverse list to end
    Node *endNode = m_head;

    if (m_head == nullptr){ // if list empty, make new node the head
        m_head = temp;

    } else {
        // cycle through list to find last node and then make that new end
        while (endNode->m_next != nullptr){
            endNode = endNode->m_next;
        }
        endNode->m_next = temp;
    }
    // increment size
    m_size++;
}

// Name: GetName()
// Preconditions: Requires a DNA sequence
// Postconditions: Returns m_name;
string DNA::GetName() {
    return m_name;
}

// Name: GetSize()
// Preconditions: Requires a DNA sequence
// Postconditions: Returns m_size;
int DNA::GetSize() {
    return m_size;
}

// Name: ReverseSequence
// Preconditions: Reverses the DNA sequence
// Postconditions: DNA sequence is reversed in place; nothing returned
void DNA::ReverseSequence() {
    Node *curr = m_head;
    Node *prev = nullptr;
    Node *next = nullptr;

    // update pointers until we reach the end
    while (curr != nullptr){
        next = curr->m_next;
        curr->m_next = prev;

        prev = curr;
        curr = next;
    }
    m_head = prev;
    // write out code to reverse a linked list
}

// Name: CompareSequence
// Preconditions: Requires two DNA sequence (suspect and passed evidence DNA)
// Postconditions: Returns true if evidence sequence exists; else false
bool DNA::CompareSequence(DNA &evidence) {
    // let's write the compare sequence function. Hardest function to write
    bool isMatched = true;
    bool matchFound = false;
    Node *suspect = m_head;
    Node *evidenceTemp = evidence.m_head;
    Node *curr;

    int matchCounter = 0;

    // nested while loops, check evidence and suspect pointers
    while (suspect != nullptr && !matchFound){
        // monitor where the suspect was pointing before being checked for matches
        curr = suspect;

        if (suspect->m_data == evidenceTemp->m_data) {
            // check if sequences keep matching consecutively and that the suspect and evidence are not at nullptr
            while (isMatched == true && suspect != nullptr && evidenceTemp != nullptr) {
                if (suspect->m_data == evidenceTemp->m_data) {
                    // update amount of matched sequences in a row
                    matchCounter++;
                    // cout << suspect->m_data << " || " << evidenceTemp->m_data << endl;

                    // keep moving pointers through if the codons are matching
                    suspect = suspect->m_next;
                    evidenceTemp = evidenceTemp->m_next;
                } else {
                    // break the loop and move suspect to where curr's next was (where sus was before inner loop).
                    isMatched = false;
                    suspect = curr->m_next;
                }

            }
            if (matchCounter == evidence.GetSize()) {
                // match found, break loop
                matchFound = true;
            } else {
                // if not perfect match, reset counter and break loop to continue moving through suspect DNA
                matchCounter = 0;
                isMatched = true;
            }
        }
        // reset evidence back to its first nucleotides for checking and suspect to curr's next (sus before inner loop)
        evidenceTemp = evidence.m_head;
        suspect = curr->m_next;
    }

    return matchFound;
}

// Name: GetData
// Desc: Returns the data at a specific location in the DNA sequence
// Preconditions: Requires a DNA sequence
// Postconditions: Returns a single char from a node
char DNA::GetData(int nodeNum) {
    // create temp node pointer
    Node *temp = m_head;
    char data;
    // search until node in sequence has same data as node searched for
    for (int i = 0; i < m_size; i++){
        if (i == nodeNum){
            data = temp->m_data;
        }
        temp = temp->m_next;
    }
    return data;
}

// Name: operator<<
// Desc: Overloaded << operator to return ostream from DNA
// Preconditions: Requires a DNA sequence
// Postconditions: Returns ostream populated from each node
ostream &operator<< (ostream &output, DNA &myDNA){
    // check that DNA strand is not empty
    if (myDNA.m_size == 0){
        output << "The list is empty!" << endl;
    } else {
        // display nodes using the output variable
        Node *temp = myDNA.m_head;
        for (int i = 0; i < myDNA.m_size; i++){
            output << temp->m_data << "->";
            temp = temp->m_next;
        }
        output << "END" << endl;
    }
    return output;
}