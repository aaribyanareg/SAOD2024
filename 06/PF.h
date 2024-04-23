#pragma once
#ifdef PF_EXPORT
#  define EXPORT __declspec(dllexport)
#else
#  define EXPORT __declspec(dllimport)
#endif

class EXPORT PF {
    char* t = nullptr;  // ����� ��� �������
    int size = 0;       // ������ �������
public:
    int* p = nullptr;   // ����� �������-�������
    PF() {}
    PF(const PF&) = delete; // ��������� �����������

    ~PF();

    /// <summary>
    /// ��������� �������-������� �� ������� s
    /// </summary>
    /// <param name="s">����� �������</param>
    /// <param name="sz">������ �������</param>
    void Init(const char s[], int sz);

    /// <summary>
    /// ���������� �������� ����� i �������
    /// </summary>
    /// <param name="i">����� ������� �������</param>
    /// <returns>���������� ������ ������� ��� �����������</returns>
    char pattern(int i) { return t[i]; }

    /// <summary>
    /// ���������� �������� i-���� �������� �������-������� �� �������.
    /// </summary>
    int operator [] (int i) { return p[i]; }
    operator int() { return size; }
    
    PF& operator = (const PF&) = delete;    // ��������� ������������
};


