/*
����� "������"

���������� ���������� ������ (���������� ������� ����� ���� ����� ���� ������).

����������� ������ ������:
- ������������ (�� ���������, ����������� �� �������� �������, ����������� �����������);
- ����������;
- ����� �������� (���������� ������ ������� ���������� ��������, ���� -1, ���� ���������� ���);
- ����/����� � ������� (���������);
- ���������� ��������� (����� ����������);
- ������� �������� �� �������;
- �������� �������� �� ������� (����� ����������� � ���� ���������� ��������� "-=").

����������� ����������:
- ��������� ������ �� ������� �� ������� ([ ]).
*/

#include <iostream>
#include <time.h>
#include <locale>

/* ��������� ���������� */
enum Errors_and_Exceptions
{
    errorInvalidArraySize,
    errorNecessaryElementIsMissingInArray,
};

using namespace std;

typedef float TF;

/* ��������� ����� "������" */
template <class T> class Array
{
    T* m_Array;             // ������
    int m_Size_Array;       // ������ �������
public:
    Array();                                                                        // ����������� �� ���������
    Array(int);                                                                     // ����������� �� �������� �������
    Array(T*, int);                                                                 // ����������� � ����������
    Array(const Array<T>&);                                                         // ����������� �����������

    ~Array();                       						                        // ����������

    int searchElement(T);   			                                            // ����� ��������

    template<class T>friend ostream& operator << (ostream&, Array<T>&);             // ��������� ����� 
    template<class T>friend istream& operator >> (istream&, Array<T>&);             // ��������� ����

    void arraySort();		                                                        // ���������� ������� (������ �������)

    bool addElement(T, int);                                                        // ���������� ��������
    bool addElementAfter(T, T);                                                     // ���������� ��������

    Array<T>& deleteElement(int);                                                   // �������� ��������
    Array<T>& operator -= (T);     	                                                // �������� �������� ��������

    T& operator [] (int); 			                                                // ��������� ������ �� ������� �� �������

    Array<T>& operator = (const Array<T>&);                                         // �������� ����������
    Array<T>& operator = (int);                                                     // �������� ������� ����������� ������� 

    void GetRand();                                                                 // ���������� ������� ���������� �������
    void inputArray();                                                              // ���� �������
    void printArray();					                                            // ����� �������

    void leftShift(int);                                                            // ����� ����� �� �������� ���������� �������
    void rightShift(int);                                                           // ����� ������ �� �������� ���������� �������

private:
    void leftShiftKey(int);                                                         // ����� �����, ������� � ������������� ������� + 1
    void rightShiftKey(int);                                                        // ����� ������, ���������� ������������� ��������

};

/* ����������� �� ��������� */
template<class T> Array<T>::Array()
{
    m_Size_Array = 1;
    m_Array = new T[m_Size_Array];

    for (int i = 0; i < m_Size_Array; i++)
    {
        m_Array[i] = T();
    }
};

/* ����������� �� �������� ������� */
template<class T> Array<T>::Array(T* massif, int arraySize)
{
    m_Size_Array = arraySize;
    m_Array = new T[arraySize];

    for (int i = 0; i < m_Size_Array; i++)
    {
        m_Array[i] = massif[i];
    }
};

/* ����������� � ����� ���������� */
template<class T> Array<T>::Array(int arraySize)
{
    m_Size_Array = arraySize;
    m_Array = new T[m_Size_Array];

    for (int i = 0; i < m_Size_Array; i++)
    {
        m_Array[i] = T(); // ����� �������� �� ��������� ��� ������ (0 �� ��������� ��� ������� �� ��������)
    }
};

/* ����������� ����������� */
template<class T> Array<T>::Array(const Array<T>& massif)
{
    m_Size_Array = massif.m_Size_Array;
    m_Array = new T[m_Size_Array];

    for (int i = 0; i < m_Size_Array; i++)
    {
        m_Array[i] = massif.m_Array[i];
    }
};

/* ���������� */
template<class T> Array<T>::~Array()
{
    delete[] m_Array;
}

/* �������� ���������� */
template <class T> Array<T>& Array<T>::operator = (const Array<T>& massif)
{
    if (this == &massif)
    {
        return *this;
    }

    *this = massif.m_Size_Array;

    for (int i = 0; i < massif.m_Size_Array; i++)
    {
        m_Array[i] = massif.m_Array[i];
    }

    return *this;
};

/* �������� ������� ������� ������� */
template <class T> Array<T>& Array<T> :: operator = (int arraySize)
{
    /* ���� ������ ������� ������ ����������, �� ��������� �������� ���������� */

    if (arraySize <= 0)
    {
        throw errorInvalidArraySize;

        arraySize = 1;
    }

    T* oldArrayPtr = m_Array;
    m_Array = new T[arraySize];

    if (arraySize < m_Size_Array)
    {
        for (int i = 0; i < arraySize; i++)
        {
            m_Array[i] = oldArrayPtr[i];
        }
    }

    else
    {
        for (int i = 0; i < m_Size_Array; i++)
        {
            m_Array[i] = oldArrayPtr[i];
        }

        for (int i = m_Size_Array; i < arraySize; i++)
        {
            m_Array[i] = T();
        }
    }

    m_Size_Array = arraySize;
    delete[] oldArrayPtr;

    return *this;
};

/* ���������� ������� ���������� ������ ������� */
void Array<int>::GetRand()
{
    const int left = 1;
    const int right = 51;

    for (int i = 0; i < m_Size_Array; i++)
    {
        m_Array[i] = left + rand() % right;
    }
};

/* ���������� ������� ���������� ������������� ������� */
void Array<float> ::GetRand()
{
    const int left = 100;
    const int right = 301;

    for (int i = 0; i < m_Size_Array; i++)
    {
        float value = (left + rand() % right);
        value = value / 100;

        m_Array[i] = value;
    }
};

/* ���������� ������� ���������� ������� */
void Array<char> ::GetRand()
{
    char arrayOfChar[26];

    for (int i = 0; i < 26; i++) //for (char i = 'a'; i <= 'z'; i++)
    {
        arrayOfChar[i] = char(i + 'a');
    }

    for (int i = 0; i < m_Size_Array; i++)
    {
        m_Array[i] = arrayOfChar[rand() % 26];
    }
};

/* ���� ������� */
template <class T> void Array<T> ::inputArray()
{
    cout << "������� ������ �� " << m_Size_Array << " ���������: " << endl;

    for (int i = 0; i < m_Size_Array; i++)
    {
        cin >> m_Array[i];
    }
};

/* ����� ������� */
template <class T> void Array<T>::printArray()
{
    cout << "������: " << endl;

    for (int i = 0; i < m_Size_Array; i++)
    {
        cout << m_Array[i] << " ";
    }

    cout << endl;
};

/* ��������� ����� */
template <class T> ostream& operator << (ostream& os, Array<T>& tmp)
{
    for (int i = 0; i < tmp.m_Size_Array; i++)
    {
        os << tmp[i] << " ";
    }

    return os;
};

/* ��������� ���� */
template <class T> istream& operator >> (istream& is, Array<T>& tmp)
{
    for (int i = 0; i < tmp.m_Size_Array; i++)
    {
        is >> tmp[i];
    }

    return is;
};

/* ��������� ������ �� ������� �� ������� */
template <class T> T& Array<T>:: operator [] (int indexElement)
{
    return m_Array[indexElement];
};

/* ����� �������� */
template <class T> int Array<T>::searchElement(T necessaryElement)
{
    /* ���� ������� �������� ������� */
    for (int indexElement = 0; indexElement < m_Size_Array; indexElement++)
    {
        if (m_Array[indexElement] == necessaryElement)
        {
            return indexElement;
        }
    }

    /* ���� �� ������� �������� ������� */
    return -1;
};

/* �������� �������� �������� */
template <class T> Array<T>& Array<T>:: operator -= (T necessaryElement)
{
    int i = searchElement(necessaryElement);

    if ((i >= 0) && (i < m_Size_Array))
    {
        for (; i < m_Size_Array - 1; i++)
        {
            m_Array[i] = m_Array[i + 1];
        }

        m_Size_Array = m_Size_Array - 1;
    }

    else
    {
        throw errorNecessaryElementIsMissingInArray;
    }

    return *this;
};

/* ���������� �������� */
template <class T> bool Array<T>::addElementAfter(T newElement, T arrayElement)
{
    int arrayElementIndex = searchElement(arrayElement);
    if (arrayElementIndex == -1)
    {
        return false;
    }
    else
    {
        return addElement(newElement, arrayElementIndex + 1);
    }
};

/* ���������� �������� */
template <class T> bool Array<T>::addElement(T newElement, int position)
{
    if ((position < 0) || (position > m_Size_Array))
    {
        return false;
    }

    *this = m_Size_Array + 1;
    rightShiftKey(position);
    m_Array[position] = newElement;

    return true;
};

/* �������� �������� */
template <class T> Array<T>& Array<T>::deleteElement(int position)
{
    leftShiftKey(position);
    *this = m_Size_Array - 1;

    return *this;
};

/* ����� ����� �� �������� ���������� ������� */
template <class T> void Array<T>::leftShift(int shiftPosition)
{
    for (int i = 0; i < shiftPosition; i++)
    {
        T massif = m_Array[0];
        leftShiftKey(0);
        m_Array[m_Size_Array - 1] = massif;
    }
};

/* ����� ������ �� �������� ���������� ������� */
template <class T> void Array<T>::rightShift(int shiftPosition)
{
    for (int i = 0; i < shiftPosition; i++)
    {
        T massif = m_Array[m_Size_Array - 1];
        rightShiftKey(0);
        m_Array[0] = massif;
    }
};

/* ���������� ������� (������ �������) */
template <class T> void Array<T>::arraySort()
{
    for (int i = 0; i < m_Size_Array - 1; i++)
    {
        int min = i;

        for (int k = i + 1; k < m_Size_Array; k++)
        {
            if (m_Array[k] < m_Array[min])
            {
                min = k;
            }
        }

        T tmp = m_Array[i];
        m_Array[i] = m_Array[min];
        m_Array[min] = tmp;
    }
};

/* ����� �����, ������� � ������������� ������� + 1 */
template <class T> void Array<T>::leftShiftKey(int position)
{
    for (int i = position; i < m_Size_Array - 1; i++)
    {
        m_Array[i] = m_Array[i + 1];
    }
};

/* ����� ������, ���������� ������������� �������� */
template <class T> void Array<T>::rightShiftKey(int position)
{
    for (int i = m_Size_Array - 1; i > position; i--)
    {
        m_Array[i] = m_Array[i - 1];
    }
};

int main()
{
    try
    {
        setlocale(LC_ALL, "Rus");
        srand(unsigned(time(NULL)));

        Array<TF> lab_Array_1;

        int lab_arraySize;
        cout << "������� ������ �������: ";
        cin >> lab_arraySize;

        lab_Array_1 = lab_arraySize;

        cout << "������� ��������� �������:\n";
        cout << "1. ���������� �������\n";
        cout << "2. ���������� ������� �� �����������\n";
        cout << "3. ���������� ����\n";
        cout << "4. ��������� ����\n";

        int fillingMethod;
        cout << "�������� ������ ����������: ";
        cin >> fillingMethod;

        switch (fillingMethod)
        {
        case 0: break;
        case 1:
        {
            lab_Array_1.GetRand();
            cout << "������: " << lab_Array_1 << endl;

            break;
        }
        case 2:
        {
            lab_Array_1.GetRand();
            lab_Array_1.arraySort();
            cout << "������: " << lab_Array_1 << endl;

            break;
        }
        case 3:
        {
            lab_Array_1.inputArray();
            cout << "������: " << lab_Array_1 << endl;

            break;
        }
        case 4:
        {
            cout << "������� ������: ";
            cin >> lab_Array_1;
            cout << "������: " << lab_Array_1 << endl;

            break;
        }
        default: cout << "�������� ����� �������" << endl; break;
        }

        cout << endl;

        cout << "\n��������� �������:\n";
        cout << "5. ���������� ������� �� �����������\n";
        cout << "6. ����� ��������\n";
        cout << "7. ���������� ��������\n";
        cout << "8. �������� ��������\n";
        cout << "0. ������� ���������\n";

        int selectFunction = -1;
        while (selectFunction != 0)
        {
            cout << "\n�������� �������: ";
            cin >> selectFunction;
            switch (selectFunction)
            {
            case 0: break;
            case 5:
            {
                lab_Array_1.arraySort();
                cout << "������ (���������������): " << lab_Array_1 << endl;

                break;
            }
            case 6:
            {
                TF necessaryElement;
                cout << "������� �������: ";
                cin >> necessaryElement;

                int i = lab_Array_1.searchElement(necessaryElement);

                if (i != -1)
                {
                    cout << "������ ��������: " << i << endl;
                }

                else
                {
                    cout << "�������� ������� ����������� � �������!" << endl;
                }

                break;
            }
            case 7:
            {
                TF necessaryElement;
                cout << "������� �������: ";
                cin >> necessaryElement;

                int position;
                cout << "������� �������: ";
                cin >> position;

                lab_Array_1.addElement(necessaryElement, position);
                cout << "������: " << lab_Array_1 << endl;

                break;
            }
            case 8:
            {
                int position;
                cout << "������� �������: ";
                cin >> position;

                lab_Array_1.deleteElement(position);
                cout << "������: " << lab_Array_1 << endl;

                break;
            }
            default: cout << "�������� ����� �������" << endl;
            }
        }
    }
    catch (Errors_and_Exceptions SomethingWentWrong)
    {
        return SomethingWentWrong;
    }

    cout << endl;
    system("pause");
}