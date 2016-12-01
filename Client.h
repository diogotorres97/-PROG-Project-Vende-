#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

#include "Date.h"
#include "utils.h"

using namespace std;

class Client {
private:
	int id;
	string name;
	string dateClient;
	double amount;

public:
	Client(); //constructor for a client without arg
	Client(int id, string name, string dateClient, double amount); //constructor for a client with args
	Client(string line); //constructor for a client that extract information by a line

	int getId() const; //get id of client
	string getName() const; //get name of client
	double getAmount() const; //get amount of client
	string getDate() const; //get date of client

	void setId(int id); //change id of client
	void setName(string name); //change name of client
	void setAmount(double amount); //change amount of client
	void setDate(string date); //change date of client

	void save(ofstream & out) const; //save a client to a file
	friend ostream& operator<<(ostream& out, const Client & cli); //show a client

};

bool operator<(const Client &cli1, const Client &cli2); //compare 2 clients (a client is less than another if your name is "alphabetically" lower)
bool sortAmount(const Client &cli1, const Client &cli2); //compare 2 clients (a client is less than another if your amount is lower)

