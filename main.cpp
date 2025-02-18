/* This is a multiline comment.
   The compiler will ignore it.
 */
 // helloworld.cpp



import airline_ticket;
import hello_world;
import employee;
import exercise_employee;
import database;
import spreadsheet_cell;
import Spreadsheet;
import person;
import ch12_exercise;
import ch13_example;
import ch14_exercise;
import ch15;
import ch17;
import ch18;
import ch19;
import ch20;
import ch21;
import ch22;
import ch23;
import ch24;
import ch25;
import ch26;
import ch27;
import std;




using namespace std;
using namespace Records;



int displayMenu();
void doHire(Database& db);
void doFire(Database& db);
void doPromote(Database& db);
void test_airlineticket();
void test_format_specifier_zeros() {
	int i{ 42 };
	cout << format("|{:06d}|", i) << endl;   // |000042|
	cout << format("|{:+06d}|", i) << endl;  // |+00042|
	cout << format("|{:06X}|", i) << endl;   // |00002A|
	cout << format("|{:#06X}|", i) << endl;  // |0X002A|

	cout << format("|{:<06d}|", i) << endl;   // |000042|
	cout << format("|{:<+06d}|", i) << endl;  // |+00042|
	cout << format("|{:<06X}|", i) << endl;   // |00002A|
	cout << format("|{:<#06X}|", i) << endl;  // |0X002A|
}

void test_format_specifier() {
	int i{ 42 };
	cout << format("|{:10d}|", i) << endl;   // |        42|
	cout << format("|{:10b}|", i) << endl;   // |    101010|
	cout << format("|{:#10b}|", i) << endl;  // |  0b101010|
	cout << format("|{:10X}|", i) << endl;   // |        2A|
	cout << format("|{:#10X}|", i) << endl;  // |      0X2A|

	double d{ 3.1415 / 2.3 };
	cout << format("|{:12g}|", d) << endl;                         // |    1.365870|
	cout << format("|{:12.2}|", d) << endl;                        // |        1.37|
	cout << format("|{:12e}|", d) << endl;                         // |1.365870e+00|

	int width{ 12 };
	int precision{ 3 };
	cout << format("|{2:{0}.{1}f}|", width, precision, d) << endl;
	cout << format("|{:{}.{}f}|", d, width, precision) << endl;
	cout << format("|{0:{1}.{2}f}|", d, width, precision) << endl;
}

void test_interface() {
	Database myDB;
	Employee& emp1{ myDB.addEmployee("Greg", "Wallis") };
	emp1.fire();

	Employee& emp2{ myDB.addEmployee("Marc", "White") };
	emp2.setSalary(100'000);

	Employee& emp3{ myDB.addEmployee("John", "Doe") };
	emp3.setSalary(10'000);
	emp3.promote();

	cout << "all employees: " << endl << endl;
	myDB.displayAll();

	cout << endl << "current employees: " << endl << endl;
	myDB.displayCurrent();

	cout << endl << "former employees: " << endl << endl;
	myDB.displayFormer();

	Database employeeDB;
	bool done{ false };
	while (!done) {
		int selection{ displayMenu() };
		switch (selection) {
		case 0:
			done = true;
			break;
		case 1:
			doHire(employeeDB);
			break;
		case 2:
			doFire(employeeDB);
			break;
		case 3:
			doPromote(employeeDB);
			break;
		case 4:
			employeeDB.displayAll();
			break;
		case 5:
			employeeDB.displayCurrent();
			break;
		case 6:
			employeeDB.displayFormer();
			break;
		default:
			cerr << "Unknown command." << endl;
			break;
		}
	}

	// Create and populate an employee.
	HR::Employee anEmployee{
		.firstInitial = 'J',
			.lastInitial = 'D',
			.employeeNumber = 42,
			.salary = 80'000,
			.title = HR::TitleType::Manager
	};
	// Output the values of an employee.
	cout << format("Employee: {}{}", anEmployee.firstInitial,
		anEmployee.lastInitial) << endl;
	cout << format("Number: {}", anEmployee.employeeNumber) << endl;
	cout << format("Salary: ${}", anEmployee.salary) << endl;
	switch (anEmployee.title) {
		using enum HR::TitleType;
	case Manager:
		cout << format("Title: Manager") << endl;
		break;
	case SeniorEngineer:
		cout << format("Title: SeniorEngineer") << endl;
		break;
	case Engineer:
		cout << format("Title: Engineer") << endl;
		break;
	default:
		cout << format("Title: Error") << endl;
		break;
	}
	array<HR::Employee, 3> employees{
		HR::Employee{ 'J', 'D', 43, 80'000, HR::TitleType::Manager },
			HR::Employee{ 'M', 'W', 44, 70'000, HR::TitleType::SeniorEngineer },
			HR::Employee{ 'Z', 'J', 45, 60'000, HR::TitleType::Engineer }
	};

	for (const auto& employee : employees) {
		cout << format("Employee: {}{}", employee.firstInitial,
			employee.lastInitial) << endl;
		cout << format("Number: {}", employee.employeeNumber) << endl;
		cout << format("Salary: ${}", employee.salary) << endl;
		switch (employee.title) {
			using enum HR::TitleType;
		case Manager:
			cout << format("Title: Manager") << endl;
			break;
		case SeniorEngineer:
			cout << format("Title: SeniorEngineer") << endl;
			break;
		case Engineer:
			cout << format("Title: Engineer") << endl;
			break;
		default:
			cout << format("Title: Error") << endl;
			break;
		}
	}
	cout << endl;

	vector<HR::Employee> employees_vector;
	employees_vector.push_back(HR::Employee{ 'J', 'D', 43, 80'000, HR::TitleType::Manager });
	employees_vector.push_back(HR::Employee{ 'M', 'U', 43, 80'000, HR::TitleType::Manager });
	employees_vector.push_back(HR::Employee{ 'F', 'K', 43, 80'000, HR::TitleType::Manager });
	employees_vector.push_back(HR::Employee{ 'L', 'P', 43, 80'000, HR::TitleType::Manager });


	for (const auto& employee : employees_vector) {
		cout << format("Employee: {}{}", employee.firstInitial,
			employee.lastInitial) << endl;
		cout << format("Number: {}", employee.employeeNumber) << endl;
		cout << format("Salary: ${}", employee.salary) << endl;
		switch (employee.title) {
			using enum HR::TitleType;
		case Manager:
			cout << format("Title: Manager") << endl;
			break;
		case SeniorEngineer:
			cout << format("Title: SeniorEngineer") << endl;
			break;
		case Engineer:
			cout << format("Title: Engineer") << endl;
			break;
		default:
			cout << format("Title: Error") << endl;
			break;
		}

	}
	cout << endl;
}

void ex2_1() {
	string s1, s2;

	//cin.ignore(numeric_limits<streamsize>::max(), '\n');

	cout << "Enter first string: " << endl;
	getline(cin, s1);

	//cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

	cout << "Enter second string: " << endl;
	getline(cin, s2);
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	strong_ordering result{ s1 <=> s2 };
	if (is_lt(result)) { cout << s1 << " " << s2 << endl; }
	else if (is_gteq(result)) { cout << s2 << " " << s1 << endl; }
	
}

string ex2_2(string_view heystack, string_view find, string_view replacement) {
	string result{ heystack };
	auto position{ result.find(find) };
	while (position != string::npos) {
		result.replace(position, find.size(), replacement);
		position = result.find(find, position+replacement.size());
	}
	return result;
}

void ex2_4() {
	vector<double> vd{};
	string input{};
	while (getline(cin, input)) {
		double d{ std::stod(input) };
		if (d == 0) break;
		vd.push_back(d);
	}
	for (const auto& d : vd) {
		cout << format("|{0:7}|{0:<7}|{0:_>7}|{0:_^7}|{0:16e}|{0:12f}|{0:<12g}|{0:#>+12g}|", d) << endl;
	}
}

class Simple
{
public:
	Simple() { m_intPtr = new int{}; }
	~Simple() { delete m_intPtr; }
	void setValue(int value) { *m_intPtr = value; }
private:
	int* m_intPtr;
};

void doSomething(Simple*& outSimplePtr)
{
	outSimplePtr = new Simple{}; // BUG! Doesn't delete the original.
}

class Point_3d {
public:
	Point_3d(double x, double y, double z) : m_x{ x }, m_y{ y }, m_z{ z } {}

	double get_x() const { return m_x; }
	double get_y() const { return m_y; }
	double get_z() const { return m_z; }
private:
	double m_x, m_y, m_z;
};

void print_point_3d(const Point_3d& p3d) {
	cout << format("x is {:g}, y is {:g}, z is {:g}.", p3d.get_x(), p3d.get_y(), p3d.get_z());
}

void fillWithM(string& text)
{
	for (auto& x : text) {
		x = 'm';
	}
}

void ex8_1() {
	Person p1{ "Tun", "Guan" };
	cout << p1.get_first_name() << " " << p1.get_last_name() << endl;
	p1.set_first_name("Cup");
	cout << p1.get_first_name() << " " << p1.get_last_name() << endl;
	p1.set_last_name("Oonm");
	cout << p1.get_first_name() << " " << p1.get_last_name() << endl;

	auto person_1_smartptr{ make_unique<Person>("TunPtr","GuanPtr")};
	cout << person_1_smartptr->get_first_name() << " " << person_1_smartptr->get_last_name() << endl;
	person_1_smartptr->set_first_name("CupPtr");
	cout << person_1_smartptr->get_first_name() << " " << person_1_smartptr->get_last_name() << endl;
	person_1_smartptr->set_last_name("OonmPtr");
	cout << person_1_smartptr->get_first_name() << " " << person_1_smartptr->get_last_name() << endl;

}

void ex8_2() {
	Person phoneBook[3];
	cout << phoneBook[0].get_first_name() << " " << phoneBook[0].get_last_name() << endl;
	cout << phoneBook[1].get_first_name() << " " << phoneBook[1].get_last_name() << endl;
	cout << phoneBook[2].get_first_name() << " " << phoneBook[2].get_last_name() << endl;
}

void ex8_3() {
	cout << "ex8_3 starts: " << endl;

	Person p1{ "Tun", "Guan" };
	Person p2{ p1 };
	p2.set_first_name("Cup");
	cout << p1.get_first_name() << " " << p1.get_last_name() << endl;
	cout << p2.get_first_name() << " " << p2.get_last_name() << endl;
	p2 = p1;
	cout << p1.get_first_name() << " " << p1.get_last_name() << endl;
	cout << p2.get_first_name() << " " << p2.get_last_name() << endl;
}

void ex8_4() {
	cout << "ex8_4 starts: " << endl;

	Person p1{ "Tun", "Guan", "SB"};
	Person p2{ "Screw","Initials"};
	cout << p1.get_initials() << p1.get_first_name() << " " << p1.get_last_name() << endl;
	cout << p2.get_initials() << p2.get_first_name() << " " << p2.get_last_name() << endl;
	p2 = p1;
	cout << p1.get_initials() << p1.get_first_name() << " " << p1.get_last_name() << endl;
	cout << p2.get_initials() << p2.get_first_name() << " " << p2.get_last_name() << endl;
	p2.set_initials("Not SB");
	cout << p1.get_initials() << p1.get_first_name() << " " << p1.get_last_name() << endl;
	cout << p2.get_initials() << p2.get_first_name() << " " << p2.get_last_name() << endl;
}

void ex8_4_answer() {
	Person person{ "John", "Doe" };
	cout << format("The initials of {} {} are {}.",
		person.get_first_name(), person.get_last_name(), person.get_initials()) << endl;

	Person person2{ "Marc", "Gregoire", "Mg" };
	cout << format("The initials of {} {} are {}.",
		person2.get_first_name(), person2.get_last_name(), person2.get_initials()) << endl;

	Person persons[3];

	// Test copy constructor.
	Person copy{ person };

	// Test assignment operator.
	Person otherPerson{ "Jane", "Doe" };
	copy = otherPerson;
}

Person createPerson()
{
	return Person{ "cole", "fuio"};
}

void ex9_1() {
	vector<Person> vec;
	for (size_t i{ 0 }; i < 2; ++i) {
		cout << "Iteration " << i << endl;
		vec.push_back(Person{ "vec", "tone"});
		cout << endl;
	}

	Person s{ "what", "cold"};
	s = createPerson();

	Person s2{ "what", "cold" };
	s2 = s;
}

void ex9_1_answer() {
	Person person{ "John", "Doe" };
	cout << format("{} {} {}", person.get_first_name(), person.get_last_name(), person.get_initials()) << endl;

	Person persons[3];

	// Test copy constructor.
	Person copy{ person };

	// Test assignment operator.
	Person otherPerson{ "Jane", "Doe" };
	copy = otherPerson;

	// Test move construction.
	Person movedToPerson{ std::move(copy) };

	// Test move assignment.
	movedToPerson = std::move(person);
}


int main() {

	
	//ch14_exercise::ex2::test();
	//ch14_exercise::ex3::test();
	//ch14_exercise::ex4::test();
	//ch15::examples::overload_subscript_original::test();
	//ch15::examples::overload_subscript::test();
	//ch15::exercises::ex1::test();
	//ch15::exercises::ex1::test_textbook();
	/*ch15::exercises::ex2::test();
	ch15::exercises::ex2::test_textbook();*/
	/*ch15::exercises::ex3::test();
	ch15::exercises::ex3::test_textbook();*/
	//ch15::exercises::ex4::test_textbook();
	/*ch17::exercises::ex1::test();
	ch17::exercises::ex1::test_textbook();
	ch17::exercises::ex2::test();
	ch17::exercises::ex2::test_textbook();
	ch17::exercises::ex2::test_mix();*/
	//ch17::exercises::ex3::test();
	//ch17::exercises::ex4::test();
	//ch17::exercises::ex_bonus::test();
	//ch17::exercises::ex_bonus::test_textbook2();
	/*ch18::exercises::ex1::test();
	ch18::exercises::ex2::test();
	ch18::exercises::ex3::test();
	ch18::exercises::ex4::test();
	ch18::exercises::ex_bonus::test();*/
	//ch18::exercises::ex1::test_textbook();

	/*ch19::exercises::ex1::test();
	ch19::exercises::ex2::test();
	ch19::exercises::ex2::test_textbook();
	ch19::exercises::ex3::test();
	ch19::exercises::ex4::test();
	ch19::exercises::ex5::test();
	ch19::exercises::ex6::test();
	ch19::exercises::ex6::test_textbook();*/

	//ch20::exercises::ex1::test();
	//ch20::exercises::ex2::test();
	//ch20::exercises::ex2::test_textbook();
	/*ch20::exercises::ex3::test();
	ch20::exercises::ex3::test_textbook();*/
	//ch20::exercises::ex4::test();
	//ch20::exercises::ex5::test();
	/*ch21::exercises::ex1::test();
	ch21::exercises::ex2::test();*/
	//ch21::exercises::ex3::test_answer();
	//ch21::exercises::ex4::test();

	/*ch22::exercises::ex1::test();
	ch22::exercises::ex1::test_textbook();

	ch22::exercises::ex2::test();*/
	/*ch22::exercises::ex2::test_textbook();*/
	/*ch22::exercises::ex3::myanswer::test();
	ch22::exercises::ex3::textbook::test();

	ch22::exercises::ex4::myanswer::test();
	ch22::exercises::ex5::myanswer::test();
	ch22::exercises::ex5::textbook::test_1();
	ch22::exercises::ex5::textbook::test_2();
	ch22::exercises::ex6::myanswer::test();
	ch22::exercises::ex6::textbook::test();
	
	ch23::exercises::ex1::test();
	ch23::exercises::ex2::test();
	ch23::exercises::ex3::test();*/

	/*ch23::exercises::ex4::test_1();
	ch23::exercises::ex4::test_2();
	ch23::exercises::ex4::test_3();
	ch23::exercises::ex4::test_4();*/
	
	/*ch24::exercises::ex1::myanswer::test();
	ch24::exercises::ex1::textbook::test();*/

	/*ch24::exercises::ex2::test();*/

	/*ch25::exercises::ex1::myanswer::test();
	ch25::exercises::ex2::myanswer::test();
	ch25::exercises::ex3::myanswer::test();*/

	//ch26::exercises::ex1::myanswer::test(); 
	//ch26::exercises::ex2::myanswer::test();
	//ch26::exercises::ex3::myanswer::test();
	/*ch26::exercises::ex4::myanswer::test();
	ch26::exercises::ex5::myanswer::test();
	ch26::exercises::ex6::myanswer::test();*/

	//ch27::exercises::ex1::myanswer::test();
	//ch27::exercises::ex2::myanswer::test();
	//ch27::exercises::ex3::myanswer::test();
	//ch27::exercises::ex3::textbook::test();
	/*ch27::exercises::ex4::myanswer::test();
	ch27::exercises::ex4::myanswer2::test();
	ch27::exercises::ex4::textbook::test();*/
	//ch27::exercises::ex5::myanswer::test();
	ch27::exercises::ex6::myanswer::test();

	/*ch13_bookcode::code_1();
	ch13_bookcode::code_2();
	ch13_bookcode::code_3();*/
	//ch13_bookcode::getReservationData();
	//ch13_bookcode::calculateSumFromCin();
	//ch13_bookcode::code_4();
	//ch13_bookcode::code_5();
	//ch13_bookcode::exercises::ex1::test();
	//ch13_bookcode::exercises::ex2::test();
	//ch13_bookcode::exercises::ex3::test();
	//ch13_bookcode::exercises::ex3::answer_test();
	//ch13_bookcode::exercises::ex4::test();
	
	/*ex12_1::test();
	ex12_2::test();
	ex12_3::test();
	ex12_4::test();
	ex12_5::test();
	ex12_6::TestFind();*/

	//array<int, 10> values{};
	//for (int index{ 0 }; index < values.size(); ++index) {
	//	values.at(index) = index;
	//}
	//values.back() = 99;
	//for (auto x:values) {
	//	cout << x << " ";
	//}

	//auto myP3dSmartPtr{ make_unique<Point_3d>(1.34535,2.12334,3.41121224463456) };
	//print_point_3d(*myP3dSmartPtr);

	//string str{ "Hello World!" };
	//cout << "Before: " << str << endl;
	//fillWithM(str);
	//cout << "After: " << str << endl;

	//SpreadsheetCell myCell, anotherCell;
	//myCell.setValue(6);
	//anotherCell.setString("3.2");
	//cout << "cell 1: " << myCell.getValue() << endl;
	//cout << "cell 2: " << anotherCell.getValue() << endl;

	//auto myCellp{ make_unique<SpreadsheetCell>() };
	//// Equivalent to:
	//// unique_ptr<SpreadsheetCell> myCellp { new SpreadsheetCell { } };
	//myCellp->setValue(3.7);
	//cout << "cell 1: " << myCellp->getValue() <<
	//	" " << myCellp->getString() << endl;

	//SpreadsheetCell mycell(5), anothercell(4);
	//cout << "cell 1: " << mycell.getValue() << endl;
	//cout << "cell 2: " << anothercell.getValue() << endl;

	//SpreadsheetCell aThirdCell{ "test" };  // Uses string-arg ctor
	//SpreadsheetCell aFourthCell{ 4.4 };    // Uses double-arg ctor
	//auto aFifthCellp{ make_unique<SpreadsheetCell>("5.5") }; // string-arg ctor
	//cout << "aThirdCell: " << aThirdCell.getValue() << endl;
	//cout << "aFourthCell: " << aFourthCell.getValue() << endl;
	//cout << "aFifthCellp: " << aFifthCellp->getValue() << endl;

	//SpreadsheetCell myCell2;
	//myCell2.setValue(6);
	//cout << "cell 1: " << myCell2.getValue() << endl;

	//EvenSequence p1{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
	//p1.dump();

	//try {
	//	EvenSequence p2{ 1.0, 2.0, 3.0 };
	//}
	//catch (const invalid_argument& e) {
	//	cout << e.what() << endl;
	//}

	//ex8_1();
	//ex8_2();
	//ex8_3();
	//ex8_4();
	//ex8_4_answer();

	//SpreadsheetApplication app;
	//Spreadsheet s1{ 2, 3, app };
	//Spreadsheet s2{ 3, 4, app };

	//SpreadsheetCell myCell3{ 5 };
	//myCell3.setColor(SpreadsheetCell::Color::Blue);
	//auto color{ myCell3.getColor() };


	//ex9_1();
	//ex9_1_answer();




	//ex2_1();
	
	/*string heystack, find, replacement;
	cout << "Enter heystack: " << endl;
	getline(cin, heystack);

	cout << "Enter find: " << endl;
	getline(cin, find);

	cout << "Enter replacement: " << endl;
	getline(cin, replacement);
	string result{ ex2_2(heystack, find, replacement) };
	cout << heystack << endl;
	cout << find << endl;
	cout << replacement << endl;
	cout << result << endl;*/

	/*ex2_4();*/


	//test_uninitialized_variable();
	//test_limit();
	//test_conversion();
	//brilliant_calculation();
	// Create and populate an employee.
	//Employee anEmployee;
	//anEmployee.firstInitial = 'J';
	//anEmployee.lastInitial = 'D';
	//anEmployee.employeeNumber = 42;
	//anEmployee.salary = 80000;
	//// Output the values of an employee.
	//cout << format("Employee: {}{}", anEmployee.firstInitial,
	//	anEmployee.lastInitial) << endl;
	//cout << format("Number: {}", anEmployee.employeeNumber) << endl;
	//cout << format("Salary: ${}", anEmployee.salary) << endl;

	//test_switch();
	//int someInt{ 3 };
	//char someChar{ 's' };
	//myFunction(8, 'a');
	//myFunction(someInt, 'b');
	//myFunction(5, someChar);

	//int sum{ addNumbers_1(5, 3) };
	//cout << sum<<'\n';
	//
	//cout << addNumbers_2(1, 2) << endl; // Calls the integer version
	//cout << addNumbers_2(1.11, 2.22);   // Calls the double version

	//func();

	//optional<int> data1{ getData(true) };
	//optional<int> data2{ getData(false) };
	//cout << "data1.has_value = " << data1.has_value() << endl;
	//if (data2) {
	//	cout << "data2 has a value." << endl;
	//}
	//cout << "data1.value = " << data1.value() << endl;
	//cout << "data1.value = " << *data1 << endl;
	//cout << "data2.value = " << data2.value_or(0) << endl;

	//AirlineTicket myTicket;
	//myTicket.setPassengerName("Sherman T. Socketwrench");
	//myTicket.setNumberOfMiles(700);
	//double cost{ myTicket.calculatePriceInDollars() };
	//cout << format("This ticket will cost ${}", cost) << endl;
	//////myTicket.setFrequentFlyerNumber(32);
	////double cost{ myTicket.calculatePriceInDollars() };
	////cost = 3.1415926;
	////const auto& name{ myTicket.getPassengerName() };
	////const auto frequent_flyer_num{ myTicket.getFrequentFlyerNumber() };
	////std::cout << std::format("This ticket will cost ${}", cost) << std::endl;

	////std::cout << std::format("{} has {} frequent flyer number.", name, frequent_flyer_num.value_or(0));
	//string str{ "C++" };
	//const string& constStr{ as_const(str) };
	//str= "Rust";
	//cout << str << "\n";
	//cout << constStr<<"\n";

	//cout << "Testing the Employee class." << endl;
	//Employee emp{ "Jane", "Doe" };
	//emp.setFirstName("John");
	//emp.setLastName("Doe");
	//emp.setEmployeeNumber(71);
	//emp.setSalary(50'000);
	//emp.promote();
	//emp.promote(50);
	//emp.hire();
	//emp.display();

	//try {
	//	cout << divideNumbers(2.5, 0.5) << endl;
	//	cout << divideNumbers(2.3, 0) << endl;
	//	cout << divideNumbers(4.5, 2.5) << endl;
	//}
	//catch (const invalid_argument& exception) {
	//	cout << format("Exception caught: {}", exception.what()) << endl;
	//}

	////test_interface();

	//test_airlineticket();

	//double value1{ 0.314 };
	//const size_t BufferSize{ 50 };
	//string out(BufferSize, ' '); // A string of BufferSize space characters.
	//auto [ptr1, error1] { to_chars(out.data(), out.data() + out.size(), value1) };
	//if (error1 == errc{}) { cout << out << endl; /* Conversion successful. */ }
	//double value2;
	//auto [ptr2, error2] { from_chars(out.data(), out.data() + out.size(), value2) };
	//if (error2 == errc{}) {
	//	if (value1 == value2) {
	//		cout << "Perfect roundtrip" << endl;
	//	}
	//	else {
	//		cout << "No perfect roundtrip?!?" << endl;
	//	}
	//}

	//test_format_specifier();
	//test_format_specifier_zeros();

	//return 0;
	
}

//For Exercise 24-3
//int main(int argc, char** argv) {
//	ch24::exercises::ex3::test(argc, argv);
//	ch24::exercises::ex4::test(argc, argv);
//	ch24::exercises::ex5::test(argc, argv);
//}




void test_airlineticket() {
	AirlineTicket myTicket;
	myTicket.setPassengerName("Sherman T. Socketwrench");
	myTicket.setNumberOfMiles(700);
	double cost{ myTicket.calculatePriceInDollars() };
	cout << format("This ticket will cost ${}", cost) << endl;
	optional<int> data1{ myTicket.getFrequentFlyerNumber() };
	myTicket.setFrequentFlyerNumber(123456);
	optional<int> data2{ myTicket.getFrequentFlyerNumber() };
	cout << "data1.value = " << data1.value_or(-996) << endl;
	cout << "data2.value = " << data2.value_or(-996) << endl;
}

int displayMenu()
{
	int selection;
	cout << endl;
	cout << "Employee Database" << endl;
	cout << "-----------------" << endl;
	cout << "1) Hire a new employee" << endl;
	cout << "2) Fire an employee" << endl;
	cout << "3) Promote an employee" << endl;
	cout << "4) List all employees" << endl;
	cout << "5) List all current employees" << endl;
	cout << "6) List all former employees" << endl;
	cout << "0) Quit" << endl;
	cout << endl;
	cout << "---> ";
	cin >> selection;
	return selection;
}

void doHire(Database& db)
{
	string firstName;
	string lastName;

	cout << "First name? ";
	cin >> firstName;

	cout << "Last name? ";
	cin >> lastName;

	auto& employee{ db.addEmployee(firstName, lastName) };
	cout << format("Hired employee {} {} with employee number {}.",
		firstName, lastName, employee.getEmployeeNumber()) << endl;
}

void doFire(Database& db)
{
	int employeeNumber;
	cout << "Employee number? ";
	cin >> employeeNumber;

	try {
		auto& emp{ db.getEmployee(employeeNumber) };
		emp.fire();
		cout << format("Employee {} terminated.", employeeNumber) << endl;
	}
	catch (const std::logic_error& exception) {
		cerr << format("Unable to terminate employee: {}",
			exception.what()) << endl;
	}
}

void doPromote(Database& db)
{
	int employeeNumber;
	cout << "Employee number? ";
	cin >> employeeNumber;

	int raiseAmount;
	cout << "How much of a raise? ";
	cin >> raiseAmount;

	try {
		auto& emp{ db.getEmployee(employeeNumber) };
		emp.promote(raiseAmount);
	}
	catch (const std::logic_error& exception) {
		cerr << format("Unable to promote employee: {}", exception.what()) << endl;
	}
}