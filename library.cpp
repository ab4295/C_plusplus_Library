#include"library.hpp"
#include<iostream>
#include<string>

using namespace std;

Library::Library() 
{
	name = "none";
	author = "none";
	field = "none";
	order = 0;
}
Library::Library(string n, string a, string f, int o) : name(n), author(a), field(f), order(o) {} // 생성자 초기화는 굳이 안쪽에 넣는 것 보다 멤버 초기자 리스트를 활용하는 것이 빠름.
Library::Library(string n) : name(n)/* Constructor */
{
	author = "none";
	field = "none";
	order = 0;
}
Library::Library(const Library& lib) /* Copy Constructor */
{
	// 동적할당이 없으므로 깊은 복사를 굳이 해야 할 필요가 없음.
	name = lib.name;
	author = lib.author;
	field = lib.field;
	order = lib.order;
}
Library& Library::operator=(const Library& lib) /* assignment operator */
{
	// 동적할당이 없으므로 굳이 깊은 복사를 해야 할 필요가 없음.
	if(this == &lib) //대입할 친구가 그 전의 친구와 동일 할 경우 그냥 원래의 것을 리턴한다.
		return *this;
	else //여긴 복사.
	{
		name = lib.name;
		author = lib.author;
		field = lib.field;
		order = lib.order;
	}
	return *this;
}