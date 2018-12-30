#include <iostream>
#include <set>
#include "Person.h"
using namespace std;
int main( int argc, char* argv[])
{
	set<Person, PersonCriterion> colls;
	colls.insert(Person("Tom","James"));
	colls.insert(Person("Mike","James"));
	colls.insert(Person("Jane","Bush"));
	colls.insert(Person("Bill","Gates"));

	std::set<Person, PersonCriterion>::iterator iter;
	for ( iter = colls.begin(); iter!=colls.end(); ++iter)
	{		
		Person p = (Person)(*iter);		

		cout<< p.FirstName<<"  "<<p.LastName<<endl;
	}		
	return 1;
}
