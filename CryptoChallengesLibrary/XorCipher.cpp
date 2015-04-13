#include "XorCipher.h"
#include <assert.h>

std::vector<byte> XorCipher::variableXor(std::vector<byte>message, std::vector<byte>key) {
	//compute equal length key (by appending key multiple times
	//or ignore bytes if key is longer than message)
	std::vector<byte> sameSizeKey;
	for (unsigned int i = 0, j = 0; i < message.size(); i++) {
		sameSizeKey.push_back(key[j++]);
		if (j == key.size()) {
			j = 0;
		}
	}
	
	return fixedXor(message, sameSizeKey);
}

std::vector<byte> XorCipher::fixedXor(std::vector<byte>in1, std::vector<byte>in2) {
	assert(in1.size() == in2.size());
	
	std::vector<byte>result;
	for (unsigned int i = 0; i < in1.size(); i++) {
		result.push_back(in1[i] ^ in2[i]);
	}
	return result;
}
