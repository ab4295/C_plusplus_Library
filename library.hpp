#ifndef LIBRARY_HPP
#define LIBRARY_HPP
#include<string>
#include<iostream>

using namespace std;

class Library
{
private:
	string name; /* 책의 이름 */
	string author; /* 책의 저자 */
	string field; /* 책의 분야 */
	int order; /* 순번 */
public:
	Library();/* default Constructor */
	Library(string n, string a, string f, int o);/* Constructor */
	Library(string n);/* Constructor */
	Library(const Library& lib); /* Copy Constructor */
	~Library(){} /* Destructor */

	Library& operator=(const Library& lib); /* assignment operator */

	void setName(string n) { name = n; } /* inline function */
	void setAuthor(string a) { author = a; } /* inline function */
	void setField(string f) { field = f; } /* inline function */
	void setOrder(int a) { order = a; } /* inline function */
};

#endif