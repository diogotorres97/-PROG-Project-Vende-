#include "Client.h"

Client::Client()
{

}

Client::Client(int id, string name, string dateClient, double amount)
{
	this->id = id;
	this->name = name;
	this->dateClient = dateClient;
	this->amount = amount;
}

Client::Client(string line)
{

	char h1;
	istringstream is;
	is.str(line);
	is >> id >> h1;
	getline(is, name, ';');
	DeleteWhitespace(name);
	getline(is, dateClient, ';');
	DeleteWhitespace(dateClient);
	is >> amount;

}


string Client::getName() const {
	return name;
}

int Client::getId() const {
	return id;
}

double Client::getAmount() const {
	return amount;
}

string Client::getDate() const {
	return dateClient;
}

void Client::save(ofstream & out) const {

	out << id << " ; " << name << " ; " << dateClient << " ; " << amount << endl;

}

void Client::setId(int id)
{
	this->id = id;
}
void Client::setName(string name)
{
	this->name = name;
}
void Client::setAmount(double amount)
{
	this->amount = amount;
}
void Client::setDate(string date)
{
	this->dateClient = date;
}


ostream& operator<<(ostream& out, const Client & cli) {

	out << right << setw(2) << cli.id << "     " << left << setw(25) << cli.name << right << setw(10) << cli.dateClient <<"    "<< left << setw(12) << cli.amount << endl;
	return out;
}



bool operator<(const Client &cli1, const Client &cli2) {

	return toupper_string(cli1.getName()) < toupper_string(cli2.getName());
}


bool sortAmount(const Client &cli1, const Client &cli2){

	return cli1.getAmount() < cli2.getAmount();
}