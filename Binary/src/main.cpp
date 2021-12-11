/*
 * main.cpp
 *
 *  Created on: Nov 27, 2021
 *      Author: Gyy
 *      Program get list of files and read binary data and sdout it from all files what is in that specified folder
 *      This program was created for SecureBug CTF where was multiple images and in every image header was one char
 *      of the flag. Spaces in filenames and directories might make program behave strange.
 *      depen: -lstdc++fs
 *      TO-DO what order files want to parse
 */
#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ReadOneFile.h"
#define SOUND 0x65

namespace fs = std::filesystem;
void readByte(std::string filename,unsigned int bytesToStart, unsigned int len)
{
        std::fstream File(filename, std::ios::in);
        File.seekg(bytesToStart, std::ios::beg);
        char F[len+1];
        File.read(F, len);
        F[len+1] = 0;
        std::cout <<F;
        File.close();
}

bool parseSound(std::string fname)
{
	ReadOneFile rf(fname, SOUND);
	return rf.checkFilesignal();
}

static void usage(const char *arg0)
{
        std::cerr<<"usage: " << arg0 << "[-d directory | -s bytes where to start | -b how many bytes read]"<<std::endl;
        exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
        if (argc < 2)
        {
                usage(argv[0]);
        }
	int c=0;
        unsigned int bytesToStart=0;
        unsigned int len = 1;
        std::string directory =".";
        std::string filename = "";
        while((c = getopt(argc,argv,"d:b:s:f:")) != -1)
        {
                switch(c)
                {
                case 'd':
                        directory = optarg;
                        break;
                case 'b':

                        bytesToStart=std::stoi(optarg);
                        break;
                case 's':
                        len = std::stoi(optarg);
                        break;
                case 'f':
                		filename = optarg;
                		if(parseSound(filename))
                		{
                			std::cout<<"there's sound in file"<<std::endl;
                		}
                		break;
                default:
                        std::cerr<<"unknown option: " << optopt << std::endl;
                        usage(argv[0]);
                        break;
                }
        }
	std::list<std::string> files;
    for (const auto & entry : fs::directory_iterator(directory))
    {
     	files.push_back(entry.path());
        std::cout << entry.path() << std::endl;
    }
    files.sort();
    for (auto it = files.begin(); it != files.end(); it++)
    {
     	readByte(it.operator *(),bytesToStart,len);
    }
    std::cout<<std::endl;
        return 0;
}
