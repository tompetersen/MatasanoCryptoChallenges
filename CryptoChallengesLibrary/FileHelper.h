/*
 * FileHelper.h
 *
 *  Created on: 13.04.2015
 *      Author: Tom Petersen
 */


#ifndef FILEHELPER_H_
#define FILEHELPER_H_

#include <vector>
#include "Symbols.h"
#include <string>

class FileHelper {
public:
	static std::vector< std::vector<byte> > linewiseRawInputFromHexFile(std::string filename);
	static std::string inputFromFile(std::string filename);
};


#endif /* FILEHELPER_H_ */
