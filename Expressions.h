#pragma once // Preprocessor Directive that only includes all the libraries once.
#include "FileParser.h"
#include "Stack.h"
#include "Errors.h"

#define MAX 100 // A MACRO that has been set to 100 that is used when dealing with lineNumbers for errors.

/*
	class Validator: This class contains methods that can be used to verify multiple things such as
	-> If the provided argument is an opening bracket or a closing one, is a beginning keyword or ending keyword.
	-> Does it contain a specific String or not.
	Along with verification, this class also contains methods to get multiple stuff such as:
	-> Getting all the brackets in a string array or a string (overloaded method).
	-> Getting a substring with a keyword from an entire string
*/
class Validator {
protected:
	bool isOpeningBracket(char); // Checks if the passed argument is an opening bracket.
	bool isClosingBracket(char);// Checks if the passed argument is an closing bracket.
	bool isBeginningKeyword(std::string); // Checks if the passed argument contains a beginning keyword.
	bool isEndingKeyword(std::string); // Checks if the passed argument contains an ending keyword.
	bool has(std::string, std::string); // Checks if the first argument contains a string equivalent to the second argument.
	bool hasKeyword(std::string); // Checks if a string has any one of the pre-defined keywords
	bool hasBrackets(std::string); // Checks if a string contains brackets.
	std::string getBrackets(std::string*, int); // Takes two arguements, one is the string array and the other is the size of that array and returns all the braces as a single string.
	std::string getBrackets(std::string); // Returns all the existing braces within a single string as a string.
	std::string getSubstring(std::string str); // Returns a pre-defined keyword existing in the passed argument.
};

/*
	class Expressions: This is a child class of Validator and extends the functionality of that class.
	Main features:
	- Checks if the brackets are balanced. IF not, throws proper error.
	- Checks if each of the keyword is balanced. If not, throws proper error along with the line number.
*/

class Expressions : private Validator {
	// Attributes
	int lineNumbers[MAX] = { NULL }; // Will contain the line numbers at which certain data exists.
	std::string* expressions; // Reads all the data from the file and stores into this pointer.
	FileParser* file_handler; // An object of FilerParser that we will dynamically allocate with the fileName later on.
	int currentLine = 0; // An index which tells us the number upto which lineNumbers array has been filled.
	// Methods
	std::string* extract(int&); // Extracts all the keywords into a string array and returns that. Takes as an argument a int by reference that will contain the size of the new array upon returning from the function.
	bool checkBrackets(); // The main method that checks if all the brackets are balanced.
	bool invokeChecks(); // This is the method that will check if the keywords are balanced, if not, will throw proper errors.
public:
	Expressions(std::string); // Default Constructor.
	FileParser* getHandle()const; // Returns a handle to the FileParser class.
	void init(); // The public method that can be used to initialize everything check.
	~Expressions(); // Destructor.
};