#include "Date.h"

Date::Date()
{
	//gives me the actual date
	string add_zero_to_month = "0";
	time_t rawtime;
	struct tm timeinfo;

	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);

	if (timeinfo.tm_mon + 1 < 10)
	{
		add_zero_to_month += to_string(timeinfo.tm_mon + 1);
	}
	else
	{
		add_zero_to_month = to_string(timeinfo.tm_mon + 1);;
	}

	this->day = timeinfo.tm_mday;
	this->month = stoi(add_zero_to_month);
	this->year = timeinfo.tm_year + 1900;
}

Date::Date(string DateStr) { // Date na forma DD/MM/AAA
	
	istringstream instr(DateStr);
	char del;
	instr >> day >> del >> month >> del >> year;
}

int Date::getday() const {
	return day;
}

int Date::getmonth() const {
	return month;
}

int Date::getyear() const {
	return year;
}

string Date::getDate() const
{
	ostringstream oss;
	string date;
	oss << day << "/" << month << "/" << year;
	date = oss.str();

	return date;
}

int Date::getCompDate() const
{
	return year * 10000 + month * 100 + day;
}

void Date::setDay(int day) {
	this->day = day;
}

void Date::setMonth(int month) {
	this->month = month;
}

void Date::setYear(int year) {
	this->year = year;
}

ostream& operator<<(ostream& out, const Date & Date) {
	out << Date.day << '/' << Date.month << '/' << Date.year;
	return out;
}

bool operator<(const Date &dat1, const Date &dat2)
{
	return dat1.getyear() * 10000 + dat1.getmonth() * 100 + dat1.getday() < dat2.getyear() * 10000 + dat2.getmonth() * 100 + dat2.getday();
}

bool operator==(const Date &dat1, const Date &dat2)
{
	return (dat1.getyear() == dat2.getyear() && dat1.getmonth() == dat2.getmonth() && dat1.getday() == dat2.getday());
}