#pragma once
#include <utility>
#include <iostream>
template <typename T>
class List
{
private:
	struct Node
	{
		T data;
		Node* previous;
		Node* next;
	};
	Node* head;
	Node* tail; 
	size_t size;

	void Copy(const List& other);
	void Move(List&& other) noexcept;

public:
	List();
	List(const List& other);
	List(List&& other) noexcept;

	~List();

	List& operator=(const List& other);
	List& operator=(List&& other) noexcept;

	void PushBack(const T& value);
	void PushFront(const T& value);

	void PopBack();
	void PopFront();

	T& Front();
	const T& Front() const;

	T& Back();
	const T& Back() const;

	void Remove(const T& value);
	bool Find(const T& value);

	void Reverse();
	void Clear();

	bool IsEmpty() const;
	size_t Size() const;
	void Show() const;
};
template <typename T>
void List<T>::Copy(const List<T>& other) {
	if (other.size == 0)
	{
		return;
	}
	head = new Node{ other.head->data, nullptr, nullptr };
	Node* current = head;
	Node* otherCurrent = other.head->next;

	while (otherCurrent != nullptr) {
		current->next = new Node{ otherCurrent->data, current, nullptr };
		current = current->next;
		otherCurrent = current->next;
	}
	size = other.size;
}
template <typename T>
List<T>::List<T>()
	:head(nullptr), tail(nullptr), size(0)
{ }
template <typename T>
List<T>::List<T>(const List<T>& other)
	: head(nullptr), tail(nullptr), size(0)
{
	if (other.size != 0) {
		Copy(other);
	}
}
template <typename T>
List<T>::List<T>(List<T>&& other) noexcept
{
	Move(std::move(other));
}
template <typename T>
List<T>::~List<T>() {
	Clear();
}
template <typename T>
typename List<T>& List<T>::operator=(const List<T>& other) {
	if (this != &other)
	{
		Clear();
		Copy(other);
	}
	return *this;
}
template <typename T>
typename List<T>& List<T>::operator=(List<T>&& other) noexcept {
	if (this != &other) {
		Clear();
		Move(std::move(other));
	}
	return *this;
}
template <typename T>
void List<T>::Move(List<T>&& other) noexcept {
	head = other.head;
	tail = other.tail;
	size = other.size;

	other.head = nullptr;
	other.tail = nullptr;
	other.size = 0;
}
template <typename T>
void List<T>::Clear() {
	while (head != nullptr) {
		Node* temp = head;
		head = head->next;
		delete temp;
	}
	tail = nullptr;
	size = 0;
}
template <typename T>
void List<T>::PushBack(const T& value) {
	if (size == 0)
	{
		head = new Node{ value, tail, nullptr };
		tail = head;
	}
	else {
		tail->next = new Node{ value, tail, nullptr };
		tail = tail->next;
	}
	size++;
}
template <typename T>
void List<T>::PushFront(const T& value) {
	if (size == 0) {
		head = new Node{ value, nullptr, nullptr };
		tail = head;
	}
	else
	{
		head = new Node{ value, nullptr, head };
		head->next->previous = head;
	}
	size++;
}
template <typename T>
void List<T>::PopBack() {
	if (size == 0)
	{
		return;
	}
	if (size == 1)
	{
		delete tail;
		head = nullptr;
		tail = nullptr;
	}
	else {
		Node* temp = tail;
		tail = tail->next;
		tail->next = nullptr;
		delete temp;
	}
	size--;
}
template <typename T>
void List<T>::PopFront() {
	if (size == 0) {
		return;
	}
	else if (size == 1) {
		delete head;
		head = nullptr;
		tail = nullptr;
	}
	else {
		Node* temp = head;
		head = head->next;
		delete temp;
	}
}
template <typename T>
T& List<T>::Front() {
	return head->data;
}
template <typename T>
const T& List<T>::Front() const {
	return head->data;
}
template <typename T>
T& List<T>::Back() {
	return tail->data;
}
template <typename T>
const T& List<T>::Back() const {
	return tail->data;
}
template <typename T>
bool List<T>::IsEmpty() const {
	return size == 0;
}
template <typename T>
bool List<T>::Find(const T& value) {
	Node* current = head;

	while (current != nullptr) {
		if (current->data == value)
		{
			return true;
		}
		current = current->next;
	}
	return false;
}
template <typename T>
size_t List<T>::Size() const {
	return size;
}
template <typename T>
void List<T>::Remove(const T& value) {
	Node* current = head;
	while (current != nullptr) {
		if (current->data == value) {
			if (head == current)
			{
				if (size == 1) {
					delete head;
					head = nullptr;
					tail = nullptr;
				}
				else
				{
					Node* temp = head;
					head = head->next;
					head->previous = nullptr;
					delete temp;
				}
			}
			else if (tail == current) {
				Node* temp = tail;
				tail = tail->previous;
				tail->next = nullptr;
				delete temp;
			}
			else {
				current->previous->next = current->next;
				current->next->previous = current->previous;
				delete current;
			}

			size--;
			return;
		}

		current = current->next;
	}
}
template <typename T>
void List<T>::Reverse() {
	tail = head;

	Node* current = head;
	Node* temp = nullptr;
	while (current != nullptr) {
		temp = current->previous;
		current->previous = current->next;
		current->next = temp;

		current = current->previous;
	}
	if (temp != nullptr)
	{
		head = temp->previous;
	}
}
template <typename T>
void List<T>::Show() const {
	if (size == 0) {
		std::cout << "List is empty\n";
		return;
	}

	Node* current = head;

	while (current != nullptr) {
		std::cout << current->data << " ";
		current = current->next;
	}

	std::cout << std::endl;
}
