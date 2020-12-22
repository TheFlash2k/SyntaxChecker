#pragma once
#include <iostream>
#include <string>

#define DEBUG 0 // A MACRO, that once set to 1, will give verbose output as to what's being pushed and popped from the stack and at other certain positions.

/*
	Class-- Node: Contains two attributes with multiple methods. One attribute contains the data whilst the other contains a pointer to next.
*/

class Node {
	std::string data; // Will contain the actual keywords/braces that need to be verified.
	Node* next; // Is a pointer to the next node in the stack.
public:
	Node();	// Default Constructor
	Node(std::string); // Parameterized Constructor
	 // Setters - Mutators
	void setData(std::string);
	void setNext(Node*);
	// Getters - Accessors
	std::string getData()const;
	Node* getNext()const;
	// Setting the class Stack to be a friend of class Node so that we can access the private members directly.
	friend class Stack;
};

/*
	Class Stack: Is the implementation of data structure stack.
	Contains the following methods:
	push(<data>)
	pop()
	top()
*/

class Stack {
	Node* root; // An object of above mentioned class Node;
public:
	Stack(); // Default Constructor
	void setTop(Node*); // Setter / Mutator
	Node* getTop(); // Getter / Accessor
	bool isEmpty(); // Checks if the stack is empty and returns a boolean value
	void push(std::string); // Pushes a string onto the stack
	void push(char); // Typecasts a char into a string and pushes it onto the stack
	std::string pop(); // Removes the value at the top of the stack and also returns it.
	std::string top(); // Returns the value on top of the stack.

#ifdef DEBUG // This function is only for debugging purposes.
	void print(); // Prints all the contents within the stack.
#endif
	~Stack(); // Destructor
};