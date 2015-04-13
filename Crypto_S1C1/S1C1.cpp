#include <iostream>
#include <vector>
#include "Raw.h"
#include "Base64.h"

using namespace std;

int main() {
	string inputHex = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
	vector<byte> inputRaw = Raw::hexStringToRaw(inputHex);
	string output = Base64::toBase64(inputRaw);
	cout << "Output(Challenge): " << output << endl;
	
	string inputHex2 = "457600000034F7EA34AA";
	inputRaw = Raw::hexStringToRaw(inputHex2);
	output = Base64::toBase64(inputRaw);
	cout << "Output(Test): " << output << endl;
	
	return 0;
}
