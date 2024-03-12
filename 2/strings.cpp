#include <iostream>
#include "utils.h"
using namespace std;

int main() {
	char str[] = "Hello!";
	cout << str << endl;
	cout << GetLength(str) << endl;
	char t[32];
	Copy(str, t);
	cout << t << endl;
	cout << Compare(str, t) << endl;
}