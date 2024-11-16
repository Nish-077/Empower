#include <bits/stdc++.h>
#include <fstream>
using namespace std;

class Employee
{

    string name;
    int employeeId;
    string position;
    int salary;
    long long phoneNumber;
    string email;
    string gender;

public:
    Employee(string name, int employeeId, string position, int salary, long long phoneNumber, string email, string gender)
    {
        this->name = name;
        this->employeeId = employeeId;
        this->position = position;
        this->salary = salary;
        this->phoneNumber = phoneNumber;
        this->email = email;
        this->gender = gender;
    }

    string getName() const
    {
        return name;
    }

    int getEmployeeId() const
    {
        return employeeId;
    }

    string getPosition() const
    {
        return position;
    }

    int getSalary() const
    {
        return salary;
    }

    long long getPhoneNumber() const
    {
        return phoneNumber;
    }

    string getEmail() const
    {
        return email;
    }

    string getGender() const
    {
        return gender;
    }

    // operator "<<" overloading
    friend ostream &operator<<(ostream &os, const Employee &employee)
    {
        os << "Name: " << employee.name << "\n"
           << "ID: " << employee.employeeId << "\n"
           << "Position: " << employee.position << "\n"
           << "Salary: " << employee.salary << "\n"
           << "Phone Number: " << employee.phoneNumber << "\n"
           << "Email: " << employee.email << "\n"
           << "Gender: " << employee.gender << "\n";
        return os;
    }
};

class EmployeeManagement
{
    vector<Employee *> employees;
    string filename;

public:
    EmployeeManagement(const string &filename) : filename(filename)
    {
        loadFromFile();
    }

    void loadFromFile()
    {
        employees.clear(); // Clear the current list of employees
        ifstream file(filename);
        string line;

        if (file.is_open())
        {
            while (getline(file, line))
            {
                stringstream ss(line);
                string name, position, email, gender;
                string employeeIdStr, salaryStr, phoneNumberStr;
                int employeeId, salary;
                long long phoneNumber;

                getline(ss, name, ',');
                getline(ss, employeeIdStr, ',');
                employeeId = stoi(employeeIdStr);
                getline(ss, position, ',');
                getline(ss, salaryStr, ',');
                salary = stoi(salaryStr);
                getline(ss, phoneNumberStr, ',');
                phoneNumber = stoll(phoneNumberStr);
                getline(ss, email, ',');
                getline(ss, gender, ',');

                employees.push_back(new Employee(name, employeeId, position, salary, phoneNumber, email, gender));
            }
        }
    }

    void addEmployee(Employee *employee)
    {
        employees.push_back(employee);

        // Open the file in append mode
        ofstream file(filename, ios::app);
        if (file.is_open())
        {
            file << employee->getName() << ","
                 << employee->getEmployeeId() << ","
                 << employee->getPosition() << ","
                 << employee->getSalary() << ","
                 << employee->getPhoneNumber() << ","
                 << employee->getEmail() << ","
                 << employee->getGender() << "\n";
        }
    }

    Employee *getEmployee(int employeeId)
    {
        loadFromFile();
        for (int i = 0; i < employees.size(); i++)
        {
            if (employees[i]->getEmployeeId() == employeeId)
            {
                return employees[i];
            }
        }
        return nullptr;
    }

    void listAllEmployees()
    {
        loadFromFile();
        if (employees.empty())
        {
            cout << "No employees found." << endl;
        }
        else
        {
            for (const auto &employee : employees)
            {
                cout << *employee << endl;
            }
        }
    }

    void updateEmployee(int employeeId, Employee *updatedEmployee)
    {
        loadFromFile();
        bool found = false;
        for (int i = 0; i < employees.size(); i++)
        {
            if (employees[i]->getEmployeeId() == employeeId)
            {
                delete employees[i];
                employees[i] = updatedEmployee;
                found = true;
                break;
            }
        }
        if (found)
        {
            ofstream file("employees.csv");
            for (const auto &employee : employees)
            {
                file << employee->getName() << ","
                     << employee->getEmployeeId() << ","
                     << employee->getPosition() << ","
                     << employee->getSalary() << ","
                     << employee->getPhoneNumber() << ","
                     << employee->getEmail() << ","
                     << employee->getGender() << "\n";
            }
            file.close();
        }
    }

    void removeEmployee(int employeeId)
    {
        loadFromFile();
        for (int i = 0; i < employees.size(); i++)
        {
            if (employees[i]->getEmployeeId() == employeeId)
            {
                delete employees[i];
                employees.erase(employees.begin() + i);
                break;
            }
        }
        ofstream file("employees.csv");
        for (const auto &employee : employees)
        {
            file << employee->getName() << ","
                 << employee->getEmployeeId() << ","
                 << employee->getPosition() << ","
                 << employee->getSalary() << ","
                 << employee->getPhoneNumber() << ","
                 << employee->getEmail() << ","
                 << employee->getGender() << "\n";
        }
        file.close(); // Close the file stream
    }
};

Employee *inputEmployee()
{
    string name;
    int employeeId;
    string position;
    int salary;
    long long phoneNumber;
    string email;
    string gender;

    cout << "Enter name: ";
    cin.ignore(); // Ignore the newline character in the input buffer
    getline(cin, name);

    cout << "Enter employee ID: ";
    cin >> employeeId;

    cout << "Enter position: ";
    cin.ignore();
    getline(cin, position);

    cout << "Enter salary: ";
    cin >> salary;

    cout << "Enter phone number: ";
    cin >> phoneNumber;

    cout << "Enter email: ";
    cin.ignore();
    getline(cin, email);

    cout << "Enter gender: ";
    cin.ignore();
    getline(cin, gender);

    return new Employee(name, employeeId, position, salary, phoneNumber, email, gender);
}

int main()
{
    EmployeeManagement em("employees.csv");

    while (true)
    {
        cout << "1. Add employee\n"
             << "2. Get employee\n"
             << "3. Update employee\n"
             << "4. Remove employee\n"
             << "5. List all employees\n"
             << "6. Exit\n"
             << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            Employee *e = inputEmployee();
            em.addEmployee(e);
            break;
        }
        case 2:
        {
            cout << "Enter the employee ID: ";
            int id;
            cin >> id;
            Employee *e = em.getEmployee(id);
            if (e != nullptr)
            {
                cout << "\n"
                     << *e << "\n";
            }
            else
            {
                cout << "No employee with the given ID was found.\n";
            }
            break;
        }
        case 3:
        {
            cout << "Enter the employee ID to update: ";
            int id;
            cin >> id;
            Employee *e = inputEmployee();
            em.updateEmployee(id, e);
            break;
        }
        case 4:
        {
            cout << "Enter the employee ID to remove: ";
            int id;
            cin >> id;
            em.removeEmployee(id);
            break;
        }
        case 5:
        {
            cout << "\n";
            em.listAllEmployees();
            break;
        }
        case 6:
            return 0;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 6.\n";
        }
    }
}