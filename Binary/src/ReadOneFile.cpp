/*
 * ReadOneFile.cpp
 *
 *  Created on: Dec 3, 2021
 *      Author: Gyy
 */

#include "ReadOneFile.h"

ReadOneFile::ReadOneFile(std::string filename, uint8_t sound) {
	// TODO Auto-generated constructor stub
this->fname = filename;
this->MAXsound = sound;

}

ReadOneFile::~ReadOneFile() {
	// TODO Auto-generated destructor stub
}
uint8_t ReadOneFile::calculateWeight(uint16_t data)
{
uint8_t low = data & 0xFF;
uint8_t high = data >> 8;
return ((low + high)/2);
}

bool ReadOneFile::checkFilesignal()
{
bool answer = false;
uint16_t pair = 0x00;
uint8_t midpoint = 0x00;
char data[2];
std::ifstream fd;
fd.open(this->fname, std::ios::in);
fd.seekg(0,fd.end);
int fsize = fd.tellg();
fd.seekg(0,fd.beg);
//skip most of the header
for (int i = 92; i < fsize; i++)
{
if (i < fsize)
{
    fd.seekg(i,std::ios::beg);
    fd.read(data,sizeof(data)/sizeof(char));
    pair = data[0];
    pair = pair << 8;
    pair += data[1];
    midpoint = this->calculateWeight(pair);
    if (midpoint > this->MAXsound)
    {
    	std::cout<<"at data point: "<<i<<std::endl;
    	return true;
    }
    i++;
}
}
return answer;
}

