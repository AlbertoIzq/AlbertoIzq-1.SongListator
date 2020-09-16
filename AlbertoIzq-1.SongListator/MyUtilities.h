#ifndef _MY_UTILITIES_H_
#define _MY_UTILITIES_H_

#include <string>

template <typename T>
T inputValidator();

template <typename T>
std::string toString(T);

std::string centrateText(const std::string&, const int&);

std::string reverseString(const std::string&);

void eraseSubstring(std::string&, const std::string&);

#endif // _MY_UTILITIES_H_
