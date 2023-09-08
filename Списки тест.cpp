#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

template<typename T>
class List {
public:
	List();
	~List();

	void print();	//Вивести на екран усі елементи списку
	void push_back(T data);		//Додати елемент в кунець списку
	void swap(int index1, int index2, int size);	//Поміняти місцями два елементи вибрані користувачем
	void remove_at(int index, int size);	//Видалити зі списку елемент вибраний користувачем
	void clear();	//Видалити всі елементи зі списку
	T& operator[](const int index);
	
private:

	template<typename T>
	class Node {
	public:
		Node* pNext;
		T data;

		Node(T data = T(), Node* pNext = nullptr) {
			this->data = data;
			this->pNext = pNext;
		}
	};
	int Size;
	Node<T> *head;
};

template<typename T>
List<T>::List() {
	Size = 0;
	head = nullptr;
}

template<typename T>
List<T>::~List() {

}

template<typename T>
void List<T>::push_back(T data) {	//Додавання елемента в кінець списку
	if (head == nullptr) {
		head = new Node<T>(data);
	}
	else {
		Node<T>* current = this->head;
		while (current->pNext != nullptr) {
			current = current->pNext;
		}
		current->pNext = new Node<T>(data);
	}
	Size++;
}

template<typename T>
void List<T>::swap(int index1, int index2, int size){	//Поміняти місцями два елементи вибрані користувачем 
	if (index1 < 0 || index2 < 0 || index1 > size || index2 > size) {
		cout << "Invalid replacement indexes" << endl;
		return;
	}

	if (index1 == index2) {
		cout << "This indexes are the same\n";
		return;
	}

	Node<T>* prev1 = nullptr;
	Node<T>* current1 = head;
	for (int i = 0; i < index1; i++) {
		prev1 = current1;
		current1 = current1->pNext;
	}

	Node<T>* prev2 = nullptr;
	Node<T>* current2 = head;
	for (int i = 0; i < index2; i++) {
		prev2 = current2;
		current2 = current2->pNext;
	}

	if (prev1) {
		prev1->pNext = current2;
	}
	else {
		head = current2;
	}

	if (prev2) {
		prev2->pNext = current1;
	}
	else {
		head = current1;
	}

	Node<T>* temp = current1->pNext;
	current1->pNext = current2->pNext;
	current2->pNext = temp;
}

template<typename T>
void List<T>::remove_at(int index, int size) {	//Видалити вибраний користувачем елемент
	if (index < 0 || index >= size) {
		cout << "Invalid index for removal" << endl;
		return;
	}

	if (index == 0) {
		Node<T>* temp = head;
		head = head->pNext;
		delete temp;
	}
	else {
		Node<T>* prev = nullptr;
		Node<T>* current = head;
		for (int i = 0; i < index; i++) {
			prev = current;
			current = current->pNext;
		}

		prev->pNext = current->pNext;
		delete current;
	}

	size--;
	
}

template<typename T>
void List<T>::clear() {		//Видалити усі елементи списку
	while (head != nullptr) {
		Node<T>* temp = head;
		head = head->pNext;
		delete temp;
	}
	Size = 0;

	cout << "All elements are deleted\n";
}

template<typename T>
void List<T>::print() {		//Вивести на єкран усі елементи списку
	Node<T>* current = head;
	
	if (current == nullptr) {
		cout << "No Elements\n";
		return;
	}
	int index = 0;
	while (current != nullptr) {
		cout << index++ << ": ";
		cout << current->data << "\t\t";
		current = current->pNext;
	}
	cout << endl;
}

template<typename T>
T& List<T>::operator[](const int index)
{
	int counter = 0;
	Node<T>* current = this->head;



	while (current != nullptr) {
		if (counter == index) {
			return current->data;
		}

		current = current->pNext;
		counter++;

	}
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	List<float> lst;

	int choise = 1;
	int size = 0;
	do{
		std::cout << "\nВиберіть операцію\n"
			<< "Додати елемент - 1\n"
			<< "Вивести список на екран - 2\n"
			<< "Вивести елемент списку за його індексом - 3\n"
			<< "Поміняти елементи місцями за їх індексами - 4\n"
			<< "Вивести поточний розмір списку - 5\n"
			<< "Видалити елемент списку за його індексом - 6\n" 
			<< "Видалити увесь список - 7\n"
			<< "Завершення роботи програми - 0\n";
		cout << "\n\tYour choise: ";
		cin >> choise;
		cout << "\nResult:\n";

		switch (choise) {
		case 1:
			float newElement;
			std::cout << "Enter your element: ";
			cin >> newElement;
			lst.push_back(newElement);
			size++;
			break;
		case 2:
			cout << "\n\t";
			lst.print();
			break;
		case 3:
			int indexElement;
			cout << "Element index: ";
			cin >> indexElement;
			if (indexElement >= size) {
				cout << "\n\tError!No element.\n";
			}
			else
				cout << "\t" << lst[indexElement] << endl;
			break;
		case 4:
			int indexElement1, indexElement2;
			cout << "First element index: ";
			cin >> indexElement1;
			cout << "Second element index: ";
			cin >> indexElement2;
			lst.swap(indexElement1, indexElement2, size);
			break;
		case 5:
			cout << "Size of list: " << size << endl;
			break;
		case 6:
			int indexRemove;
			cout << "Index of element to be removed: ";
			cin >> indexRemove;
			lst.remove_at(indexRemove, size);
			size--;
			break;
		case 7:
			lst.clear();
			break;
		default:
			cout << "\n\tError. Wrong choise\n";
		}
	} while (choise != 0);

	return 0;
}