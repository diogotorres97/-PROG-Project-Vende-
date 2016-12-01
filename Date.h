# pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <string>

using namespace std;

class Date {
private:
	int day;
	int month;
	int year;

public:
	Date();//constructor for a date without args
	Date(string date); //constructor for a date with a string (DD/MM/YYYY)

	int getday() const; //get day of date
	int getmonth() const; //get month of date
	int getyear() const; //get year of date
	string getDate() const; //get date in a string
	int getCompDate() const; //get date in form of integer to compare

	void setDay(int day); //set day of date
	void setMonth(int month); //set month of date
	void setYear(int year); //set year of date

	
	friend ostream& operator<<(ostream& out, const Date & Date); //show a date
	
};

bool operator<(const Date &dat1, const Date &dat2); //compare 2 dates (a date is less than another if it's chronologically lower)
bool operator==(const Date &dat1, const Date &dat2); //compare 2 dates


