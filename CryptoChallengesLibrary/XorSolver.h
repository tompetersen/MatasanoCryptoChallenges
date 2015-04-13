/*
 * XorSolver.h
 *
 *  Created on: 13.03.2015
 *      Author: Tom Petersen
 */

#ifndef XORSOLVER_H_
#define XORSOLVER_H_

#include <string>
#include <vector>
#include "Symbols.h"

class DecryptionResult {
public:
	std::string result;
	double score;
	char key;

	DecryptionResult(std::string result, double score, char key) {
		this->result = result;
		this->score = score;
		this->key = key;
	}

	bool operator <(const DecryptionResult& str) const {
		return (score < str.score);
	}
};

class XorSolver {
public:
	static DecryptionResult solveSingleCharacterXorBestResult(std::vector<byte> message, std::vector<char> possibleKeys);
	static DecryptionResult solveSingleCharacterXorBestResult(std::vector<byte> message);

	static std::vector<DecryptionResult> solveSingleCharacterXorAllResults(std::vector<byte> message, std::vector<char> possibleKeys);
	static std::vector<DecryptionResult> solveSingleCharacterXorAllResults(std::vector<byte> message);

	static std::vector<std::string> crackXorEncryptedMessage(std::vector<byte> message, int MIN_KEYSIZE = 2, int MAX_KEYSIZE = 40, int TRY_NUMBER_OF_KEYSIZES = 3);
};

#endif /* XORSOLVER_H_ */
