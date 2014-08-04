//specification file for the Check class

#ifndef CHECK_H
#define CHECK_H
#include "Transaction.h"
#include <string>

using namespace std;

class Check : public Transaction
{
private:
	string payee;
	double checkAmt;
	string memo;

	// Validation function for deposit amount
	void validateCheckAmt();

public:
	// Exception Classes
	class InvalidAmount
	{};

	class InsufficientFunds
	{};

	class InvalidPayee
	{};

	//constructor
	Check();
	Check(string payee, double amt, string memo, double bal);
	
	//setter
	void makeCheck(double amt);
	void setTransId();
	void setTransAmt(double amt);
	void setTransCode();

	//getter
	double getCheckAmt();

};
#endif