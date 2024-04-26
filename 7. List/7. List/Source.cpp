/*
����� "������"

� ������ ������������ ��������� ����������� ��������� ��������� �������� ������������� ������ ����������� ���������� �������.

������ ����� ���� ��� ����������������, ��� � ���������������, �� ������ ����������.

��� ���������� ���������� ������� ��� ������: Node (���� ������) � List (��� ������).

����������� ������ ������:
- ������������ (�� ���������, � �����������, ����������� �� ������� int, ����������� �����������);
- ����������;
- ����/����� � ������� (���������);
- ����� �������� �� ����� (���������� ��������� �� ������� ��� nullptr, ���� �������� ��� � ������);
- ���������� �������� (� ������);
- �������� �������� (������).

����������� ����������:
- ������������ (=);
- ��������� ������ �� ���� �������� ([ ]);
- ��������� (==, !=).
*/

/* ��������������� ������ */

#include <iostream>
#include <time.h>
#include <cstdlib>
#include <cstring>
#include <locale>

using namespace std;

/* ��������� ���������� */
enum Errors_and_Exceptions
{
	/* ��� List */
	errorArraySizeLessZero,
	errorArrayAdressNotPassed,
	errorNumberOfArrayElementsWasPassedIncorrectly,
	errorElementIndexWasPassedIncorrectly,
};

/* ����� "������" */
class List;

/* ����� "���� ������" */
class Node
{
private:
	int m_Key;				// ����
	Node* m_Previous;		// ����������
	Node* m_Next;			// ���������

public:
	Node(int key = 0, Node* previous = 0, Node* next = 0);				// ����������� �� ���������

	int getKey();
	int& getLinkToKey();
	void setKey(int value);

	Node* getPreviousNode();
	void setPreviousNode(Node* next);

	Node* getNextNode();
	void setNextNode(Node* node);
};

/* ����������� �� ��������� */
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

/* ����� "������" */
class List
{
private:
	Node* m_Head;
	Node* m_Tail;

public:
	List();																// ����������� �� ���������
	List(int arraySize);												// ����������� � ���������� (������������ ������ �� n ��������� �����)
	List(int* listArray, int arraySize);								// ����������� �� ������� int
	List(const List& other);											// ����������� �����������

	~List();															// ����������

	friend ostream& operator << (ostream& os, List& list);				// ��������� �����
	friend istream& operator >> (istream& is, List& list);				// ��������� ����

	Node* searchKeyElement(int key);									// ����� �������� �� �����

	void addToHead(int necessaryElement);								// ���������� �������� (� ������)

	void deleteTail();													// �������� �������� (� ������)

	List& operator = (const List& other);								// �������� ������������

	int& operator [] (int keyElement);									// ��������� ������ �� ���� ��������

	bool operator == (const List other);								// �������� ��������� (�������� �� ���������)
	bool operator != (const List other);								// �������� ��������� (�������� �� �����������)

	bool isEmpty();														// �������� ������ �� �������

	void inputList(int arraySize);										// ���� ������ (�� n ���������)
	void printList();													// ����� ������

	void clearList();													// ������� ������
};

/* ����������� �� ��������� */
List::List()
{
	m_Head = NULL;
	m_Tail = NULL;
}

/* ����������� � ���������� */
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

/* ����������� �� ������� int */
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

/* ����������� ����������� */
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

/* ���������� */
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

/* ��������� ����� */
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

/* ��������� ���� */
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

/* ����� �������� �� ����� */
Node* List::searchKeyElement(int key)
{
	Node* pointer;

	for (pointer = m_Head; pointer && pointer->getKey() != key; pointer = pointer->getNextNode());

	return pointer;
}

/* ���������� �������� (� ������) */
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

/* �������� �������� (� ������) */
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

/* �������� ������������ */
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

/* ��������� ������ �� ���� �������� */
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

/* �������� ��������� (�������� �� ���������) */
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

/* �������� ��������� (�������� �� �����������) */
inline bool List:: operator != (const List other)
{
	return !(*this == other);
}

/* �������� ������ �� ������� */
bool List::isEmpty()
{
	return m_Head == NULL;
}

/* ���� ������ */
void List::inputList(int arraySize)
{
	clearList();

	if (arraySize < 0)
	{
		throw errorArraySizeLessZero;
	}

	else if (arraySize > 0)
	{
		cout << "������� ������: ";
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

/* ����� ������ */
void List::printList()
{
	Node* pointer = m_Head;

	while (pointer)
	{
		cout << pointer->getKey() << " ";
		pointer = pointer->getNextNode();
	}
}

/* ������� ������ */
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

		/* ������ 1*/
		cout << "������� ������ ������ 1: ";
		int newHeadList1;
		cin >> newHeadList1;

		cout << "������ 1: ";
		List lab_List_1;

		lab_List_1.addToHead(newHeadList1);
		lab_List_1.printList();

		cout << endl << endl;

		/* ������ 2 */
		cout << "������� ����������� ������ 2: ";
		int sizeList2;
		cin >> sizeList2;

		List lab_List_2;

		lab_List_2.inputList(sizeList2);
		cout << "������ 2: ";
		lab_List_2.printList();

		cout << "\n������ 2 ����� �������� ������: ";
		lab_List_2.deleteTail();
		lab_List_2.printList();

		cout << endl << endl;

		/* ������ 3 */
		cout << "������� ����������� ������ 3: ";
		int sizeList3;
		cin >> sizeList3;

		List lab_List_3;

		lab_List_3.inputList(sizeList3);
		cout << "������ 3: ";
		lab_List_3.printList();

		cout << "\n������ 3 ����� �������� ������: ";
		lab_List_3.deleteTail();
		lab_List_3.printList();

		cout << "\n������� ����� ������ ������ 3: ";
		int newHeadList3;
		cin >> newHeadList3;

		cout << "������ 3 ����� ���������� �������� � ������: ";
		lab_List_3.addToHead(newHeadList3);
		lab_List_3.printList();

		cout << "\n������� �������, ������� �������� � ������ 3 ���������� ���������: ";
		int necessaryElement;
		cin >> necessaryElement;

		if (lab_List_3.searchKeyElement(necessaryElement))
		{
			cout << "������� " << necessaryElement << " ������������ � ������!";
		}

		else
		{
			cout << "������� " << necessaryElement << " ����������� � ������!";
		}

		cout << "\n�������� ������ 3 �� �������:\n";

		if (lab_List_3.isEmpty())
		{
			cout << "������ 3 ����!\n";
		}

		else
		{
			cout << "������ 3 �� ����!\n";
		}

		cout << "��������� ������ 2 � ������ 3:\n";

		if (lab_List_2 == lab_List_3)
		{
			cout << "������ �����!\n";
		}

		else
		{
			cout << "������ �� �����!\n";
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
