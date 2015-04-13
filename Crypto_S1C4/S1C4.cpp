#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Raw.h"
#include "Symbols.h"
#include "XorSolver.h"
#include "FileHelper.h"

using namespace std;

int main() {
	vector< vector<byte> > messages = FileHelper::linewiseRawInputFromHexFile("4.txt");

	vector<DecryptionResult> resultVector;
	for(unsigned int j = 0; j < messages.size(); j++) {
		vector<DecryptionResult> messageResults = XorSolver::solveSingleCharacterXorAllResults(messages[j]);
		resultVector.insert(resultVector.end(), messageResults.begin(), messageResults.end());
	}
	
	sort(resultVector.begin(), resultVector.end());

	for (int j = 0; j < 10; j++) {
		cout << j << ". " << resultVector[j].score << " " << resultVector[j].result;
		cout << " ['" << resultVector[j].key <<  "]" << endl;
	}	
	
	return 0;
}
