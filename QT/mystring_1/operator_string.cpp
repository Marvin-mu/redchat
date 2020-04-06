#include<iostream>
#include<cstring>

using namespace std;

class Mystring
{
private:
	char* data;
public:
	Mystring(const char* s =NULL);
	Mystring(const Mystring &other);
	void print()const{
		cout << this->data << endl;
	}
	Mystring operator+(const Mystring &other);
	Mystring operator+=(const Mystring &other);
	Mystring &operator=(const Mystring &other);
	char operator[](const int &a);
	bool operator<(const Mystring &other);
	bool operator>(const Mystring &other);
	bool operator<=(const Mystring &other);
	bool operator>=(const Mystring &other);
	bool operator==(const Mystring &other);
	~Mystring(){
		delete []data;
	}
};
Mystring::Mystring(const char* s)
{
	if(s == NULL){
		data = new char[1];
	}else{
		data = new char[strlen(s) + 1];
		strcpy(data,s);
	}
	cout << "create:" << this->data << endl;
}
Mystring::Mystring(const Mystring &other){
	this->data = new char[strlen(other.data) + 1];
	strcpy(this->data,other.data);
	cout << "copy create" << endl;
}
Mystring Mystring::operator+(const Mystring &other)//重载+
{
	static Mystring temp;
	delete []temp.data;
	int len = strlen(this->data) + strlen(other.data) + 1;
	temp.data = new char[len];
	strcpy(temp.data,this->data);
	strcat(temp.data,other.data);
	return temp;
}
Mystring Mystring::operator+=(const Mystring &other)//重载+=
{
	*this = this->operator+(other);
	return *this;
}
Mystring &Mystring::operator=(const Mystring &other)
{
	strcpy(this->data,other.data);
	return *this;
}
char Mystring::operator[](const int &a)
{
	if( a - 1 > strlen(this->data)){
		cerr << "越界咯.........." << endl;
		return 0;
	}
	return this->data[a - 1];
}
bool Mystring::operator<(const Mystring &other){
	if(this->data - other.data < 0){
		return true;
	}else{
		return false;
	}
}
bool Mystring::operator>(const Mystring &other){
	if(this->data - other.data > 0){
		return true;
	}else{
		return false;
	}
}
bool Mystring::operator<=(const Mystring &other){
	if(this->data - other.data <= 0){
		return true;
	}else{
		return false;
	}
}
bool Mystring::operator>=(const Mystring &other){
	if(this->data - other.data >= 0){
		return true;
	}else{
		return false;
	}
}
bool Mystring::operator==(const Mystring &other){
	if(this->data == other.data){
		return true;
	}else{
		return false;
	}
}

int main(void)
{
	Mystring s1("hello,");
	Mystring s2("world!");
	Mystring s3 = s1.operator+(s2);
	cout <<"s3 = \"hello,\"+\"world\"=";
	s3.print();
	cout << "s1:";s1.print();
	cout << "s2:";s2.print();
	s1 += s2;
	cout <<"\"hello,\"+=\"world!\" :";
	s1.print();
	s1 = s2;
	cout <<"\"hello,\"=\"world\" :";
	s1.print();
	cout << "[]:" << s2[2] << endl;
	bool retval = s1 < s2;
	cout << "< bool结果:" << retval << endl;
	retval = s1 > s2;
	cout << "> bool结果:" << retval << endl;
	retval = s1 <= s2;
	cout << "<= bool结果:" << retval << endl;
	retval = s1 >= s2;
	cout << ">= bool结果:" << retval << endl;
	retval = s1 == s1;
	cout << "== bool结果:" << retval << endl;

	return 0;
}
