#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>

#include "Date.h"
#include "utils.h"

using namespace std;

class Transaction {
private:
	int idClient;
	string date; // DD/MM/AAAAA
	vector<string> products;

public:
	Transaction(); //constructor for a transaction without arg
	Transaction(int id, string date, vector<string> products); //constructor for a transaction with args
	Transaction(string line); //constructor for a product that extract information by a line (idClient ; Date ; list of Products)

	int getIdClient() const; //get id of transaction
	string getDate() const; //get date of transaction
	vector <string> getProducts() const; //get products of transaction

	void setId(int id); //change id of transaction
	void setDate(string date); //change date of transaction
	void setProducts(vector<string>products); //change products of transaction

	void save(ofstream & out) const; // save Transaction
	friend ostream& operator<<(ostream& out, const Transaction & trans); //show Transaction

};

bool operator<(const Transaction &t1, const Transaction &t2); //compare 2 transactions (a transaction is less than another if your date is lower)



