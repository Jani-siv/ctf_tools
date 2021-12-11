/*
 * Prime.cpp
 *
 *  Created on: Dec 11, 2021
 *      Author: Gyy
 */

#include "Prime.h"

Prime::Prime() {
	// TODO Auto-generated constructor stub
std::ifstream fd("primeNum.log", std::ios::in);
std::string str;
if (fd.is_open())
{
	int i = 0;
 while (std::getline(fd, str))
 {
     this->savedPri.push_back(stoi(str));
     i++;
 }
 fd.close();
 std::cout<<"Loaded " <<i<<" amount of prime numbers in memory"<<std::endl;
}
else
{
	std::ofstream fd("primeNum.log", std::ios::ate);
	fd << 2;
	fd << '\n';
	fd.close();
}
std::ifstream fd1("NotprimeNum.log", std::ios::in);
if (fd1.is_open())
{
	int p = 0;
 while (std::getline(fd1, str))
 {
     this->savedNotPri.push_back(stoi(str));
     p++;
 }
 fd.close();
 std::cout<<"Loaded " <<p<<" amount of prime numbers in memory"<<std::endl;
}
else
{
	std::ofstream fd1("NotprimeNum.log", std::ios::ate);
	fd1 << 1;
	fd1 << 0;
	fd1 << '\n';
	fd1.close();
}



}

void Prime::createRestPrimenum()
{
this->savedPri.sort();
long long int numero= 0;
for (auto it = this->savedPri.begin(); it != this->savedPri.end(); it++)
{
	long long int temp = it.operator *();
	if (temp > numero)
	{
		numero = temp;
	}
}
std::cout<<"numero on: "<<numero<<std::endl;
while(numero > 2)
{
	auto it = std::find(this->savedPri.begin(),this->savedPri.end(),numero);
	if (it == this->savedPri.end())
	{
		//lasketaan prinum
		bool answer = true;
		/*test from list*/
		if ((numero & (1 << 0)) == 0 )
		{
			answer = false;
		}
		else if (numero==2 || numero == 3)
	    {
	        answer = true;
	    }
	    else {
	        if (numero <=1 || numero % 2 == 0 || numero % 3 == 0){
	            answer = false;
	            }

	        for (int i =5; i*i <= numero; i+=6){
	            if (numero% i == 0 || numero % (i+2) == 0){
	                answer = false;
	            }
	        }
	    }

	    if (answer == true)
	    {
	    	std::cout<<"found new number: "<<numero<<std::endl;
	    	std::ofstream fd("primeNum.log", std::ios::app);
	    	fd << std::to_string(numero);
	    	fd << '\n';
	    	fd.close();
	    }
	}
	numero--;
}
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
	std::string com ="echo \"" + answer + "\"";
	system(com.c_str());
	std::cout<<"answer: "<<answer<<std::endl;
this->deletaAllLists();
}



void Prime::deletaAllLists()
{
std::ofstream fd("primeNum.log", std::ios::app);

	for (auto i = this->primenum.begin(); i != this->primenum.end(); i++)
	{
		long long int temp = i.operator *();
		auto it = std::find(this->savedPri.begin(),this->savedPri.end(),temp);
		if (it == this->savedPri.end())
		{
			fd << std::to_string(temp);
			fd << '\n';
			this->savedPri.push_back(temp);
		}
	}
	fd.close();
	std::ofstream fd1("NotprimeNum.log", std::ios::app);

		for (auto i = this->notprime.begin(); i != this->notprime.end(); i++)
		{
			long long int temp = i.operator *();
			auto it = std::find(this->savedNotPri.begin(),this->savedNotPri.end(),temp);
			if (it == this->savedNotPri.end())
			{
				fd1 << std::to_string(temp);
				fd1 << '\n';
				this->savedNotPri.push_back(temp);
			}
		}
		fd1.close();


	std::cout<<"last run found: "<<this->found<<" prime numbers from file"<<std::endl;
	std::cout<<"last run found: "<<this->foundNot<<" not prime num"<<std::endl;
	std::cout<<"total calculations: "<<this->totalCalc<<std::endl;
	this->testdata.erase(this->testdata.begin(),this->testdata.end());
	this->primenum.erase(this->primenum.begin(),this->primenum.end());
	this->nthpos.erase(this->nthpos.begin(),this->nthpos.end());
	this->notprime.erase(this->notprime.begin(),this->notprime.end());
}

bool Prime::testPrime(long long int value)
{
this->totalCalc++;
	auto it = std::find(this->savedPri.begin(), this->savedPri.end(),value);
		{
		if (it != this->savedPri.end())
			{
			this->found++;
			return true;
			}
		}

	auto it1 = std::find(this->savedNotPri.begin(), this->savedNotPri.end(),value);
		{
		if (it1 != this->savedNotPri.end())
			{
			this->foundNot++;
			return false;
			}
		}
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
