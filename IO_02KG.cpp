#include<iostream>

using namespace std;

template <typename T>
class Node {
public:
	T data;
	Node* next;
	Node* prev;

	Node() : next(nullptr), prev(nullptr) {}
};

class List_of_projects {
	Node<Project>* tail = nullptr;
	Node<Project>* head = nullptr;
	int size = 0;
public:
	void add_new(Project x)
	{
		Node<Project>* temp = new Node<Project>;
		temp->data = x;

		if (tail == nullptr)
		{
			tail = temp;
			head = temp;
		}
		else
		{
			tail->next = temp;
			temp->prev = tail;
			tail = temp;
		}
		size++;
	}

	Node<Project>* get_node(int index)
	{
		Node<Project>* temp = tail;
		for (int i = 0; i != index; i++)
		{
			temp = temp->prev;
		}
		return temp;
	}

	void remove_val(Project val)
	{
		if (size == 0)
		{
			cout << "Lista jest pusta" << endl;
			return;
		}

		for (int i = 0; i < size; i++)
		{
			if (get_node(i)->data == val)
			{
				remove(i);
			}
		}
	}

	void remove(int val)
	{

		Node<Project>* temp = get_node(val);
		if (temp == tail && temp == head)
		{
			delete(temp);
			head = nullptr;
			tail = nullptr;
		}
		else if (temp == tail)
		{
			tail = temp->prev;
			tail->next = nullptr;
			delete(temp);
		}
		else if (temp == head)
		{
			head = temp->next;
			head->prev = nullptr;
			delete(temp);
		}
		else
		{
			Node<Project>* p_temp = temp->prev;
			Node<Project>* n_temp = temp->next;

			p_temp->next = n_temp;
			n_temp->prev = p_temp;
		}
		size--;
	}
	void size_of_list()
	{
		cout << "Rozmiar listy to: " << size << endl;
	}

	bool is_empty()
	{
		if (size == 0)
			return true;
		else
			return false;

	}
};

class Project {
	Node<Task>* tail = nullptr;
	Node<Task>* head = nullptr;
	int size = 0;
public:
	bool operator==(Project& p)
	{
		if (size != p.size)
			return false;
		else
		{
			for (int i = 0; i < size; i++)
			{
				return(get_node(i)->data == p.get_node(i)->data);
			}
		}
	}
	void add_new(Task x)
	{
		Node<Task>* temp = new Node<Task>;
		temp->data = x;

		if (tail == nullptr)
		{
			tail = temp;
			head = temp;
		}
		else
		{
			tail->next = temp;
			temp->prev = tail;
			tail = temp;
		}
		size++;
	}

	Node<Task>* get_node(int index)
	{
		Node<Task>* temp = tail;
		for (int i = 0; i != index; i++)
		{
			temp = temp->prev;
		}
		return temp;
	}

	void remove_val(Task val)
	{
		if (size == 0)
		{
			cout << "Lista jest pusta" << endl;
			return;
		}

		for (int i = 0; i < size; i++)
		{
			if (get_node(i)->data == val)
			{
				remove(i);
			}
		}
	}

	void remove(int val)
	{

		Node<Task>* temp = get_node(val);
		if (temp == tail && temp == head)
		{
			delete(temp);
			head = nullptr;
			tail = nullptr;
		}
		else if (temp == tail)
		{
			tail = temp->prev;
			tail->next = nullptr;
			delete(temp);
		}
		else if (temp == head)
		{
			head = temp->next;
			head->prev = nullptr;
			delete(temp);
		}
		else
		{
			Node<Task>* p_temp = temp->prev;
			Node<Task>* n_temp = temp->next;

			p_temp->next = n_temp;
			n_temp->prev = p_temp;
		}
		size--;
	}


};

class Task {
	int importance;  //from 1 to 10
	int id;
	string name;
	string description;
public:
	bool operator==(Task& t)
	{
		return(id == t.id && importance == t.importance && name == t.name && description == t.description);
		
	}
};

int main()
{

}