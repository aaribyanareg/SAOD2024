#include <cmath>
using namespace std;

class Complex {
public:
    double Re;
    double Im;

    Complex() { 
        Re = 0; 
        Im = 0; 
    }

    Complex(int re, int im) { 
        Re = re; 
        Im = im; 
    }

    Complex GetConjugated() {
        return Complex(Re, -Im);
    }

    double GetAbs() {
        return sqrt(Re * Re + Im * Im);
    }

    double GetArg() {
        if (GetAbs() == 0)
            return 0;
        else if (Re > 0)
            return atan(Im / Re);
        else if (Re < 0) {
            if (Im >= 0)
                return acos(-1) + atan(Im / Re);
            else
                return -acos(-1) - atan(Im / Re);
        }
        else {
            if (Im > 0)
                return acos(0);
            else
                return -acos(0);
        }
    }

    friend ostream& operator<<(ostream& o, const Complex& c) {
        return o << '(' << c.Re << ", " << c.Im << ')';
    }

    const Complex operator +(const Complex& c) {
        return Complex(Re + c.Re, Im + c.Im);
    }

    const Complex operator -(const Complex& c) {
        return Complex(Re - c.Re, Im - c.Im);
    }

    const Complex operator *(const Complex& c) {
        return Complex(Re * c.Re - Im * c.Im, Re * c.Im + Im * c.Re);
    }

    const Complex operator /(const Complex& c) {
        return Complex((Re * c.Re + Im * c.Im)/(c.Re * c.Re + c.Im * c.Im), (-Re * c.Im + c.Re * Im)/(c.Re * c.Re + c.Im * c.Im));
    }
};