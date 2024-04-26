/*
Класс "Список"

В данной лабораторной требуется реализовать списочную структуру хранения целочисленных данных посредством композиции классов.

Список может быть как однонаправленным, так и двунаправленным, по вашему усмотрению.

Для реализации необходимо создать два класса: Node (узел списка) и List (сам список).

Необходимые методы класса:
- конструкторы (по умолчанию, с параметрами, конструктор из массива int, конструктор копирования);
- деструктор;
- ввод/вывод в консоль (потоковый);
- поиск элемента по ключу (возвращает указатель на элемент или nullptr, если элемента нет в списке);
- добавление элемента (в голову);
- удаление элемента (хвоста).

Необходимые перегрузки:
- присваивание (=);
- получение ссылки на ключ элемента ([ ]);
- сравнение (==, !=).
*/

/* Двунаправленный список */

#include <iostream>
#include <time.h>
#include <cstdlib>
#include <cstring>
#include <locale>

using namespace std;

/* Обработка исключений */
enum Errors_and_Exceptions
{
	/* Для List */
	errorArraySizeLessZero,
	errorArrayAdressNotPassed,
	errorNumberOfArrayElementsWasPassedIncorrectly,
	errorElementIndexWasPassedIncorrectly,
};

/* Класс "Список" */
class List;

/* Класс "Узел списка" */
class Node
{
private:
	int m_Key;				// Ключ
	Node* m_Previous;		// Предыдущий
	Node* m_Next;			// Следующий

public:
	Node(int key = 0, Node* previous = 0, Node* next = 0);				// Конструктор по умолчанию

	int getKey();
	int& getLinkToKey();
	void setKey(int value);

	Node* getPreviousNode();
	void setPreviousNode(Node* next);

	Node* getNextNode();
	void setNextNode(Node* node);
};

/* Конструктор по умолчанию */
Node::Node(int key, Node* previous, Node* next)
{
	m_Key = key;
	m_Previous = previous;
	m_Next = next;
}

/*  */
int Node::getKey()
{
	return m_Key;
}

/*  */
int& Node::getLinkToKey()
{
	return m_Key;
}

/*  */
void Node::setKey(int value)
{
	m_Key = value;
}

/*  */
Node* Node::getPreviousNode()
{
	return m_Previous;
}

void Node::setPreviousNode(Node* next)
{
	m_Previous = next;
}

/*  */
Node* Node::getNextNode()
{
	return m_Next;
}

/*  */
void Node::setNextNode(Node* node)
{
	m_Next = node;
}

/* Класс "Список" */
class List
{
private:
	Node* m_Head;
	Node* m_Tail;

public:
	List();																// Конструктор по умолчанию
	List(int arraySize);												// Конструктор с параметром (формирование списка из n случайных чисел)
	List(int* listArray, int arraySize);								// Конструктор из массива int
	List(const List& other);											// Конструктор копирования

	~List();															// Деструктор

	friend ostream& operator << (ostream& os, List& list);				// Потоковый вывод
	friend istream& operator >> (istream& is, List& list);				// Потоковый ввод

	Node* searchKeyElement(int key);									// Поиск элемента по ключу

	void addToHead(int necessaryElement);								// Добавление элемента (в голову)

	void deleteTail();													// Удаление элемента (с хвоста)

	List& operator = (const List& other);								// Оператор присваивания

	int& operator [] (int keyElement);									// Получение ссылки на ключ элемента

	bool operator == (const List other);								// Оператор сравнения (проверка на равенство)
	bool operator != (const List other);								// Оператор сравнения (проверка на неравенство)

	bool isEmpty();														// Проверка списка на пустоту

	void inputList(int arraySize);										// Ввод списка (из n элементов)
	void printList();													// Вывод списка

	void clearList();													// Очистка списка
};

/* Конструктор по умолчанию */
List::List()
{
	m_Head = NULL;
	m_Tail = NULL;
}

/* Конструктор с параметром */
List::List(int arraySize)
{
	if (arraySize < 0)
	{
		throw errorArrayAdressNotPassed;
	}

	else if (arraySize == 0)
	{
		m_Head = NULL;
		m_Tail = NULL;
	}

	else
	{
		Node* pointer = NULL;
		pointer = new Node(rand());
		m_Head = pointer;

		for (int i = 1; i < arraySize; i++, pointer = pointer->getNextNode())
		{
			pointer->setNextNode(new Node(rand(), pointer));
		}

		m_Tail = pointer;
	}
}

/* Конструктор из массива int */
List::List(int* listArray, int arraySize)
{
	if (!listArray)
	{
		throw errorArrayAdressNotPassed;
	}

	if (arraySize < 0)
	{
		throw errorNumberOfArrayElementsWasPassedIncorrectly;
	}

	else if (arraySize == 0)
	{
		m_Head = NULL;
		m_Tail = NULL;
	}

	else
	{
		int i = 0;
		Node* pointer = NULL;
		pointer = new Node(listArray[i]);
		m_Head = pointer;

		for (i++; i < arraySize; i++, pointer = pointer->getNextNode())
		{
			pointer->setNextNode(new Node(listArray[i], pointer));
		}

		m_Tail = pointer;
	}
}

/* Конструктор копирования */
List::List(const List& other)
{
	if (other.m_Head)
	{
		Node* pointerA = other.m_Head;
		Node* pointerB = NULL;

		pointerB = new Node(pointerA->getKey());
		m_Head = pointerB;

		for (pointerA = pointerA->getNextNode(); pointerA; pointerA = pointerA->getNextNode(), pointerB = pointerB->getNextNode())
		{

			pointerB->setNextNode(new Node(pointerA->getKey(), pointerB));
		}

		m_Tail = pointerB;
	}

	else
	{
		m_Head = NULL;
		m_Tail = NULL;
	}
}

/* Деструктор */
List:: ~List()
{
	Node* pointer = m_Head;

	if (pointer)
	{
		while (pointer->getNextNode())
		{
			pointer = pointer->getNextNode();
			delete pointer->getPreviousNode();
		}

		delete pointer;
	}
}

/* Потоковый вывод */
ostream& operator << (ostream& os, List& list)
{
	Node* pointer = list.m_Head;

	while (pointer)
	{
		os << pointer->getKey() << " ";
		pointer = pointer->getNextNode();
	}

	return os;
}

/* Потоковый ввод */
istream& operator >> (istream& is, List& list)
{
	list.clearList();

	Node* pointer = list.m_Head;
	int number;

	while (pointer)
	{
		is >> number;

		pointer->setKey(number);
		pointer = pointer->getNextNode();
	}

	list.m_Head = pointer;

	return is;
}

/* Поиск элемента по ключу */
Node* List::searchKeyElement(int key)
{
	Node* pointer;

	for (pointer = m_Head; pointer && pointer->getKey() != key; pointer = pointer->getNextNode());

	return pointer;
}

/* Добавление элемента (в голову) */
void List::addToHead(int necessaryElement)
{
	if (m_Head)
	{
		Node* tmp = new Node(necessaryElement);
		tmp->setNextNode(m_Head);
		m_Head->setPreviousNode(tmp);
		m_Head = tmp;
	}

	else
	{
		m_Head = new Node(necessaryElement);
		m_Tail = m_Head;
	}
}

/* Удаление элемента (с хвоста) */
void List::deleteTail()
{
	if (m_Tail)
	{
		if (m_Tail->getPreviousNode())
		{
			m_Tail = m_Tail->getPreviousNode();

			if (m_Tail->getNextNode())
			{
				delete m_Tail->getNextNode();
				m_Tail->setNextNode(NULL);
			}
		}

		else
		{
			if (m_Tail)
			{
				delete m_Tail;
			}

			m_Tail = NULL;
			m_Head = NULL;
		}
	}
}

/* Оператор присваивания */
List& List:: operator = (const List& other)
{
	if (this == &other)
	{
		return *this;
	}

	clearList();

	Node* pointerA = other.m_Head;
	Node* pointerB = NULL;

	pointerB = new Node(pointerA->getKey());
	m_Head = pointerB;

	for (pointerA = pointerA->getNextNode(); pointerA; pointerA = pointerA->getNextNode(), pointerB = pointerB->getNextNode())
	{
		pointerB->setNextNode(new Node(pointerA->getKey(), pointerB));
	}

	m_Tail = pointerB;

	return *this;
}

/* Получение ссылки на ключ элемента */
int& List:: operator[] (int keyElement)
{
	Node* pointer = m_Head;
	int i;

	for (i = 0; pointer && i < keyElement; pointer = pointer->getNextNode(), i++);

	if ((i == keyElement) && pointer)
	{
		return pointer->getLinkToKey();
	}

	else
	{
		throw errorElementIndexWasPassedIncorrectly;
	}
}

/* Оператор сравнения (проверка на равенство) */
bool List:: operator == (const List other)
{
	Node* pointerA = m_Head;
	Node* pointerB = other.m_Head;

	for (; pointerA && pointerB && (pointerA->getKey()) == (pointerB->getKey()); pointerA = pointerA->getNextNode(), pointerB = pointerB->getNextNode());

	if (pointerA || pointerB)
	{
		return false;
	}

	return true;
}

/* Оператор сравнения (проверка на неравенство) */
inline bool List:: operator != (const List other)
{
	return !(*this == other);
}

/* Проверка списка на пустоту */
bool List::isEmpty()
{
	return m_Head == NULL;
}

/* Ввод списка */
void List::inputList(int arraySize)
{
	clearList();

	if (arraySize < 0)
	{
		throw errorArraySizeLessZero;
	}

	else if (arraySize > 0)
	{
		cout << "Вводите список: ";
		int number;
		cin >> number;

		Node* pointer = new Node(number);
		m_Head = pointer;

		for (int i = 1; i < arraySize; i++, pointer = pointer->getNextNode())
		{
			cin >> number;
			pointer->setNextNode(new Node(number, pointer));
		}

		m_Tail = pointer;
	}
}

/* Вывод списка */
void List::printList()
{
	Node* pointer = m_Head;

	while (pointer)
	{
		cout << pointer->getKey() << " ";
		pointer = pointer->getNextNode();
	}
}

/* Очистка списка */
void List::clearList()
{
	while (m_Head)
	{
		deleteTail();
	}
}

int main()
{
	try
	{
		setlocale(LC_ALL, "Rus");
		srand(unsigned(time(NULL)));

		/* Список 1*/
		cout << "Задайте голову списка 1: ";
		int newHeadList1;
		cin >> newHeadList1;

		cout << "Список 1: ";
		List lab_List_1;

		lab_List_1.addToHead(newHeadList1);
		lab_List_1.printList();

		cout << endl << endl;

		/* Список 2 */
		cout << "Задайте размерность списка 2: ";
		int sizeList2;
		cin >> sizeList2;

		List lab_List_2;

		lab_List_2.inputList(sizeList2);
		cout << "Список 2: ";
		lab_List_2.printList();

		cout << "\nСписок 2 после удаления хвоста: ";
		lab_List_2.deleteTail();
		lab_List_2.printList();

		cout << endl << endl;

		/* Список 3 */
		cout << "Задайте размерность списка 3: ";
		int sizeList3;
		cin >> sizeList3;

		List lab_List_3;

		lab_List_3.inputList(sizeList3);
		cout << "Список 3: ";
		lab_List_3.printList();

		cout << "\nСписок 3 после удаления хвоста: ";
		lab_List_3.deleteTail();
		lab_List_3.printList();

		cout << "\nЗадайте новую голову списка 3: ";
		int newHeadList3;
		cin >> newHeadList3;

		cout << "Список 3 после добавления элемента в голову: ";
		lab_List_3.addToHead(newHeadList3);
		lab_List_3.printList();

		cout << "\nВведите элемент, наличие которого в списке 3 необходимо проверить: ";
		int necessaryElement;
		cin >> necessaryElement;

		if (lab_List_3.searchKeyElement(necessaryElement))
		{
			cout << "Элемент " << necessaryElement << " присутствует в списке!";
		}

		else
		{
			cout << "Элемент " << necessaryElement << " отсутствует в списке!";
		}

		cout << "\nПроверка списка 3 на пустоту:\n";

		if (lab_List_3.isEmpty())
		{
			cout << "Список 3 пуст!\n";
		}

		else
		{
			cout << "Список 3 не пуст!\n";
		}

		cout << "Сравнение списка 2 и списка 3:\n";

		if (lab_List_2 == lab_List_3)
		{
			cout << "Списки равны!\n";
		}

		else
		{
			cout << "Списки не равны!\n";
		}
	}
	catch (Errors_and_Exceptions SomethingWentWrong)
	{
		return SomethingWentWrong;
	}

	cout << endl;
	system("pause");
	return 0;
}
