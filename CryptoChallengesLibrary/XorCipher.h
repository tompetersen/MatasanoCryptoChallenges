#ifndef XORCIPHER_H_
#define XORCIPHER_H_

#include <vector>
#include "Symbols.h"

class XorCipher {
public:
	static std::vector<byte> fixedXor(std::vector<byte>in1, std::vector<byte>in2);
	static std::vector<byte> variableXor(std::vector<byte>message, std::vector<byte>key);
};

#endif
