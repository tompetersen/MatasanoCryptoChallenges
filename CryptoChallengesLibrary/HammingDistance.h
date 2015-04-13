/*
 * HammingDistance.h
 *
 *  Created on: 15.03.2015
 *      Author: Tom Petersen
 */

#ifndef HAMMINGDISTANCE_H_
#define HAMMINGDISTANCE_H_

#include <vector>
#include "Symbols.h"

class HammingDistance {
public:
	static int calculateHammingDistance(byte b1, byte b2);
	static int calculateHammingDistance(std::vector<byte>b1, std::vector<byte>b2);
};

#endif /* HAMMINGDISTANCE_H_ */
