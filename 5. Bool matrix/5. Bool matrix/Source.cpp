/*
Класс "Булева матрица"

В данной лабораторной требуется реализовать булеву матрицу с помощью агрегации разработанного ранее булевого вектора.

Необходимые методы класса:
- конструкторы (по умолчанию, с параметрами (количество строк/столбцов и значения разрядов), конструктор из матрицы char, конструктор копирования);
- деструктор;
- ввод/вывод в консоль;
- вес матрицы (количество единичных компонент);
- конъюнкция всех строк (возвращает булев вектор).

Необходимые перегрузки:
- присваивание (=);
- получение строки ([ ]);
- построчное побитовое умножение (&);
- построчное побитовое сложение (|).
*/

#include <iostream>
#include <cmath>
#include <cstring>
#include <time.h>
#include <locale>

using namespace std;

typedef unsigned char UC;

/* Обработка исключений */
enum Errors_and_Exceprions
{
    /* Для БВ */
    errorLenghtLessZero = 1,
    errorRangeIndexOutBooleanVector,
    errorShiftLenghtLessZero,
    errorWrongSymbol,

    /* Для БМ */
    errorRowOrColumn,
    errorArraySringsNotPassed,
    errorStringAdressIsMissing,
    errorRangeIndexOutBooleanMatrix,
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

    int operator[](int) const;                                      // Получение компоненты

    BooleanVector& operator<<=(const int);                          // Побитовый сдвиг влево (с присвоением)
    BooleanVector operator<<(const int) const;                      // Побитовый сдвиг влево
    BooleanVector& operator>>=(const int);                          // Побитовый сдвиг вправо (с присвоением)
    BooleanVector operator>>(const int) const;                      // Побитовый сдвиг вправо 

    BooleanVector operator| (const BooleanVector&) const;           // Побитовое ИЛИ
    BooleanVector& operator|= (const BooleanVector&);               // побитовое ИЛИ (с присвоением) 
    BooleanVector operator& (const BooleanVector&) const;           // Побитовое И
    BooleanVector& operator&= (const BooleanVector&);               // Побитовое И (с присвоением) 
    BooleanVector& operator~ ();                                    // Побитовое НЕ
    BooleanVector operator=(const BooleanVector& other);            // Присваивание

    friend ostream& operator << (ostream&, const BooleanVector&);   // Потоковый ввод
    friend istream& operator >> (istream&, BooleanVector&);         // Потоковый ввывод

    int weight();                                                   // Вес вектора
};

inline BooleanVector::BooleanVector()
{
    m_Lenght_BV = 0;
    m_Memory_BV = 1;
    m_BV = new UC[m_Memory_BV];
    m_BV[0] = 0;
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
            m_BV[i + 1] = 255;
        }

        if (m_Lenght_BV % 8 == 0)
        {
            m_BV[0] = 255;
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

inline int BooleanVector::operator[] (int necessaryBit) const
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

BooleanVector& BooleanVector:: operator<<=(const int shiftBit)
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

BooleanVector BooleanVector:: operator<< (const int shiftBit) const
{
    BooleanVector result(*this);
    result <<= shiftBit;

    return result;
}

BooleanVector& BooleanVector:: operator>>=(const int shiftBit)
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

BooleanVector BooleanVector:: operator>> (const int shiftBit) const
{
    BooleanVector result(*this);
    result >>= shiftBit;

    return result;
}

BooleanVector BooleanVector:: operator | (const BooleanVector& lenght_BV) const
{
    const BooleanVector* min;
    const BooleanVector* max;

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

inline BooleanVector& BooleanVector::operator |= (const BooleanVector& lenght_BV)
{
    (*this) = ((*this) | lenght_BV);

    return *this;
}

BooleanVector BooleanVector:: operator & (const BooleanVector& lenght_BV) const
{
    const BooleanVector* min;
    const BooleanVector* max;

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

inline BooleanVector& BooleanVector::operator &= (const BooleanVector& lenght_BV)
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

BooleanVector BooleanVector::operator=(const BooleanVector& other)
{
    if (this == &other)
    {
        return *this;
    }

    if (m_Memory_BV != other.m_Memory_BV)
    {
        delete[] m_BV;
        m_BV = new UC[other.m_Memory_BV];
        m_Memory_BV = other.m_Memory_BV;
    }

    m_Lenght_BV = other.m_Lenght_BV;

    for (int i = 0; i < m_Memory_BV; ++i)
    {
        m_BV[i] = other.m_BV[i];
    }

    return *this;
}

ostream& operator << (ostream& os, const BooleanVector& lenght_BV)
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

int BooleanVector::weight()
{
    int weightBV = 0;

    for (int i = 0; i < m_Lenght_BV; i++)
    {
        if ((int)operator[](i))
        {
            weightBV++;
        }
    }

    return weightBV;
}

/* Класс "Булева матрица" */
class BooleanMatrix
{
private:
    BooleanVector* m_BM;            // БМ
    int m_Row_BM;                   // Строки БМ
    int m_Column_BM;                // Столбцы БМ

public:
    BooleanMatrix();                                                // Конструктор по умолчанию
    BooleanMatrix(int, int, bool);                                  // Конструктор с параметрами
    BooleanMatrix(char**, int, int);                                // Конструктор из матрицы char
    BooleanMatrix(const BooleanMatrix&);                            // Конструктор копирования

    ~BooleanMatrix();                                               // Деструктор

    BooleanMatrix operator = (const BooleanMatrix&);                // Оператор присваивания
    BooleanVector& operator [](const int);                          // Получение строки

    friend istream& operator>>(istream&, BooleanMatrix&);           // Потоковый ввод
    friend ostream& operator<<(ostream&, const BooleanMatrix&);     // Потоковый вывод

    BooleanVector rowConjuction() const;                            // Конъюнкция строк
    BooleanVector rowDisjunction() const;                           // Дизъюнкция строк

    BooleanMatrix operator & (const BooleanMatrix&) const;          // Конъюнкция матрицы
    BooleanMatrix& operator &= (const BooleanMatrix&);              // Конъюнкция матрицы (с присванием) 
    BooleanMatrix operator | (const BooleanMatrix&) const;          // Дизъюнкция матрицы
    BooleanMatrix& operator |= (const BooleanMatrix&);              // дизъюнкция матрицы (с присвоением) 

    int weightBM() const;                                           // Вес БМ
};

BooleanMatrix::BooleanMatrix()
{
    m_Row_BM = 8;
    m_Column_BM = 8;
    m_BM = new BooleanVector[m_Row_BM];

    for (int i = 0; i < m_Row_BM; ++i)
    {
        m_BM[i] = BooleanVector(m_Column_BM, 0);
    }
}

BooleanMatrix::BooleanMatrix(int row, int column, bool value)
{
    if (row <= 0 || column <= 0)
    {
        throw errorRowOrColumn;
    }

    m_Row_BM = row;
    m_Column_BM = column;
    m_BM = new BooleanVector[m_Row_BM];

    for (int i = 0; i < m_Row_BM; ++i)
    {
        m_BM[i] = BooleanVector(m_Column_BM, value);
    }
}

BooleanMatrix::BooleanMatrix(char** string_BM, int row, int column)
{
    if (!string_BM)
    {
        throw errorArraySringsNotPassed;
    }

    if (row <= 0 || column <= 0)
    {
        throw errorRowOrColumn;
    }

    m_Row_BM = row;
    m_Column_BM = column;
    m_BM = new BooleanVector[m_Row_BM];

    for (int i = 0; i < m_Row_BM; i++)
    {
        if (!(string_BM[i]))
        {
            throw errorStringAdressIsMissing;
        }

        BooleanVector bm(string_BM[i], m_Column_BM);
        m_BM[i] = bm;
    }
}

BooleanMatrix::BooleanMatrix(const BooleanMatrix& other)
{
    m_Row_BM = other.m_Row_BM;
    m_Column_BM = other.m_Column_BM;
    m_BM = new BooleanVector[m_Row_BM];

    for (int i = 0; i < m_Row_BM; i++)
    {
        m_BM[i] = other.m_BM[i];
    }
}

BooleanMatrix::~BooleanMatrix()
{
    delete[] m_BM;
}

BooleanMatrix BooleanMatrix:: operator = (const BooleanMatrix& other)
{
    if (this != &other)
    {
        if (m_BM)
        {
            delete[] m_BM;
        }

        m_Row_BM = other.m_Row_BM;
        m_Column_BM = other.m_Column_BM;
        m_BM = new BooleanVector[m_Row_BM];

        for (int i = 0; i < m_Row_BM; i++)
        {
            m_BM[i] = other.m_BM[i];
        }
    }

    return (*this);
}

BooleanVector& BooleanMatrix:: operator [](const int indexBit)
{
    if (indexBit < 0 || indexBit >= m_Row_BM)
    {
        throw errorRangeIndexOutBooleanMatrix;
    }

    return m_BM[indexBit];
}

istream& operator>>(istream& is, BooleanMatrix& bm)
{
    cout << "Количество строк: ";
    is >> bm.m_Row_BM;

    cout << "Количество столбцов: ";
    is >> bm.m_Column_BM;

    delete[] bm.m_BM;
    bm.m_BM = new BooleanVector[bm.m_Row_BM];
    cout << "Вводите матрицу:\n";

    for (int i = 0; i < bm.m_Row_BM; i++)
    {
        is >> bm.m_BM[i];
    }

    return is;
}

ostream& operator<<(ostream& os, const BooleanMatrix& bm)
{
    for (int i = 0; i < bm.m_Row_BM; i++)
    {
        os << bm.m_BM[i] << endl;
    }

    return os;
}

BooleanVector BooleanMatrix::rowConjuction() const
{
    BooleanVector result(m_Column_BM, 1);

    for (int i = 0; i < m_Row_BM; i++)
    {
        result &= m_BM[i];
    }

    return result;
}

BooleanVector BooleanMatrix::rowDisjunction() const
{
    BooleanVector result(m_Column_BM, 0);

    for (int i = 0; i < m_Row_BM; i++)
    {
        result |= m_BM[i];
    }

    return result;
}

BooleanMatrix BooleanMatrix:: operator & (const BooleanMatrix& other) const
{
    const BooleanMatrix* min;
    const BooleanMatrix* max;

    int maxColumn;

    if (m_Column_BM > other.m_Column_BM)
    {
        maxColumn = m_Column_BM;
    }

    else
    {
        maxColumn = other.m_Column_BM;
    }

    int i;
    int k;

    if (m_Row_BM > other.m_Row_BM)
    {
        min = &other;
        max = this;
    }

    else
    {
        min = this;
        max = &other;
    }

    BooleanMatrix result(*max);
    BooleanVector saveMax(maxColumn);

    for (i = 0; i < min->m_Row_BM; i++)
    {
        result.m_BM[i] &= min->m_BM[i];
    }

    for (i = min->m_Row_BM; i < max->m_Row_BM; i++)
    {
        result.m_BM[i] = saveMax;
    }

    return result;
}

inline BooleanMatrix& BooleanMatrix:: operator &= (const BooleanMatrix& other)
{
    (*this) = (*this) & other;

    return *this;
}

BooleanMatrix BooleanMatrix:: operator | (const BooleanMatrix& other) const
{
    const BooleanMatrix* min;
    const BooleanMatrix* max;

    int maxColumn;

    if (m_Column_BM > other.m_Column_BM)
    {
        maxColumn = m_Column_BM;
    }

    else
    {
        maxColumn = other.m_Column_BM;
    }

    int i;
    int k;

    if (m_Row_BM > other.m_Row_BM)
    {
        min = &other;
        max = this;
    }

    else
    {
        min = this;
        max = &other;
    }

    BooleanMatrix result(*max);
    BooleanVector saveMax(maxColumn);

    for (i = 0; i < min->m_Row_BM; i++)
    {
        result.m_BM[i] |= min->m_BM[i];
    }

    for (i = min->m_Row_BM; i < max->m_Row_BM; i++)
    {
        result.m_BM[i] |= saveMax;
    }

    return result;
}

inline BooleanMatrix& BooleanMatrix:: operator |= (const BooleanMatrix& other)
{
    (*this) = (*this) | other;

    return *this;
}

int BooleanMatrix::weightBM() const
{
    int weightBM = 0;

    for (int i = 0; i < m_Row_BM; i++)
    {
        weightBM += m_BM[i].weight();
    }

    return weightBM;
}

int main()
{
    try
    {
        setlocale(LC_ALL, "Rus");
        srand(unsigned(time(NULL)));

        BooleanMatrix lab_BM_1;

        cout << "Способы заполнения булевой матрицы:\n";
        cout << "1. Потоковый ввод\n";

        cout << endl;
        int selectFill;
        cout << "Нажмите 1, чтобы начать заполнение: ";
        cin >> selectFill;
        switch (selectFill)
        {
        case 1:
        {
            cin >> lab_BM_1;
            cout << "\nБулева матрица:\n" << lab_BM_1;

            break;
        }
        default: exit(0);
        }

        cout << "\nДоступные функции:\n";
        cout << "2. Возвращение ссылки на строку\n";
        cout << "3. Конъюнкция строк\n";
        cout << "4. Дизъюнкция строк\n";
        cout << "5. Конъюкция матриц\n";
        cout << "6. Дизъюнкция матриц\n";
        cout << "0. Закрыть программу\n";

        int selectFunction = -1;
        while (selectFunction != 0)
        {
            cout << "\nВыберите функцию: ";
            cin >> selectFunction;
            switch (selectFunction)
            {
            case 2:
            {
                int necessaryRow;
                cout << "Укажите, какую строку вывести: ";
                cin >> necessaryRow;

                cout << lab_BM_1[necessaryRow - 1] << endl;

                break;
            }
            case 3:
            {
                BooleanVector resultingVector = lab_BM_1.rowConjuction();
                cout << "Результирующий вектор: " << resultingVector;

                break;
            }
            case 4:
            {
                BooleanVector resultingVector = lab_BM_1.rowDisjunction();
                cout << "Результирующий вектор: " << resultingVector;

                break;
            }
            case 5:
            {
                BooleanMatrix lab_BM_2;
                cout << "Задайте параметры второй матрицы:\n";
                cin >> lab_BM_2;

                cout << "Первая матрица:\n" << lab_BM_1;
                cout << "Вторая матрица:\n" << lab_BM_2;

                lab_BM_1 &= lab_BM_2;
                cout << "Результат:\n" << lab_BM_1;

                break;
            }
            case 7:
            {
                BooleanMatrix lab_BM_2;
                cout << "Задайте параметры второй матрицы:\n";
                cin >> lab_BM_2;

                cout << "Первая матрица:\n" << lab_BM_1;
                cout << "Вторая матрица:\n" << lab_BM_2;

                lab_BM_1 |= lab_BM_2;
                cout << "Результат:\n" << lab_BM_1;

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