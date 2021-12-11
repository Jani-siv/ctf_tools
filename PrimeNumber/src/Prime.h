/*
 * Prime.h
 *
 *  Created on: Dec 11, 2021
 *      Author: Gyy
 */

#ifndef SRC_PRIME_H_
#define SRC_PRIME_H_
#include <map>
#include <string>
#include <iostream>
#include <list>
#include <stdint.h>
#include <sstream>
#include <unistd.h>
class Prime {
public:
	Prime();
	~Prime();
	void runProgram();
private:
	std::list<long long int> primenum;
	std::list<long long int> notprime;
	std::list<long long int> nthpos;
	std::list<long long int> testdata;
	void parsePos(std::string data, std::string delimiter);
	void giveAnswer();
	void selectParsing(std::string data);
	int parseString(std::string data, std::string delimiter);
	bool testPrime(long long int value);
	void deletaAllLists();
	int K = 0;
	int N = 0;
	std::map<long long int, bool> values;
};

#endif /* SRC_PRIME_H_ */
