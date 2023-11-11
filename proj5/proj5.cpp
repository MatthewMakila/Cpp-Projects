/*****************************************
** File:    proj5.cpp
** Project: Project 5: Vectors
** Author:  Matthew Makila
** Date:    4/20/21
** Section: 10/13
** E-mail:  mmakila1@umbc.edu
**
** This file is the main driver for project 5. It constructs
 * the vectors passed in from a file by type float or int and calls the
 * sorted insert to properly populate them. Then, Runner is called to
 * start the program.
 *
 * Created by Nathenael Dereb on 2/8/21
***********************************************/

// The R language - Vector Computations
// NumVec1 <- c(1, 4.5, 9, 10, 3)
// NumVec2 <- c(-5, 10, -2, 20, 3)

// Vectors are Linked Lists
// NumVec1:  1 -> 4.5 -> 9 -> 10 -> 3
// NumVec2:  -5 -> 10 -> -2 -> 20 -> 3

// Vector addition | overload + operator
// > NumVec1 + NumVec2
// > [1] -4.0  14.5  7.0  30.0  6.0

// Vector multiplication - overload * operator
//> NumVec1 * NumVec2
//> [1]  -5  45  -18  200  9

// Vector Comparison | overloaded [<, >, ==] operators
// NumVec1 > NumVec2
// [1]  TRUE FALSE TRUE FALSE FALSE
// > NumVec1 == NumVec2
// [1] FALSE FALSE FALSE FALSE  TRUE


#include <iostream>
#include <string>
#include "Runner.cpp"
using namespace std;

// Prototypes
void loadData(string);


int main(int argc, const char * argv[]) {
  cout << "Vector Computations" << endl;
  loadData(argv[1]);
  return 0;
}


void loadData(string filename) {
  ifstream inputStream;
  inputStream.open(filename);
  
  string dataType, size, number;
  
  Vector<int>* vector1_int = new Vector<int>();
  Vector<int>* vector2_int = new Vector<int>();
  Vector<float>* vector1_float = new Vector<float>();
  Vector<float>* vector2_float = new Vector<float>();
  
  if (inputStream.is_open()) {
    getline(inputStream, dataType, ',');
    getline(inputStream, size, '\n');
    
    if (dataType == "int") {
      for (int i = 0; i < stoi(size); i++) {
	if (i == stoi(size)-1) getline(inputStream, number, '\n');
	else getline(inputStream, number, ',');
	vector1_int->SortedInsert(stoi(number));
      }
      for (int i = 0; i < stoi(size); i++) {
	if (i == stoi(size)-1) getline(inputStream, number, '\n');
	else getline(inputStream, number, ',');
	vector2_int->SortedInsert(stoi(number));
      }
    } else if (dataType == "float") {
      for (int i = 0; i < stoi(size); i++) {
	if (i == stoi(size)-1) getline(inputStream, number, '\n');
	else getline(inputStream, number, ',');
	vector1_float->SortedInsert(stof(number));
      }
      for (int i = 0; i < stoi(size); i++) {
	if (i == stoi(size)-1) getline(inputStream, number, '\n');
	else getline(inputStream, number, ',');
	vector2_float->SortedInsert(stof(number));
      }
    }
  }
  inputStream.close();
  
  if (dataType == "int") {
    Runner<int>(vector1_int, vector2_int);
  } else {
    Runner<float>(vector1_float, vector2_float);
  }
  
  delete vector1_int;
  delete vector2_int;
  delete vector1_float;
  delete vector2_float;
  cout << "Thank you for using the Vector Tool" << endl;
}
