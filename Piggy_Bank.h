#pragma once
#include <vector> 

class Piggy_Bank
{
public:
	Piggy_Bank(int);
	~Piggy_Bank();


	std::vector<Piggy_Bank*> Keys;
	
	int id;
	int index;
	int lowlink;
	int KeyNum;
	int inDegree;
	bool onStack;
	bool check;



private:

};


