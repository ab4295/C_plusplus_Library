#include <iostream> /* 사실 대부분의 시스템에서 필요x */
#include <fstream>
#include <unistd.h>
#include <iomanip>
#include <cstdlib>	
#include "library.hpp"

using namespace std;
/* -------- student info ------- */
typedef struct InfoStudent
{
	string student_order;
	string stu_name;
	string password;
}InfoStudent;
/* -------- 상수 ------- */
const int LIMIT_OF_PASSWORD = 512; // 전처리기 #define은 왠만하면 쓰지 말자. const와 항상 친할것.
const int TRUE = 1;
const int LIM = 20;
const char* file = "book.txt";
int Check_of_Login = 0; // 전역변수 많이 사용하면 안되는데...흠...이번만 쓸께요ㅠ
InfoStudent user;
inline void eatline() { while(cin.get() != '\n') continue; }
/* -------- function(declare)-------- */

void setUI(int n);
struct InfoStudent Login();
void Sign();
void Manage_Login();
void Loading_Bar();
void Library_Task();
void My_Page();
void In_Book();
/* -------- main --------- */
int main()
{
	setUI(1);
	Manage_Login();
	if(Check_of_Login == 1)
	{
		Library_Task();
	}
	return 0;
}

/* function */
void setUI(int n)
{
	int time = 0;

	switch(n)
	{
		case 1:
			system("clear");
			cout <<  "  ___| |__   __ _ _   _  ___    _   _ _ __ (_)_   __"        << endl;
 			cout <<  " / __| '_ \\ / _` | | | |/ _ \\  | | | | '_ \\| \\ \\ / /"   << endl;
			cout <<  "| (__| | | | (_| | |_| | (_) | | |_| | | | | |\\ V / "       << endl;
 			cout <<  " \\___|_| |_|\\__,_|\\__, |\\___/   \\__,_|_| |_|_| \\_(_) " << endl;
            cout <<  "                  |___/   		                  "        << endl;	
            cout << "	 _ _ _                           "   << endl;     
			cout << "	| (_) |__  _ __ __ _ _ __ _   _  "   << endl;
			cout << "	| | | '_ \\| '__/ _` | '__| | | | "  << endl;
			cout << "	| | | |_) | | | (_| | |  | |_| | "   << endl;
			cout << "	|_|_|_.__/|_|  \\__,_|_|   \\__, | " << endl;
            cout << "            		  	  |___/  "       << endl;
						                          

			cout << "안녕하세요 xx대학교 도서관리 프로그램입니다." << endl;
			cout << "이름과 학번, 비밀번호를 입력하여 로그인 하십시오." << endl;
			break;
		case 2:
			cout << "일치하지 않습니다! 다시 입력하여 주십시오! " << endl;
			break;
		case 3:
			system("clear");
			cout << "로그인 성공! 잠시만 기다려 주십시오....." << endl;
			break;
		case 4:
			system("clear"); /* 여기서 학번을 확인 하는 프로그램은 따로 만들지 않음 */
			cout << "회원이 아니십니까? 이름과 학번, 그리고 비밀번호를 입력하십시오." << endl;
			break;
	}
}
struct InfoStudent Login()
{
	InfoStudent student;
	ifstream inFile; /* 파일 스트림 열기(읽기) */
	string checker_Of_Login; // 로그인을 하기위해 정보가 들어있는걸 확인하는 체커.
	string line;
	int flag = 0;
	int times = 0;
	int offset;

	while(flag == 0)
	{
		system("clear");
		if(times == 0)
		{
			cin.get();
		}
		else if(times == 3)
		{
			cout << "3번이 초과되어 프로그램을 종료합니다." << endl;
			exit(1);
		}
		fflush(stdin);
		cout << "이름을 압력하십시오: ";
		getline(cin,student.stu_name);
		cout << "학번을 입력하십시오: ";
		getline(cin,student.student_order);
		cout << "비밀번호를 입력하십시오: ";
		getline(cin,student.password);

		checker_Of_Login = student.stu_name + ":" + student.student_order + "," + student.password;
		inFile.open("INFO.txt");
		if(inFile.is_open())
		{
			while(!inFile.eof())
			{
				getline(inFile,line);
				if((offset = line.find(checker_Of_Login,0)) != string::npos)
				{
					flag = 1;
				}
			}
			if(flag == 1)
			{
				Check_of_Login = 1;
				Loading_Bar();
				setUI(3);
			}
			else
			{
				setUI(2);
				times++;
				sleep(1);
				inFile.close();
			}
		}
		else
			cerr << "파일을 여는데 실패하였습니다!" << endl;
	}

	return student;
}
void Loading_Bar()
{
	for(int i = 0;i<10;i++)
	{
		cout << ">>>>>>" << endl;
		sleep(1);
	}
	cout << "Loading......." << endl;
	sleep(1);
}
void Sign()
{
	InfoStudent student;
	ofstream outFile; /* 파일 스트림 열기(쓰기) */
	setUI(4);
	cin.get();
	cout << "이름을 압력하십시오: ";
	getline(cin,student.stu_name);
	cout << "학번을 입력하십시오: ";
	getline(cin,student.student_order);
	cout << "비밀번호를 입력하십시오(최대 512자): ";
	getline(cin,student.password);

	outFile.open("INFO.txt", ios_base::out | ios_base::app); //해당 파일을 쓰기 전용으로만 열고, 맨 마지막으로 넣는다.
	if(!outFile.is_open()) // exception handling.
		cout << "파일을 찾을 수 없습니다.";

	outFile << student.stu_name << ":" << student.student_order << "," << student.password; // 파일에다가 이 정보를 들여 놓는다.
	outFile.close();

	cout << "회원가입이 완료되었습니다. 로그인 하십시오.";
}
void Manage_Login()
{
	int checker;

	while(TRUE)
	{
		cout << "1. 아이디를 가지고 있습니다." << endl;
		cout << "2. 아이디를 가지고 있지 않습니다. " << endl;
		cout << "3. 프로그램을 종료합니다." << endl;
		cout << ">>";
		cin >> checker;

		if(checker == 1)
		{
			user = Login();
			break;
		}
		else if(checker == 2)
		{
			Sign();
			system("clear");
			Login();
			break;
		}
		else if(checker == 3)
		{
			break;
			exit(1);
		}
		else
			cout << "잘못 입력하셨습니다.";
	}
}
void Library_Task()
{
	int choice;

	cout << " _____         _    " << endl;
	cout << "|_   _|_ _ ___| | __" << endl;
	cout << "  | |/ _` / __| |/ /" << endl;
 	cout << "  | | (_| \\__ \\   < " << endl;
  	cout << "  |_|\\__,_|___/_|\\_\\" << endl;

  	cout << "하고 싶은 일을 선택하세요~" << endl;
  	cout << "1. 책 입력" << endl;
  	cout << "2. 책 색인" << endl;
  	cout << "3. 책 대출(2권까지 가능)" << endl;
  	cout << "4. 마이 페이지" << endl;
  	cout << "5. 종료" << endl;
  	cout << ">>>";

  	cin >> choice;

  	switch(choice)
  	{
  		case 1:
  			In_Book();
  			break;
  		case 4:
  			My_Page();
  			break;
  		case 5:
  			cout << "작업을 끝내겠습니다." << endl;
  			break;
  		default:
  			cout << "잘못 입력하셨습니다~" << endl;
  	}
}
void In_Book()
{
	fstream finout;
	int cnt = 0;
	string name, author, field;
	int order;

	finout.open(file,ios_base::app | ios_base::out);

	if(finout.is_open())
	{
		eatline();
		cout << "입력 하고 싶은 책의 정보를 입력 하여 주십시오" << endl;
		cout << "이름: ";
		getline(cin, name);
		cout << "저자: ";
		getline(cin,author);
		cout << "분야: ";
		getline(cin, field);
		cout << "순번(숫자로 입력하세요..): ";
		cin >> order;

		Library book(name, author, field, order);

		finout << "이름:" << name << "\n" << "저자:" << author << "\n" << "분야: " << field << "\n" << "순서:" << order << "\n" << "-----------------------" << "\n" << endl;
	}
	else
	{
		cerr << "파일을 열 수 없습니다!!" << endl;
	}
	finout.close();
}
void My_Page()
{
	cout << "이름: " << user.stu_name << endl;
	cout << "학번: " << user.student_order << endl;
}