#include "FileParser.h"
#include "Errors.h"
#include <algorithm> // Only included for the strip method

// Checks whether the file exists/ is accessible or not
bool FileParser::isAccessible() {
	if (fileName == "") // If the filename isn't set, it will automatically be set to "" and hence a false will be returned.
		return false;
	return handle.good();
}
// This method takes the pointer to the beginning of the file.
void FileParser::go_to_beginning() {
	if (fileName == "")
		return;
	if (handle.is_open())
		handle.seekg(0, std::ios::beg); // Takes the pointer to 0th index i.e. the beginning of the file.
}
// Default Constructor that can also act as a parametrized constructor
FileParser::FileParser(std::string fileName = "") : fileName(fileName) {
	handle.open(fileName, std::ios::in); // Opens a handle to the file.
}
// Destructor
FileParser::~FileParser() {
	delete fileContents; // Deletes the dynamically allocated memory to avoid wandering pointers.
	handle.close(); // Closes the file.
}

// Getters / Accessors
int FileParser::getNumLines() {
	if (!isAccessible())
		ERROR::generateError("FileError", "File is inaccessible OR not found!", 502);
	/*
	Creating a temporary pointer of type string that will read value from the file
	and will be deleted once the file has been read completely and number of lines have been found.
	*/
	tLines = 0; // Setting this to 0 so that if it's call again, the value is recalculated again instead of appending to the old value.
	std::string* temp = new std::string;
	while (!handle.eof()) {
		std::getline(handle, *temp);
		tLines++;
	}
	go_to_beginning(); // Taking pointer to begininning of the file.
	delete temp;
	return tLines;
}
std::string FileParser::getFileName()const {
	return fileName;
}
// Setter / Mutator
void FileParser::setFileName(std::string fileName) {
	this->fileName = fileName;
}
// Other method(s)
void FileParser::readContents() {
	// Reads the content of the file and stores them in the string array
	if (!isAccessible())
		ERROR::generateError("FileError", "File is inaccessible OR not found!", 502);
	fileContents = new std::string[getNumLines()]; // Allocates memory according to number of lines.
	int iterator = 0;
	while (!handle.eof())
		std::getline(handle, fileContents[iterator++], '\n'); // reads data into each index of the array.
	go_to_beginning();
	readCount++;
}
std::string* FileParser::getContents() {
	if (readCount == 0)
		readContents();
	return strip(); // Returns the content with no spaces
}
void FileParser::printContents() {
	// Validates if any kind of error exists. If not, print the array.
	if (fileName == "")
		ERROR::generateError("FileError", "No File Name Provided", 501);
	if(!isAccessible())
		ERROR::generateError("FileError", "File is inaccessible OR not found!", 502);
	if (readCount == 0)
		readContents();
	if (tLines == 0)
		ERROR::generateError("FileError", "Empty file read. Contains no content", 503);
	// Prints the content of the file!
	std::cout << "Contents of the file " << fileName << " are:\n\n";
	std::cout << "=============================================================\n"; // Purely for aesthetics
	for (int i = 0; i < tLines; i++) {
		std::cout << fileContents[i] << std::endl;
	}
	std::cout << "=============================================================\n";
	std::cout << "End of program!\n\n";
}
// Removes unnecessary whitespaces and returns a pointer
std::string* FileParser::strip() { // This method removes all the unnecessary whitespaces
	if (fileName == "")
		ERROR::generateError("FileError", "No File Name Provided", 501);
	if (!isAccessible())
		ERROR::generateError("FileError", "File is inaccessible OR not found!", 502);
	if (readCount == 0)
		readContents();
	if (tLines == 0)
		ERROR::generateError("FileError", "Empty file read. Contains no content", 503);
	// Main method begins here
	std::string prettifier;
	std::string* temp = new std::string[tLines];
	temp = fileContents;
	for (int i = 0; i < tLines; i++) {
		prettifier = temp[i];
		// Removes any extra double spaces
		prettifier.erase(remove(prettifier.begin(), prettifier.end(), '  '), prettifier.end());
		// Removes any extra triple spaces
		prettifier.erase(remove(prettifier.begin(), prettifier.end(), '   '), prettifier.end());
		// Removes any extra tab (four) spaces
		prettifier.erase(remove(prettifier.begin(), prettifier.end(), '\t'), prettifier.end());
		// Removes any extra newline characters
		prettifier.erase(remove(prettifier.begin(), prettifier.end(), '\n'), prettifier.end());
		// Removes the extra space in the beginning of the string
		if (prettifier[0] == ' ')
			prettifier.erase(0, 1);
		// Removes the extra space at the end of the string
		if (prettifier[prettifier.length() - 1] == ' ')
			prettifier.erase(prettifier.length() - 1);
		// Saves it back to the index.
		temp[i] = prettifier;
	}
	return temp;
}