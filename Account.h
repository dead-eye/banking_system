//specification file for the Account class

#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>
#include "Deposit.h"
#include "Withdrawal.h"
#include "Check.h"

using namespace std;

class Account
{
protected:
	int acctNum;
	string firstName;
	string lastName;
	string password;
	double balance;
	int numOfTrans;
	int numOfDeps;
	int numOfWths;
	int numOfChks;
	string trans;
    string * transList;


public:
	//excepton class
	class InvalidPassword
	{};

	// Validation functions
	void validatePassword(string pWord);

	//constructors
	Account();
	Account(int aNum, string fName, string lName, string pWord, double bal);

	//destructor
	~Account();

	//setters
	void setAcctNum(int aNum);
	void setFirstName(string fName);
	void setLastName(string lName);
	void setPassword(string pWord);
	void setBalance(double bal);
	void setNumOfTrans(int numTran);
	void setTransList();
	void setDepList();
	void setWthList();
	void setChkList();
	void setTrans(string);
	string * enlargeTransList(string [], int &, string);
	void deleteTransList();
	void deleteDepList();
	void deleteWthList();
	void deleteChkList();

	//getters
	int getAcctNum();
	string getFirstName();
	string getLastName();
	string getPassword();
	double getBalance();
	int getNumOfTrans();
	int getNumOfDeps();
	double getDep(int idx);
	string getTrans(int);
};

#endif