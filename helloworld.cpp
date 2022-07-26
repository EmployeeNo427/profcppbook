// helloworld.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

import <iostream>;
import <format>;
import <vector>;
import <utility>;
import <string>;
//import employee;

using namespace std;

int addNumbers(int a, int b) { return a + b; }
double addNumbers(double a, double b) { return a + b; }


int main()
{
    //// Create and populate an employee.
    //Employee anEmployee;
    //anEmployee.firstInitial = 'J';
    //anEmployee.lastInitial = 'D';
    //anEmployee.employeeNumber = 42;
    //anEmployee.salary = 80000;
    //// Output the values of an employee.
    //cout << format("Employee: {}{}", anEmployee.firstInitial,
    //    anEmployee.lastInitial) << endl;
    //cout << format("Number: {}", anEmployee.employeeNumber) << endl;
    //cout << format("Salary: ${}", anEmployee.salary) << endl;
    // Create a vector of integers.
    vector<int> myVector{ 11, 22 };

    // Add some more integers to the vector using push_back().
    myVector.push_back(33);
    myVector.push_back(44);

    // Access elements.
    cout << format("1st element: {}", myVector[0]) << endl;

    pair myPair{ 1.23,5 };
    cout << format("{} {}", myPair.first, myPair.second);

    string myString{ "Hello, World" };
    cout << format("The value of myString is {}", myString) << endl;
    cout << format("The second letter is {}", myString[1]) << endl;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
