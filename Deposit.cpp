//implementation file for the Deposit class

#include "Deposit.h"

// Validation function for Shift Number
void Deposit::validateDepositAmt()
{
	if (depositAmt < 0)
		throw InvalidAmount();
}

//constructor
Deposit::Deposit() : Transaction()
{
	depositAmt = 0.0;
}

Deposit::Deposit(double amt)
{
	if (amt > 0)
	{
		depositAmt = amt;
		setTransAmt(amt);
		setTransCode();
	}
	else
		throw InvalidAmount();
}

//setter
void Deposit::makeDeposit(double amt)
{
	if (amt >= .01)
		depositAmt = amt;
	else
		throw InvalidAmount();
}


void Deposit::setTransId()
{
	transactionId = transactionId + 1;
}

void Deposit::setTransAmt(double amt)
{
	transactionAmt = amt;
}

void Deposit::setTransCode()
{
	transactionCode = 'D';
}

//getter
double Deposit::getDepositAmt()
{
	return depositAmt;
}