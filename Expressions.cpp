#include "Expressions.h"

/*
	- METHODS DEFINITION FOR CLASS VALIDATOR
*/
// Checks if the passed argument is an opening bracket.
bool Validator::isOpeningBracket(char _brace) {
	return _brace == '{'
		|| _brace == '['
		|| _brace == '(';
}
// Checks if the passed argument is an closing bracket.
bool Validator::isClosingBracket(char _brace) {
	return _brace == '}'
		|| _brace == ']'
		|| _brace == ')';
}
// Checks if the passed argument contains a beginning keyword.
bool Validator::isBeginningKeyword(std::string keyword) {
	return (keyword == "Begin" || keyword == "begin")
		|| keyword == "if"
		|| keyword == "for"
		|| keyword == "while"
		|| keyword == "elseif"
		|| keyword == "else";
}
// Checks if the passed argument contains an ending keyword.
bool Validator::isEndingKeyword(std::string keyword) {
	return keyword == "end"
		|| keyword == "endfor"
		|| keyword == "endwhile";
}
// Checks if the first argument (str) contains a string equivalent to the second argument (substr).
bool Validator::has(std::string str, std::string substr) {
	std::string keyword = "";
	for (size_t i = 0; i < str.length(); i++) {
		// This if statement verifies if the passed character is not an alphabet, the loop will break
		if ((isOpeningBracket(str[i]) || isClosingBracket(str[i]) && (i < str.length() - 1) && !isalpha(str[i + 1])))
			break;
		if (isalpha(str[i]))
			keyword += str[i];
	}
	return keyword == substr;
}
// Checks if a string has any one of the pre-defined keywords
bool Validator::hasKeyword(std::string str) {
	const int WORDS = 10;
	std::string keywords[WORDS] =
	{
		"Begin",  "if", "elseif", "else",
		"for", "endfor", "while", "endwhile",
		"end", "endif"
	};
	for (int i = 0; i < WORDS; ++i) {
		if (has(str, keywords[i]))
			return true;
	}
	return false;
}
// Checks if a string contains brackets.
bool Validator::hasBrackets(std::string str) {
	for (char x : str) {
		if (isOpeningBracket(x) || isClosingBracket(x))
			return true;
	}
	return false;
}
/*
	- OVERLOADED FUNCTIONS
*/
// Takes two arguements, one is the string array and the other is the size of that array and returns all the braces as a single string.
std::string Validator::getBrackets(std::string* expressions, int len) {
	std::string ret = "";
	for (int i = 0; i < len; i++) {
		std::string temp = expressions[i];
		// A For each loop that has an if statement that checks if the passed character is a bracket, if it is, appends it to the ret string.
		for (char x : temp) {
			if (isOpeningBracket(x) || isClosingBracket(x))
				ret += x;
		}
	}
	return ret;
}
// Returns all the existing braces within a single string as a string.
std::string Validator::getBrackets(std::string expression) {
	std::string braces = "";
	for (char brace : expression) {
		// A For each loop that has an if statement that checks if the passed character is a bracket, if it is, appends it to the ret string.
		if (isOpeningBracket(brace) || isClosingBracket(brace))
			braces += brace;
	}
	return braces;
}
// Returns a pre-defined keyword existing in the passed argument.
std::string Validator::getSubstring(std::string str) {
	const int WORDS = 11;
	std::string ret;
	std::string keywords[WORDS] =
	{
		"Begin", "begin" ,"if", "elseif", "else",
		"for", "endfor", "while", "endwhile",
		"end", "endif"
	};
	// Firstly checks if the passed string contains a keyyword.
	for (int i = 0; i < WORDS; ++i) {
		if (has(str, keywords[i])) {
			ret = keywords[i];
			break;
		}
	}

	std::string keyword = "";
	for (size_t i = 0; i < str.length(); i++) {
		// This if statement verifies if the passed character is not an alphabet, the loop will break
		if ((isOpeningBracket(str[i]) || isClosingBracket(str[i]) && (i < str.length() - 1) && !isalpha(str[i + 1])))
			break;
		if (isalpha(str[i]))
			keyword += str[i];
	}
	// Compares the value that we received in the first check and the current value we got and returns the value if they're same.
	if (keyword == ret)
		return ret;
	return "";
}

/*
	- METHODS DEFINITION FOR CLASS Expressions
*/
// Extracts all the keywords into a string array and returns that. Takes as an argument a int by reference that will contain the size of the new array upon returning from the function.
std::string* Expressions::extract(int& size) {
	// Dynamically allocates an array with the max size being the number of lines of the file and 1.
	std::string* _ret = new std::string[file_handler->getNumLines() + 1];
	int filledTo = 0; // Tells the size upto which the array has been filled to.

	for (int i = 0; i < file_handler->getNumLines(); i++) {
		std::string comp = expressions[i];
		if (hasKeyword(comp)) { // Checks if the string has a keyword.
			_ret[filledTo++] = getSubstring(comp); // Extracts only the keyword and stores it into the array and increments the filledTo size.
			lineNumbers[currentLine++] = i + 1; // Stores the line number of the keyword. Adding 1 because i starts from 0 and file numbering starts with 1.
		}
	}
	size = filledTo; // Setting the size to be equaled to filledTo which will change the value of size var in the callee function.
	return _ret;
}
// The main method that checks if all the brackets are balanced.
bool Expressions::checkBrackets() {
	// Gets all the brackets using the funcion in Validator class and stores it.
	std::string expr = getBrackets(expressions, file_handler->getNumLines());

	Stack stack;
	char popped;

	for (size_t i = 0; i < expr.length(); i++) {
		if (isOpeningBracket(expr[i])) {
			stack.push(expr[i]);
			continue;
		}
		// This will cause an error if an ending bracket is passed without passing an opening bracket first.
		if (stack.isEmpty())
			ERROR::generateError("Empty_Stack_Error", "Invalid value pushed onto the stack", 10);
		// Main checking function.
		switch (expr[i]) {
		case ')':
			popped = stack.top()[0];
			stack.pop();
			if (popped == '[' || popped == '{')
				return false;
			break;
		case '}':
			popped = stack.top()[0];
			stack.pop();
			if (popped == '(' || popped == '[')
				return false;
			break;
		case ']':
			popped = stack.top()[0];
			stack.pop();
			if (popped == '(' || popped == '{')
				return false;
			break;
		}
	}
	return stack.isEmpty();
}
// This is the method that will check if the keywords are balanced, if not, will throw proper errors.
bool Expressions::invokeChecks() {
	// Checks if parenthesis are balanced.
	if (!checkBrackets())
		ERROR::generateError("Parenthesis_Mismatch_Error", "Parenthesis are not balanced. Check the code!", -50);
	// Extracts the keywords into a seperate string array.
	int len;
	std::string* expression = extract(len);
	if (DEBUG) { // Will only be invoked if debugging is enabled.
		for (int i = 0; i < len; i++) {
			std::cout << lineNumbers[i] << "\t" << expression[i] << std::endl;
		}
	}

	Stack stack;
	std::string verify;

	// Checks if the first string is Begin or not.
	if (expression[0] != "Begin" && expression[0] != "begin")
		ERROR::generateError("BeginError", "Code doesn't begin with \"begin\" statement! Instead, starts with the keyword: " + expression[0], 50, lineNumbers[0]);
	// Checks if the last string is end or not.
	if (expression[len - 1] != "end")
		ERROR::generateError("EndError", "Program doesn't end with \"end\" statement!", 51, lineNumbers[len - 1]);
	// Flag value to keep a count of IF statements etc.
	int ifCounter = 0,
		elseifCounter = 0,
		elseCounter = 0;

	// Implementation of main algorithm.

	for (int i = 0; i < len; i++) {
		std::string expr = expression[i];
		// Checks if the passed value is either a beginning keyword
		if (isBeginningKeyword(expr)) {
			// If the passed keyword is begin and index is not 0, that means another begin statement has been found, so, displaying proper error.
			if ((has(expr, "Begin") || has(expr, "begin")) && i != 0)
				ERROR::generateError("SyntaxError", "Multiple \"begin\" statements found!", 51, lineNumbers[i]);
			// Checks if the passed keyword is "if", if it is, incremenet and assign values accordingly.
			if (has(expr, "if")) {
				ifCounter++;
				elseCounter = 0;
			}
			// Checks if the passed keyword is "elseif"
			if (has(expr, "elseif")) {
				// If the counter == 0, that means, no if has been pushed. Throwing proper error.
				if (!ifCounter)
					ERROR::generateError("SyntaxError", "\"elseif\" pushed onto the stack but no \"if\" was pushed before!", 52, lineNumbers[i]);
				// If elsecounter has been changed from 0, that means else has been pushed so, throwing an error.
				if (elseCounter)
					ERROR::generateError("SyntaxError", "\"elseif\" pushed onto the stack after \"else\" had already been pushed!", 53, lineNumbers[i]);
				elseifCounter++;
			}
			// Checks if the passed keyword is "else"
			if (has(expr, "else")) {
				// If the counter == 0, that means, no if has been pushed. Throwing proper error.
				if (!ifCounter)
					ERROR::generateError("SyntaxError", "\"else\" pushed onto the stack but no \"if\" was pushed before!", 54, lineNumbers[i]);
				// If elsecounter has been changed from 0, that means another else has already been pushed so, throwing an error.
				if (elseCounter)
					ERROR::generateError("SyntaxError", "Multiple \"else\" statements found!", 55, lineNumbers[i]);
				elseCounter++;
			}
			// Pushing the keyword onto stack
			stack.push(expression[i]);
			continue;
		}
		// This is not going to be called because we've already made pre-checks before the first keyword has to be "begin"
		// or else, the program will stop there.
		if (stack.isEmpty())
			ERROR::generateError("Empty_Stack_Error", "Invalid value pushed onto the stack", 10);

		// Checks if the current expression is "endif"
		if (has(expr, "endif")) {
			// Iterates through out and pops the value to the amount of total value of counters.
			for (int j = 0; j < (ifCounter + elseifCounter + elseCounter); j++) {
				verify = stack.pop();
				// Checks if the popped out value doesn't equate to any if-elseif-else
				if (verify != "if" && verify != "elseif" && verify != "else") {
					// Checks if the popped value is either for or while and throws error. If not, throws another error.
					if (verify == "for" || verify == "while")
						ERROR::generateError("SyntaxError", "A \"" + verify + "\" statement discovered without a proper \"end" + verify + "\"", 57, lineNumbers[i]);
					ERROR::generateError("SyntaxError", "Invalid \"if\" \"endif\" declaration!", 57);
				}
			}
		}
		// Checks if the current expression is "endfor"
		if (has(expr, "endfor")) {
			verify = stack.pop();
			// Checks if the popped out value doesn't equate to "for", if not, throws proper error.
			if (verify != "for")
				ERROR::generateError("SyntaxError", "\"endfor\" statement found but no \"for\" was found to initialize it!", 58, lineNumbers[i]);
		}
		// Checks if the current expression is "endwhile"
		if (has(expr, "endwhile")) {
			verify = stack.pop();
			// Checks if the popped out value doesn't equate to "while", if not, throws proper error.
			if (verify != "while")
				ERROR::generateError("SyntaxError", "\"endwhile\" statement found but no \"while\" was found to initialize it!", 59, lineNumbers[i]);
		}
		// Checks if the current expression is "end"
		if (has(expr, "end")) {
			// If the length is the end of file, that would mean multiple end statements have been declared.
			if (i != len - 1)
				ERROR::generateError("SyntaxError", "Multiple \"end\" statements found!", 60, lineNumbers[i]);
			verify = stack.pop();
			// Although this cannot be the case in our implementation, but it is good to also define a possible outcome.
			if (verify != "Begin")
				ERROR::generateError("SyntaxError", "\"end\" didnot end with \"begin\" but rather \"" + verify + "\"", 61, lineNumbers[i]);
		}
	}
	return stack.isEmpty();
}
// Default Parameterized Constructor
Expressions::Expressions(std::string fileName) {
	file_handler = new FileParser(fileName); // Initializes the file_handler by calling the constructor with fileName
	expressions = new std::string[file_handler->getNumLines()]; // Initializes the expressions to an array by getting the number of lines in the file.
	expressions = file_handler->getContents(); // Reads the content of the file into expressions.
}
// Returns a handle to the FileParser*.
FileParser* Expressions::getHandle()const {
	return this->file_handler;
}
// The interface function that is called to initialize everything.
void Expressions::init() {
	if (!invokeChecks()) // Calls the invokeChecks() function and if it returns false, throws an error, else shows that syntax is balanced.
		ERROR::generateError("Unempty_Stack_Error", "oops! Something was left in the stack unpopped.", 62);
	std::cout << " -- Syntax of data from " << file_handler->getFileName() << " is perfectly balanced!\n";
}
// Destructor.
Expressions::~Expressions() {
	delete expressions; // Deleting expressions class.
	file_handler->~FileParser(); // Explicitly calling the destructor of FileParser().
	delete file_handler; // delete the handle.
	for (int i = 0; i < MAX; i++) // Setting all the lineNumbers to NULL(0)
		lineNumbers[i] = { NULL };
	currentLine = 0; // Setting the current line to NULL.
}