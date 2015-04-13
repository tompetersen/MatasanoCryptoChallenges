#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <assert.h>
#include "Raw.h"
#include "Symbols.h"
#include "XorSolver.h"

using namespace std;

vector< vector<byte> > getFileInput() {
	vector< vector<byte> > result;
	string str;

	ifstream fIn("4.txt");
	assert(fIn != NULL);
	while(fIn >> str) {
		result.push_back(Raw::hexStringToRaw(str));
	}
	fIn.close();
	
	return result;
}

int main() {
	vector< vector<byte> > messages = getFileInput();

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
