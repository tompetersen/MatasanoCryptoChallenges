#ifndef RAW_H_
#define RAW_H_

#include "Symbols.h"
#include <vector>
#include <string>

class Raw {
public:
	static byte byteFromHex(char hex);	
	static std::vector<byte> hexStringToRaw(std::string hex);
	static std::vector<byte> stringToRaw(std::string string);
	static std::string rawToHexString(std::vector<byte> in);
};

#endif
