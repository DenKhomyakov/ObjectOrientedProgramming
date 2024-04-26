/*
Требуется реализовать класс "Массив":
Реализация массива целых чисел. Отличительной особенностью класса является возможность автоматического расширения/сжатия массива при добавлении/удалении элементов.

Необходимые методы класса:
- конструкторы (по умолчанию, конструктор из обычного массива, конструктор копирования);
- деструктор;
- поиск элемента (возвращает индекс первого совпавшего элемента, либо -1, если совпадений нет);
- ввод/вывод в консоль (потоковый);
- сортировка элементов (любым алгоритмом);
- вставка элемента по индексу;
- удаление элемента по индексу (также реализовать в виде перегрузки оператора "-=").

Необходимые перегрузки:
- получение ссылки на элемент по индексу ([]).
*/

#include <iostream>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;

class Array
{
private:
	int* massif;
	int size;

public:
	Array();
	Array(int n);
	Array(const Array& copy);
	Array(int copy[], int n);

	~Array();

	int searchElement(int el);

	friend std::istream& operator>>(std::istream& in, Array& tmp);
	friend std::ostream& operator<<(std::ostream& out, Array tmp);
	void setArray();
	void getArray();

	void sortArray();

	void addElement(int index, int Element);

	void deleteElement(int index);
	Array& operator-=(int index);

	int& operator[](int index);
};

/* Конструктор */
Array::Array()
{
	size = 0;
	massif = nullptr;
}

/* Создание массива длины n, заполненного нулями */
Array::Array(int n)
{
	size = n;
	massif = new int[size];

	for (int i = 0; i < size; i++)
	{
		massif[i] = 0;
	}
}

/* Создание массива путём копирования существующего массива типа Array */
Array::Array(const Array& copy)
{
	size = copy.size;
	massif = new int[size];

	for (int i = 0; i < size; i++)
	{
		massif[i] = copy.massif[i];
	}
}

/* Создание массива путём копирования существующего */
Array::Array(int copy[], int n)
{
	size = n;
	massif = new int[size];

	for (int i = 0; i < size; i++)
	{
		massif[i] = copy[i];
	}
}

/* Деструктор */
Array::~Array()
{
	delete[] massif;
}

/* Поиск элемента в массиве и вывод его индекса */
int Array::searchElement(int el)
{
	for (int i = 0; i < size; i++)
	{
		if (massif[i] == el) return i;
	}

	return -1;
}

/* Потоковый ввод элементов на консоль */
std::istream& operator>>(std::istream& in, Array& tmp)
{
	for (int i = 0; i < tmp.size; i++)
	{
		in >> tmp.massif[i];
	}

	return in;
}

/* Потоковый вывод элементов на консоль */
std::ostream& operator<<(std::ostream& out, Array tmp)
{
	for (int i = 0; i < tmp.size; i++)
	{
		out << tmp.massif[i] << " ";
	}
	out << std::endl;

	return out;
}

/* Ручной ввод элементов массива */
void Array::setArray()
{
	for (int i = 0; i < size; i++)
	{
		std::cin >> massif[i];
	}
}

/* Вывод элементов массива на консоль */
void Array::getArray()
{
	for (int i = 0; i < size; i++)
	{
		std::cout << massif[i];
	}
}

/* Сортировка элементов массива пузырьком */
void Array::sortArray()
{
	for (int k = 1; k < size; k++)
	{
		int i;
		int tmp = massif[k];
		for (i = k; tmp < massif[i - 1] && i != 0; i--)
		{
			massif[i] = massif[i - 1];
		}
		massif[i] = tmp;
	}
}

/* Добавление элемента в массив по указанному индексу */
void Array::addElement(int index, int Element)
{
	Array tmp(*this);
	delete[] massif;
	size = tmp.size + 1;
	massif = new int[size];

	for (int i = 0; i < size - 1; i++)
	{
		massif[i] = tmp.massif[i];
	}

	for (int i = size - 2; i >= index; i--)
	{
		massif[i + 1] = tmp.massif[i];
	}

	massif[index] = Element;
}

/* Удаление эдемента с указанным индексом из массива */
void Array::deleteElement(int index)
{
	Array tmp(*this);
	delete[] massif;
	size = tmp.size + 1;
	massif = new int[size];

	int i = 0;
	int x = 0;
	while (x <= size)
	{
		if (x != index)
		{
			massif[i] = tmp.massif[x];
			i++;
		}

		else
		{
			massif[i] = tmp.massif[x + 1];
			i++;
			x++;
		}

		x++;
	}
}

/* Удаление (по индексу) элемента массива */
Array& Array::operator-=(int index)
{
	deleteElement(index);

	return *this;
}

/* Получение ссылки на элемент по индексу */
int& Array::operator[](int index)
{
	if (index < 0 || index >= size)
	{
		std::cerr << "Выход за предел!";
		exit(1);
	}

	return massif[index];
}

int main()
{
	setlocale(LC_ALL, "Rus");

	cout << "Введите элементы массива (5 шт): ";
	Array lab_Massif(5);
	cin >> lab_Massif;
	cout << "Ваш массив: ";
	cout << lab_Massif;

	cout << "Массив после удаления третьего элемента: ";
	lab_Massif.deleteElement(2);
	cout << lab_Massif;

	cout << "Массив после добавления нового элемента: ";
	lab_Massif.addElement(3, 19);
	cout << lab_Massif;

	cout << "Массив после сортировки: ";
	lab_Massif.sortArray();
	cout << lab_Massif;

	/* Завершение работы программы */
	cout << endl;
	system("pause");
}