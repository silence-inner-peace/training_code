#include <string>
//#include <stdio.h>
//#include <stdlib.h>
using namespace std;
class Person
{
public:
	Person();
	//~Person();
	Person(string _firstname, string _lastname)
	{
		this->FirstName = _firstname;
		this->LastName = _lastname;
	};
public:
	string FirstName;
	string LastName;
	// additional information
};

class PersonCriterion
{
public:
	bool operator()(const Person& p1, const Person& p2)
	{
		return p1.LastName < p2.LastName ||(!(p2.LastName<p1.LastName) && p1.FirstName<p2.FirstName);
	}
};

