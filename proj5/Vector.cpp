/*****************************************
** File:    Vector.cpp
** Project: Project 5: Vectors
** Author:  Matthew Makila
** Date:    4/20/21
** Section: 10/13
** E-mail:  mmakila1@umbc.edu
**
** This file is the class for the Vector we design. The Vector
 * is a linked list with a copy constructor, destructor, and
 * an overloaded assignment operator. The class also includes methods
 * to overload several operators for computations and to insert or remove elements
 *
 * Created by Nathenael Dereb on 2/8/21
***********************************************/


#ifndef VECTOR_CPP
#define VECTOR_CPP

#include <string>
#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;

template <class T> 
struct Node {
public:
  Node(T value) {
    m_value = value;
    next = nullptr;
  }
  
  Node(T value, Node* _next) {
    m_value = value;
    next = _next;
  }
  
  T getValue() {
    return m_value;
  }
  
  Node<T>* getNextNode() {
    return next;
  }
  
  void setNextNode(Node<T>* newNode) {
    next = newNode;
  }
  
private:
  T m_value;
  Node<T>* next;
};


template <class T>
class Vector {
public:
  // Name: Default Constructor
  // Precondition: None (Must be templated)
  // Postcondition: Creates a vector using a linked list
  Vector();
   
  // Name: Destructor
  // Desc: Frees memory
  // Precondition: Existing Vector
  // Postcondition: Destructs existing Vector
  ~Vector();  

  // Name: Copy Constructor
  // Desc: Copies an existing vector
  // Precondition: Existing Vector
  // Postcondition: Two identical vectors (in separate memory spaces)
  // Hint: Utilize overloaded [] operator
  Vector (Vector<T>* const& source);
  
  // Name: Overloaded Assignment operator
  // Desc: Assingns a vector
  // Precondition: Existing Vector
  // Postcondition: Assigns a vector
  // Hint: Utilize overloaded [] operator
  Vector<T>* operator=(Vector<T>* source);  
  
  // Name: Overloaded [] operator
  // Desc: to retrive use [indx]
  // Precondition: Existing Vector
  // Postcondition: Returns the value of the element at the given index
  T operator[](int indx);
    
  // Name: Insert
  // Desc: insert a node to the end of the vector
  // Precondition: Existing Vector
  // Postcondition: A vector with the newly added value
  void Insert(T);  
    
  // Name: SortedInsert
  // Desc: Inserts a node into the vector at it's correct position (sorted ascendingly)
  // Precondition: Existing Vector
  // Postcondition: sorted vector (low to high)
  void SortedInsert(T);
      
  // Name: Remove
  // Desc: removes a node from the vector
  // Precondition: Existing Vector
  // Postcondition: A vector that holds the results of the vectors added
  void Remove(int indx);
    
  // Name: Overloaded + operator | Vector Addition
  // Desc: Adds two vectors and returns the result
  // Precondition: Existing Vector, vectors can be of different size
  // Postcondition: A vector that holds the results of the vectors added
  Vector<T>* operator+(Vector<T>& source);
    
  // Name: Overloaded * operator | Vector Multiplication
  // Desc: Multiplys two vectors and returns the result
  // Precondition: Existing Vector, vectors can be of different size
  // Postcondition: returns a vector that holds the results of the vectors multiplied
  Vector<T>* operator*(Vector<T>& other);
    
  // Name: Overloaded < operator | Vector Comparision
  // Desc: Compares two vectors [using the < operator] and returns the result
  // Precondition: Existing Vector -> vectors need to be of the same size
  // Postcondition: returns a vector that holds the boolean char (T or F) value of each node comparison
  Vector<char>* operator<(Vector<T>& other);
      
  // Name: Overloaded == operator | Vector Comparision
  // Desc: Compares two vectors [using the == operator] and returns the result
  // Precondition: Existing Vector, vectors need to be of the same size
  // Postcondition: returns a vector that holds the boolean char (T or F) value of each node comparison
  Vector<char>* operator==(Vector<T>& other);
    
  // Name: Size
  // Desc: number of nodes in Vector
  // Precondition: Existing Vector
  // Postcondition: returns the size of the vector
  int Size();  
    
  // Name: Display
  // Desc: displays the contents of the vector
  // Precondition: Existing Vector
  // Postcondition: prints to console the contents of Vector
  void Display();
    
  // Name: median
  // Desc: Computes the median of the vector
  // Precondition: Existing Vector
  // Postcondition: returns the median value
  float Median();  
    
  // Name: Mean
  // Desc: Computes the mean of the vector
  // Precondition: Existing Vector
  // Postcondition: returns the mean value
  float Mean();
    
  // Name: StDev
  // Desc: Computes the standard derivation of the vector
  // Precondition: Existing Vector
  // Postcondition: returns the standard derivation
  float StDev();
      
private:
    Node<T>* m_head;
};


/**** Add class definition below *****/
// Name: Default Constructor
// Precondition: None (Must be templated)
// Postcondition: Creates a vector using a linked list
template <class T>
Vector<T>::Vector(){
    m_head = nullptr;
}

// Name: Destructor
// Desc: Frees memory
// Precondition: Existing Vector
// Postcondition: Destructs existing Vector
template <class T>
Vector<T>::~Vector(){
    // cout << "Calling destruction" << endl;
    // delete every node in the Vector we created
    Node<T> *temp = m_head;
    while(m_head != nullptr){
        temp = m_head->getNextNode();
        delete m_head;
        m_head = temp;
    }
    m_head = nullptr;
}

// Name: Copy Constructor
// Desc: Copies an existing vector
// Precondition: Existing Vector
// Postcondition: Two identical vectors (in separate memory spaces)
// Hint: Utilize overloaded [] operator
template <class T>
Vector<T>::Vector(Vector<T>* const& source){
    // copy constructor
    m_head = nullptr;
    if (source->Size()){
        for (int i = 0; i < source->Size(); i++){
            // operator[](i) = source->operator[](i);
            Node<T> *temp = new Node<T>(source->operator[](i));
            // make node to traverse list to end
            Node<T> *endNode = m_head;

            if (m_head == nullptr){ // if list empty, make new node the head
                m_head = temp;
            } else {
                // cycle through list to find last node and then make that new end
                while (endNode->getNextNode() != nullptr){
                    endNode = endNode->getNextNode();
                }
                endNode->setNextNode(temp);
            }
        }
    }
}

// Name: Overloaded Assignment operator
// Desc: Assingns a vector
// Precondition: Existing Vector
// Postcondition: Assigns a vector
// Hint: Utilize overloaded [] operator
template <class T>
Vector<T>* Vector<T>::operator=(Vector<T>* source){
    // assignment operator
    if (this == source)
        return this;
    else {
        m_head = nullptr;
        if (source->Size()){
            for (int i = 0; i < source->Size(); i++){

                Node<T> *temp = new Node<T>(source->operator[](i));
                // make node to traverse list to end
                Node<T> *endNode = m_head;

                if (m_head == nullptr){ // if list empty, make new node the head
                    m_head = temp;
                } else {
                    // cycle through list to find last node and then make that new end
                    while (endNode->getNextNode() != nullptr){
                        endNode = endNode->getNextNode();
                    }
                    endNode->setNextNode(temp);
                }
            }
        }
    }
    return this;
}

// Name: Overloaded [] operator
// Desc: to retrive use [indx]
// Precondition: Existing Vector
// Postcondition: Returns the value of the element at the given index
template <class T>
T Vector<T>::operator[](int indx){
    // const char ERROR = 'X';
    // return what is at the index passed: operator[](indx)
    T data;
    int count = 0;
    // initialize a count and loop through LL to find and return total size
    Node<T> *temp = m_head;
    // make sure index is in bounds of vector
    if (indx < Size() && indx >= 0){
        while (temp != nullptr){
            if (count == indx) {
                data = temp->getValue();
            }
            temp = (temp->getNextNode());
            count++;
        }
    } else {
        // You are trying to access a value out of range, but return 0 because it's likely due to 2 diff len vectors
        cout << "Vector out of range!" << endl;
        return 0; // return ERROR;
    }

    return data;
}

// Name: Insert
// Desc: insert a node to the end of the vector
// Precondition: Existing Vector
// Postcondition: A vector with the newly added value
template <class T>
void Vector<T>::Insert(T data){
    // do like insertEnd
    // create new node with data and a pointer to next node
    Node<T> *temp = new Node<T>(data);
    // make node to traverse list to end
    Node<T> *endNode = m_head;

    if (m_head == nullptr){ // if list empty, make new node the head
        m_head = temp;

    } else {
        // cycle through list to find last node and then make that new end
        while (endNode->getNextNode() != nullptr){
            endNode = endNode->getNextNode();
        }
        endNode->setNextNode(temp);
    }
}

// Name: SortedInsert
// Desc: Inserts a node into the vector at it's correct position (sorted ascendingly)
// Precondition: Existing Vector
// Postcondition: sorted vector (low to high)
template <class T>
void Vector<T>::SortedInsert(T data){
    // this does NOT sort the LL, but rather inserts elements in order
    // create new node with data and a pointer to next node
    Node<T> *temp = new Node<T>(data);
    Node<T> *curr;

    if (m_head == nullptr || temp->getValue() <= m_head->getValue()) {
        // if list empty, make new node the head or if new data less than first node, make it head
        temp->setNextNode(m_head);
        m_head = temp;

    } else {
        curr = m_head;

        // while not end of LL and the curr val less than what we want to insert, keep searching
        while (curr->getNextNode() != nullptr && curr->getNextNode()->getValue() < temp->getValue()){
            curr = curr->getNextNode();
        }
        // once found, insert node at proper location
        temp->setNextNode((curr->getNextNode()));
        curr->setNextNode(temp);
    }

}

// Name: Remove
// Desc: removes a node from the vector
// Precondition: Existing Vector
// Postcondition: A vector that holds the results of the vectors added
template <class T>
void Vector<T>::Remove(int indx){
    // remove a node at specific index
    Node<T> *curr = m_head;
    Node<T> *prev = m_head;
    int counter = 0;

    while(curr != nullptr){
        // remove element when found at index
        if(counter == indx){
            prev->setNextNode(curr->getNextNode());
            delete curr;
            return;
        }
        // keep iterating over nodes
        prev = curr;
        curr = curr->getNextNode();
        counter++;
    }
}

// Name: Overloaded + operator | Vector Addition
// Desc: Adds two vectors and returns the result
// Precondition: Existing Vector, vectors can be of different size
// Postcondition: A vector that holds the results of the vectors added
template <class T>
Vector<T>* Vector<T>::operator+(Vector<T>& source){
    // let's weave the LL's together by adding each item at the same index (i) together
    // end result: new LL with elements added
    int size = (source.Size() > Size())? source.Size() : (Size());
    Vector<T>* addition = new Vector<T>;

    // for every element in existing vectors, add their elements at that index and add it to the new vector
    for (int i = 0; i < size; i++){
        T addend = source.operator[](i) + operator[](i);
        addition->Insert(addend);
    }
    return addition;
}

// Name: Overloaded * operator | Vector Multiplication
// Desc: Multiplies two vectors and returns the result
// Precondition: Existing Vector, vectors can be of different size
// Postcondition: returns a vector that holds the results of the vectors multiplied
template <class T>
Vector<T>* Vector<T>::operator*(Vector<T>& other){
    // let's weave the LL's together by multiplying each item at the same index (i) together
    // end result: new LL with elements multiplied
    Vector<T>* multiply = new Vector<T>;
    int size = (other.Size() > Size())? other.Size() : (Size());

    // for every element in existing vectors, multiply their elements at that index and add it to the new vector
    for (int i = 0; i < size; i++){
        T addend = other.operator[](i) * operator[](i);
        multiply->Insert(addend);
    }
    return multiply;
}

// Name: Overloaded < operator | Vector Comparison
// Desc: Compares two vectors [using the < operator] and returns the result
// Precondition: Existing Vector -> vectors need to be of the same size
// Postcondition: returns a vector that holds the boolean char (T or F) value of each node comparison
template <class T>
Vector<char>* Vector<T>::operator<(Vector<T>& other){
    // create vector to hold the chars and true/false
    const char TRUE = 'T';
    const char FALSE = 'F';
    Vector<char>* lessThan = new Vector<char>;

    // check if vectors are both same size or one is empty
    if (Size() != other.Size() || Size() == 0){
        cout << "Vectors are either empty or not the same size!" << endl;
    } else {
        // use the operator [] to check if vector1 is LESS than vector 2 at index (i)
        for (int i = 0; i < Size(); i++){
            if (operator[](i) < other.operator[](i)){
                lessThan->Insert(TRUE);
            } else {
                lessThan->Insert(FALSE);
            }
        }
    }
    return lessThan;
}

// Name: Overloaded == operator | Vector Comparison
// Desc: Compares two vectors [using the == operator] and returns the result
// Precondition: Existing Vector, vectors need to be of the same size
// Postcondition: returns a vector that holds the boolean char (T or F) value of each node comparison
template <class T>
Vector<char>* Vector<T>::operator==(Vector<T>& other){
    // create vector to hold the chars and true/false
    const char TRUE = 'T';
    const char FALSE = 'F';
    Vector<char>* equality = new Vector<char>;

    if (Size() != other.Size() || Size() == 0){
        cout << "Vectors are either empty or not the same size!" << endl;
    } else {
        // use the operator [] to check if vector1 is LESS than vector 2 at index (i)
        for (int i = 0; i < Size(); i++){
            if (operator[](i) == other.operator[](i)){
                equality->Insert(TRUE);
            } else {
                equality->Insert(FALSE);
            }
        }
    }
    return equality;
}

// Name: Size
// Desc: number of nodes in Vector
// Precondition: Existing Vector
// Postcondition: returns the size of the vector
template <class T>
int Vector<T>::Size(){
    int count = 0;
    // initialize a count and loop through LL to find and return total size
    Node<T> *temp = m_head;
    while (temp != nullptr){
        temp = (temp->getNextNode());
        count++;
    }
    return count;
}

// Name: Display
// Desc: displays the contents of the vector
// Precondition: Existing Vector
// Postcondition: prints to console the contents of Vector
template <class T>
void Vector<T>::Display(){
    if (Size() == 0){
        cout << "The list is empty!" << endl;
    } else {
        // display each node in vector
        Node<T> *temp = m_head;
        for (int i = 0; i < Size(); i++){
            // display nodes as comma separated except last node
            if (i != Size() - 1) {
                cout << temp->getValue() << ", ";
            } else {
                cout << temp->getValue();
            }
            // move to next node
            temp = (temp->getNextNode());
        }
        cout << endl;
    }
}

// Name: median
// Desc: Computes the median of the vector
// Precondition: Existing Vector
// Postcondition: returns the median value
template <class T>
float Vector<T>::Median(){
    // pro tip: divide whole data set by 2 (index = Size() / 2) and then go to that middle index
    // works nicely since set is ordered

    // if size even, find median by averaging 2 middle nums
    int medIndex = 0;
    if (Size() > 0){
        if (Size() % 2 == 0){
            int firstCheck = Size() / 2; // finds middle-right index
            int secondCheck = firstCheck - 1; // get index to left of mid-right
            return (operator[](firstCheck) + operator[](secondCheck)) / 2; // average them

        } else if (Size() % 2 == 1){ // if size odd, median is just middle index
            medIndex = Size() / 2;

        }
    }
    return operator[](medIndex);
}

// Name: Mean
// Desc: Computes the mean of the vector
// Precondition: Existing Vector
// Postcondition: returns the mean value
template <class T>
float Vector<T>::Mean(){
    // find sum of entire vector and divide by size
    float sum = 0;
    for (int i = 0; i < Size(); i++){
        sum += operator[](i);
    }
    // return avg (total sum divided by size)
    return sum / Size();
}

// Name: StDev
// Desc: Computes the standard derivation of the vector
// Precondition: Existing Vector
// Postcondition: returns the standard derivation
template <class T>
float Vector<T>::StDev(){
    // square the (mean - num) for each term and find avg of that
    float result = 0;
    float piece;
    float mean = Mean();
    for (int i = 0; i < Size(); i++){
        // each "piece" will have the num at index i minus the mean ^2
        piece = pow((operator[](i) - mean), 2);
        result += piece;
    }

    // return the sqrt of avg of the "pieces"
    return pow((result / Size()), 0.5);
}

#endif /* VECTOR_CPP */
