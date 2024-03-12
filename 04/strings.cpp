#include <iostream>
#include "Str.h"
using namespace std;

int main() {
	Str str("123");
	str = "234";
	cout << str << endl;
	cout << strlen(str) << endl;
	Str str2(str);
	cout << str2 << endl;
	Str str3;
	str3 = str2 = str;
	cout << str3 << endl;
	str3 += "000";
	cout << str3 << endl;
	Str str4 = str + str3;
	cout << str4 << endl;
}