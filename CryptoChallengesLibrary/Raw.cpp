#include "Raw.h"
#include <assert.h>

byte Raw::byteFromHex(char hex) {
	if (hex >= '0' && hex <= '9') { return hex - '0'; }
	else if (hex >= 'A' && hex <= 'F') { return hex - 'A' + 10; }
	else if (hex >= 'a' && hex <= 'f') { return hex - 'a' + 10; }
	else { assert(false); return 0; }
}

std::vector<byte> Raw::hexStringToRaw(std::string hex) {
	int inputLength = hex.size();
	assert (inputLength % 2 == 0);

	std::vector<byte> result;
	for (int i = 0; i < inputLength; i += 2) {
		result.push_back((byteFromHex(hex[i]) << 4) | byteFromHex(hex[i+1]));
	}
	
	return result;
}

std::string Raw::rawToHexString(std::vector<byte> in) {
	char const hex_chars[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
	
	std::string result;
	for (unsigned int i = 0; i < in.size(); i++) {
		result += hex_chars[in[i] >> 4];
		result += hex_chars[in[i] & 0xF];
	}
	return result;
}

std::vector<byte> Raw::stringToRaw(std::string string) {
	int inputLength = string.size();

	std::vector<byte> result;
	for (int i = 0; i < inputLength; i ++) {
		result.push_back(string[i]);
	}

	return result;
}
