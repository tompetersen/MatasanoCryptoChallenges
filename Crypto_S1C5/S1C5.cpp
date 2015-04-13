#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm> 
#include "Raw.h"
#include "XorCipher.h"
#include "Symbols.h"
#include "CharFrequency.h"

using namespace std;

int main() {
	string message = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
	string key = "ICE";
	
	vector<byte> messageBytes = Raw::stringToRaw(message);
	vector<byte> keyBytes = Raw::stringToRaw(key);
	
	vector<byte> xoredBytes = XorCipher::variableXor(messageBytes, keyBytes);
	string result = Raw::rawToHexString(xoredBytes);
	string expectedResult = "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f";
	
	cout << "Result: " << result << endl;
	cout << "Expect: " << expectedResult << endl;
	cout << "CORRECT: " << boolalpha << (result.compare(expectedResult) == 0) << endl;
}
