#include<iostream>

using namespace std;


class Task {
    int importance;  //from 1 to 10
    string name;
    string description;
public:
    bool operator==(Task& t)
    {
        return(importance == t.importance && name == t.name && description == t.description);
    }

    Task(int importance, string name, string description) : importance(importance), name(name), description(description) {}
    Task()= default;

    string get_name() { return name; }
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

    int get_index_login(string val)
    {
        if (size == 0)
        {
            cout << "Lista jest pusta" << endl;
            //exit(1);
        }

        for (int i = 0; i < size; i++)
        {
            if (get_node(i)->data.get_login() == val)
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
            head->prev = nullptr;
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

    int get_size()
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
    List<Task> completed_tasks;
public:
    explicit Project(string name): name(name) {}

    Project()= default;

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

    void delete_task_name(string name)
    {
        int index = tasks.get_index_name(name);
        Task temp = tasks.remove(index);
        completed_tasks.add_new(temp);
    }
};

class Account
{
    string login;
    string password;
    List<Project> projects;
    List<Project> completed_projects;
public:
    Account(string login, string password): login(login), password(password)
    {
        projects.add_new(Project("def_project"));
    }
    Account()= default;
    string get_login() {return login;}
    string get_password() {return password;}

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
        if (projects.is_empty())
            cout << "Nie posiadasz zadnych projektow, najpierw stworz projekt" << endl;
        else
        {
            cout << "Podaj nazwe projektu do ktorego chcesz dodac zadanie" << endl;
            string t_name;
            cin >> t_name;

            if (projects.get_index_name(t_name) == -1)
                cout << "Niema takiego projektu" << endl;
            else
            {
                Project temp = projects.get_node((projects.get_index_name(t_name)))->data;
                temp.create_task();
                cout << "Akcja zakonczona sukcesem!" << endl;
            }
        }
    }

    void delete_task()
    {
        if (projects.is_empty())
            cout << "Nie posiadasz zadnych projektow" << endl;
        else
        {
            cout << "Podaj nazwe projektu z ktorego chcesz usunac zadanie" << endl;
            string p_name;
            cin >> p_name;

            if (projects.get_index_name(p_name) == -1)
                cout << "Niema takiego projektu" << endl;
            else{
                Project temp = projects.get_node((projects.get_index_name(p_name)))->data;

                cout << "Podaj nazwe zadania ktore chcesz usunac" << endl;
                string t_name;
                cin >> t_name;
                temp.delete_task_name(t_name);
                cout << "Akcja zakonczona sukcesem!" << endl;
            }
        }
    }

    void create_project()
    {
        string name;
        cout << "Podaj nazwe nowego projektu" << endl;
        cin >> name;

        Project new_project = Project(name);
        projects.add_new(new_project);
        cout << "Akcja zakonczona sukcesem!" << endl;
    }

    void delete_project()
    {
        if (projects.is_empty())
            cout << "Nie posiadasz zadnych projektow" << endl;
        else
        {
            cout << "Podaj nazwe projektu z ktory chcesz usunac" << endl;
            string p_name;
            cin >> p_name;

            if (projects.get_index_name(p_name) == -1)
                cout << "Niema takiego projektu" << endl;
            else {
                projects.remove(projects.get_index_name(p_name));
                cout << "Akcja zakonczona sukcesem!" << endl;
            }

        }
    }
};

class Security{
    List<Account> accounts;
    Account def_acc = Account("login1", "password1");
public:
    Security(){accounts.add_new(def_acc);}

    int registration(string login, string password)
    {
        if(accounts.get_index_login(login) != -1)
        {
            cout << "Ten login jest zajety, prosze wybrac inny" << endl;
            return 1;
        }
        else
        {
            Account new_acc(login, password);
            accounts.add_new(new_acc);
            return 0;
        }
    }

    Account log_in(string login, string password)
    {
        int acc_index = accounts.get_index_login(login);

        if(acc_index == -1 || password != accounts.get_node(acc_index)->data.get_password())
        {
            cout << "Niepoprawny login lub haslo" << endl;
            throw (-1);
        }
        else
            return accounts.get_node(acc_index)->data;


    }
};

Account login_proccess(int input)
{
    Security security;

    string login;
    string password;

    bool log_flag = false;
    bool reg_flag = false;

    Account user;

    if(input == 1)
    {
        while(!log_flag)
        {
            cout << "Podaj login:";
            cin >> login;
            cout << "Podaj haslo:";
            cin >> password;

            try{
                user = security.log_in(login, password);
                log_flag = true;
            }
            catch (int error_code){}
        }
    }
    else if(input == 2)
    {
        while(!reg_flag)
        {
            cout << "Podaj login:";
            cin >> login;
            cout << "Podaj haslo:";
            cin >> password;
            if(security.registration(login, password) == 0)
            {
                reg_flag = true;
                security.log_in(login, password);
            }
        }
    }
    else
        exit(0);
    return user;
}

void app()
{
    int input;
    Account user;

    cout << "----------------------------------LOGIN----------------------------------" << endl;
    cout << "1 - Logowanie" << endl;
    cout << "2 - Rejestracja" << endl;
    cout << "inne - Wyjscie z programu" << endl;
    cout << "-------------------------------------------------------------------------" << endl;

    cin >> input;
    user = login_proccess(input);

    while(true)
    {
        cout << "----------------------------------Manual----------------------------------" << endl;
        cout << "1 - Dodaj zadanie" << endl;
        cout << "2 - Dodaj Projekt" << endl;
        cout << "3 - Usun zadanie" << endl;
        cout << "4 - Usun Projekt" << endl;
        cout << "5 - Zmien dane konta" << endl;
        cout << "6 - Czysc konsole" << endl;
        cout << "inne - Zakoncz program" << endl;
        cout << "-------------------------------------------------------------------------" << endl;

        cin >> input;

        switch (input) {
            case 1:
                user.add_task();
                break;
            case 2:
                user.create_project();
                break;
            case 3:
                user.delete_task();
                break;
            case 4:
                user.delete_project();
                break;
            case 5:
                user.change_data();
                break;
            case 6:
                //system("cls");
                break;
            default:
                exit(0);
        }
    }
}

int main()
{
    app();
    /*Account acc("login", "haslo");
    bool run_program = true;
    int input;

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

    return 0;*/
}


