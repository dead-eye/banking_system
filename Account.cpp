//implementation file for the Account class

#include "Account.h"

// Validation function for the password
void Account::validatePassword(string pWord)
{
	if (pWord != password)
		throw InvalidPassword();
}

//constructors
Account::Account()
{
	acctNum = 0;
	firstName = "";
	lastName = "";
	password = "";
	balance = 0.0;
	numOfTrans = 0;
	numOfDeps = 0;
	numOfWths = 0;
	numOfChks = 0;
}

Account::Account(int aNum, string fName, string lName, string pWord, double bal)
{
	acctNum = aNum;
	firstName = fName;
	lastName = lName;
	password = pWord;
	balance = bal;
	numOfTrans = 0;
	numOfDeps = 0;
	numOfWths = 0;
	numOfChks = 0;
	Deposit * depList = new Deposit[numOfDeps];
}

//destructor
Account::~Account()
{}

//setters
void Account::setAcctNum(int aNum)
{
	acctNum = aNum;
}

void Account::setFirstName(string fName)
{
	firstName = fName;
}

void Account::setLastName(string lName)
{
	lastName = lName;
}

void Account::setPassword(string pWord)
{
	password = pWord;
}

void Account::setBalance(double bal)
{
	balance = bal;
}

void Account::setNumOfTrans(int numTran)
{
	numOfTrans = numTran;
}

void Account::setTrans(string entry)
{
	trans = entry;
	transList = Account::enlargeTransList(transList, numOfTrans, entry);
}

string * Account::enlargeTransList(string transList[], int & numTrans, string entry)
{
	//declare temp array
	string *tempTransList;

	// create new temp array
	tempTransList = new string[numTrans];
	
	// copy contents of account array to temp array
	for (int index = 0; index < numTrans; index ++)
		tempTransList[index] = transList[index];

	// delete original accounts array
	delete [] transList;
	transList = 0;

	// increment array size
	numTrans++;

	// create new larger accounts array
	transList = new string [numTrans];

	// copy contents of temp array to new accounts array
	for (int index = 0; index < numTrans - 1; index ++)
	transList[index] = tempTransList[index];

	// add contents to the new last element
	transList[numTrans - 1] = entry;
			
	// delete the temp array
	delete [] tempTransList;
	tempTransList = 0;

	//return pointer to the new transList array
	return transList;
}

void Account::setTransList()
{
	transList = new string[numOfTrans];
}

void Account::deleteTransList()
{
	delete [] transList;
	transList = 0;
	numOfTrans = 0;
}

//getters
int Account::getAcctNum()
{
	return acctNum;
}

string Account::getFirstName()
{
	return firstName;
}

string Account::getLastName()
{
	return lastName;
}

string Account::getPassword()
{
	return password;
}

double Account::getBalance()
{
	return balance;
}

int Account::getNumOfTrans()
{
	return numOfTrans;
}

int Account::getNumOfDeps()
{
	return numOfDeps;
}

string Account::getTrans(int idx)
{
	return transList[idx];
}