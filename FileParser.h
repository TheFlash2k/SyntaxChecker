#pragma once
#include <iostream>
#include <fstream>
#include <string>
/*
	This class reads the file into a string array and has multiple
	methods to deal with multiple errors and proper output with
	and without extra whitespaces using the method strip().
*/
class FileParser {
	int tLines = 0; // Will contain the number of lines in the file.
	std::string* fileContents = NULL; // Pointer used to dynamically allocate an array later.
	std::string fileName = ""; // Contains the name of the file.
	std::fstream handle; // A handle to the file.

	int readCount = 0; // Keeps number of times the file has been read. This helps in getContents() method.

	bool isAccessible();// Checks whether the file exists/ is accessible or not
	void go_to_beginning(); // This method takes the pointer to the beginning of the file.
public:
	FileParser(std::string); // Constructor
	~FileParser(); // Destructor
	int getNumLines(); // Gets the number of lines in the file
	void setFileName(std::string); // Sets the file name
	std::string getFileName()const; // Returns the name of the file
	void readContents(); // Reads the contents from the file
	std::string* getContents(); // Returns a pointer to the contents
	void printContents(); // Prints all the contents to the screen.
	std::string* strip(); // Removes unnecessary whitespaces and returns a pointer
};