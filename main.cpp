#include "Expressions.h"


// Function prototypes.
void menu(); // Prints out the menu.
void input(int&); // Takes the user input and validates it
void readFromFile(std::string&); // Reads data from a file.
void readFromSTDOUT(std::string&); // Reads data from the user from the console and stores it into a file.

int main() {

	int uInput = 0; // Will contain the user's choice.
	std::string* fileContents = NULL; // Is used to read all the data from the file.
	std::string fileName = ""; // Is the file name from which data is to be read.
	Expressions* exp = NULL; // Is a dynamically allocated object of type Expressions.

	menu();
	input(uInput);
	(uInput == 1) ? readFromFile(fileName) : readFromSTDOUT(fileName);
	std::cout << std::endl << std::endl; // Purely for aesthetic purposes.
	exp = new Expressions(fileName); // Dynamically allocating an object
	// Dynamically allocating a string array to store all the data that was read from the file
	fileContents = exp->getHandle()->getContents();
	// Simply invoking the method and not storing the result as we know that, we'll only come to this phase if no errors occured and the equations are perfectly balanced.
	exp->init();
	// Printing the final output | If it ever reaches to this point
	exp->getHandle()->printContents();

	// Clearing all the dynamically allocated memory.
	exp = NULL; // Setting to NULL before deleting.
	fileContents = NULL;
	delete exp;
	delete fileContents;


	std::cout << std::endl << std::endl;
	system("pause");
	return 0;
}

// Function definition
void menu() {
	std::cout << " -- Syntax Checker --\n";
	std::cout << " -- Written in C++ by:\n";
	std::cout << " -- 190792 - Ali Taqi Wajid - BS-CYS-3A\n";
	std::cout << " -- 190787 - Amal Abrar     - BS-CYS-3A\n\n\n";
	std::cout << " -- Our Syntax Checker has two modes of functionality:\n";
	std::cout << " -- 1) Read input from a file.\n";
	std::cout << " -- 2) Read user input and validate that.\n";
	std::cout << "\n\n -- What would you choose? (1 or 2): ";
}
void input(int& uInput) {
	std::cin >> uInput;
	// Checks if the user entered data is either 1 or 2, if not, keeps on taking input.
	while (uInput != 1 && uInput != 2) {
		std::cin.clear(); // Clears the input buffer
		std::cin.ignore(INT_MAX, '\n'); // Ignores any char or any other kind of input.
		std::cout << " -- An invalid value has been entered.\n -- Try again and enter a valid value: ";
		std::cin >> uInput;
	}
}
void readFromFile(std::string& fileName) {
	// Clearing the buffer before taking input.
	std::cin.ignore();
	std::cout << " -- You have chosen to read data from a file.\n";
	std::cout << " -- We've already provided a file named \"dummy_data.txt\" along with our project.\n";
	std::cout << " -- Enter the name of the file you want to read data from OR\n";
	std::cout << " -- press enter and read current data in \"dummy_data.txt\"\n -- > ";
	std::getline(std::cin, fileName); // Prompts user for file name.
	if (fileName == "")
		fileName = "dummy_data.txt"; // Sets to a default value.
	else {
		// If user provides a file name, check if the file name is valid.
		std::ifstream* check = new std::ifstream;
		check->open(fileName);
		if (!check->good())
			ERROR::generateError("FileError", "File is inaccessible OR not found!", 502);
		check->close();
		delete check;
	}
}
void readFromSTDOUT(std::string& fileName) {
	fileName = "uinput.txt";
	int uBuffer;
	std::string* uDataInput;
	std::cout << " -- Enter how much buffer size you want in which you'll enter your data:  ";
	std::cin >> uBuffer;
	while (uBuffer < 0) {
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		std::cout << " -- An invalid value has been entered.\nTry again and enter a valid value: ";
		std::cin >> uBuffer;
	}
	std::cout << " -- NOTE: Take extra note of case-sensitivity!\n";
	std::cout << " -- USER INPUT MODE --\n\n";
	// Dynamically allocating
	uDataInput = new std::string[uBuffer];
	std::cin.ignore(); // Clearing the stdin buffer.
	std::cout << "==============================================================\n";
	for (int i = 0; i < uBuffer; i++) {
		std::cout << i + 1 << "\t| ";
		std::getline(std::cin, uDataInput[i]);
	}
	std::cout << "==============================================================\n";
	// Storing the user input to a output file, then reading the file.
	std::ofstream out;
	out.open(fileName);
	if (!out.good())
		ERROR::generateError("FileError", "Unable to write RAW input to a file. Try manual saving!", 506);
	for (int i = 0; i < uBuffer; i++) {
		out << uDataInput[i];
		if (i != uBuffer - 1)
			out << std::endl;
	}
	out.close();
}