#include <iostream>
#include <vector>
#include <string>
#include "Symbols.h"
#include "Base64.h"
#include "XorSolver.h"
#include "FileHelper.h"

using namespace std;

const int MIN_KEYSIZE = 2;
const int MAX_KEYSIZE = 40;
const int TRY_DIFFERENT_KEYSIZES = 3;

int main() {
	string input = FileHelper::inputFromFile("6.txt");
	vector<byte> inputRaw = Base64::fromBase64(input);

	vector<string> decryptedMessages = XorSolver::crackXorEncryptedMessage(inputRaw, MIN_KEYSIZE, MAX_KEYSIZE, TRY_DIFFERENT_KEYSIZES);

	for (int i = 0; i < TRY_DIFFERENT_KEYSIZES; i++) {
		cout << "Possible Message " << i << endl << "-------------------" << endl << decryptedMessages[i] << endl << endl;
	}

	return 0;
}
