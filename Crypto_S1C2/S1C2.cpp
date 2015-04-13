#include <iostream>
#include <vector>
#include "Raw.h"
#include "XorCipher.h"
#include "Symbols.h"

using namespace std;

int main() {
	string input1 = "1c0111001f010100061a024b53535009181c";
	string input2 = "686974207468652062756c6c277320657965";
	
	vector<byte> inputRaw1 = Raw::hexStringToRaw(input1);
	vector<byte> inputRaw2 = Raw::hexStringToRaw(input2);
	
	vector<byte> result = XorCipher::fixedXor(inputRaw1, inputRaw2);
	
	cout << "Result: " << Raw::rawToHexString(result) << endl;
	
	return 0;
}
