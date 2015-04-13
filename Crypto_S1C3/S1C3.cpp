#include <iostream>
#include <vector>
#include "Raw.h"
#include "Symbols.h"
#include "CharFrequency.h"
#include "XorCipher.h"
#include <iomanip>
#include "XorSolver.h"

using namespace std;

int main() {
	string input = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
	vector<byte> message = Raw::hexStringToRaw(input);

	std::vector<char> possibleKeys;
	for (char c = 'A'; c <= 'Z'; c++) {
		possibleKeys.push_back(c);
	}

	DecryptionResult solvedXor = XorSolver::solveSingleCharacterXorBestResult(message, possibleKeys);
	cout << "Result: " << solvedXor.result << endl;

	return 0;
}
