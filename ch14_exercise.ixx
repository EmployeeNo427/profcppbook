export module ch14_exercise;
import std;

export namespace ch14_exercise {
	namespace ex2 {
		using namespace std;

		void changeNumberForID(string_view filename, int id, string_view newNumber)
		{
			fstream ioData{ filename.data() };
			if (ioData.fail()) {
				// We failed to open the file: throw an exception.
				throw runtime_error{format("failed to open the file {}", filename.data())};
			}
			// Loop until the end of file
			while (ioData) {
				// Read the next ID.
				int idRead;
				ioData >> idRead;
				if (!ioData)
					break;

				// Check to see if the current record is the one being changed.
				if (idRead == id) {
					// Seek the write position to the current read position.
					ioData.seekp(ioData.tellg());
					if (ioData.fail()) {
						throw runtime_error{ "seekp and/or tellg failed" };
					}
					// Output a space, then the new number.
					ioData << " " << newNumber;
					if (ioData.fail()) {
						throw runtime_error{ "failed to write to the output stream with space and number" };
					}
					break;
				}

				// Read the current number to advance the stream.
				string number;
				ioData >> number;
				if (ioData.fail()) {
					throw runtime_error{ "failed to read the current number to advance the stream" };
				}
			}
		}
		void test() {
			std::string filePath = "D:\\cppliblearn\\professionalcppbook\\profcppbook\\data.txt"; // or use forward slashes
			try { 
				changeNumberForID(filePath, 263, "415-555-3333"); 
			}
			catch (const exception& e) {
				cerr << format("Caught exception is: {}", e.what()) << endl;
			}
		}
	}
	namespace ex3 {
		using namespace std;

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

			void output(std::ostream& output) const
			{
				output << std::format("{} {} ({})",
					getFirstName(), getLastName(), getInitials()) << std::endl;
			}

			// Only this single line of code is needed to add support
			// for all six comparison operators.
			[[nodiscard]] auto operator<=>(const Person&) const = default;

		private:
			std::string m_firstName;
			std::string m_lastName;
			std::string m_initials;
		};
		class Database
		{
		public:
			// Adds the given person to the database.
			void add(Person person);

			// Removes all persons from the database.
			void clear();

			// Saves all persons in the database to the given file.
			void save(std::string_view filename) const;

			// Loads all persons from the given file and stores them in the database.
			void load(std::string_view filename);

			// Outputs all persons to the given stream.
			void outputAll(std::ostream& output) const;

		private:
			std::vector<Person> m_persons;
		};
		void Database::add(Person person)
		{
			m_persons.push_back(move(person));
		}

		void Database::clear()
		{
			m_persons.clear();
		}

		void Database::save(string_view filename) const
		{
			ofstream outFile{ filename.data(), ios_base::trunc };
			if (!outFile) {
				// We failed to open the file: throw an exception.
				throw runtime_error{ format("failed to open the file {} for saving.", filename.data()) };
			}

			for (const auto& person : m_persons) {
				// We need to support spaces in names.
				// So, to be able to read back names later in load(),
				// we simply quote all parts of the name.
				outFile << quoted(person.getFirstName())
					<< quoted(person.getLastName())
					<< quoted(person.getInitials()) << endl;
				if (!outFile) {
					// We failed to open the file: throw an exception.
					throw runtime_error{ format("failed to write {}, {}, {} in the file {} for saving.", 
						person.getFirstName(), 
						person.getLastName(),
						person.getInitials(),
						filename.data()) 
					};
				}
			}
		}

		void Database::load(string_view filename)
		{
			ifstream inFile{ filename.data() };
			if (!inFile) {
				// We failed to open the file: throw an exception.
				throw runtime_error{ format("failed to open the file {} for loading.", filename.data()) };
			}

			while (inFile) {
				// Read line by line, so we can skip empty lines.
				// The last line in the file is empty, for example.
				string line;
				getline(inFile, line);
				if (!inFile && !inFile.eof()) {
					throw runtime_error{ format("failed to read line from file.") };
				}
				if (line.empty()) { // Skip empty lines
					continue;
				}

				// Make a string stream and parse it.
				istringstream inLine{ line };
				string firstName, lastName, initials;
				inLine >> quoted(firstName) >> quoted(lastName) >> quoted(initials);
				if (inLine.bad()) {
					cerr << "Error reading person. Ignoring." << endl;
					continue;
				}

				// Create a person and add it to the database.
				m_persons.push_back(Person{ move(firstName), move(lastName), move(initials) });
			}
		}

		void Database::outputAll(ostream& output) const
		{
			for (const auto& person : m_persons) {
				person.output(output);
			}
		}

		void test() {
			try {
				// Fill a database.
				Database db;
				db.add(Person{ "John", "Doe" });
				db.add(Person{ "Marc", "Gregoire", "Mg" });
				db.add(Person{ "Peter", "Van Weert", "PVW" });

				// Output all persons in the database to standard output.
				cout << "Initial database contents:" << endl;
				db.outputAll(cout);

				// Save the database to a file.
				db.save("person_ch14.db");

				// Clear the database.
				db.clear();
				cout << "\nDatabase contents after clearing:" << endl;
				db.outputAll(cout);

				// Load database from file.
				cout << "\nLoading database from file..." << endl;
				db.load("person_ch14.db");
				cout << "\nDatabase contents after loading from file:" << endl;
				db.outputAll(cout);
			}
			catch (const exception& e) {
				cerr << format("Caught exception in original test code: {}", e.what()) << endl;
			}
			try {
				// Fill a database.
				Database db;
				db.add(Person{ "John", "Doe" });
				db.add(Person{ "Marc", "Gregoire", "Mg" });
				db.add(Person{ "Peter", "Van Weert", "PVW" });

				// Output all persons in the database to standard output.
				cout << "Initial database contents:" << endl;
				db.outputAll(cout);

				// Save the database to a read only file.
				db.save("read_only.db");

				// Clear the database.
				db.clear();
				cout << "\nDatabase contents after clearing:" << endl;
				db.outputAll(cout);

				// Load database from file.
				cout << "\nLoading database from file..." << endl;
				db.load("person_ch14.db");
				cout << "\nDatabase contents after loading from file:" << endl;
				db.outputAll(cout);
			}
			catch (const exception& e) {
				cerr << format("Caught exception in problematic test code for writing: {}", e.what()) << endl;
			}
			try {
				// Fill a database.
				Database db;
				// Load database from file.
				cout << "\nLoading database from file..." << endl;
				db.load("write_only.db");
				cout << "\nDatabase contents after loading from file:" << endl;
				db.outputAll(cout);
			}
			catch (const exception& e) {
				cerr << format("Caught exception in problematic test code for reading: {}", e.what()) << endl;
			}

		}
		
	}
	namespace ex4 {
		using namespace std;

		class SpreadsheetCell
		{
		public:
			SpreadsheetCell() = default;
			SpreadsheetCell(double initialValue);
			SpreadsheetCell(std::string_view initialValue);

			void setValue(double value);
			double getValue() const;

			void setString(std::string_view value);
			std::string getString() const;

		private:
			std::string doubleToString(double value) const;
			double stringToDouble(std::string_view value) const;

			double m_value{ 0 };
		};

		class Spreadsheet
		{
		public:
			Spreadsheet(size_t width, size_t height);
			Spreadsheet(const Spreadsheet& src);
			Spreadsheet(Spreadsheet&& src) noexcept; // Move constructor
			~Spreadsheet();

			Spreadsheet& operator=(const Spreadsheet& rhs);
			Spreadsheet& operator=(Spreadsheet&& rhs) noexcept;  // Move assignment

			void setCellAt(size_t x, size_t y, const SpreadsheetCell& cell);
			SpreadsheetCell& getCellAt(size_t x, size_t y);

			void swap(Spreadsheet& other) noexcept;

			static const size_t m_maxwidth{ 100 };
			static const size_t m_maxheight{ 100 };

		private:
			void verifyCoordinate(size_t x, size_t y) const;

			size_t m_width{ 0 };
			size_t m_height{ 0 };
			SpreadsheetCell** m_cells{ nullptr };
		};

		void swap(Spreadsheet& first, Spreadsheet& second) noexcept;

		class InvalidCoordinate : public exception
		{
		public:
			InvalidCoordinate(size_t width, size_t height, size_t maxwidth, size_t maxheight) : 
				m_width{ width }, 
				m_height{ height },
				m_maxwidth{ maxwidth },
				m_maxheight{ maxheight } {}
			const char* what() const noexcept override { return m_message.c_str(); }
		private:
			size_t m_width{ 0 };
			size_t m_height{ 0 };
			size_t m_maxwidth{ 0 };
			size_t m_maxheight{ 0 };
			string m_message{
				format("Allowed range:[0-{})*[0-{}), but received {}*{}",m_maxwidth,m_maxheight,m_width,m_height)
			};
		};

		SpreadsheetCell::SpreadsheetCell(double initialValue)
			: m_value{ initialValue }
		{
		}

		SpreadsheetCell::SpreadsheetCell(string_view initialValue)
			: m_value{ stringToDouble(initialValue) }
		{
		}

		void SpreadsheetCell::setValue(double value)
		{
			m_value = value;
		}

		double SpreadsheetCell::getValue() const
		{
			return m_value;
		}

		void SpreadsheetCell::setString(string_view value)
		{
			m_value = stringToDouble(value);
		}

		string SpreadsheetCell::getString() const
		{
			return doubleToString(m_value);
		}

		string SpreadsheetCell::doubleToString(double value) const
		{
			return to_string(value);
		}

		double SpreadsheetCell::stringToDouble(string_view value) const
		{
			double number{ 0 };
			from_chars(value.data(), value.data() + value.size(), number);
			return number;
		}

		Spreadsheet::Spreadsheet(size_t width, size_t height)
		try
			: m_width{ width }
			, m_height{ height }
		{
			cout << "Normal constructor" << endl;

			m_cells = new SpreadsheetCell * [m_width];
			for (size_t i{ 0 }; i < m_width; i++) {
				m_cells[i] = new SpreadsheetCell[m_height];
			}
		}
		catch (const exception& e) {
			cerr << format("Caught exception in Spreadsheet::Spreadsheet(size_t width, size_t height): {}", e.what()) << endl;
		}

		Spreadsheet::~Spreadsheet()
		{
			try {
				for (size_t i{ 0 }; i < m_width; i++) {
					delete[] m_cells[i];
				}
				delete[] m_cells;
				m_cells = nullptr;
			}
			catch (const exception& e) {
				cerr << format("Caught exception in Spreadsheet::~Spreadsheet(): {}, delete failed", e.what()) << endl;
			}
		}

		Spreadsheet::Spreadsheet(const Spreadsheet& src)
			: Spreadsheet{ src.m_width, src.m_height }
		{
			cout << "Copy constructor" << endl;

			// The ctor-initializer of this constructor delegates first to the
			// non-copy constructor to allocate the proper amount of memory.

			// The next step is to copy the data.
			for (size_t i{ 0 }; i < m_width; i++) {
				for (size_t j{ 0 }; j < m_height; j++) {
					m_cells[i][j] = src.m_cells[i][j];
				}
			}
		}

		void Spreadsheet::verifyCoordinate(size_t x, size_t y) const
		{
			if (x >= m_width || y >= m_height) {
				throw InvalidCoordinate{ x,y,m_width,m_height };
			}
		}

		void Spreadsheet::setCellAt(size_t x, size_t y, const SpreadsheetCell& cell)
		{
			verifyCoordinate(x, y);
			m_cells[x][y] = cell;
		}

		SpreadsheetCell& Spreadsheet::getCellAt(size_t x, size_t y)
		{
			verifyCoordinate(x, y);
			return m_cells[x][y];
		}

		void Spreadsheet::swap(Spreadsheet& other) noexcept
		{
			std::swap(m_width, other.m_width);
			std::swap(m_height, other.m_height);
			std::swap(m_cells, other.m_cells);
		}

		void swap(Spreadsheet& first, Spreadsheet& second) noexcept
		{
			first.swap(second);
		}

		Spreadsheet& Spreadsheet::operator=(const Spreadsheet& rhs)
		{
			cout << "Copy assignment operator" << endl;

			// Copy-and-swap idiom
			Spreadsheet temp{ rhs }; // Do all the work in a temporary instance
			swap(temp); // Commit the work with only non-throwing operations
			return *this;
		}

		// Move constructor
		Spreadsheet::Spreadsheet(Spreadsheet&& src) noexcept
		{
			cout << "Move constructor" << endl;

			ex4::swap(*this, src);
		}

		// Move assignment operator
		Spreadsheet& Spreadsheet::operator=(Spreadsheet&& rhs) noexcept
		{
			cout << "Move assignment operator" << endl;

			ex4::swap(*this, rhs);
			return *this;
		}

		Spreadsheet createObject()
		{
			return Spreadsheet{ 3, 2 };
		}

		void test() {
			vector<Spreadsheet> vec;
			for (size_t i{ 0 }; i < 2; ++i) {
				cout << "Iteration " << i << endl;
				vec.push_back(Spreadsheet{ 100, 100 });
				cout << endl;
			}

			Spreadsheet s{ 2, 3 };
			s = createObject();

			Spreadsheet s2{ 5, 6 };
			s2 = s;

			try {
				Spreadsheet s{ 2, 3 };
				s.getCellAt(1, 2);
				s.getCellAt(2, 3);
			}
			catch (const exception& e) {
				cerr << format("Caught exception for getCellAt: {}", e.what()) << endl;
			}

			try {
				Spreadsheet s{ 50, 30 };
				s.setCellAt(25, 15, SpreadsheetCell{ 2 });
				s.setCellAt(53, 33, SpreadsheetCell{ 6 });
			}
			catch (const exception& e) {
				cerr << format("Caught exception for setCellAt: {}", e.what()) << endl;
			}
		}
	}
}