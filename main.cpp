import <iostream>;
import <format>;
import <array>;
import <vector>;
import employee;

using namespace std;
using namespace HR;

int main()
{
    // Create and populate an employee.
    Employee anEmployee{
        .firstInitial = 'J',
        .lastInitial = 'D',
        .employeeNumber = 42,
        .salary = 80000,
        .title = Title::SeniorEngineer
    };
    Employee anEmployee2{
        .firstInitial = 'H',
        .lastInitial = 'B',
        .employeeNumber = 43,
        .salary = 3000,
        .title = Title::Manager
    };
    Employee anEmployee3{
        .firstInitial = 'Q',
        .lastInitial = 'T',
        .employeeNumber = 48,
        .salary = 1500,
        .title = Title::SeniorEngineer
    };

    //array<Employee, 3> arr{ anEmployee, anEmployee2, anEmployee3 };
    vector<Employee> employees{};
    employees.push_back(anEmployee);
    employees.push_back(anEmployee2);
    employees.push_back(anEmployee3);

    // Output the values of an employee.
    for (const auto& anEmployee : employees) {
        cout << format("Employee: {}{}", anEmployee.firstInitial,
            anEmployee.lastInitial) << endl;
        cout << format("Number: {}", anEmployee.employeeNumber) << endl;
        cout << format("Salary: ${}", anEmployee.salary) << endl;

        cout << "Title: ";
        switch (anEmployee.title) {
            using enum Title;

        case Manager:
            cout << "Manager good for you!\n";
            break;
        case SeniorEngineer:
            cout << "Senior Engineer hello!\n";
            break;
        case Engineer:
            cout << "Engineer WoW!\n";
            break;
        }
    }
}