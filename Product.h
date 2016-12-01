#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <vector>
#include "utils.h"

using namespace std;

class Product {
private:
	string name;
	double cust;

public:
	Product(); //constructor for a product without arg
	Product(string name, double cust); //constructor for a product with args
	Product(string line); //constructor for a product that extract information by a line

	string getName() const; //get name of product
	double getCust() const; //get cust of product

	void setName(string name); //change name of product
	void setCust(double cust); //change cust of product

	friend ostream& operator<<(ostream& out, const Product & prod);  //show a client
};

bool operator<(const Product &prod1, const Product &prod2); //compare 2 products (a product is less than another if your name is "alphabetically" lower)