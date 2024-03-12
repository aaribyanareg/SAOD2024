#include <iostream>
#include "Complex.h"
using namespace std;

int main() {
	Complex comp1(1, 2);
	Complex comp2(1, 2);
	cout << comp1 + comp2 << endl;
	cout << comp1 - comp2 << endl;
	cout << comp1 * comp2 << endl;
	cout << comp1 / comp2 << endl;
	cout << comp1.GetConjugated() << endl;
	cout << comp1.GetAbs() << endl;
	cout << comp1.GetArg() << endl;
	Complex comps[4]{ Complex(), Complex(-1, -1), comp1, comp2 };
	for (int i = 0; i < 4; i++)
		cout << comps[i] << ' ';
	cout << endl;
	Complex* pc = new Complex(1,2);
	cout << pc << endl;
	delete pc;
	//я не понял, что от меня по большей части хотят в пункте 8
}