#include <time.h>
export module ch13_example;
import std;

export namespace ch13_bookcode{
	using namespace std;
	using namespace std::filesystem;
	void code_1() {
		int i{ 7 };
		cout << i << endl;

		char ch{ 'a' };
		cout << ch << endl;

		string myString{ "Hello World." };
		cout << myString << endl;
	}
	void code_2() {
		const char* test{ "hello there\n" };
		cout.write(test, strlen(test));

		cout.put('a');

		cout << "abc";
		cout.flush();    // abc is written to the console.
		cout << "def";
		cout << endl;    // def is written to the console.

		if (cout.good()) {
			cout << "All good" << endl;
		}

		cout.flush();
		if (!cout) {
			cerr << "Unable to flush to standard out" << endl;
		}

		cout.exceptions(ios::failbit | ios::badbit | ios::eofbit);
		try {
			cout << "Hello World." << endl;
		}
		catch (const ios_base::failure& ex) {
			cerr << "Caught exception: " << ex.what()
				<< ", error code = " << ex.code() << endl;
		}
	}
	void code_3() {
		// Boolean values
		bool myBool{ true };
		cout << "This is the default: " << myBool << endl;
		cout << "This should be true: " << boolalpha << myBool << endl;
		cout << "This should be 1: " << noboolalpha << myBool << endl;

		// Simulate printf-style "%6d" with streams
		int i{ 123 };
		printf("This should be '   123': %6d\n", i);
		cout << "This should be '   123': " << setw(6) << i << endl;

		// Simulate printf-style "%06d" with streams
		printf("This should be '000123': %06d\n", i);
		cout << "This should be '000123': " << setfill('0') << setw(6) << i << endl;

		// Fill with *
		cout << "This should be '***123': " << setfill('*') << setw(6) << i << endl;
		// Reset fill character
		cout << setfill(' ');

		// Floating-point values
		double dbl{ 1.452 };
		double dbl2{ 5 };
		cout << "This should be ' 5': " << setw(2) << noshowpoint << dbl2 << endl;
		cout << "This should be @@1.452: " << setw(7) << setfill('@') << dbl << endl;
		// Reset fill character
		cout << setfill(' ');

		// Instructs cout to start formatting numbers according to your location.
		// Chapter 21 explains the details of the imbue() call and the locale object.
		cout.imbue(locale{ "" });

		// Format numbers according to your location
		cout << "This is 1234567 formatted according to your location: " << 1234567
			<< endl;

		// Monetary value. What exactly a monetary value means depends on your
		// location. For example, in the USA, a monetary value of 120000 means 120000
		// dollar cents, which is 1200.00 dollars.
		cout << "This should be a monetary value of 120000, "
			<< "formatted according to your location: "
			<< put_money("120000") << endl;

		// Date and time
		time_t t_t = std::time(nullptr);  // Get current system time.
		tm t;                        // tm struct to hold local time.
		localtime_s(&t, &t_t);       // Convert to local time safely.

		cout << "This should be the current date and time "
			<< "formatted according to your location: "
			<< put_time(&t, "%c") << endl;

		// Quoted string
		cout << "This should be: \"Quoted string with \\\"embedded quotes\\\".\": "
			<< quoted("Quoted string with \"embedded quotes\".") << endl;

		cout << "This should be '1.2346': " << setprecision(5) << 1.23456789 << endl;
		cout.precision(5);
		cout << "This should be '1.2346': " << 1.23456789 << endl;
	}
	void getReservationData()
	{
		string guestName;
		int partySize;
		cout << "Name and number of guests: ";
		cin >> guestName >> partySize;
		cout << "Thank you, " << guestName << "." << endl;
		if (partySize > 10) {
			cout << "An extra gratuity will apply." << endl;
		}
	}
	int calculateSumFromCin() {
		cout << "Enter numbers on separate lines to add.\n"
			<< "Use Control+D followed by Enter to finish (Control+Z in Windows).\n";
		int sum{ 0 };

		if (!cin.good()) {
			cerr << "Standard input is in a bad state!" << endl;
			return 1;
		}

		while (!cin.bad()) {
			int number;
			cin >> number;
			if (cin.good()) {
				sum += number;
			}
			else if (cin.eof()) {
				break; // Reached end of file
			}
			else if (cin.fail()) {
				// Failure!
				cin.clear(); // Clear the failure state.
				string badToken;
				cin >> badToken; // Consume the bad input.
				cerr << "WARNING: Bad input encountered: " << badToken << endl;
			}
		}
		cout << "The sum is " << sum << endl;
	}
	void code_4() {
		cout << "Enter multiple lines of text. "
			<< "Use an @ character to signal the end of the text.\n> ";
		string myString;
		getline(cin, myString, '@');
		cout << format("Read text: \"{}\"", myString) << endl;
	}
	void printDirectoryStructure(const path& p)
	{
		if (!exists(p)) {
			return;
		}

		recursive_directory_iterator begin{ p };
		recursive_directory_iterator end{ };
		for (auto iter{ begin }; iter != end; ++iter) {
			const string spacer(iter.depth() * 2, ' ');

			auto& entry{ *iter }; // Dereference iter to access directory_entry.

			if (is_regular_file(entry)) {
				cout << format("{}File: {} ({} bytes)",
					spacer, entry.path().string(), file_size(entry)) << endl;
			}
			else if (is_directory(entry)) {
				cout << format("{}Dir: {}", spacer, entry.path().string()) << endl;
			}
		}
	}
	void printDirectoryStructure_2(const path& p, size_t level = 0)
	{
		if (!exists(p)) {
			return;
		}

		const string spacer(level * 2, ' ');

		if (is_regular_file(p)) {
			cout << format("{}File: {} ({} bytes)",
				spacer, p.string(), file_size(p)) << endl;
		}
		else if (is_directory(p)) {
			cout << format("{}Dir: {}", spacer, p.string()) << endl;
			for (auto& entry : directory_iterator{ p }) {
				printDirectoryStructure_2(entry, level + 1);
			}
		}
	}
	void code_5() {
		
		path p1{ R"(D:\Foo\Bar)" };
		path p2{ "D:/Foo/Bar" };
		cout << p1 << endl;
		cout << p2 << endl;

		{
			path p{ "D:\\Foo" };
			p.append("Bar");
			p /= "Bar";
			cout << p << endl; 
		}
		{
			path p{ "D:\\Foo" };
			p.concat("Bar");
			p += "Bar";
			cout << p << endl;
		}
		{
			path p{ R"(C:\Foo\Bar)" };
			for (const auto& component : p) {
				cout << component << endl;
			}
		}
		{
			path p{ R"(C:\Foo\Bar\file.txt)" };
			cout << p.root_name() << endl;
			cout << p.filename() << endl;
			cout << p.stem() << endl;
			cout << p.extension() << endl;
		}
		{
			path myPath{ "c:/windows/win.ini" };
			directory_entry dirEntry{ myPath };
			if (dirEntry.exists() && dirEntry.is_regular_file()) {
				cout << "File size: " << dirEntry.file_size() << endl;
			}
		}
		{
			space_info s{ space("c:\\") };
			cout << "Capacity: " << s.capacity << endl;
			cout << "Free: " << s.free << endl;
		}
		{
			path p{ R"(D:\opensourcework\virtualboxstuff\drivers\network)" };
			printDirectoryStructure(p);
			printDirectoryStructure_2(p);
		}
	}
	namespace exercises {
		namespace ex1 {
			class Person
			{
			public:
				// Two-parameter constructor automatically creates initials and
				// delegates the work to the three-parameter constructor.
				Person(std::string firstName, std::string lastName)
					: Person{ std::move(firstName), std::move(lastName),
					std::format("{}{}", firstName[0], lastName[0]) }
				{
				}

				Person() = default;

				Person(std::string firstName, std::string lastName, std::string initials)
					: m_firstName{ std::move(firstName) }
					, m_lastName{ std::move(lastName) }
					, m_initials{ std::move(initials) }
				{
				}

				const std::string& getFirstName() const { return m_firstName; }
				void setFirstName(std::string firstName) { m_firstName = std::move(firstName); }

				const std::string& getLastName() const { return m_lastName; }
				void setLastName(std::string lastName) { m_lastName = std::move(lastName); }

				const std::string& getInitials() const { return m_initials; }
				void setInitials(std::string initials) { m_initials = std::move(initials); }

				void output() const {
					cout << format("First name:{}\nLast name:{}\nInitials:{}\n", this->getFirstName(), this->getLastName(), this->getInitials());
				}

				//// Only this single line of code is needed to add support
				//// for all six comparison operators.
				[[nodiscard]] auto operator<=>(const Person&) const = default;

			private:
				std::string m_firstName;
				std::string m_lastName;
				std::string m_initials;
			};
			void test() {
				Person person{ "John", "Doe" };
				person.output();

				Person person2{ "Marc", "Gregoire", "Mg" };
				person2.output();

				Person persons[3];

				// Test copy constructor.
				Person copy{ person };

				// Test assignment operator.
				Person otherPerson{ "Jane", "Doe" };
				copy = otherPerson;

				// Test comparison operators.
				if (person < person2) { cout << "person < person2" << endl; }
				if (person > person2) { cout << "person > person2" << endl; }
				if (person <= person2) { cout << "person <= person2" << endl; }
				if (person >= person2) { cout << "person >= person2" << endl; }
				if (person == person2) { cout << "person == person2" << endl; }
				if (person != person2) { cout << "person != person2" << endl; }
			}
		}
		namespace ex2 {
			class Person
			{
			public:
				// Two-parameter constructor automatically creates initials and
				// delegates the work to the three-parameter constructor.
				Person(std::string firstName, std::string lastName)
					: Person{ std::move(firstName), std::move(lastName),
					std::format("{}{}", firstName[0], lastName[0]) }
				{
				}

				Person() = default;

				Person(std::string firstName, std::string lastName, std::string initials)
					: m_firstName{ std::move(firstName) }
					, m_lastName{ std::move(lastName) }
					, m_initials{ std::move(initials) }
				{
				}

				const std::string& getFirstName() const { return m_firstName; }
				void setFirstName(std::string firstName) { m_firstName = std::move(firstName); }

				const std::string& getLastName() const { return m_lastName; }
				void setLastName(std::string lastName) { m_lastName = std::move(lastName); }

				const std::string& getInitials() const { return m_initials; }
				void setInitials(std::string initials) { m_initials = std::move(initials); }

				void output(ostream& ost) const{
					ost << format("First name:{}\nLast name:{}\nInitials:{}\n", this->getFirstName(), this->getLastName(), this->getInitials());
				}

				//// Only this single line of code is needed to add support
				//// for all six comparison operators.
				[[nodiscard]] auto operator<=>(const Person&) const = default;

			private:
				std::string m_firstName;
				std::string m_lastName;
				std::string m_initials;
			};
			void test() {	
				ostringstream outStream;
				ofstream outFile{ "output.txt" };
				
				cout << "1\n";
				Person person{ "John", "Doe" };
				person.output(cout);
				person.output(outStream);
				person.output(outFile);

				cout << "2\n";
				Person person2{ "Marc", "Gregoire", "Mg" };
				person2.output(cout);
				person2.output(outStream);
				person2.output(outFile);

				cout << "ostringstream outStream output" << outStream.str()<<"\n";

				Person persons[3];

				// Test copy constructor.
				Person copy{ person };

				// Test assignment operator.
				Person otherPerson{ "Jane", "Doe" };
				copy = otherPerson;

				// Test comparison operators.
				if (person < person2) { cout << "person < person2" << endl; }
				if (person > person2) { cout << "person > person2" << endl; }
				if (person <= person2) { cout << "person <= person2" << endl; }
				if (person >= person2) { cout << "person >= person2" << endl; }
				if (person == person2) { cout << "person == person2" << endl; }
				if (person != person2) { cout << "person != person2" << endl; }
			}
		}
		namespace ex3 {
			class Person
			{
			public:
				// Two-parameter constructor automatically creates initials and
				// delegates the work to the three-parameter constructor.
				Person(std::string firstName, std::string lastName)
					: Person{ std::move(firstName), std::move(lastName),
					std::format("{}{}", firstName[0], lastName[0]) }
				{
				}

				Person() = default;

				Person(std::string firstName, std::string lastName, std::string initials)
					: m_firstName{ std::move(firstName) }
					, m_lastName{ std::move(lastName) }
					, m_initials{ std::move(initials) }
				{
				}

				const std::string& getFirstName() const { return m_firstName; }
				void setFirstName(std::string firstName) { m_firstName = std::move(firstName); }

				const std::string& getLastName() const { return m_lastName; }
				void setLastName(std::string lastName) { m_lastName = std::move(lastName); }

				const std::string& getInitials() const { return m_initials; }
				void setInitials(std::string initials) { m_initials = std::move(initials); }

				void output(ostream& ost) const {
					ost << format("First name:{}\nLast name:{}\nInitials:{}\n", this->getFirstName(), this->getLastName(), this->getInitials());
				}

				//// Only this single line of code is needed to add support
				//// for all six comparison operators.
				[[nodiscard]] auto operator<=>(const Person&) const = default;

			private:
				std::string m_firstName;
				std::string m_lastName;
				std::string m_initials;
			};
			class Database {
			public:
				void add(Person p) {
					vp.push_back(move(p));
				}
				int save(string_view file_path) {
					ofstream outFile{ static_cast<string>(file_path), ios_base::trunc };
					if (!outFile.good()) {
						cerr << "Error while opening output file!" << endl;
						return -1;
					}
					for (const auto& p : vp) {
						p.output(outFile);
					}
					return 0;
				}
				int load(string_view file_path) {
					vector<Person> persons;
					ifstream inFile{ static_cast<string>(file_path) };
					if (!inFile.good()) {
						cerr << "Error while opening input file!" << endl;
						return -1;
					}
					string line, key, value;
					string firstName, lastName, initials;
					while (getline(inFile,line)) {
						stringstream ss{ line };
						getline(ss, key, ':');
						getline(ss, value);

						if (key == "First name") {
							if (!firstName.empty()) {
								vp.emplace_back(firstName, lastName, initials);
								firstName.clear();
								lastName.clear();
								initials.clear();
							}
							firstName = value;
						}
						else if (key == "Last name") {
							lastName = value;
						}
						else if (key == "Initials") {
							initials = value;
						}
					}
					if (!firstName.empty()) {
						vp.emplace_back(firstName, lastName, initials);
					}
					return 0;
				}
				void clear() {
					vp.clear();
				}
				void outputAll(ostream& ost) const {
					for (const auto& p : vp) {
						p.output(ost);
					}
				}
			private:
				vector<Person> vp{};
			};
			void test() {
				Person person1{ "John", "Doe" };
				Person person2{ "Marc", "Gregoire", "Mg" };
				Person person3{ "Zijian", "Guan", "Zj" };
				Person person4{ "Nutrition", "Facts"};
				Database db, db2;

				db.add(person1);
				db.add(person2);
				db.add(person3);
				db.add(person4);
				db.save("test.txt");

				db2.load("test.txt");
				db.clear();

				cout << "db:" << endl;
				db.outputAll(cout);
				cout << "db2:" << endl;
				db2.outputAll(cout);
			}
			void answer_test() {
				// Fill a database.
				Database db;
				db.add(Person{ "John", "Doe" });
				db.add(Person{ "Marc", "Gregoire", "Mg" });
				db.add(Person{ "Peter", "Van Weert", "PVW" });

				// Output all persons in the database to standard output.
				cout << "Initial database contents:" << endl;
				db.outputAll(cout);

				// Save the database to a file.
				db.save("person.db");

				// Clear the database.
				db.clear();
				cout << "\nDatabase contents after clearing:" << endl;
				db.outputAll(cout);

				// Load database from file.
				cout << "\nLoading database from file..." << endl;
				db.load("person.db");
				cout << "\nDatabase contents after loading from file:" << endl;
				db.outputAll(cout);
			}
		}
		namespace ex4 {
			class Person
			{
			public:
				// Two-parameter constructor automatically creates initials and
				// delegates the work to the three-parameter constructor.
				Person(std::string firstName, std::string lastName)
					: Person{ std::move(firstName), std::move(lastName),
					std::format("{}{}", firstName[0], lastName[0]) }
				{
				}

				Person() = default;

				Person(std::string firstName, std::string lastName, std::string initials)
					: m_firstName{ std::move(firstName) }
					, m_lastName{ std::move(lastName) }
					, m_initials{ std::move(initials) }
				{
				}

				const std::string& getFirstName() const { return m_firstName; }
				void setFirstName(std::string firstName) { m_firstName = std::move(firstName); }

				const std::string& getLastName() const { return m_lastName; }
				void setLastName(std::string lastName) { m_lastName = std::move(lastName); }

				const std::string& getInitials() const { return m_initials; }
				void setInitials(std::string initials) { m_initials = std::move(initials); }

				void output(ostream& ost) const {
					ost << format("First name:{}\nLast name:{}\nInitials:{}\n", this->getFirstName(), this->getLastName(), this->getInitials());
				}

				//// Only this single line of code is needed to add support
				//// for all six comparison operators.
				[[nodiscard]] auto operator<=>(const Person&) const = default;

			private:
				std::string m_firstName;
				std::string m_lastName;
				std::string m_initials;
			};
			class Database {
			public:
				void add(Person p) {
					vp.push_back(move(p));
				}
				int save(const path& file_directory) {
					if (!exists(file_directory)) {
						if (!create_directory(file_directory)) {
							cerr << "Failed to create directory: " << file_directory << endl;
							return -1;
						}
					}
					for (const auto& p : vp) {
						const path& path_for_name{ file_directory / (p.getInitials() + ".person") };
						ofstream file_for_output{ path_for_name, ios_base::trunc };
						if (!file_for_output) {
							cerr << "Cannot open file: " << path_for_name << endl;
							return -1;
						}
						p.output(file_for_output);
					}
					return 0;
				}
				int load(const path& file_directory) {
					vector<Person> persons;

					if (!exists(file_directory)) {
						return -1;
					}

					recursive_directory_iterator begin{ file_directory };
					recursive_directory_iterator end{ };
					for (auto iter{ begin }; iter != end; ++iter) {
						auto& entry{ *iter }; // Dereference iter to access directory_entry.
						if (is_regular_file(entry) && entry.path().extension() == ".person") {
							ifstream inFile{ entry.path() };
							if (!inFile.good()) {
								cerr << "Error while opening input file!" << endl;
								return -1;
							}
							string line, key, value;
							string firstName, lastName, initials;
							while (getline(inFile, line)) {
								stringstream ss{ line };
								getline(ss, key, ':');
								getline(ss, value);

								if (key == "First name") {
									if (!firstName.empty()) {
										vp.emplace_back(firstName, lastName, initials);
										firstName.clear();
										lastName.clear();
										initials.clear();
									}
									firstName = value;
								}
								else if (key == "Last name") {
									lastName = value;
								}
								else if (key == "Initials") {
									initials = value;
								}
							}
							if (!firstName.empty()) {
								vp.emplace_back(firstName, lastName, initials);
							}
						}
						else if (is_directory(entry)) {
							cout << format("Not supposed to have directories") << endl;
						}
					}

					return 0;
				}
				void clear() {
					vp.clear();
				}
				void outputAll(ostream& ost) const {
					for (const auto& p : vp) {
						p.output(ost);
					}
				}
			private:
				vector<Person> vp{};
			};
			void test() {
				// Fill a database.
				Database db;
				db.add(Person{ "John", "Doe" });
				db.add(Person{ "Marc", "Gregoire", "Mg" });
				db.add(Person{ "Peter", "Van Weert", "PVW" });

				// Output all persons in the database to standard output.
				cout << "Initial database contents:" << endl;
				db.outputAll(cout);

				// Save the database to a file.
				db.save(R"(D:\cppliblearn\professionalcppbook\profcppbook\ch13_ex4_output)");

				// Clear the database.
				db.clear();
				cout << "\nDatabase contents after clearing:" << endl;
				db.outputAll(cout);

				// Load database from file.
				cout << "\nLoading database from file..." << endl;
				db.load(R"(D:\cppliblearn\professionalcppbook\profcppbook\ch13_ex4_output)");
				cout << "\nDatabase contents after loading from file:" << endl;
				db.outputAll(cout);
			}
		}
	}
};