#ifndef BASE64_H_
#define BASE64_H_

#include "Symbols.h"
#include <string>
#include <vector>

class Base64 {
	static char base64Encode(byte in);
	static byte base64Decode(char in);
public:
	static std::string toBase64(std::vector<byte> input);
	static std::vector<byte> fromBase64(std::string input);
};

#endif
