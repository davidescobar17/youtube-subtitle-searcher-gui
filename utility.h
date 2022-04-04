#ifndef UTILITY_H
#define UTILITY_H

#include <string>

// check if line read from the subtitle is the timestamp
bool isTime(std::string line);

// checks if a line in the subtitles contains the searched term
bool containsTarget(std::string line, std::string target);

// remove tags inside of the subtitles
std::string removeTags(std::string s);

// convert string to lowercase
std::string toLowerString(std::string s);

bool videoTitleContainsTarget(std::string line, std::string target);

// extract time in seconds from subtitle timestamp
int extractTime(std::string str);

#endif // UTILITY_H
