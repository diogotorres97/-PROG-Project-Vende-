#include "Transaction.h"

Transaction::Transaction()
{

}

Transaction::Transaction(int id, string date, vector<string> products)
{
	this->idClient = id;
	this->date = date;
	this->products = products;
}

Transaction::Transaction(string line) { // le uma Transaction na forma de  idClient ; Date ; lista Products

	istringstream is;
	char h1;
	is.str(line);
	is >> idClient >> h1;
	getline(is, date, ';');
	DeleteWhitespace(date);
	while (getline(is, line, ','))
	{
		products.push_back(truncate_strings(line));
	}

}

int Transaction::getIdClient() const {
	return idClient;
}

string Transaction::getDate() const {
	return date;
}

vector <string> Transaction::getProducts() const {
	return products;
}

void Transaction::setId(int id) {
	this->idClient = id;
}

void Transaction::setDate(string date) {
	this->date = date;
}

void Transaction::setProducts(vector<string> products) {
	this->products = products;
}


void Transaction::save(ofstream & out) const { // Transaction guardada como na forma de  idClient ; Date ; lista Products
	out << idClient << " ; " << date << " ; " << write_vector_products_name(products) << endl;
}


ostream& operator<<(ostream& out, const Transaction & trans) {

	out << right << setw(2) << trans.idClient << "     " << left << setw(10) << trans.date << "   " << write_vector_products_name(trans.products) << endl;

	return out;
}

bool operator<(const Transaction &t1, const Transaction &t2)
{
	Date d1(t1.getDate()), d2(t2.getDate());
	return d1 < d2;
}
