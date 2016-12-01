#include "utils.h"

void clearScreen() {

	COORD upperLeftCorner = { 0,0 };
	DWORD charsWritten;
	DWORD conSize;
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO  csbi;

	GetConsoleScreenBufferInfo(hCon, &csbi);
	conSize = csbi.dwSize.X * csbi.dwSize.Y;

	// fill with spaces
	FillConsoleOutputCharacter(hCon, TEXT(' '), conSize, upperLeftCorner, &charsWritten);
	GetConsoleScreenBufferInfo(hCon, &csbi);
	FillConsoleOutputAttribute(hCon, csbi.wAttributes, conSize, upperLeftCorner, &charsWritten);

	// cursor to upper left corner
	SetConsoleCursorPosition(hCon, upperLeftCorner);
}

bool fileExists(string fileName)
{
	ifstream f;
	f.open(fileName);
	if (!f.is_open())
	{
		cerr << "File " << fileName << " not found !\n";
		return false;
	}
	else
	{
		f.close();
		return true;
	}
}

void DeleteWhitespace(string &s)
{
	//Delete whitespace characters in the beginning
	int index = 0;

	while (s.at(index) == ' ')
	{
		s.erase(index, 1);
	}
	//Delete whitespace characters in the end
	int lastindex = s.size() - 1;
	while (s.at(lastindex) == ' ')
	{
		s.erase(lastindex, 1);
		lastindex--;
	}
}

string truncate_strings(string word)
{
	int i = 0, j;
	while (word.at(i) == ' ')
	{
		word = word.substr(1);
	}
	j = word.size() - 1;
	while (word.at(j) == ' ')
	{
		word = word.substr(0, j);
		j--;
	}
	return word;
}

bool is_valid_date(string date)
{
	int day;
	int month;
	int year;
	istringstream readtemp;
	readtemp.str(date);
	readtemp >> day;
	readtemp.ignore(INT_MAX, '/');
	readtemp >> month;
	readtemp.ignore(INT_MAX, '/');
	readtemp >> year;
	/* Variable that determines if given date is invalid. Is set to true if at least one of the following apply:
	- Given day is bigger than 31
	- Given month is bigger than 12
	- Given day is bigger than 30 and month is February, April, June, September or November
	- Given day is bigger than 29 and month is February*/
	bool invalidstate = (day < 1) || (month < 1) || (day > 31) || (month > 12) || (day > 30 && (month == 2 || month == 4 || month == 6 || month == 9 || month == 11)) || (day > 29 && month == 2);
	/*If all conditions fail, then it's a valid date, the opposite of the variable's logic value. Same thing if vice-versa, so what needs to be returned is its logical negation*/
	return !invalidstate;
}

bool bissextile(int &y)
{
	bool val = false;;
	if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0))
	{

		val = true;


	}
	return val;

}

bool check_has_letters(string str)
{
	for (size_t i = 0; i < str.size(); i++)
	{
		if (!isdigit(str.at(i)) && str.at(i) != '.')
		{
			return true;
		}
	}
	return false;
}

bool check_has_digits(string str)
{
	for (size_t i = 0; i < str.size(); i++)
	{
		if (isdigit(str.at(i)))
		{
			return true;
		}
	}
	return false;
}

double read_double(string msg)
{
	bool valid = false;
	double value, flag = 0;

	do
	{
		if (flag >= 1)
		{
			
			cout <<endl<<TAB<<"Please indicate a value that only contains digits!!" << endl;
		}
		cout <<endl<< TAB<<msg;
		cin >> value;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
		}
		else
		{
			valid = true;
		}
		flag++;
	} while (valid == false);

	return value;

}

int read_int(string msg)
{
	bool valid = false;
	int value, flag = 0;

	do
	{
		if (flag >= 1)
		{
			cout<<endl<<TAB << "Please indicate a value that only contains digits!!" << endl;
		}
		
		cout <<endl<< TAB << msg;
		cin >> value;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
		}
		else
		{
			valid = true;
		}
		flag++;
	} while (valid == false);

	return value;

}

unsigned int read_op(int min, int max)
{

	unsigned int op;

	bool valid = false;
	int flag = 0;

	do
	{
		if (flag >= 1)
		{
			cout<<TAB << "Please indicate a valid option!!!" << endl;
			cout << TAB << "Enter your option: ";
		}

		cin >> op;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
		}
		else
		{
			if (op<min || op > max)
			{
				valid = false;
			}
			else
			{
				valid = true;
			}
		}
		flag++;
	} while (valid == false);

	return op;
}

int searchPosInteger(int elem, vector <int> v1)
{

	int pos = find(v1.begin(), v1.end(), elem) - v1.begin();
	if (pos >= v1.size()) {
		//id not found
		pos = -1;
	}
	return pos;
}

int searchPosString(vector <string> v1, string str)
{
	int pos = find(v1.begin(), v1.end(), str) - v1.begin();
	if (pos >= v1.size()) {
		//id not found
		pos = -1;
	}
	return pos;
}

bool searchString(vector <string> v1, string str)
{
	int pos = find(v1.begin(), v1.end(), str) - v1.begin();
	if (pos >= v1.size()) {
		//prod not found
		return false;
	}
	return true;;
}

bool verify_dates_end_gr_beg(string date_beg, string date_end)
{

	Date dt_beg(date_beg), dt_end(date_end);
	int dbeg, dend;
	int db = dt_beg.getday(), de = dt_end.getday(), mb = dt_beg.getmonth(), me = dt_end.getmonth(), yb = dt_beg.getyear(), ye = dt_end.getyear();

	dbeg = yb * 10000 + mb * 100 + db;
	dend = ye * 10000 + me * 100 + de;

	if (dbeg < dend)
	{
		return true;
	}
	else {
		return false;
	}

}

vector <string> split(string line, char delim)
{
	vector<string> elems;
	size_t prev = 0, pos;

	while ((pos = line.find_first_of(delim, prev)) != string::npos)
	{
		if (pos > prev)
			elems.push_back(line.substr(prev, pos - prev));
		prev = pos + 1;
	}
	if (prev < line.length())
	{
		elems.push_back(line.substr(prev, std::string::npos));
	}

	return elems;
}

bool verify_date_between(string date_new, string date_beg, string date_end)
{
	int dnew, dbeg, dend;
	int dn, db, de, mn, mb, me, yn, yb, ye;

	vector <string> vec_date = split(date_new, '/');

	dn = stoi(vec_date.at(0));
	mn = stoi(vec_date.at(1));
	yn = stoi(vec_date.at(2));

	vec_date = split(date_beg, '/');
	db = stoi(vec_date.at(0));
	mb = stoi(vec_date.at(1));
	yb = stoi(vec_date.at(2));

	vec_date = split(date_end, '/');
	de = stoi(vec_date.at(0));
	me = stoi(vec_date.at(1));
	ye = stoi(vec_date.at(2));

	dnew = yn * 10000 + mn * 100 + dn;
	dbeg = yb * 10000 + mb * 100 + db;
	dend = ye * 10000 + me * 100 + de;

	if (dnew >= dbeg && dnew <= dend)
	{
		return true;
	}
	else
	{
		return false;
	}

}

string write_vector_products_name(vector <string> vec)
{
	string str = "";
	for (size_t i = 0; i < vec.size(); i++)
	{
		str += vec.at(i) + ", ";
	}
	return str.substr(0, str.size() - 2);
}


int getMax(vector <int> v1)
{
	int max = v1.at(0);
	int pos = 0;

	for (size_t i = 1; i < v1.size(); i++)
	{
		if (v1.at(i) > max)
		{
			max = v1.at(i);
			pos = i;
		}
	}
	return pos;
}

string toupper_string(string s)
{
	for (int i = 0; i < s.length(); i++)
	{
		s.at(i) = toupper(s.at(i));
	}

	return s;
}

