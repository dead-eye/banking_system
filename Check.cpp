//implementation file for the Check class

#include "Check.h"

// Validation function for Shift Number
void Check::validateCheckAmt()
{
	if (checkAmt < 0)
		throw InvalidAmount();
}

//constructor
Check::Check() : Transaction()
{
	checkAmt = 0.0;
}

Check::Check(string pay, double amt, string mem, double bal)
{
	if (amt < 0.01)
	{
		throw InvalidAmount();
	}
	else if (amt > bal)
	{
		throw InsufficientFunds();
	}
	else if (pay == "")
	{
		throw InvalidPayee();
	}
	else
	{
		payee = pay;
		checkAmt = amt;
		memo = mem;
		setTransAmt(amt);
		setTransCode();
	}
}

//setter
void Check::makeCheck(double amt)
{
	if (amt >= .01)
		checkAmt = amt;
	else
		throw InvalidAmount();
}


void Check::setTransId()
{
	transactionId = transactionId + 1;
}

void Check::setTransAmt(double amt)
{
	transactionAmt = amt;
}

void Check::setTransCode()
{
	transactionCode = 'C';
}

//getter
double Check::getCheckAmt()
{
	return checkAmt;
}