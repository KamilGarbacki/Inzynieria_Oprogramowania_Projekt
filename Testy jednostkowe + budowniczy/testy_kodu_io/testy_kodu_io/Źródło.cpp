#include <iostream>
#include <utility>
#include <vector>
#include <typeinfo>

using namespace std;

class Task {
    int priority;
    string name;
    string description;
public:
    bool operator==(Task& t) {
        return(priority == t.priority && name == t.name && description == t.description);
    }

    Task(int priority, string name, string description) : priority(priority), name(std::move(name)), description(std::move(description)) {}
    Task() = default;

    string get_name() { return name; }

    void set_name(string n) { this->name = n; }
    void set_description(string d) { this->description = d; }
    void set_priority(int p) { this->priority = p; }
};

class Task_Builder {
    virtual void build_name() = 0;
    virtual void build_description() = 0;
    virtual void build_priority() = 0;
    virtual Task get_task() const = 0;
};

class Simple_Task_Builder : Task_Builder{
    Task task;
public:
    void build_name() override {
        task.set_name("simple_task");
    }
    void build_description() override{
        task.set_description("a simple task for tests");
    }
    void build_priority() override {
        task.set_priority(2);
    }
    Task get_task() const override {
        return task;
    }
};


class Project {
    string name;
    vector<Task> tasks;
public:
    bool operator==(Project& p) {
        return(name == p.name);
    }

    explicit Project(string name) : name(std::move(name)) {
        tasks.emplace_back(1, "def_task", "def_description");
    }
    Project() = default;

    string get_name() { return name; }

    void add_task(Task& t) {
        tasks.push_back(t);
    }

    void delate_task(string name) {
        for (int i = 0; i < tasks.size(); ++i) {
            if (tasks[i].get_name() == name) {
                tasks.erase(tasks.begin() + i);
            }
        }


    }

    void display_tasks() {
        for (auto& task : tasks) {
            cout << task.get_name() << endl;
        }
    }

    int check_for_task(string name) {
        for (int i = 0; i < tasks.size(); i++){
            if (tasks[i].get_name() == name) {
                return 1;
            }
        }
        return 0;
    }
};

class Account {
    string log;
    string pass;

    vector<Project> projects;

    Project* get_project(string name) {
        for (auto& project : projects) {
            if (project.get_name() == name)
            {
                return &project;
            }
        }
        return nullptr;
    }

public:
    Account(string log, string pass) : log(std::move(log)), pass(std::move(pass)) {
        projects.emplace_back("def_project");
    }
    Account() = default;

    string get_log() { return log; }
    string get_pass() { return pass; }


    Project check_for_project(string name) {
        for (auto& project : projects) {
            if (project.get_name() == name)
            {
                return project;
            }
        }
        return Project("null");
    }

    void update_data() {
        string curr_l;
        string curr_p;

        cout << "Podaj aktualne login i haslo" << endl;
        cin >> curr_l;
        cin >> curr_p;

        if (curr_l == log && curr_p == pass) {
            string new_l;
            string new_p;

            cout << "Podaj nowy login i haslo" << endl;

            cin >> new_l;
            cin >> new_p;

            log = new_l;
            pass = new_p;

            cout << "Dane zostaly zaktualizowane" << endl;
        }
    }

    void create_project(Project p) {
        //cout << "Podaj nazwe nowego projektu" << endl;
        //string name;
        //cin >> name;
        //Project new_p(name);
        projects.push_back(p);
    }

    void delete_project() {
        if (projects.empty()) {
            cout << "Nie posiadasz zadnych projektow" << endl;
        }
        else {
            cout << "Podaj nazwe projektu do usuniecia" << endl;
            string name;
            cin >> name;

            for (int i = 0; i < projects.size(); ++i) {
                if (projects[i].get_name() == name) {
                    projects.erase(projects.begin() + i);
                }
            }

        }
    }

    void create_task(string p_name, string t_name, int t_priority, string t_description) {
        cout << "Podaj nazwe projektu do ktorego chcesz dodac zadanie" << endl;
        //string name;
        //cin >> name;

        Project* p_temp = get_project(p_name);
        if (p_temp == nullptr)
        {
            cout << "Nie ma takiego projektu" << endl;
        }
        else {
            cout << "Podaj parametry (nazwa, waga, opis)" << endl;
            //string t_name;
            //string t_description;
            //int t_priority;
            //cin >> t_name;
            //cin >> t_priority;
            //cin >> t_description;
            Task t_temp(t_priority, t_name, t_description);
            p_temp->add_task(t_temp);
        }
    }

    void delete_task(string project_name, string task_name) {
        cout << "Podaj nazwe projektu z ktorego chcesz usunac zadanie" << endl;
        //string name;
        //cin >> name;

        Project* p_temp = get_project(project_name);
        if (p_temp == nullptr)
        {
            cout << "Nie ma takiego projektu" << endl;
        }
        else {
            cout << "Podaj nazwe zadania" << endl;
            //string t_name;
            //cin >> t_name;
            p_temp->delate_task(task_name);
        }
    }

    void display_projects() {
        for (auto& project : projects) {
            cout << project.get_name() << endl;
        }
    }

    void display_project_data() {
        cout << "Podaj nazwe projektu z z ktorego chcesz wyswietlic zadania" << endl;
        string name;
        cin >> name;

        Project* p_temp = get_project(name);
        if (p_temp == nullptr)
        {
            cout << "Nie ma takiego projektu" << endl;
        }
        else {
            p_temp->display_tasks();
        }
    }
};

class Users_database {
protected:
    vector<Account> accounts;
    vector<Account> admins;
};

class Admin_acc : public Account, public Users_database {
    string log;
    string pass;
public:
    Admin_acc(string log, string pass) : log(std::move(log)), pass(std::move(pass)) {}
    Admin_acc() = default;
    void display_users() {
        for (auto& account : accounts) {
            cout << account.get_log() << ", " << account.get_pass() << endl;
        }
    }

    void ban_user() {
        cout << "Podaj login uzytkownika ktorego chcesz usunac" << endl;
        string log_temp;
        string pass_temp;

        for (int i = 0; i < accounts.size(); ++i) {
            if (accounts[i].get_log() == log_temp && accounts[i].get_pass() == pass_temp)
                accounts.erase(accounts.begin() + i);
        }
    }
};

class Security : Users_database {
public:
    Security() {
        Account def_acc("def_log", "def_pass");
        Admin_acc admin("admin1", "admin1");
        accounts.push_back(def_acc);
        admins.push_back(admin);
    }

    int registration(string log, string pass) {
        int error_flag = 0;

        for (auto& account : accounts) {
            if (account.get_log() == log && account.get_pass() == pass)
            {
                error_flag = 1;
            }
        }

        if (error_flag == 0) {
            Account new_acc(log, pass);
            accounts.push_back(new_acc);
        }
        return error_flag;
    }

    Account log_in(string log, string pass) {
        for (auto& admin : admins) {
            if (admin.get_log() == log && admin.get_pass() == pass)
                return admin;
        }
        for (auto& account : accounts) {
            if (account.get_log() == log && account.get_pass() == pass)
                return account;
        }
        cout << "Niepoprawne dane" << endl;
        return Account("error", "error");
    }

    Account log_reg_process(int input) {
        string log;
        string pass;

        bool log_flag = false;
        bool reg_flag = false;

        Account user;

        if (input == 1) {
            while (!log_flag) {
                cout << "Podaj login:";
                cin >> log;
                cout << "Podaj haslo:";
                cin >> pass;

                /*try {
                    user = log_in(log, pass);
                    log_flag = true;
                }
                catch (int error_code) {}*/
            }
        }
        else if (input == 2) {
            while (!reg_flag) {
                cout << "Podaj login:";
                cin >> log;
                cout << "Podaj haslo:";
                cin >> pass;

                if (registration(log, pass) == 0) {
                    user = log_in(log, pass);
                    reg_flag = true;
                }
            }
        }
        else exit(0);

        return user;
    }
};

void app()
{
    int input;
    Account user;
    Security app_system;

    cout << "----------------------------------LOGIN----------------------------------" << endl;
    cout << "1 - Logowanie" << endl;
    cout << "2 - Rejestracja" << endl;
    cout << "inne - Wyjscie z programu" << endl;
    cout << "-------------------------------------------------------------------------" << endl;

    cin >> input;
    user = app_system.log_reg_process(input);

    while (true)
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
            //user.create_task();
            break;
        case 2:
            //user.create_project();
            break;
        case 3:
            //user.delete_task();
            break;
        case 4:
            user.delete_project();
            break;
        case 5:
            user.update_data();
            break;
        case 6:
            system("cls");
            break;
        default:
            exit(0);
        }
    }
}

int main() {
    app();
}
