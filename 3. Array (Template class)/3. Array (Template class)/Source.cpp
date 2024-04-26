/*
Класс "Массив"

Реализация шаблонного класса (элементами массива могут быть любые типы данных).

Необходимые методы класса:
- конструкторы (по умолчанию, конструктор из обычного массива, конструктор копирования);
- деструктор;
- поиск элемента (возвращает индекс первого совпавшего элемента, либо -1, если совпадений нет);
- ввод/вывод в консоль (потоковый);
- сортировка элементов (любым алгоритмом);
- вставка элемента по индексу;
- удаление элемента по индексу (также реализовать в виде перегрузки оператора "-=").

Необходимые перегрузки:
- получение ссылки на элемент по индексу ([ ]).
*/

#include <iostream>
#include <time.h>
#include <locale>

/* Обработка исключений */
enum Errors_and_Exceptions
{
    errorInvalidArraySize,
    errorNecessaryElementIsMissingInArray,
};

using namespace std;

typedef float TF;

/* Шаблонный класс "Массив" */
template <class T> class Array
{
    T* m_Array;             // Массив
    int m_Size_Array;       // Размер массива
public:
    Array();                                                                        // Конструктор по умолчанию
    Array(int);                                                                     // Конструктор из обычного массива
    Array(T*, int);                                                                 // Конструктор с аргументом
    Array(const Array<T>&);                                                         // Конструктор копирования

    ~Array();                       						                        // Деструктор

    int searchElement(T);   			                                            // Поиск элемента

    template<class T>friend ostream& operator << (ostream&, Array<T>&);             // Потоковый вывод 
    template<class T>friend istream& operator >> (istream&, Array<T>&);             // Потоковый ввод

    void arraySort();		                                                        // Сортировка массива (прямым выбором)

    bool addElement(T, int);                                                        // Добавление элемента
    bool addElementAfter(T, T);                                                     // Добавление элемента

    Array<T>& deleteElement(int);                                                   // Удаление элемента
    Array<T>& operator -= (T);     	                                                // Оператор удаления элемента

    T& operator [] (int); 			                                                // Получение ссылки на элемент по индексу

    Array<T>& operator = (const Array<T>&);                                         // Оператор присвоения
    Array<T>& operator = (int);                                                     // Оператор задания размерности массива 

    void GetRand();                                                                 // Заполнение массива случайными числами
    void inputArray();                                                              // Ввод массива
    void printArray();					                                            // Вывод массива

    void leftShift(int);                                                            // Сдвиг влево на заданное количество позиций
    void rightShift(int);                                                           // Сдвиг вправо на заданное количество позиций

private:
    void leftShiftKey(int);                                                         // Сдвиг влево, начиная с установленной позиции + 1
    void rightShiftKey(int);                                                        // Сдвиг вправо, заканчивая установленной позицией

};

/* Конструктор по умолчанию */
template<class T> Array<T>::Array()
{
    m_Size_Array = 1;
    m_Array = new T[m_Size_Array];

    for (int i = 0; i < m_Size_Array; i++)
    {
        m_Array[i] = T();
    }
};

/* Конструктор из обычного массива */
template<class T> Array<T>::Array(T* massif, int arraySize)
{
    m_Size_Array = arraySize;
    m_Array = new T[arraySize];

    for (int i = 0; i < m_Size_Array; i++)
    {
        m_Array[i] = massif[i];
    }
};

/* Конструктор с целым аргументом */
template<class T> Array<T>::Array(int arraySize)
{
    m_Size_Array = arraySize;
    m_Array = new T[m_Size_Array];

    for (int i = 0; i < m_Size_Array; i++)
    {
        m_Array[i] = T(); // Кладём значение по умолчанию для класса (0 не сработает для массива из массивов)
    }
};

/* Конструктор копирования */
template<class T> Array<T>::Array(const Array<T>& massif)
{
    m_Size_Array = massif.m_Size_Array;
    m_Array = new T[m_Size_Array];

    for (int i = 0; i < m_Size_Array; i++)
    {
        m_Array[i] = massif.m_Array[i];
    }
};

/* Деструктор */
template<class T> Array<T>::~Array()
{
    delete[] m_Array;
}

/* Оператор присвоения */
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

/* Оператор задания размера массива */
template <class T> Array<T>& Array<T> :: operator = (int arraySize)
{
    /* Если размер массива больше имеющегося, то свободные элементы зануляются */

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

/* Заполнение массива случайными целыми числами */
void Array<int>::GetRand()
{
    const int left = 1;
    const int right = 51;

    for (int i = 0; i < m_Size_Array; i++)
    {
        m_Array[i] = left + rand() % right;
    }
};

/* Заполнение массива случайными вещественными числами */
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

/* Заполнение массива случайными буквами */
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

/* Ввод массива */
template <class T> void Array<T> ::inputArray()
{
    cout << "Введите массив из " << m_Size_Array << " элементов: " << endl;

    for (int i = 0; i < m_Size_Array; i++)
    {
        cin >> m_Array[i];
    }
};

/* Вывод массива */
template <class T> void Array<T>::printArray()
{
    cout << "Массив: " << endl;

    for (int i = 0; i < m_Size_Array; i++)
    {
        cout << m_Array[i] << " ";
    }

    cout << endl;
};

/* Потоковый вывод */
template <class T> ostream& operator << (ostream& os, Array<T>& tmp)
{
    for (int i = 0; i < tmp.m_Size_Array; i++)
    {
        os << tmp[i] << " ";
    }

    return os;
};

/* Потоковый ввод */
template <class T> istream& operator >> (istream& is, Array<T>& tmp)
{
    for (int i = 0; i < tmp.m_Size_Array; i++)
    {
        is >> tmp[i];
    }

    return is;
};

/* Получение ссылки на элемент по индексу */
template <class T> T& Array<T>:: operator [] (int indexElement)
{
    return m_Array[indexElement];
};

/* Поиск элемента */
template <class T> int Array<T>::searchElement(T necessaryElement)
{
    /* Если нашёлся заданный элемент */
    for (int indexElement = 0; indexElement < m_Size_Array; indexElement++)
    {
        if (m_Array[indexElement] == necessaryElement)
        {
            return indexElement;
        }
    }

    /* Если не нашёлся заданный элемент */
    return -1;
};

/* Оператор удаления элемента */
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

/* Добавление элемента */
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

/* Добавление элемента */
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

/* Удаление элемента */
template <class T> Array<T>& Array<T>::deleteElement(int position)
{
    leftShiftKey(position);
    *this = m_Size_Array - 1;

    return *this;
};

/* Сдвиг влево на заданное количество позиций */
template <class T> void Array<T>::leftShift(int shiftPosition)
{
    for (int i = 0; i < shiftPosition; i++)
    {
        T massif = m_Array[0];
        leftShiftKey(0);
        m_Array[m_Size_Array - 1] = massif;
    }
};

/* Сдвиг вправо на заданное количество позиций */
template <class T> void Array<T>::rightShift(int shiftPosition)
{
    for (int i = 0; i < shiftPosition; i++)
    {
        T massif = m_Array[m_Size_Array - 1];
        rightShiftKey(0);
        m_Array[0] = massif;
    }
};

/* Сортировка массива (прямым выбором) */
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

/* Сдвиг влево, начиная с установленной позиции + 1 */
template <class T> void Array<T>::leftShiftKey(int position)
{
    for (int i = position; i < m_Size_Array - 1; i++)
    {
        m_Array[i] = m_Array[i + 1];
    }
};

/* Сдвиг вправо, заканчивая установленной позицией */
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
        cout << "Введите размер массива: ";
        cin >> lab_arraySize;

        lab_Array_1 = lab_arraySize;

        cout << "Способы генерации массива:\n";
        cout << "1. Случайными числами\n";
        cout << "2. Случайными числами по возрастанию\n";
        cout << "3. Консольный ввод\n";
        cout << "4. Потоковый ввод\n";

        int fillingMethod;
        cout << "Выберите способ заполнения: ";
        cin >> fillingMethod;

        switch (fillingMethod)
        {
        case 0: break;
        case 1:
        {
            lab_Array_1.GetRand();
            cout << "Массив: " << lab_Array_1 << endl;

            break;
        }
        case 2:
        {
            lab_Array_1.GetRand();
            lab_Array_1.arraySort();
            cout << "Массив: " << lab_Array_1 << endl;

            break;
        }
        case 3:
        {
            lab_Array_1.inputArray();
            cout << "Массив: " << lab_Array_1 << endl;

            break;
        }
        case 4:
        {
            cout << "Введите массив: ";
            cin >> lab_Array_1;
            cout << "Массив: " << lab_Array_1 << endl;

            break;
        }
        default: cout << "Неверный номер способа" << endl; break;
        }

        cout << endl;

        cout << "\nДоступные функции:\n";
        cout << "5. Сортировка массива по возрастанию\n";
        cout << "6. Поиск элемента\n";
        cout << "7. Добавление элемента\n";
        cout << "8. Удаление элемента\n";
        cout << "0. Закрыть программу\n";

        int selectFunction = -1;
        while (selectFunction != 0)
        {
            cout << "\nВыберите функцию: ";
            cin >> selectFunction;
            switch (selectFunction)
            {
            case 0: break;
            case 5:
            {
                lab_Array_1.arraySort();
                cout << "Массив (отсортированный): " << lab_Array_1 << endl;

                break;
            }
            case 6:
            {
                TF necessaryElement;
                cout << "Введите элемент: ";
                cin >> necessaryElement;

                int i = lab_Array_1.searchElement(necessaryElement);

                if (i != -1)
                {
                    cout << "Индекс элемента: " << i << endl;
                }

                else
                {
                    cout << "Заданный элемент отсутствует в массиве!" << endl;
                }

                break;
            }
            case 7:
            {
                TF necessaryElement;
                cout << "Введите элемент: ";
                cin >> necessaryElement;

                int position;
                cout << "Введите позицию: ";
                cin >> position;

                lab_Array_1.addElement(necessaryElement, position);
                cout << "Массив: " << lab_Array_1 << endl;

                break;
            }
            case 8:
            {
                int position;
                cout << "Введите позицию: ";
                cin >> position;

                lab_Array_1.deleteElement(position);
                cout << "Массив: " << lab_Array_1 << endl;

                break;
            }
            default: cout << "Неверный номер функции" << endl;
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