/*
 * Prime.cpp
 *
 *  Created on: Dec 11, 2021
 *      Author: Gyy
 */

#include "Prime.h"

Prime::Prime() {
	// TODO Auto-generated constructor stub

}

Prime::~Prime() {
	// TODO Auto-generated destructor stub
}

void Prime::runProgram()
{
	std::string line;

while (std::getline(std::cin, line))
		{
		this->selectParsing(line);
		std::cout<<line<<std::endl;
		//usleep(10000);
		}
}
void Prime::selectParsing(std::string data)
{
	std::stringstream ss;
	std::string temp;
	long long int test;
	std::string N_line = "N";
	std::string K_line = "K";
	std::string numbers_line = "numbers";
	std::string queries_line = "queries";
	std::string answer_line = "answers";
if (data.find(N_line) == 0)
{
	ss << data;
	while (!ss.eof())
		{
		ss >> temp;
		if (std::stringstream(temp) >> test)
			{
			this->N = test;
			}
		}
}
else if (data.find(K_line) == 0)
{
	ss << data;
	while (!ss.eof())
		{
		ss >> temp;
		if (std::stringstream(temp) >> test)
			{
			this->K = test;
			}
		}
}
else if (data.find(numbers_line) == 0)
{
//clean before numbers

	data.erase(0,data.find("[")+1);
	data.replace(data.find(']'),1,",");// (data.find("]"),1);

	this->parseString(data,",");
}
else if (data.find(queries_line) == 0)
{

	data.erase(0,data.find("[")+1);
	data.replace(data.find(']'),1,",");

	this->parsePos(data,",");
}
else if (data.find(answer_line) == 0)
{

}
}


int Prime::parseString(std::string data, std::string delimiter)
{
	size_t pos = 0;
	std::string token;
	long long int test;

	while ((pos = data.find(delimiter)) != std::string::npos) {
	    token = data.substr(0, pos);
	    if (std::stringstream(token) >> test)

	    {
	    	bool answer = this->testPrime(test);
	    	if (answer)
	    	{
	    		this->primenum.push_back(test);
	    	}
	    	if(!answer)
	    	{
	    		this->notprime.push_back(test);
	    	}
	    }
	    data.erase(0, pos + delimiter.length());
	}


return 0;
}

void Prime::parsePos(std::string data, std::string delimiter)
{

	size_t pos = 0;
	std::string token;
	long long int test;
	while ((pos = data.find(delimiter)) != std::string::npos)
	{

		token = data.substr(0,pos);
		if (std::stringstream(token) >> test)
		{
			this->nthpos.push_back(test);
		}
		data.erase(0, pos + delimiter.length());
	}
	this->giveAnswer();
}

void Prime::giveAnswer()
{
	std::string answer = "[";
	for (auto it = this->primenum.begin(); it != this->primenum.end(); it++)
	{
		for (auto itnon = this->notprime.begin(); itnon != this->notprime.end(); itnon++)
		{
			this->testdata.push_back((itnon.operator *() + it.operator *()));
		}
	}
	this->testdata.sort();

	for (auto it = this->nthpos.begin(); it != this->nthpos.end(); it++)
	{
		std::list<long long int>::iterator data = this->testdata.begin();
		//tässä hyppää väärään arvoon
		int positio = it.operator *();
		positio--;
		std::advance(data,positio);
		answer += std::to_string(data.operator *());
		answer += ",";
	}


	answer.replace(answer.length()-1,1,"]");
	std::ofstream fd("answer.log",std::ios::ate);
	fd << answer;
	fd.close();
	std::cout<<"answer: "<<answer<<std::endl;
this->deletaAllLists();
}



void Prime::deletaAllLists()
{
	this->testdata.erase(this->testdata.begin(),this->testdata.end());
	this->primenum.erase(this->primenum.begin(),this->primenum.end());
	this->nthpos.erase(this->nthpos.begin(),this->nthpos.end());
	this->notprime.erase(this->notprime.begin(),this->notprime.end());
}

bool Prime::testPrime(long long int value)
{
	bool answer = true;
	/*test from list*/
	if ((value & (1 << 0)) == 0 )
	{
		return false;
	}
    if (value==2 || value == 3)
    {
        return true;
    }
    else {
        if (value <=1 || value % 2 == 0 || value % 3 == 0){
            return false;
            }

        for (int i =5; i*i <= value; i+=6){
            if (value % i == 0 || value % (i+2) == 0){
                return false;
            }
        }
    }
    return true;


	/*
	    if (value == 0 || value == 1) {
	        return false;
	    }
	    else {
	        for (int i = 2; i <= value / 2; ++i) {
	            if (value % i == 0) {
	                return false;
	            }
	        }
	    }

	    return true;
*/
	return answer;
}
