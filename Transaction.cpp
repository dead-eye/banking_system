//implementiation file for the Transaction class

#include "Transaction.h"

//constructors
Transaction::Transaction()
{
	transactionId = 0;
	transactionAmt = 0.0;
	transactionCode = ' ';
}

Transaction::Transaction(int id, double amt, char code)
{
	transactionId = id;
	transactionAmt = amt;
	transactionCode = code;
}


//destructor
Transaction::~Transaction()
{ }


//getters
int Transaction::getTransId()
{
	return transactionId;
}

double Transaction::getTransAmt()
{
	return transactionAmt;
}

char Transaction::getTransCode()
{
	return transactionCode;
}


//setters
void Transaction::setTransId(int id)
{
	transactionId = id;
}

void Transaction::setTransAmt(double amt)

{
	transactionAmt = amt;
}

void Transaction::setTransCode(char code)
{
	transactionCode = code;
}