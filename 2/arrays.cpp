#include <iostream>
#include "utils.h"
using namespace std;

int main() {
	int a[5]{1, 2, 3, 4, 5};
	WriteArray(a, 5);
	Rotate(a, 5);
	WriteArray(a, 5);
	Rotate(a, 5, true);
	WriteArray(a, 5);
}