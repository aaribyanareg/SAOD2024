#pragma once

class Str {
private:
	char* _pszText;
public:
    Str(const char* str) {
        int length = 0;
        while (str[length] != '\0') {
            length++;
        }
        _pszText = new char[length + 1];
        for (int i = 0; i < length; i++) {
            _pszText[i] = str[i];
        }
        _pszText[length] = '\0';
    }

    Str(const Str& s)
    {
        _pszText = new char[strlen(s._pszText) + 1];
        strcpy_s(_pszText,
            strlen(s._pszText) + 1,
            s._pszText);
    }


	Str() {
		_pszText = new char[1] {0};
	}

	~Str() { delete[]_pszText; }

    Str& operator =(const Str& s) {
        if (this == &s) 
            return *this;
        delete[] _pszText; 
        _pszText = new char[strlen(s._pszText) + 1];
        strcpy_s(_pszText, strlen(s._pszText) + 1, s._pszText);
        return *this; 
    }

    Str& operator +=(const char* sz) {
        int newLength = strlen(_pszText) + strlen(sz);
        char* newStr = new char[newLength + 1];
        strcpy_s(newStr, strlen(_pszText) + 1, _pszText);
        strcat_s(newStr, newLength + 1, sz);
        delete[] _pszText;
        _pszText = newStr;
        return *this;
    }

    Str operator +(const char* sz) const {
        int newLength = strlen(_pszText) + strlen(sz);
        char* newStr = new char[newLength + 1];
        strcpy_s(newStr, strlen(_pszText) + 1, _pszText);
        strcat_s(newStr, newLength + 1, sz);
        return newStr;
    }

    operator const char* ()const { return _pszText; }
};
