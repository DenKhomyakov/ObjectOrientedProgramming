/*
��������� ����������� ����� "������":
���������� ������� ����� �����. ������������� ������������ ������ �������� ����������� ��������������� ����������/������ ������� ��� ����������/�������� ���������.

����������� ������ ������:
- ������������ (�� ���������, ����������� �� �������� �������, ����������� �����������);
- ����������;
- ����� �������� (���������� ������ ������� ���������� ��������, ���� -1, ���� ���������� ���);
- ����/����� � ������� (���������);
- ���������� ��������� (����� ����������);
- ������� �������� �� �������;
- �������� �������� �� ������� (����� ����������� � ���� ���������� ��������� "-=").

����������� ����������:
- ��������� ������ �� ������� �� ������� ([]).
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

/* ����������� */
Array::Array()
{
	size = 0;
	massif = nullptr;
}

/* �������� ������� ����� n, ������������ ������ */
Array::Array(int n)
{
	size = n;
	massif = new int[size];

	for (int i = 0; i < size; i++)
	{
		massif[i] = 0;
	}
}

/* �������� ������� ���� ����������� ������������� ������� ���� Array */
Array::Array(const Array& copy)
{
	size = copy.size;
	massif = new int[size];

	for (int i = 0; i < size; i++)
	{
		massif[i] = copy.massif[i];
	}
}

/* �������� ������� ���� ����������� ������������� */
Array::Array(int copy[], int n)
{
	size = n;
	massif = new int[size];

	for (int i = 0; i < size; i++)
	{
		massif[i] = copy[i];
	}
}

/* ���������� */
Array::~Array()
{
	delete[] massif;
}

/* ����� �������� � ������� � ����� ��� ������� */
int Array::searchElement(int el)
{
	for (int i = 0; i < size; i++)
	{
		if (massif[i] == el) return i;
	}

	return -1;
}

/* ��������� ���� ��������� �� ������� */
std::istream& operator>>(std::istream& in, Array& tmp)
{
	for (int i = 0; i < tmp.size; i++)
	{
		in >> tmp.massif[i];
	}

	return in;
}

/* ��������� ����� ��������� �� ������� */
std::ostream& operator<<(std::ostream& out, Array tmp)
{
	for (int i = 0; i < tmp.size; i++)
	{
		out << tmp.massif[i] << " ";
	}
	out << std::endl;

	return out;
}

/* ������ ���� ��������� ������� */
void Array::setArray()
{
	for (int i = 0; i < size; i++)
	{
		std::cin >> massif[i];
	}
}

/* ����� ��������� ������� �� ������� */
void Array::getArray()
{
	for (int i = 0; i < size; i++)
	{
		std::cout << massif[i];
	}
}

/* ���������� ��������� ������� ��������� */
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

/* ���������� �������� � ������ �� ���������� ������� */
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

/* �������� �������� � ��������� �������� �� ������� */
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

/* �������� (�� �������) �������� ������� */
Array& Array::operator-=(int index)
{
	deleteElement(index);

	return *this;
}

/* ��������� ������ �� ������� �� ������� */
int& Array::operator[](int index)
{
	if (index < 0 || index >= size)
	{
		std::cerr << "����� �� ������!";
		exit(1);
	}

	return massif[index];
}

int main()
{
	setlocale(LC_ALL, "Rus");

	cout << "������� �������� ������� (5 ��): ";
	Array lab_Massif(5);
	cin >> lab_Massif;
	cout << "��� ������: ";
	cout << lab_Massif;

	cout << "������ ����� �������� �������� ��������: ";
	lab_Massif.deleteElement(2);
	cout << lab_Massif;

	cout << "������ ����� ���������� ������ ��������: ";
	lab_Massif.addElement(3, 19);
	cout << lab_Massif;

	cout << "������ ����� ����������: ";
	lab_Massif.sortArray();
	cout << lab_Massif;

	/* ���������� ������ ��������� */
	cout << endl;
	system("pause");
}