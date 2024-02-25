#include <iostream>
#include <string>
#include <memory>

template <typename T>
class List
{
public:
	List();
	~List();

	void push_back(T data);
	int GetSize() { return Size; }
	T& operator [] (const int index); // ���������� ������� ������ & because ��� �� ������ ���������� �� � ������ ������
	
	void pop_front();
	void clear();

	void push_frond();
	void insert(T value, int index);
	void removeAt(int index);
	void pop_back();

private:

	template <typename T>
	class Node
	{
	public:
		Node* pNext;
		T data;

		Node(T data = T(), Node* pNext = nullptr) // �������� �� ��������� �������� ��� ���������� �������� // T()  
		{
			this->data = data;
			this->pNext = pNext;
		}
	};

	Node<T> *head; // ��������� ������ // ��������� �������� ��� ��� ��� �������� List ����� � ������������ ������
	int Size;
};

template <typename T>
List<T>::List() //  ��� ��� ����� ���� ��������� �� ������������ � ������ ��������� ����� 
{
	Size = 0;
	head = nullptr;
}

template <typename T>
List<T>::~List()
{
	std::cout << "DESTRUCTOR " << std::endl;
	clear();
}

template<typename T>
void List<T>::push_back(T data)
{
	if (head == nullptr)
	{
		head = new Node<T>(data);
	}
	else
	{
		Node<T>* current = this->head; // ������� ��������� ����������  Node � ���������� ������ ���������� �������� 
		while (current->pNext != nullptr) // ���� �� ���� ����� ��������� ���� ���������� pNext == nullptr 
		{
			current = current->pNext; 
		}			// ����� �� ��������� ���������� current � ���� pNext ����� nullptr ������ ��������� � ������� �� �����
		current->pNext = new Node<T>(data); // ���������� �������� ������ nullptr ����������� ������ ����� Node
	}
	Size++;
}

// ������(���������� ������ ������� � ����������� ������ �� ����): 
template<typename T>
T& List<T>::operator[](const int index)
{
	Node<T>* current = this->head; //
	int count = 0; // ������� ��� ����������� ��� �� ������ ���������
	while (current != nullptr)
	{
		if (count == index)
		{
			return current->data;
		}
		current = current->pNext; // ��������� � ���������� �������� 
		count++; // � ����������� �������
	}
}

template<typename T>
void List<T>::pop_front()
{
	Node<T> *temp = head; // �� ��������� ���������� temp �� �������� ���������(*) head
	head = head->pNext; // � ������ ���������� ��������  ������ head
	delete temp;
	Size--;
}

template<typename T>
void List<T>::clear()
{
	while (Size != 0) // ����� Size �� ����� ����� 0
	{
		pop_front();
	}
}

template<typename T>
void List<T>::push_frond()
{
	head = new Node<T>(data, head); // ���������� ����������� (���� �� ������� ���������� � ����������)
	Size++;

}

template<typename T>
void List<T>::insert(T value, int index)
{
	if (index == 0) // ���� �������� ���������� � 0 ������
	{
		push_frond(value);
	}
	else
	{
		Node<T>* previous = this->head; // ���������  ���������, ��� ��� �� ���������� ������ ��������� ������� 
		for (int i = 0; i < index-1; i++) // ������� �� ��������������� ��������, ����� ���������� ������ �� �����������
		{
			previous = previous->pNext; // ���������� � previous ������ �������� ����� ��������������
		}
		Node<T>* newNode = new Node<T>(value, previous->pNext); // � ����� ��������� �������� �  ������ ������������
		previous->pNext = newNode; // � ���������� ��������� ������ �������������� ��������
		Size++;
	}
}

template<typename T>
void List<T>::removeAt(int index)
{
	if (index == 0)
	{
		pop_front();
	}
	else
	{
		Node<T>* previos = this->head;
		for (int i = 0; i <index-1; i++)
		{
			previos = previos->pNext;
		}

		Node<T>* toDelete = previos->pNext; // ������� ������ ���������� �������� � ��������� �� ��������� ���������

		previos->pNext = toDelete->pNext; // ������������ � �������������� ������� ������ �� ���������� ����� ���������� �������� 

		delete toDelete;
		Size--;

	}
}

template<typename T>
void List<T>::pop_back()
{
	removeAt(Size - 1);
}







int main()
{
	setlocale(LC_ALL, "ru");

	List < int> lst;


	lst.push_back(7);
	lst.push_back(3);
	lst.push_back(22);

	std::cout << lst[2] << std::endl;

	lst.pop_front();

	for (int i = 0; i < lst.GetSize(); i++)
	{
		std::cout << lst[i] << std::endl;
	}





	//std:: shared_ptr<int> 
	return 0;
}