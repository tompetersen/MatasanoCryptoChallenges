/*
 * HammingDistance.cpp
 *
 *  Created on: 15.03.2015
 *      Author: Tom Petersen
 */


#include "HammingDistance.h"
#include <assert.h>

int HammingDistance::calculateHammingDistance(byte b1, byte b2) {
	byte differ = (b1 ^ b2);
	int numberOfSetBits = 0;

	for (int b = 1; b <= 0xFF; b = b << 1) {
		if ((b & differ) > 0) {
			numberOfSetBits++;
		}
	}

	return numberOfSetBits;
}

int HammingDistance::calculateHammingDistance(std::vector<byte>b1, std::vector<byte>b2) {
	assert(b1.size() == b2.size());

	int hammingDist = 0;
	for (unsigned int i = 0; i < b1.size(); i++) {
		hammingDist += calculateHammingDistance(b1[i], b2[i]);
	}

	return hammingDist;
}


