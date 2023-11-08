#include<iostream>

using namespace std;


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

    Task(int importance, string name, string description) : importance(importance), id(rand() % 9999), name(name), description(description) {}
    Task(){}
    string get_name() { return name; }
    int get_id() { return id; }
};


template <typename T>
class Node {
public:
    T data;
    Node* next;
    Node* prev;

    Node(): next(nullptr), prev(nullptr){}
};

template <typename T>
class List {
    Node<T>* tail = nullptr;
    Node<T>* head = nullptr;
    int size = 0;

public:
    Node<T>* get_node(int index)
    {
        Node<T>* temp = head;
        for (int i = 0; i != index; i++)
        {
            temp = temp->next;
        }
        return temp;
    }

    void add_new(T x)
    {
        Node<T>* temp = new Node<T>;
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

    int get_index_name(string val)
    {
        if (size == 0)
        {
            cout << "Lista jest pusta" << endl;
            //exit(1);
        }

        for (int i = 0; i < size; i++)
        {
            if (get_node(i)->data.get_name() == val)
            {
                return i;
            }
        }
        return -1;
    }
    int get_index_id(int val)
    {
        if (size == 0)
        {
            cout << "Lista jest pusta" << endl;
            //exit(1);
        }

        for (int i = 0; i < size; i++)
        {
            if (get_node(i)->data.get_id() == val)
            {
                return i;
            }
        }
        return -1;
    }

    T remove(int index)
    {

        Node<T>* temp = get_node(index);
        T ret = temp->data;
        if (temp == tail && temp == head)
        {
            head = nullptr;
            tail = nullptr;
        }
        else if (temp == tail)
        {
            tail = temp->prev;
            tail->next = nullptr;
        }
        else if (temp == head)
        {
            head = temp->next;
            head->prev = nullptr;;
        }
        else
        {
            Node<T>* p_temp = temp->prev;
            Node<T>* n_temp = temp->next;

            p_temp->next = n_temp;
            n_temp->prev = p_temp;

        }
        delete(temp);
        size--;
        return ret;
    }

    int size_of_list()
    {
        return size;
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
    string name;
    List<Task> tasks;
    List<Task> compleated_tasks;
public:
    Project(string name): name(name) {}
    Project(){}
    string get_name() { return name; }
    void create_task()
    {
        int importance;
        string name;
        string description;
        cout << "Podaj parametry zadania: " << endl;
        cin >> importance;
        cin >> name;
        cin >> description;
        Task new_task(importance, name, description);
        tasks.add_new(new_task);
    }
    void delate_task_name(string name)
    {
        int index = tasks.get_index_name(name);
        Task temp = tasks.remove(index);
        compleated_tasks.add_new(temp);
    }
    void delate_task_name(int id)
    {
        int index = tasks.get_index_id(id);
        Task temp = tasks.remove(index);
        compleated_tasks.add_new(temp);
    }
};

class Account
{
    string login;
    string password;
    List<Project> list_of_projects;
public:
    Account(string login, string password): login(login), password(password)
    {
        list_of_projects.add_new(Project("def_project"));
    }

    void change_data()
    {
        string temp_l;
        string temp_p;

        cout << "Podaj aktualne login i password" << endl;

        cin >> temp_l;
        cin >> temp_p;

        if (temp_l == login && temp_p == password)
        {
            string new_l;
            string new_p;

            cout << "Podaj nowe login i haslo" << endl;

            cin >> new_l;
            cin >> new_p;

            login = new_l;
            password = new_p;
            cout << "Dane zostaly zaktualizowane" << endl;
        }
        else
            cout << "Niepoprawne dane" << endl;
    }

    void add_task()
    {
        if (list_of_projects.size_of_list() == 0)
            cout << "Nie posiadasz zadnych projektow, najpierw stworz projekt" << endl;
        else
        {
            cout << "Podaj nazwe projektu do ktorego chcesz dodac zadanie" << endl;
            string t_nazwa;
            cin >> t_nazwa;

            if (list_of_projects.get_index_name(t_nazwa) == -1)
            {
                cout << "Niema takiego projektu" << endl;
                exit(1);
            }

            Project temp = list_of_projects.get_node((list_of_projects.get_index_name(t_nazwa)))->data;
            temp.create_task();
        }
    }

    void create_project()
    {
        string name;
        cout << "Podaj nazwe nowego projektu" << endl;
        cin >> name;

        Project new_project = Project(name);
        list_of_projects.add_new(new_project);
    }
};

int main()
{
    Account acc("login", "haslo");
    bool run_program = true;
    int input;

    cout << "Manual:" << endl;
    cout << "1 - 'add task' - adds a new tast to a chosen project" << endl;
    cout << "2 - 'create project' creates a new project" << endl;
    cout << "3 - 'change user data' changes your login and password" << endl;
    cout << "4 - 'exit' ends the application" << endl;
    cout << "--------------------------------------------------------------------" << endl;

    while(run_program)
    {
        cin >> input;
        if(input == 1)
            acc.add_task();
        else if(input == 2)
            acc.create_project();
        else if(input == 3)
            acc.change_data();
        else if(input == 4)
            run_program = false;
        else
            cout << "Error" << endl;
    }

    return 0;
}