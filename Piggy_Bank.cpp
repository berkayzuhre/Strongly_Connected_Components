#include "Piggy_Bank.h"


Piggy_Bank::Piggy_Bank(int _id)
{
	id = _id;
	inDegree = 0;
	onStack = false;
	check = false;
	index = -1;

}

Piggy_Bank::~Piggy_Bank()
{
}