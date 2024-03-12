#include <iostream>
#include "utils.h"
using namespace std;

int main() 
{
	/*int x = 3;
	int* p = &x;
	cout << x << ' ' << *p << ' ' << endl;
	p++;
	cout << p << endl;
	cout << p - &x << endl;
	typedef unsigned char byte;
	byte* pb = (byte*)--p;
	for (byte* pt = pb; pt - pb < sizeof(int); pt++)
		cout << (int)*pt << ' ';
	cout << endl;*/
	int a = 5;
	int b = 3;
	Swap(&a, &b);
	cout << a << ' ' << b << endl;
}