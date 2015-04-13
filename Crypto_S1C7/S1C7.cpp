#include <iostream>
#include <string.h>
#include "Base64.h"
#include "AesCipher.h"
#include "FileHelper.h"

using namespace std;

int main() {
	unsigned char* KEY = (unsigned char*)"YELLOW SUBMARINE";
	string input = FileHelper::inputFromFile("7.txt");
	vector<byte> inputRaw = Base64::fromBase64(input);

	cout << "InputRawSize=" << inputRaw.size() << endl;
	unsigned char result[inputRaw.size()]; //HMMMM, verreckt wenn zu klein...

	AesCipher cipher;
	int resultLength = cipher.decrypt(&inputRaw[0], inputRaw.size(), KEY, result);

	cout << "RESULT (length = " << resultLength << "): " << endl << endl;// << result << endl;
	for (int i = 0; i < resultLength; i++) {
		cout << result[i];
	}

	return 0;
}
