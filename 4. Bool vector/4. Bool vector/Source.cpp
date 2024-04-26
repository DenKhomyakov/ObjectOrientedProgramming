/*
����� "����� ������"

��� ���������� ������� ������ ������� �������� ������ �������� �� ��� �������:
1. ������ ��������� ����� ������ (��������, int) ����� �������� � ����������� �� ����������� ����������. ����� �������, ���������� ������������ ���� ������, ������� ���������� ������ (��������, char). ����� ����, ������� ������ ��, ��� � �������� ����� ���� �� �������� ������������ ��� �������� �����.
2. ��������� ����������� ������� ��������� ������ ����� ���������� �������� ���� ����, ������� �� ������ ������������, ����� �������� ����� "�������" ��� �����������. ��, ��� ������ � ������� ��� ����� �����������, ������ �� �� �� ��������� ����������� ������� ��� ���, �������� �� �����. ������� - ����� ��� �� ��������� � �������, �������� ��� ������������� ������� ��������.

����������� ������ ������:
- ������������ (�� ���������, � ����������� (������ � �������� - ���� � �� �� ��� ���� ��������), ����������� �� ������� const char *, ����������� �����������);
- ����������;
- ����/����� � ������� (���������);
- �������� ���� ��������� �������;
- �������� i-�� ����������;
- ��������� � 0/1 i-�� ����������.

����������� ����������:
- ��������� ���������� ([ ], ��. ���������� ����);
- ��������� ��������� (&, &=);
- ��������� �������� (|, |=);
- ��������� ������ (<<, >>, <<=, >>=);
- ��������� ����������� ��� (^, ^=).

����������: ��������� ���������� ��������������� ������ �� ������ (�.�., ������������ �������� ���� � ���� int/char/bool, � �������� �������� � ��� ������ - ��� ����� ����� ������������ ��������������� �������).
*/

#include <iostream>
#include <cmath>
#include <cstring>
#include <locale>
#include <time.h>

using namespace std;

typedef unsigned char UC;

/* ��������� ���������� */
enum Errors_and_Exceprions
{
    errorLenghtLessZero = 1,
    errorRangeIndexOutBooleanVector,
    errorShiftLenghtLessZero,
};

/* ����� "����� ������" */
class BooleanVector
{
private:
    UC* m_BV;                   // ��
    int m_Lenght_BV;            // ����� ��
    int m_Memory_BV;            // ���������� ���������� ������

public:
    BooleanVector();                                                // ����������� �� ���������
    BooleanVector(int lenght_BV, int fillingMethod = 0);            // ����������� � ����������� ������� � �������� ��� ���� ��������
    BooleanVector(const char* string_BV, int lenght_BV);            // ����������� char* �� ������� � ������
    BooleanVector(const BooleanVector&);                            // ����������� �����������

    ~BooleanVector();                                               // ����������

    void setOne(int necessaryBit, int lenght_BV = 1);               // ���������� 1 � ����������� ����
    void setZero(int necessaryBit, int lenght_BV = 1);              // ���������� 0 � ����������� ����
    void inverseComponent(int necessaryBit, int lenght_BV = 1);     // �������� ������������ ����

    int operator[](int);                                            // ��������� ����������

    BooleanVector& operator<<=(int);                                // ��������� ����� ����� (� �����������)
    BooleanVector operator<<(int);                                  // ��������� ����� �����
    BooleanVector& operator>>=(int);                                // ��������� ����� ������ (� �����������)
    BooleanVector operator>>(int);                                  // ��������� ����� ������ 

    BooleanVector operator| (BooleanVector&);                       // ��������� ���
    BooleanVector& operator|= (BooleanVector&);                     // ��������� ��� (� �����������) 
    BooleanVector operator& (BooleanVector&);                       // ��������� �
    BooleanVector& operator&= (BooleanVector&);                     // ��������� � (� �����������) 
    BooleanVector operator ^(BooleanVector&);                       // ���������� ����������� ���
    BooleanVector& operator ^=(BooleanVector&);                     // ���������� ����������� ��� (� �����������)

    BooleanVector& operator~ ();                                    // ��������� ��

    friend ostream& operator << (ostream&, BooleanVector&);         // ��������� ����
    friend istream& operator >> (istream&, BooleanVector&);         // ��������� ������
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
    cout << "����� �������: ";
    is >> lenght_BV.m_Lenght_BV;

    if (lenght_BV.m_Lenght_BV <= 0)
    {
        throw errorLenghtLessZero;
    }

    cout << "������� �������� ������� (��� ��������): ";
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

        cout << "������� ���������� �������� �������:\n";
        cout << "1. ���������� �������\n";
        cout << "2. ��������� ����\n";

        cout << endl;
        int selectFill;
        cout << "�������� ������ ����������: ";
        cin >> selectFill;

        switch (selectFill)
        {
        case 1:
        {
            int lab_Lenght_BV;
            cout << "����� �������: ";
            cin >> lab_Lenght_BV;

            int fillingMethod;
            cout << "������� 0, ����� ��������� ������, 1 - ���������, ����� ������ ����� - ��������� �������: ";
            cin >> fillingMethod;

            BooleanVector tmp(lab_Lenght_BV, fillingMethod);
            lab_BV_1 = tmp;
            cout << "\n����� ������:\n" << lab_BV_1;

            break;
        }
        case 2:
        {
            cin >> lab_BV_1;
            cout << "\n����� ������:\n" << lab_BV_1;

            break;
        }
        default: exit(0);
        }

        cout << endl;

        cout << "\n��������� �������:\n";
        cout << "3. ��������� 1 � �������� ������\n";
        cout << "4. ��������� 0 � �������� ������\n";
        cout << "5. �������� ��������� �������\n";
        cout << "6. �������� ���������� �������\n";
        cout << "7. ��������� ����� �����\n";
        cout << "8. ��������� ����� ������\n";
        cout << "9. ���������� ��������\n";
        cout << "10. ��������� ��������\n";
        cout << "11. ����������� ��� ��������\n";
        cout << "12. �������� �������\n";
        cout << "0. ������� ���������\n";

        int selectFunction = -1;
        while (selectFunction != 0)
        {
            cout << "\n�������� �������: ";
            cin >> selectFunction;
            switch (selectFunction)
            {
            case 3:
            {
                int necessaryBit;
                cout << "������, ���������� ���������: ";
                cin >> necessaryBit;

                int quanityBit;
                cout << "���������� �������� ��� ��������� (������ ������): ";
                cin >> quanityBit;

                lab_BV_1.setOne(necessaryBit, quanityBit);
                cout << lab_BV_1;

                cout << endl;
                break;
            }
            case 4:
            {
                int necessaryBit;
                cout << "������, ���������� ���������: ";
                cin >> necessaryBit;

                int quanityBit;
                cout << "���������� �������� ��� ��������� (������ ������): ";
                cin >> quanityBit;

                lab_BV_1.setZero(necessaryBit, quanityBit);
                cout << lab_BV_1;

                cout << endl;
                break;
            }
            case 5:
            {
                int necessaryBit;
                cout << "������, ���������� ���������: ";
                cin >> necessaryBit;

                int quanityBit;
                cout << "���������� �������� ��� ��������� (������ ������): ";

                cin >> quanityBit;
                lab_BV_1.inverseComponent(necessaryBit, quanityBit);
                cout << lab_BV_1;

                cout << endl;
                break;
            }
            case 6:
            {
                int necessaryBit;
                cout << "������, ���������� ���������: ";
                cin >> necessaryBit;

                cout << lab_BV_1[necessaryBit];

                cout << endl;
                break;
            }
            case 7:
            {
                int quanityBit;
                cout << "���������� �������� ��� ������: ";
                cin >> quanityBit;

                lab_BV_1 <<= quanityBit;
                cout << lab_BV_1;

                cout << endl;
                break;
            }
            case 8:
            {
                int quanityBit;
                cout << "���������� �������� ��� ������: ";
                cin >> quanityBit;

                lab_BV_1 >>= quanityBit;
                cout << lab_BV_1;

                cout << endl;
                break;
            }
            case 9:
            {
                BooleanVector lab_BV_2;
                cout << "������� ��������� ������� �������:\n";
                cin >> lab_BV_2;

                cout << "������ ������:\n" << lab_BV_1 << endl;
                cout << "������ ������:\n" << lab_BV_2 << endl;

                lab_BV_1 |= lab_BV_2;
                cout << "�������������� ������:\n" << lab_BV_1;

                cout << endl;
                break;
            }
            case 10:
            {
                BooleanVector lab_BV_2;
                cout << "������� ��������� ������� �������:\n";
                cin >> lab_BV_2;

                cout << "������ ������:\n" << lab_BV_1 << endl;
                cout << "������ ������:\n" << lab_BV_2 << endl;

                lab_BV_1 &= lab_BV_2;
                cout << "�������������� ������:\n" << lab_BV_1;

                cout << endl;
                break;
            }
            case 11:
            {
                BooleanVector lab_BV_2;
                cout << "������� ��������� ������� �������:\n";
                cin >> lab_BV_2;

                cout << "������ ������:\n" << lab_BV_1 << endl;
                cout << "������ ������:\n" << lab_BV_2 << endl;

                lab_BV_1 ^= lab_BV_2;
                cout << "�������������� ������:\n" << lab_BV_1;

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