/*
��������� ����������� ����� ������������ �����, ��������� �� ������������� ��������� � �����������

����������� ������ ������:
- ����������� (���� �� ��������� � ��� ������� ���� ����������� � �����������);
- ������������/��������� ���������/����������� �����;
- �������������� �������� ����� ������� (+, -, *, /). ����� ���� ����������� � ���� ���������� ��� ������� �������;
- �������� ��������� (>, <, ==, !=). ����� ���� ����������� � ���� ���������� ��� ������� �������;
- ���������� ����� � ������������;
- ����/����� ����� � �������;
- ��� ������� ��� ���������� ����������� ������ �� ���� ����������.
*/

#include <iostream>
#include <math.h>

using std::cout;
using std::cin;
using std::endl;

class Fraction
{
private:
    int numerator;
    int denominator;

public:
    Fraction();
    Fraction(int numer, int denom);
    ~Fraction();

    void setNumerator(int numer);
    int getNumerator();
    void setDenominator(int denom);
    int getDenominator();

    Fraction operator+(Fraction tmp);
    Fraction operator-(Fraction tmp);
    Fraction operator*(Fraction tmp);
    Fraction operator/(Fraction tmp);

    bool operator>(Fraction tmp);
    bool operator<(Fraction tmp);
    bool operator==(Fraction tmp);
    bool operator!=(Fraction tmp);

    void reduce();

    friend std::istream& operator>>(std::istream& in, Fraction& tmp);
    friend std::ostream& operator<<(std::ostream& out, Fraction tmp);

    void revert();
    bool isProper();
};

/* ����������� */
Fraction::Fraction()
{
    numerator = 1;
    denominator = 1;
}

/* ����������� � ���������� */
Fraction::Fraction(int numer, int denom)
{
    if (denom != 0)
    {
        numerator = numer;
        denominator = denom;
    }

    else
    {
        throw "����������� �� ����� ���� ����� 0!";
    }
}

/* ���������� */
Fraction::~Fraction()
{
}

/* ������������ ��������� */
void Fraction::setNumerator(int numer)
{
    numerator = numer;
}

/* ��������� ���������*/
int Fraction::getNumerator()
{
    return numerator;
}

/* ������������ ����������� */
void Fraction::setDenominator(int denom)
{
    try
    {
        if (denom != 0)
        {
            denominator = denom;
        }
    }
    catch (const std::exception& ex)
    {
        cout << "����������� �� ����� ���� ����� 0!" << endl;
    }
}

/* ��������� ����������� */
int Fraction::getDenominator()
{
    return denominator;
}

/* �������������� �������� �������� (+) */
Fraction Fraction::operator+(Fraction tmp)
{
    Fraction lab_Fraction(numerator * tmp.denominator + denominator * tmp.numerator, denominator * tmp.denominator);
    lab_Fraction.reduce();
    return lab_Fraction;
}

/* �������������� �������� ��������� (-) */
Fraction Fraction::operator-(Fraction tmp)
{
    Fraction lab_Fraction(numerator * tmp.denominator - denominator * tmp.numerator, denominator * tmp.denominator);
    lab_Fraction.reduce();
    return lab_Fraction;
}

/* �������������� �������� ��������� (*) */
Fraction Fraction::operator*(Fraction tmp)
{
    Fraction lab_Fraction(numerator * tmp.numerator, denominator * tmp.denominator);
    lab_Fraction.reduce();
    return lab_Fraction;
}

/* �������������� �������� ������� (/) */
Fraction Fraction::operator/(Fraction tmp)
{
    if (tmp.numerator != 0)
    {
        Fraction lab_Fraction(numerator * tmp.denominator, denominator * tmp.numerator);
        lab_Fraction.reduce();
        return lab_Fraction;
    }

    else
    {
        throw "������� �� 0!";
    }
}

/* �������� ��������� (������, >) */
bool Fraction::operator>(Fraction tmp)
{
    if (numerator * tmp.denominator > tmp.numerator * denominator)
    {
        return true;
    }

    else
    {
        return false;
    }
}

/* �������� ��������� (������, <) */
bool Fraction::operator<(Fraction tmp)
{
    if (numerator * tmp.denominator < tmp.numerator * denominator)
    {
        return true;
    }

    else
    {
        return false;
    }
}

/* �������� ��������� (�����, ==) */
bool Fraction::operator==(Fraction tmp)
{
    if (numerator * tmp.denominator == tmp.numerator * denominator)
    {
        return true;

    }

    else
    {
        return false;
    }
}

/* �������� ��������� (�� �����, !=) */
bool Fraction::operator!=(Fraction tmp)
{
    return !operator==(tmp);
}

/* ���������� ����� � ������������ */
void Fraction::reduce()
{
    int i = 2;

    while ((denominator / i) != 0 && (numerator / i) != 0)
    {
        if ((denominator % i) == 0 && (numerator % i) == 0)
        {
            denominator /= i;
            numerator /= i;
        }

        else
        {
            i++;
        }
    }
}

/* ���� ����� �� ������� */
std::istream& operator>>(std::istream& in, Fraction& tmp)
{
    in >> tmp.numerator >> tmp.denominator;
    return in;
}

/* ����� ����� �� �������*/
std::ostream& operator<<(std::ostream& out, Fraction tmp)
{
    out << tmp.numerator << '/' << tmp.denominator;
    return out;
}

/* �������� ����� */
void Fraction::revert()
{
    if (numerator != 0)
    {
        int tmp = numerator;
        numerator = denominator;
        denominator = tmp;
    }
}

/* �������� ���� ����� - ����������/������������ */
bool Fraction::isProper()
{
    if (numerator < denominator)
    {
        cout << "����� ����������!" << endl;
        return true;
    }

    else
    {
        cout << "����� ������������!" << endl;
        return true;
    }
}

int main()
{
    setlocale(LC_ALL, "Rus");

    try
    {
        /* ������ ����� */
        cout << "(�����)" << endl;

        cout << "������� ���������: ";
        int lab_Numerator_1;
        cin >> lab_Numerator_1;

        cout << "������� �����������: ";
        int lab_Denominator_1;
        cin >> lab_Denominator_1;

        cout << "���� �����: ";
        Fraction lab_Fraction_1(lab_Numerator_1, lab_Denominator_1);
        cout << lab_Fraction_1 << endl << endl;

        /* ������ ����� */
        cout << "(����������/������������)" << endl;

        cout << "������� ���������: ";
        int lab_Numerator_2;
        cin >> lab_Numerator_2;

        cout << "������� �����������: ";
        int lab_Denominator_2;
        cin >> lab_Denominator_2;

        cout << "���� �����: ";
        Fraction lab_Fraction_2(lab_Numerator_2, lab_Denominator_2);
        cout << lab_Fraction_2 << endl;
        lab_Fraction_2.isProper();
    }
    catch (const char* message)
    {
        cout << message << endl;
    }

    /* ���������� ������ ��������� */
    cout << endl;
    system("pause");
}