/*
Требуется реализовать класс обыкновенной дроби, состоящей из целочисленных числителя и знаменателя

Необходимые методы класса:
- конструктор (один по умолчанию и как минимум один конструктор с параметрами);
- установление/получение числителя/знаменателя дроби;
- арифметические операции между дробями (+, -, *, /). Могут быть реализованы в виде перегрузок или обычных методов;
- операции сравнения (>, <, ==, !=). Могут быть реализованы в виде перегрузок или обычных методов;
- приведение дроби к несократимой;
- ввод/вывод дроби в консоль;
- как минимум два уникальных собственных метода на ваше усмотрение.
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

/* Конструктор */
Fraction::Fraction()
{
    numerator = 1;
    denominator = 1;
}

/* Констурктор с параметром */
Fraction::Fraction(int numer, int denom)
{
    if (denom != 0)
    {
        numerator = numer;
        denominator = denom;
    }

    else
    {
        throw "Знаменатель не может быть равен 0!";
    }
}

/* Деструктор */
Fraction::~Fraction()
{
}

/* Установление числителя */
void Fraction::setNumerator(int numer)
{
    numerator = numer;
}

/* Получение числителя*/
int Fraction::getNumerator()
{
    return numerator;
}

/* Установление знаменателя */
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
        cout << "Знаменатель не может быть равен 0!" << endl;
    }
}

/* Получение знаменателя */
int Fraction::getDenominator()
{
    return denominator;
}

/* Арифметическая операция сложения (+) */
Fraction Fraction::operator+(Fraction tmp)
{
    Fraction lab_Fraction(numerator * tmp.denominator + denominator * tmp.numerator, denominator * tmp.denominator);
    lab_Fraction.reduce();
    return lab_Fraction;
}

/* Арифметическая операция вычитания (-) */
Fraction Fraction::operator-(Fraction tmp)
{
    Fraction lab_Fraction(numerator * tmp.denominator - denominator * tmp.numerator, denominator * tmp.denominator);
    lab_Fraction.reduce();
    return lab_Fraction;
}

/* Арифметическая операция умножения (*) */
Fraction Fraction::operator*(Fraction tmp)
{
    Fraction lab_Fraction(numerator * tmp.numerator, denominator * tmp.denominator);
    lab_Fraction.reduce();
    return lab_Fraction;
}

/* Арифметическая операция деления (/) */
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
        throw "Деление на 0!";
    }
}

/* Операция сравнения (больше, >) */
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

/* Операция сравнения (меньше, <) */
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

/* Операция сравнения (равно, ==) */
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

/* Операция сравнения (не равно, !=) */
bool Fraction::operator!=(Fraction tmp)
{
    return !operator==(tmp);
}

/* Приведение дроби к несократимой */
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

/* Ввод дроби на консоль */
std::istream& operator>>(std::istream& in, Fraction& tmp)
{
    in >> tmp.numerator >> tmp.denominator;
    return in;
}

/* Вывод дроби на консоль*/
std::ostream& operator<<(std::ostream& out, Fraction tmp)
{
    out << tmp.numerator << '/' << tmp.denominator;
    return out;
}

/* Обратная дробь */
void Fraction::revert()
{
    if (numerator != 0)
    {
        int tmp = numerator;
        numerator = denominator;
        denominator = tmp;
    }
}

/* Проверка вида дроби - правильная/неправильная */
bool Fraction::isProper()
{
    if (numerator < denominator)
    {
        cout << "Дробь правильная!" << endl;
        return true;
    }

    else
    {
        cout << "Дробь неправильная!" << endl;
        return true;
    }
}

int main()
{
    setlocale(LC_ALL, "Rus");

    try
    {
        /* Первая дробь */
        cout << "(Дробь)" << endl;

        cout << "Введите числитель: ";
        int lab_Numerator_1;
        cin >> lab_Numerator_1;

        cout << "Введите знаменатель: ";
        int lab_Denominator_1;
        cin >> lab_Denominator_1;

        cout << "Ваша дробь: ";
        Fraction lab_Fraction_1(lab_Numerator_1, lab_Denominator_1);
        cout << lab_Fraction_1 << endl << endl;

        /* Вторая дробь */
        cout << "(Правильная/неправильная)" << endl;

        cout << "Введите числитель: ";
        int lab_Numerator_2;
        cin >> lab_Numerator_2;

        cout << "Введите знаменатель: ";
        int lab_Denominator_2;
        cin >> lab_Denominator_2;

        cout << "Ваша дробь: ";
        Fraction lab_Fraction_2(lab_Numerator_2, lab_Denominator_2);
        cout << lab_Fraction_2 << endl;
        lab_Fraction_2.isProper();
    }
    catch (const char* message)
    {
        cout << message << endl;
    }

    /* Завершение работы программы */
    cout << endl;
    system("pause");
}