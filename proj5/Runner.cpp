/*****************************************
** File:    Runner.cpp
** Project: Project 5: Vectors
** Author:  Matthew Makila
** Date:    4/20/21
** Section: 10/13
** E-mail:  mmakila1@umbc.edu
**
** This file is the class for Runner, which handles the Vector
 * computations. It uses a main menu and switch statement to control
 * what operations are called.
 *
 * Created by Nathenael Dereb on 2/8/21
***********************************************/

#ifndef RUNNER_CPP
#define RUNNER_CPP

#include <cstdlib>
#include "Vector.cpp"
using namespace std;


template <class T>
class Runner {
public:
    // Name: Default Constructor
    // Precondition: None
    // Postcondition: Initiates state/environment
    Runner(Vector<T>*, Vector<T>*);
    
    // Name: mainMenu
    // Desc: Main Menu
    // Precondition: Existing Vectors
    // Postcondition: Handles various menu commands
    int mainMenu();
    
private:
    Vector<T> m_vector1;
    Vector<T> m_vector2;
};

// **** Add class definition below ****
template <class T>
Runner<T>::Runner(Vector<T>* v1, Vector<T>* v2){
    enum {DISPLAY=1, LESS, EQUAL, ADD, MULTIPLY, MED, MEAN, STD, EXIT};
    int choice = mainMenu();
    m_vector1 = v1;
    m_vector2 = v2;
    while (choice != EXIT){
        // make switch statement for all of the different
        Vector<char>* charResult;
        Vector<char>* charResultEqual;
        Vector<T>* additionResult;
        Vector<T>* multiplyResult;


        switch (choice) {
            case DISPLAY:
                // call display function for vectors
                cout << "Vector 1: ";
                v1->Display();
                cout << "Vector 2: ";
                v2->Display();
                break;

            case LESS:
                // check if vector 1 is less than vector 2
                cout << "Vector 1 < Vector 2: ";
                charResult = m_vector1 < m_vector2;
                charResult->Display();
                delete charResult;
                break;

            case EQUAL:
                // check if vector 1 is equal to vector 2
                cout << "Vector 1 == Vector 2: ";
                charResultEqual = m_vector1 == m_vector2;
                charResultEqual->Display();
                delete charResultEqual;
                break;

            case ADD:
                // add vectors
                cout << "Vector 1 + Vector 2: ";
                additionResult = m_vector1 + m_vector2;
                additionResult->Display();
                delete additionResult;
                break;

            case MULTIPLY:
                // multiply vectors
                cout << "Vector 1 * Vector 2: ";
                multiplyResult = m_vector1 * m_vector2;
                multiplyResult->Display();
                delete multiplyResult;
                break;

            case MED:
                // call median function for vectors
                cout << "Vector 1 median: " << m_vector1.Median() << endl;
                cout << "Vector 2 median: " << m_vector2.Median() << endl;
                break;

            case MEAN:
                // call Mean function for vectors
                cout << "Vector 1 mean: " << m_vector1.Mean() << endl;
                cout << "Vector 2 mean: " << m_vector2.Mean() << endl;
                break;

            case STD:
                // call StDev function for vectors
                cout << "Vector 1 StDev: " << m_vector1.StDev() << endl;
                cout << "Vector 2 StDev: " << m_vector2.StDev() << endl;
                break;

        }
        // call menu again
        choice = mainMenu();
    }
}

template <class T>
int Runner<T>::mainMenu(){
    enum {DISPLAY=1, LESS, EQUAL, ADD, MULTIPLY, MED, MEAN, STD, EXIT};
    int choice;
    do {
        cout << endl;
        cout << "Choose an option\n"
                "1. Display Vectors\n"
                "2. Vector comparison (<)\n"
                "3. Vector comparison (==)\n"
                "4. Vector addition\n"
                "5. Vector multiplication\n"
                "6. Compute median\n"
                "7. Compute mean\n"
                "8. Compute Standard Derivation\n"
                "9. Exit" << endl;
        cin >> choice;
    } while (choice < DISPLAY || choice > EXIT);

    return choice;
}






#endif /* Runner_h */


