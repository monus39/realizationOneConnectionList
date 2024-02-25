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
	T& operator [] (const int index); // возвращать ИММЕННО ССЫЛКУ & because нам не только возвращать НО И МЕНЯТЬ ДАННЫЕ
	
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

		Node(T data = T(), Node* pNext = nullptr) // параметр по умолчанию ставится для последнего элемента // T()  
		{
			this->data = data;
			this->pNext = pNext;
		}
	};

	Node<T> *head; // начальный индекс // указатель ставится так как все элементы List будут в динамической памяти
	int Size;
};

template <typename T>
List<T>::List() //  так как класс стал шаблонным то конструкторы и методы выносятся через 
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
		Node<T>* current = this->head; // создаем ВРЕМЕННУЮ переменную  Node и закидываем ссылку последнего элемента 
		while (current->pNext != nullptr) // идем по всем нашим элементам пока переменная pNext == nullptr 
		{
			current = current->pNext; 
		}			// когда во временной переменной current в поле pNext будел nullptr ЗНАЧИТ ПОСЛЕДНИЙ и выходим из цикла
		current->pNext = new Node<T>(data); // последнему элементу вместо nullptr присваиваем адресс новой Node
	}
	Size++;
}

// Логика(нахождение нашего индекса и возвращение данных по нему): 
template<typename T>
T& List<T>::operator[](const int index)
{
	Node<T>* current = this->head; //
	int count = 0; // счетчик для определения где мы сейчас находится
	while (current != nullptr)
	{
		if (count == index)
		{
			return current->data;
		}
		current = current->pNext; // переходим к следующему элементу 
		count++; // и увеличиваем счетчик
	}
}

template<typename T>
void List<T>::pop_front()
{
	Node<T> *temp = head; // во временную переменную temp мы закинули указатель(*) head
	head = head->pNext; // а адресс следующего элемента  делаем head
	delete temp;
	Size--;
}

template<typename T>
void List<T>::clear()
{
	while (Size != 0) // когда Size не будет равен 0
	{
		pop_front();
	}
}

template<typename T>
void List<T>::push_frond()
{
	head = new Node<T>(data, head); // используем конструктор (если не понятно посмотреть в откладчике)
	Size++;

}

template<typename T>
void List<T>::insert(T value, int index)
{
	if (index == 0) // если вставить необходимо в 0 индекс
	{
		push_frond(value);
	}
	else
	{
		Node<T>* previous = this->head; // временный  указатель, так как не собираемся менять начальный элемент 
		for (int i = 0; i < index-1; i++) // доходим до предшествующего элемента, чтобы перекинуть ссылку на вставляемый
		{
			previous = previous->pNext; // закидываем в previous ссылку элемента после вставляевомого
		}
		Node<T>* newNode = new Node<T>(value, previous->pNext); // в новый вставляем значение и  ссылку последующего
		previous->pNext = newNode; // в предыдущий вставляем ссылку вставляевомого элемента
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

		Node<T>* toDelete = previos->pNext; // создали ссылку удаляемого элемента и поместили во ВРЕМЕННУЮ ПЕРЕМЕНУЮ

		previos->pNext = toDelete->pNext; // перекидываем в предшествующий элемент ссылку на предыдущий после удаляемого элемента 

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