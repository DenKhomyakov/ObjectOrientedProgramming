/*
Класс "Булев вектор"

При реализации данного класса следует обратить особое внимание на два момента:
1. Размер некоторых типов данных (например, int) может меняться в зависимости от архитектуры компьютера. Таким образом, желательно использовать типы данных, имеющие одинаковый размер (например, char). Кроме того, следует учесть то, что в знаковых типах один из разрядов используется для хранения знака.
2. Поскольку минимальная единица выделения памяти будет ограничена размером того типа, который вы будете использовать, часть разрядов будут "лишними" или незначащими. То, где именно в векторе они будут расположены, будете ли вы их заполнять определённым образом или нет, значения не имеет. Главное - чтобы они не приводили к ошибкам, особенно при осуществлении битовых операций.

Необходимые методы класса:
- конструкторы (по умолчанию, с параметрами (размер и значение - одно и то же для всех разрядов), конструктор из массива const char *, конструктор копирования);
- деструктор;
- ввод/вывод в консоль (потоковый);
- инверсия всех компонент вектора;
- инверсия i-ой компоненты;
- установка в 0/1 i-ой компоненты.

Необходимые перегрузки:
- получение компоненты ([ ], см. примечание ниже);
- побитовое умножение (&, &=);
- побитовое сложение (|, |=);
- побитовые сдвиги (<<, >>, <<=, >>=);
- побитовое исключающее ИЛИ (^, ^=).

Примечание: получение компоненты подразумевается только на чтение (т.е., возвращается значение бита в виде int/char/bool, а записать значение в бит нельзя - для этого можно использовать соответствующую функцию).
*/

#include <iostream>
#include <cmath>
#include <cstring>
#include <locale>
#include <time.h>

using namespace std;

typedef unsigned char UC;

/* Обработка исключений */
enum Errors_and_Exceprions
{
    errorLenghtLessZero = 1,
    errorRangeIndexOutBooleanVector,
    errorShiftLenghtLessZero,
};

/* Класс "Булев вектор" */
class BooleanVector
{
private:
    UC* m_BV;                   // БВ
    int m_Lenght_BV;            // Длина БВ
    int m_Memory_BV;            // Количество выделенной памяти

public:
    BooleanVector();                                                // Конструктор по умолчанию
    BooleanVector(int lenght_BV, int fillingMethod = 0);            // Конструктор с параметрами размера и значения для всех разрядов
    BooleanVector(const char* string_BV, int lenght_BV);            // Конструктор char* со строкой и числом
    BooleanVector(const BooleanVector&);                            // Конструктор копирования

    ~BooleanVector();                                               // Деструктор

    void setOne(int necessaryBit, int lenght_BV = 1);               // Установить 1 в определённом бите
    void setZero(int necessaryBit, int lenght_BV = 1);              // Установить 0 в определённом бите
    void inverseComponent(int necessaryBit, int lenght_BV = 1);     // Инверсия определённого бита

    int operator[](int);                                            // Получение компоненты

    BooleanVector& operator<<=(int);                                // Побитовый сдвиг влево (с присвоением)
    BooleanVector operator<<(int);                                  // Побитовый сдвиг влево
    BooleanVector& operator>>=(int);                                // Побитовый сдвиг вправо (с присвоением)
    BooleanVector operator>>(int);                                  // Побитовый сдвиг вправо 

    BooleanVector operator| (BooleanVector&);                       // Побитовое ИЛИ
    BooleanVector& operator|= (BooleanVector&);                     // побитовое ИЛИ (с присвоением) 
    BooleanVector operator& (BooleanVector&);                       // Побитовое И
    BooleanVector& operator&= (BooleanVector&);                     // Побитовое И (с присвоением) 
    BooleanVector operator ^(BooleanVector&);                       // Побитовове исключающее ИЛИ
    BooleanVector& operator ^=(BooleanVector&);                     // Побитовове исключающее ИЛИ (с присвоением)

    BooleanVector& operator~ ();                                    // Побитовое НЕ

    friend ostream& operator << (ostream&, BooleanVector&);         // Потоковый ввод
    friend istream& operator >> (istream&, BooleanVector&);         // Потоковый ввывод
};

inline BooleanVector::BooleanVector()
{
    m_Lenght_BV = 0;
    m_Memory_BV = 1;
    m_BV = new UC[m_Memory_BV];
}

BooleanVector::BooleanVector(int lenght_BV, int fillingMethod)
{
    if (lenght_BV <= 0)
    {
        throw errorLenghtLessZero;
    }

    m_Lenght_BV = lenght_BV;
    m_Memory_BV = (m_Lenght_BV + 7) / 8;
    m_BV = new UC[m_Memory_BV];

    if (fillingMethod == 0)
    {
        for (int i = 0; i < m_Memory_BV; i++)
        {
            m_BV[i] = 0;
        }
    }

    else if (fillingMethod == 1)
    {
        for (int i = 0; i < m_Memory_BV - 1; i++)
        {
            m_BV[i + 1] = pow(2, 8) - 1;
        }

        if (m_Lenght_BV % 8 == 0)
        {
            m_BV[0] = pow(2, 8) - 1;
        }

        else
        {
            m_BV[0] = 0;
            m_BV[0] = ~m_BV[0];
            m_BV[0] = m_BV[0] >> (8 - m_Lenght_BV % 8);
        }
    }

    else
    {
        m_BV[0] = 0;

        for (int i = 0; i < m_Lenght_BV; i++)
        {
            if ((rand() % 2) == 1)
            {
                setOne(i);
            }

            else
            {
                setZero(i);
            }
        }
    }
}

BooleanVector::BooleanVector(const char* string_BV, int lenght_BV)
{
    int i;
    int nextString = strlen(string_BV);

    m_Lenght_BV = lenght_BV;
    m_Memory_BV = (m_Lenght_BV + 7) / 8;
    m_BV = new UC[m_Memory_BV];

    for (i = 0; i < m_Memory_BV; i++)
    {
        m_BV[i] = 0;
    }

    if (nextString >= m_Lenght_BV)
    {
        i = m_Lenght_BV - 1;
    }

    else
    {
        i = nextString - 1;
    }

    for (int k = 0; i >= 0; i--, k++)
    {
        if (string_BV[i] == '1')
        {
            setOne(k);
        }
    }
}

BooleanVector::BooleanVector(const BooleanVector& bv)
{
    m_Lenght_BV = bv.m_Lenght_BV;
    m_Memory_BV = bv.m_Memory_BV;
    m_BV = new UC[m_Memory_BV];

    for (int i = 0; i < m_Memory_BV; i++)
    {
        m_BV[i] = bv.m_BV[i];
    }
}

inline BooleanVector::~BooleanVector()
{
    delete[] m_BV;
    m_BV = NULL;
}

inline void BooleanVector::setOne(int necessaryBit, int lenght_BV)
{
    for (; lenght_BV > 0; necessaryBit++, lenght_BV--)
    {
        if (lenght_BV >= m_Lenght_BV || lenght_BV < 0)
        {
            throw errorRangeIndexOutBooleanVector;
        }

        int indexBit;
        int positionBit;
        UC mask = 1;
        indexBit = m_Memory_BV - necessaryBit / 8 - 1;
        positionBit = necessaryBit % 8;
        m_BV[indexBit] |= (mask << positionBit);
    }
}

inline void BooleanVector::setZero(int necessaryBit, int lenght_BV)
{
    for (; lenght_BV > 0; necessaryBit++, lenght_BV--)
    {
        if (necessaryBit >= m_Lenght_BV || necessaryBit < 0)
        {
            throw errorRangeIndexOutBooleanVector;
        }

        int indexBit;
        int positionBit;
        UC mask = 1;
        indexBit = m_Memory_BV - necessaryBit / 8 - 1;
        positionBit = necessaryBit % 8;
        m_BV[indexBit] &= ~(mask << positionBit);
    }
}

inline void BooleanVector::inverseComponent(int necessaryBit, int lenght_BV)
{
    for (; lenght_BV > 0; necessaryBit++, lenght_BV--)
    {
        if (necessaryBit < 0 || necessaryBit >= m_Lenght_BV)
        {
            throw errorRangeIndexOutBooleanVector;
        }

        if (operator[](necessaryBit) == 0)
        {
            setOne(necessaryBit);
        }

        else
        {
            setZero(necessaryBit);
        }
    }
}

inline int BooleanVector::operator[] (int necessaryBit)
{
    if (necessaryBit >= m_Lenght_BV || necessaryBit < 0)
    {
        throw errorRangeIndexOutBooleanVector;
    }

    int indexBit;
    int positionBit;
    UC mask = 1;
    indexBit = m_Memory_BV - necessaryBit / 8 - 1;
    positionBit = necessaryBit % 8;

    if (m_BV[indexBit] & (mask << positionBit))
    {
        return 1;
    }

    return 0;
}

BooleanVector& BooleanVector:: operator<<=(int shiftBit)
{
    if (shiftBit < 0)
    {
        throw errorShiftLenghtLessZero;
    }

    int i;
    int k;
    for (i = m_Lenght_BV - 1 - shiftBit, k = m_Lenght_BV - 1; i >= 0; i--, k--)
    {
        if (operator[](i) == 1)
        {
            setOne(k);
        }

        else
        {
            setZero(k);
        }
    }

    for (k; k >= 0; k--)
    {
        setZero(k);
    }

    return *this;
}

BooleanVector BooleanVector:: operator<< (int shiftBit)
{
    BooleanVector result(*this);
    result <<= shiftBit;

    return result;
}

BooleanVector& BooleanVector:: operator>>=(int shiftBit)
{
    if (shiftBit < 0)
    {
        throw errorShiftLenghtLessZero;
    }

    int i;
    int k;
    for (i = shiftBit, k = 0; i < m_Lenght_BV; i++, k++)
    {
        if (operator[](i) == 1)
        {
            setOne(k);
        }

        else
        {
            setZero(k);
        }
    }

    for (k; k < m_Lenght_BV; k++)
    {
        setZero(k);
    }

    return *this;
}

BooleanVector BooleanVector:: operator>> (int shiftBit)
{
    BooleanVector result(*this);
    result >>= shiftBit;

    return result;
}

BooleanVector BooleanVector:: operator | (BooleanVector& lenght_BV)
{
    BooleanVector* min;
    BooleanVector* max;

    int i;
    int k;

    if (m_Lenght_BV > lenght_BV.m_Lenght_BV)
    {
        min = &lenght_BV;
        max = this;
    }

    else
    {
        min = this;
        max = &lenght_BV;
    }

    BooleanVector result(*max);

    for (i = min->m_Memory_BV - 1, k = result.m_Memory_BV - 1; i >= 0; i--, k--)
    {
        result.m_BV[k] |= min->m_BV[i];
    }

    return result;
}

inline BooleanVector& BooleanVector::operator |= (BooleanVector& lenght_BV)
{
    (*this) = ((*this) | lenght_BV);

    return *this;
}

BooleanVector BooleanVector:: operator & (BooleanVector& lenght_BV)
{
    BooleanVector* min;
    BooleanVector* max;

    int i;
    int k;

    if (m_Lenght_BV > lenght_BV.m_Lenght_BV)
    {
        min = &lenght_BV;
        max = this;
    }

    else
    {
        min = this;
        max = &lenght_BV;
    }

    BooleanVector result(*max);

    for (i = min->m_Memory_BV - 1, k = result.m_Memory_BV - 1; i >= 0; i--, k--)
    {
        result.m_BV[k] &= min->m_BV[i];
    }

    for (i = 0; i < max->m_Memory_BV - min->m_Memory_BV; i++)
    {
        result.m_BV[i] = 0;
    }

    return result;
}

inline BooleanVector& BooleanVector::operator &= (BooleanVector& lenght_BV)
{
    (*this) = ((*this) & lenght_BV);

    return *this;
}

BooleanVector& BooleanVector::operator ~()
{
    int nmem = (m_Lenght_BV + 7) / 8;

    for (int i = m_Memory_BV - 1; i >= m_Memory_BV - nmem; i--)
    {
        m_BV[i] = ~m_BV[i];
    }

    UC mask = (~0) << ((m_Lenght_BV - 1) % 8 + 1);
    m_BV[m_Memory_BV - nmem] = m_BV[m_Memory_BV - nmem] & (~mask);

    return *this;
}

BooleanVector BooleanVector:: operator ^ (BooleanVector& lenght_BV)
{
    if (m_Memory_BV > lenght_BV.m_Memory_BV)
    {
        BooleanVector result(*this);

        for (int i = 0; i < lenght_BV.m_Memory_BV; i++)
        {
            result.m_BV[i + m_Memory_BV - lenght_BV.m_Memory_BV] ^= lenght_BV.m_BV[i];
        }

        return result;
    }

    else
    {
        BooleanVector result(lenght_BV);

        for (int i = 0; i < m_Memory_BV; i++)
        {
            result.m_BV[i + lenght_BV.m_Memory_BV - m_Memory_BV] ^= m_BV[i];
        }

        return result;
    }
}

inline BooleanVector& BooleanVector::operator ^= (BooleanVector& lenght_BV)
{
    (*this) = ((*this) ^ lenght_BV);

    return *this;
}

ostream& operator << (ostream& os, BooleanVector& lenght_BV)
{
    for (int i = lenght_BV.m_Lenght_BV - 1; i >= 0; i--)
    {
        if ((lenght_BV[i]) == 1)
        {
            os << " 1";
        }

        else
        {
            os << " 0";
        }
    }

    return os;
}

istream& operator >> (istream& is, BooleanVector& lenght_BV)
{
    cout << "Длина вектора: ";
    is >> lenght_BV.m_Lenght_BV;

    if (lenght_BV.m_Lenght_BV <= 0)
    {
        throw errorLenghtLessZero;
    }

    cout << "Введите элементы вектора (без пробелов): ";
    char* s = new char[lenght_BV.m_Lenght_BV];
    lenght_BV.m_Memory_BV = (lenght_BV.m_Lenght_BV + 7) / 8;
    lenght_BV.m_BV = new UC[lenght_BV.m_Memory_BV];

    char c;
    for (int i = lenght_BV.m_Lenght_BV - 1; i >= 0; i--)
    {
        is >> c;

        if (c == '0')
        {
            lenght_BV.setZero(i);
        }

        else
        {
            lenght_BV.setOne(i);
        }
    }

    return is;
}

int main()
{
    try
    {
        setlocale(LC_ALL, "Rus");
        srand(unsigned(time(NULL)));

        BooleanVector lab_BV_1;

        cout << "Способы заполнения булевого вектора:\n";
        cout << "1. Случайными числами\n";
        cout << "2. Потоковый ввод\n";

        cout << endl;
        int selectFill;
        cout << "Выберите способ заполнения: ";
        cin >> selectFill;

        switch (selectFill)
        {
        case 1:
        {
            int lab_Lenght_BV;
            cout << "Длина вектора: ";
            cin >> lab_Lenght_BV;

            int fillingMethod;
            cout << "Введите 0, чтобы заполнить нулями, 1 - единицами, любое другое число - случайным образом: ";
            cin >> fillingMethod;

            BooleanVector tmp(lab_Lenght_BV, fillingMethod);
            lab_BV_1 = tmp;
            cout << "\nБулев вектор:\n" << lab_BV_1;

            break;
        }
        case 2:
        {
            cin >> lab_BV_1;
            cout << "\nБулев вектор:\n" << lab_BV_1;

            break;
        }
        default: exit(0);
        }

        cout << endl;

        cout << "\nДоступные функции:\n";
        cout << "3. Установка 1 в заданный разряд\n";
        cout << "4. Установка 0 в заданный разряд\n";
        cout << "5. Инверсия заданного разряда\n";
        cout << "6. Значение выбранного разряда\n";
        cout << "7. Побитовый сдвиг влево\n";
        cout << "8. Побитовый сдвиг вправо\n";
        cout << "9. Дизъюнкция векторов\n";
        cout << "10. Конъюкция векторов\n";
        cout << "11. Исключающее ИЛИ векторов\n";
        cout << "12. Инверсия вектора\n";
        cout << "0. Закрыть программу\n";

        int selectFunction = -1;
        while (selectFunction != 0)
        {
            cout << "\nВыберите функцию: ";
            cin >> selectFunction;
            switch (selectFunction)
            {
            case 3:
            {
                int necessaryBit;
                cout << "Разряд, подлежащий изменению: ";
                cin >> necessaryBit;

                int quanityBit;
                cout << "Количество разрядов для изменения (справа налево): ";
                cin >> quanityBit;

                lab_BV_1.setOne(necessaryBit, quanityBit);
                cout << lab_BV_1;

                cout << endl;
                break;
            }
            case 4:
            {
                int necessaryBit;
                cout << "Разряд, подлежащий изменению: ";
                cin >> necessaryBit;

                int quanityBit;
                cout << "Количество разрядов для изменения (справа налево): ";
                cin >> quanityBit;

                lab_BV_1.setZero(necessaryBit, quanityBit);
                cout << lab_BV_1;

                cout << endl;
                break;
            }
            case 5:
            {
                int necessaryBit;
                cout << "Разряд, подлежащий изменению: ";
                cin >> necessaryBit;

                int quanityBit;
                cout << "Количество разрядов для изменения (справа налево): ";

                cin >> quanityBit;
                lab_BV_1.inverseComponent(necessaryBit, quanityBit);
                cout << lab_BV_1;

                cout << endl;
                break;
            }
            case 6:
            {
                int necessaryBit;
                cout << "Разряд, подлежащий изменению: ";
                cin >> necessaryBit;

                cout << lab_BV_1[necessaryBit];

                cout << endl;
                break;
            }
            case 7:
            {
                int quanityBit;
                cout << "Количество разрядов для сдвига: ";
                cin >> quanityBit;

                lab_BV_1 <<= quanityBit;
                cout << lab_BV_1;

                cout << endl;
                break;
            }
            case 8:
            {
                int quanityBit;
                cout << "Количество разрядов для сдвига: ";
                cin >> quanityBit;

                lab_BV_1 >>= quanityBit;
                cout << lab_BV_1;

                cout << endl;
                break;
            }
            case 9:
            {
                BooleanVector lab_BV_2;
                cout << "Задайте параметры второго вектора:\n";
                cin >> lab_BV_2;

                cout << "Первый вектор:\n" << lab_BV_1 << endl;
                cout << "Второй вектор:\n" << lab_BV_2 << endl;

                lab_BV_1 |= lab_BV_2;
                cout << "Результирующий вектор:\n" << lab_BV_1;

                cout << endl;
                break;
            }
            case 10:
            {
                BooleanVector lab_BV_2;
                cout << "Задайте параметры второго вектора:\n";
                cin >> lab_BV_2;

                cout << "Первый вектор:\n" << lab_BV_1 << endl;
                cout << "Второй вектор:\n" << lab_BV_2 << endl;

                lab_BV_1 &= lab_BV_2;
                cout << "Результирующий вектор:\n" << lab_BV_1;

                cout << endl;
                break;
            }
            case 11:
            {
                BooleanVector lab_BV_2;
                cout << "Задайте параметры второго вектора:\n";
                cin >> lab_BV_2;

                cout << "Первый вектор:\n" << lab_BV_1 << endl;
                cout << "Второй вектор:\n" << lab_BV_2 << endl;

                lab_BV_1 ^= lab_BV_2;
                cout << "Результирующий вектор:\n" << lab_BV_1;

                cout << endl;
                break;
            }
            case 12:
            {
                cout << ~lab_BV_1;

                cout << endl;
                break;
            }
            default: exit(0);
            }
        }
    }
    catch (Errors_and_Exceprions SomethingWentWrong)
    {
        return SomethingWentWrong;
    }

    cout << endl;
    system("pause");
}