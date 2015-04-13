#ifndef CHARFREQUENCY_H_
#define CHARFREQUENCY_H_

#include <map>
#include <vector>
#include <string>
#include "Symbols.h"

class CharFrequency {
private:
	static std::map<char, double> englishCharFrequencyMap;
public:
	static std::map<char, double> englishCharFrequency();
	static double getEnglishCharScore(std::string in);
};

#endif
