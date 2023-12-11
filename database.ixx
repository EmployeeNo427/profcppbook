export module database;
import std;
import employee;

namespace Records {
	const int FirstEmployeeNumber{ 1'000 };
	/**
	 * The Database stores a collection of employees. It supports
	 * adding and retrieving employees, and displaying employees
     * satisfying certain constraints.
     */
	export class Database
	{
	public:
		/**
		 * Adds an employee with given name to the database. 
		 * 
		 * @param firstName The first name of the employee to add.
	     * @param lastName The last name of the employee to add.
		 * @throws vector<Employee> m_employees might throw.
		 * @return The reference to m_employees.back(), i.e. the last of employees.
		 */
		Employee& addEmployee(const std::string& firstName,
						const std::string& lastName);
		/**
		 * Finds an employee based on an employee number.
		 *	
		 * @param employeeNumber, int 
		 * @throws logic_error if employeeNumber is not in vector.
		 * @return Employee& of the employee found.
		 */
		Employee& getEmployee(int employeeNumber);
		/**
		 * Finds an employee based on a name.
		 * 
		 * @param firstName The first name of the employee to add.
	     * @param lastName The last name of the employee to add.
		 * @throws logic_error if no corresponding firstName and lastName found.
		 * @return Employee& of the employee found.
		 */
		Employee& getEmployee(const std::string& firstName,
						const std::string& lastName);
		/**
		 * Display all employees employed or former.
		 * @throws std::format might throw.
		 */
		void displayAll() const;
		/**
		 * Display current employees.
		 * @throws std::format might throw.
		 */
		void displayCurrent() const;
		/**
		 * Display former employees.
		 * @throws std::format might throw.
		 */
		void displayFormer() const;
	private:
		std::vector<Employee> m_employees;
		int m_nextEmployeeNumber{ FirstEmployeeNumber };
	};
}

export void MyFunc();