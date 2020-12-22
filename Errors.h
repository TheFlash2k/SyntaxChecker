#pragma once

#include <iostream>
#include <string>

// This header file only contains a single class that contains a method which will display error and the type of error that has occured.

class ERROR {
	ERROR() {} // Creating the constructor be private so that this class cannot be instantiated.
public:
	static void generateError(std::string error_type, std::string error_message, int error_code, int line_number = 0) {
		std::cout << "----------------------------------------------\n";
		std::cout << "[!] An ERROR occurred!\n\n";
		std::cout << "[*] Error Type   : " << error_type << std::endl;
		std::cout << "[*] Error Message: " << error_message << std::endl;
		if(line_number)
			std::cout << "[*] Error on Line: " << line_number << std::endl;
		std::cout << "[*] Error Code   : " << error_code << std::endl;
		std::cout << "----------------------------------------------\n\n\n";
		std::cout << "-- The program will now close!\n\n";
		system("pause");
		exit(error_code);
	}
};