/*
 * XorSolver.cpp
 *
 *  Created on: 13.03.2015
 *      Author: Tom Petersen
 */

#include "XorSolver.h"
#include <algorithm>
#include "XorCipher.h"
#include "CharFrequency.h"
#include "HammingDistance.h"


DecryptionResult XorSolver::solveSingleCharacterXorBestResult(std::vector<byte> message) {
	std::vector<DecryptionResult> resultVector = XorSolver::solveSingleCharacterXorAllResults(message);
	return resultVector[0];
}

DecryptionResult XorSolver::solveSingleCharacterXorBestResult(std::vector<byte> message, std::vector<char> possibleKeys) {
	std::vector<DecryptionResult> resultVector = XorSolver::solveSingleCharacterXorAllResults(message, possibleKeys);
	return resultVector[0];
}

std::vector<DecryptionResult> XorSolver::solveSingleCharacterXorAllResults(std::vector<byte> message) {
	std::vector<char> keys;
	for (char c = 32; c <= 126; c++) {
		keys.push_back(c);
	}

	return XorSolver::solveSingleCharacterXorAllResults(message, keys);
}

std::vector<DecryptionResult> XorSolver::solveSingleCharacterXorAllResults(std::vector<byte> message, std::vector<char> possibleKeys) {
	std::vector<DecryptionResult> resultVector;

	for (unsigned int i = 0; i < possibleKeys.size(); i++) {
		std::vector<byte> key;
		key.push_back(possibleKeys[i]);

		std::vector<byte> byteResult = XorCipher::variableXor(message, key);
		std::string result = std::string(byteResult.begin(), byteResult.end());
		double score = CharFrequency::getEnglishCharScore(result);

		DecryptionResult res(result, score, possibleKeys[i]);
		resultVector.push_back(res);
	}

	std::sort(resultVector.begin(), resultVector.end());

	return resultVector;
}

class KeysizeResult {
public:
	int keysize;
	double normalizedHammingDistance;

	KeysizeResult(int keysize, double normalizedHammingDistance) {
		this->keysize = keysize;
		this->normalizedHammingDistance = normalizedHammingDistance;
	}

	bool operator <(const KeysizeResult& res) const {
		return (normalizedHammingDistance < res.normalizedHammingDistance);
	}
};

std::vector<std::string> XorSolver::crackXorEncryptedMessage(std::vector<byte> message, int MIN_KEYSIZE, int MAX_KEYSIZE, int TRY_NUMBER_OF_KEYSIZES) {
	std::vector<std::string> results;

	std::vector<KeysizeResult> keysizeResults;
	for (int keysize = MIN_KEYSIZE; keysize <= MAX_KEYSIZE; keysize ++) {
		std::vector<byte> firstKeysizeBytes(message.begin(), message.begin() + keysize);
		std::vector<byte> secondKeysizeBytes(message.begin() + keysize, message.begin() + 2 * keysize);
		std::vector<byte> thirdKeysizeBytes(message.begin() + 2 * keysize, message.begin() + 3 * keysize);
		std::vector<byte> fourthKeysizeBytes(message.begin() + 3 * keysize, message.begin() + 4 * keysize);

		double hammingDistance = (double)(HammingDistance::calculateHammingDistance(firstKeysizeBytes, secondKeysizeBytes) +
				HammingDistance::calculateHammingDistance(secondKeysizeBytes, thirdKeysizeBytes) +
				HammingDistance::calculateHammingDistance(thirdKeysizeBytes, fourthKeysizeBytes) +
				HammingDistance::calculateHammingDistance(fourthKeysizeBytes, firstKeysizeBytes) ) / 4;
		double normalizedDistance = hammingDistance / keysize;

		KeysizeResult res(keysize, normalizedDistance);
		keysizeResults.push_back(res);
	}

	sort(keysizeResults.begin(), keysizeResults.end());

	//for the first TRY_DIFFERENT_KEYSIZES keysizes try to solve ciphertexts
	for (int i = 0; i < TRY_NUMBER_OF_KEYSIZES; i++) {
		int keysize = keysizeResults[i].keysize;
		//cout << "Keysize=" << keysize << endl;

		//Initialize vector with empty vectors
		std::vector< std::vector<byte> > blocks;
		for (int k = 0; k < keysize; k++) {
			std::vector<byte> tmp;
			blocks.push_back(tmp);
		}

		//transpose blocks
		for (unsigned int j = 0; j < message.size(); j++) {
			blocks[j % keysize].push_back(message[j]);
		}

		std::vector<byte> key;
		for (int k = 0; k < keysize; k++) {
			DecryptionResult result = XorSolver::solveSingleCharacterXorBestResult(blocks[k]);
			key.push_back(result.key);
		}

		std::vector<byte> resultingMessage = XorCipher::variableXor(message, key) ;
		results.push_back(std::string(resultingMessage.begin(), resultingMessage.end()));
	}

	return results;
}
