#include "MyUtilities.h"

#include <sstream>
#include <iostream>
#include <limits> // std::numeric_limits

template <typename T>
T inputValidator() {
	T value{};
	std::string user_entry;
	bool done{ false };
	do {
		std::cin >> user_entry;
		std::istringstream iss{ user_entry };
		if (iss >> value) {
			done = true;
		}
		else {
			std::cout << "Incorrect input, please try again: ";
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discards the input buffer
		}
	} while (!done);
	return value;
}

/*
template <typename T>
std::string toString(const T &element) {
	std::ostringstream ss;
	ss << element;
	std::string result = ss.str();
	return result;
}
*/

std::string centrateText(const std::string& s, const int& width) {
	std::string result;
	int white_spaces{ (width - static_cast<int>(s.length())) / 2 };
	for (int i{ 0 }; i < white_spaces; ++i)
		result += " ";
	result += s;
	for (int i{ 0 }; i < (white_spaces + (width - static_cast<int>(s.length())) % 2); ++i)
		result += " ";
	return result;
}

std::string reverseString(const std::string& s) {
	std::string result;
	for (char c : s) {
		switch (c) {
		case '\\':
			c = '/';
			break;
		case '/':
			c = '\\';
			break;
		case '(':
			c = ')';
			break;
		case ')':
			c = '(';
			break;
		case '<':
			c = '>';
			break;
		case '>':
			c = '<';
			break;
		default:
			break;
		}
		result = c + result;
	}
	return result;
}

void eraseSubstring(std::string& mainString, const std::string& toErase) {
	// Search for the substring in string
	size_t pos = mainString.find(toErase);

	if (pos != std::string::npos)
	{
		// If found then erase it from string
		mainString.erase(pos, toErase.length());
	}
}