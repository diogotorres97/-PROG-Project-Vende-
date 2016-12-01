#include "Product.h"

Product::Product()
{

}

Product::Product(string name, double cust)
{
	this->name = name;
	this->cust = cust;
}

Product::Product(string line)
{
	istringstream is;
	is.str(line);
	getline(is, name, ';');
	DeleteWhitespace(name);
	is >> cust;
}

string Product::getName() const {
	return name;
}

double Product::getCust() const {
	return cust;
}

void Product::setName(string name) {
	this->name = name;
}

void Product::setCust(double cust) {
	this->cust = cust;
}


ostream& operator<<(ostream& out, const Product & prod) {

	cout << left <<setw(18) << prod.name << left << setw(4) << prod.cust << endl;

	return out;

}

bool operator<(const Product &prod1, const Product &prod2) {


	return toupper_string(prod1.getName()) < toupper_string(prod2.getName());
}