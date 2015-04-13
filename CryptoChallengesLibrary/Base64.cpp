#include "Base64.h"
#include <assert.h>

#include <iostream>

char Base64::base64Encode(byte in) {
	if (in <= 25) { return 'A' + in; }
	else if (in <= 51) { return 'a' + in - 26; }
	else if (in <= 61) { return '0' + in - 52; }
	else if (in == 62) { return '+'; }
	else if (in == 63) { return '/'; }
	else { assert(false); return '?';  }
}

byte Base64::base64Decode(char in) {
	if (isupper(in)) { return in - 'A'; }
	else if (islower(in)) { return in - 'a' + 26; }
	else if (isdigit(in)) { return in - '0' + 52; }
	else if (in == '+') { return 62; }
	else if (in == '/') { return 63; }
	else if (in == '=') { return 0; }
	else { assert(false); return 0; }
}

std::string Base64::toBase64(std::vector<byte> input) {
	std::string appendix;
	while (input.size() % 3 != 0) {
		input.push_back(0);
		appendix += "=";
	}
	
	std::string result;
	for (unsigned int i = 0; i < input.size(); i+=3) {
		result += base64Encode(input[i] >> 2);
		result += base64Encode(((input[i] << 4) & 0x30) | (input[i+1] >> 4));
		result += base64Encode(((input[i+1] << 2) & 0x3c) | (input[i+2] >> 6));
		result += base64Encode((input[i+2] & 0x3F));
	} 
	
	return result.substr(0, result.size() - appendix.size()) + appendix;
}

std::vector<byte> Base64::fromBase64(std::string input) {
	assert(input.size() % 4 == 0);

	//get number of trailing =
	int trailingEqualsSigns = 0, j = input.size() - 1;
	while (input[j] == '=') {
		trailingEqualsSigns ++;
		j--;
	}

	std::vector<byte> result;
	for (unsigned int i = 0; i < input.size(); i+=4) {
		result.push_back( (base64Decode(input[i]) << 2) | (base64Decode(input[i+1]) >> 4) );
		result.push_back( ((base64Decode(input[i+1]) & 0xF) << 4) | ((base64Decode(input[i+2]) & 0x3c) >> 2) );
		result.push_back( (base64Decode(input[i+2]) << 6) | base64Decode(input[i+3]) );
	}

	//remove as much trailing bytes as there where = at the end of input
	while (trailingEqualsSigns > 0) {
		result.pop_back();
		trailingEqualsSigns --;
	}

	return result;
}
