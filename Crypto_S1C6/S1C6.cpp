#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <assert.h>
#include "Symbols.h"
#include "Base64.h"
#include "XorSolver.h"

using namespace std;

string getFileContents() {
	string result;
	string str;

	ifstream fIn("6.txt");
	assert (fIn != NULL);
	while (fIn >> str) {
		result += str;
	}
	fIn.close();

	return result;
}

const int MIN_KEYSIZE = 2;
const int MAX_KEYSIZE = 40;
const int TRY_DIFFERENT_KEYSIZES = 3;

int main() {
	string input = getFileContents();
	vector<byte> inputRaw = Base64::fromBase64(input);

	vector<string> decryptedMessages = XorSolver::crackXorEncryptedMessage(inputRaw, MIN_KEYSIZE, MAX_KEYSIZE, TRY_DIFFERENT_KEYSIZES);

	for (int i = 0; i < TRY_DIFFERENT_KEYSIZES; i++) {
		cout << "Possible Message " << i << endl << "-------------------" << endl << decryptedMessages[i] << endl << endl;
	}

	return 0;
}
