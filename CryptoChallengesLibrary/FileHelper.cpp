/*
 * FileHelper.cpp
 *
 *  Created on: 13.04.2015
 *      Author: Tom Petersen
 */

#include "FileHelper.h"

#include <assert.h>
#include <fstream>
#include "Raw.h"


std::vector< std::vector<byte> > FileHelper::linewiseRawInputFromHexFile(std::string filename) {
	std::ifstream fIn(filename.c_str());
	assert(fIn != NULL);

	std::vector< std::vector<byte> > result;
	std::string str;

	while(fIn >> str) {
		result.push_back(Raw::hexStringToRaw(str));
	}
	fIn.close();

	return result;
}

std::string FileHelper::inputFromFile(std::string filename) {
	std::ifstream fIn(filename.c_str());
	assert (fIn != NULL);

	std::string result;
	std::string str;

	while (fIn >> str) {
		result += str;
	}
	fIn.close();

	return result;
}


