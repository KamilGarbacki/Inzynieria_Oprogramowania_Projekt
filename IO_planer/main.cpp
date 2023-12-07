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


    void write_list()
    {
        for (int i = 0; i < size; ++i) {
            Node<T>* temp = get_node(i);
            cout << i << "." << temp->data.name << endl;
        }
    }

    void write_tasks()
    {
        for (int i = 0; i < size; ++i) {
            Node<T>* temp = get_node(i);
            cout << i << "." << temp->data.name << endl;
            cout << "-waznosc: " << temp->data.importance << "/10" << endl;
            cout << "-opis: " << temp->data.description;
        }
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

    void create_task() //KG
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
protected:
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

    void change_data() //KG
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

    void add_task() //KG
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

    string input_project_data()
    {
        string name;
        cout << "Podaj nazwe nowego projektu" << endl;
        cin >> name;
        return name;
    }

    void create_project()
    {
        string name = input_project_data();

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
    static List<Account> accounts;
    static List<Account> admins;
    Account def_acc = Account("login1", "password1");
public:
    Security(){accounts.add_new(def_acc);}

    friend class Admin_acc;

    void add_admin(Account temp)
    {
        admins.add_new(temp);
    }

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
        int admin_acc_index = admins.get_index_login(login);

        if(admin_acc_index == -1 || password != accounts.get_node(admin_acc_index)->data.get_password())
        {
            int user_acc_index = accounts.get_index_login(login);

            if(user_acc_index == -1 || password != accounts.get_node(user_acc_index)->data.get_password())
            {
                cout << "Niepoprawny login lub haslo" << endl;
                throw (-1);
            }
            else
                return accounts.get_node(user_acc_index)->data;
        }
        else
            return admins.get_node(admin_acc_index)->data;

    }
};

class Admin_acc : public Account
{
public:
    Admin_acc(string log, string pass)
    {
        login = log;
        password = pass;
        projects.add_new(Project("def_project"));
    }

    int add_new_admin(string login, string password)
    {
        if(Security::admins.get_index_login(login) != -1)
        {
            cout << "Ten login jest zajety, prosze wybrac inny" << endl;
            return 1;
        }
        else
        {
            Admin_acc new_acc(login, password);
            Security::admins.add_new(new_acc);
            return 0;
        }
    }

    void ban_user()
    {
        if (Security::admins.is_empty())
            cout << "W bazie danych nie ma zarejestrowanych uzytkownikow" << endl;
        else
        {
            cout << "Podaj login konta ktore chcesz usunac" << endl;
            string p_name;
            cin >> p_name;

            if (Security::admins.get_index_login(p_name) == -1)
                cout << "Niema takiego konta" << endl;
            else {
                projects.remove(Security::admins.get_index_login(p_name));
                cout << "Akcja zakonczona sukcesem!" << endl;
            }

        }
    }
};

Account login_proccess(int input)
{
    Security security;
    Admin_acc temp ("admin1", "login1");
    security.add_admin(temp);


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
                system("cls");
                break;
            default:
                exit(0);
        }
    }
}

int main()
{
    app();

    return 0;
}


