/*
 * ReadOneFile.h
 *
 *  Created on: Dec 3, 2021
 *      Author: Gyy
 */

#ifndef SRC_READONEFILE_H_
#define SRC_READONEFILE_H_
#include <string>
#include <fstream>
#include <iostream>
#include <stdbool.h>
#include <stdint.h>
class ReadOneFile {
public:
	ReadOneFile(std::string filename, uint8_t sound);
	~ReadOneFile();
	bool checkFilesignal();
private:
	std::string fname;
	uint8_t MAXsound;
	uint8_t calculateWeight(uint16_t data);

};

#endif /* SRC_READONEFILE_H_ */
