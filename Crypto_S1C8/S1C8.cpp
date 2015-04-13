#include <iostream>
#include <string.h>
#include "Raw.h"
#include "FileHelper.h"

using namespace std;

int main() {
	vector< vector<byte> > input = FileHelper::linewiseRawInputFromHexFile("8.txt");

	//for each line search for equal 16 byte blocks
	int lineNumber = 0;
	for (vector<byte>line : input) {
		lineNumber++;

		//create blocks
		vector<vector<byte> > blocks;
		for (unsigned int i = 0; i < line.size(); i++) {
			if (i % 16 == 0) {
				vector<byte> tmp;
				blocks.push_back(tmp);
			}
			vector<byte> *currentBlock = &blocks[i/16];
			currentBlock->push_back(line[i]);
		}

		//compute number of same blocks
		int sameBlocks = 0;
		for (unsigned int i = 0; i < blocks.size() - 1; i++) {
			for (unsigned int j = i + 1; j < blocks.size(); j++) {
				if (blocks[i] == blocks[j]) {
					sameBlocks ++;
				}
			}
		}

		if (sameBlocks > 0) {
			cout << "Line " << lineNumber << " - Blocks " << blocks.size() << " SameBlocks " << sameBlocks << endl;
		}
	}

	return 0;
}
