export module ch12_exercise;
import std;

static const size_t NOT_FOUND{ static_cast<size_t>(-1) };

export namespace ex12_1 {

	export template <typename KeyType, typename ValueType>
		class KeyValuePair {
		public:
			KeyValuePair(const KeyType& key, const ValueType& value) :m_key{ key }, m_value{ value } {}
			const KeyType& getkey() const{ return m_key; }
			const ValueType& getvalue() const { return m_value; }
			void setkey(KeyType key) { m_key = key; }
			void setvalue(ValueType value) { m_value = value; }


		private:
			KeyType m_key;
			ValueType m_value;
	};

	export void test() {
		using namespace std;

		KeyValuePair<int, string> intstr_pair{ 1,"Hello" };
		cout << format("key: {}, value: {}\n", intstr_pair.getkey(), intstr_pair.getvalue());
		intstr_pair.setkey(2);
		intstr_pair.setvalue("walawalabong");
		cout << format("key: {}, value: {}\n", intstr_pair.getkey(), intstr_pair.getvalue());

		KeyValuePair charstr_pair{ 'a',"Hello"s };
		cout << format("key: {}, value: {}\n", charstr_pair.getkey(), charstr_pair.getvalue());
		charstr_pair.setkey('b');
		charstr_pair.setvalue("walawalabong"s);
		cout << format("key: {}, value: {}\n", charstr_pair.getkey(), charstr_pair.getvalue());

		KeyValuePair intint_pair{ 3,4 };
		cout << format("key: {}, value: {}\n", intint_pair.getkey(), intint_pair.getvalue());
		intint_pair.setkey(1);
		intint_pair.setvalue(2);
		cout << format("key: {}, value: {}\n", intint_pair.getkey(), intint_pair.getvalue());

	};
}
export namespace ex12_2 {
	export template <typename KeyType, typename ValueType>
		class KeyValuePair {
		public:
			KeyValuePair(const KeyType& key, const ValueType& value) :m_key{ key }, m_value{ value } {}
			const KeyType& getkey() const { return m_key; }
			const ValueType& getvalue() const { return m_value; }
			void setkey(const KeyType& key) { m_key = key; }
			void setvalue(const ValueType& value) { m_value = value; }
		private:
			KeyType m_key;
			ValueType m_value;
	};

	export template<>
		class KeyValuePair<const char*, const char*> {
		public:
			KeyValuePair(const char* key, const char* value) :m_key{ key }, m_value{ value } {}
			const std::string& getkey() { return m_key; }
			const std::string& getvalue() { return m_value; }
			void setkey(const std::string& key) { m_key = key; }
			void setvalue(const std::string& value) { m_value = value; }
		private:
			std::string m_key;
			std::string m_value;
	};

	KeyValuePair(const char*, const char*)->KeyValuePair<const char*, const char*>;

	export void test() {
		using namespace std;

		KeyValuePair<int, string> intstr_pair{ 1,"Hello" };
		cout << format("key: {}, value: {}\n", intstr_pair.getkey(), intstr_pair.getvalue());
		intstr_pair.setkey(2);
		intstr_pair.setvalue("walawalabong");
		cout << format("key: {}, value: {}\n", intstr_pair.getkey(), intstr_pair.getvalue());

		KeyValuePair charstr_pair{ 'a',"Hello"s };
		cout << format("key: {}, value: {}\n", charstr_pair.getkey(), charstr_pair.getvalue());
		charstr_pair.setkey('b');
		charstr_pair.setvalue("walawalabong"s);
		cout << format("key: {}, value: {}\n", charstr_pair.getkey(), charstr_pair.getvalue());

		KeyValuePair intint_pair{ 3,4 };
		cout << format("key: {}, value: {}\n", intint_pair.getkey(), intint_pair.getvalue());
		intint_pair.setkey(1);
		intint_pair.setvalue(2);
		cout << format("key: {}, value: {}\n", intint_pair.getkey(), intint_pair.getvalue());

		KeyValuePair strstr_pair{ "nice","job"};//would save as string
		cout << format("key: {}, value: {}\n", strstr_pair.getkey(), strstr_pair.getvalue());
		strstr_pair.setkey("good");
		strstr_pair.setvalue("work");
		cout << format("key: {}, value: {}\n", strstr_pair.getkey(), strstr_pair.getvalue());

	};
}
export namespace ex12_3 {
	export template <std::integral KeyType, std::floating_point ValueType>
		class KeyValuePair {
		public:
			KeyValuePair(const KeyType& key, const ValueType& value) :m_key{ key }, m_value{ value } {}
			const KeyType& getkey() const { return m_key; }
			const ValueType& getvalue() const { return m_value; }
			void setkey(KeyType key) { m_key = key; }
			void setvalue(ValueType value) { m_value = value; }


		private:
			KeyType m_key;
			ValueType m_value;
	};

	export void test() {
		using namespace std;

		KeyValuePair intfloat_pair{ 3,3.1415926 };
		cout << format("key: {}, value: {}\n", intfloat_pair.getkey(), intfloat_pair.getvalue());
		intfloat_pair.setkey(1);
		intfloat_pair.setvalue(2);
		cout << format("key: {}, value: {}\n", intfloat_pair.getkey(), intfloat_pair.getvalue());

		//KeyValuePair intstr_pair{ 1,"Hello" };
		//cout << format("key: {}, value: {}\n", intstr_pair.getkey(), intstr_pair.getvalue());
		//intstr_pair.setkey(2);
		//intstr_pair.setvalue("walawalabong");
		//cout << format("key: {}, value: {}\n", intstr_pair.getkey(), intstr_pair.getvalue());

		//KeyValuePair charstr_pair{ 'a',"Hello"s };
		//cout << format("key: {}, value: {}\n", charstr_pair.getkey(), charstr_pair.getvalue());
		//charstr_pair.setkey('b');
		//charstr_pair.setvalue("walawalabong"s);
		//cout << format("key: {}, value: {}\n", charstr_pair.getkey(), charstr_pair.getvalue());

		KeyValuePair<int,double> intint_pair{ 3,4 };
		cout << format("key: {}, value: {}\n", intint_pair.getkey(), intint_pair.getvalue());
		intint_pair.setkey(1);
		intint_pair.setvalue(2);
		cout << format("key: {}, value: {}\n", intint_pair.getkey(), intint_pair.getvalue());

	};
}
export namespace ex12_4 {
	template <typename T>
	concept my_numeric = std::integral<T> || std::floating_point<T>;

	template <typename T>
	concept answer_numeric = requires(const T& t) { std::to_string(t); };

	decltype(auto) concat(const answer_numeric auto& v1, const answer_numeric auto& v2) {
		return std::to_string(v1) + std::to_string(v2);
	}

	void test() {
		using namespace std;
		auto result1{ concat(1.414, 3) };
		auto result2{ concat(1, 3) };
		auto result3{ concat(3, -3.1415926) };
		cout << format("1:{}, 2:{}, 3:{}\n", result1, result2, result3);
		//auto result{ concat("hello", "world")};
	}
}
export namespace ex12_5 {
	template <typename T>
	concept answer_numeric = requires(const T & t) { std::to_string(t); };

	decltype(auto) concat(const answer_numeric auto& v1, const answer_numeric auto& v2) {
		return std::to_string(v1) + std::to_string(v2);
	}

	decltype(auto) concat(const answer_numeric auto& v1, std::string_view v2) {
		return std::to_string(v1) + std::string{ v2 };
	}

	decltype(auto) concat(std::string_view v1, const answer_numeric auto& v2) {
		return std::string{ v1 } + std::to_string(v2);
	}

	decltype(auto) concat(std::string_view v1, std::string_view v2) {
		return std::string{ v1 } + std::string{ v2 };
	}

	void test() {
		using namespace std;
		auto result1{ concat(1.414, 3) };
		auto result2{ concat(1, 3) };
		auto result3{ concat(3, -3.1415926) };
		auto result4{ concat("hello", "world") };
		auto result5{ concat("hello", 42) };
		auto result6{ concat(42, "world")};
		cout << format("1:{}, 2:{}, 3:{}, 4:{}, 5:{}, 6:{}\n", result1, result2, result3, result4, result5, result6);
	}
}
export namespace ex12_6 {
	using namespace std;

	class SpreadsheetCell
	{
	public:
		SpreadsheetCell() = default;
		SpreadsheetCell(double initialValue);
		SpreadsheetCell(std::string_view initialValue);

		void set(double value);
		void set(std::string_view value);

		double getValue() const;
		std::string getString() const;

		SpreadsheetCell& operator+=(const SpreadsheetCell& rhs);
		SpreadsheetCell& operator-=(const SpreadsheetCell& rhs);
		SpreadsheetCell& operator*=(const SpreadsheetCell& rhs);
		SpreadsheetCell& operator/=(const SpreadsheetCell& rhs);

		[[nodiscard]] auto operator<=>(const SpreadsheetCell&) const = default;

	private:
		static std::string doubleToString(double value);
		static double stringToDouble(std::string_view value);

		double m_value{ 0 };
	};

	export SpreadsheetCell operator+(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
	export SpreadsheetCell operator-(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
	export SpreadsheetCell operator*(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);
	export SpreadsheetCell operator/(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);

	SpreadsheetCell::SpreadsheetCell(double initialValue)
		: m_value{ initialValue }
	{
	}

	SpreadsheetCell::SpreadsheetCell(string_view initialValue)
		: m_value{ stringToDouble(initialValue) }
	{
	}

	void SpreadsheetCell::set(double value)
	{
		m_value = value;
	}

	double SpreadsheetCell::getValue() const
	{
		return m_value;
	}

	void SpreadsheetCell::set(string_view value)
	{
		m_value = stringToDouble(value);
	}

	string SpreadsheetCell::getString() const
	{
		return doubleToString(m_value);
	}

	string SpreadsheetCell::doubleToString(double value)
	{
		return to_string(value);
	}

	double SpreadsheetCell::stringToDouble(string_view value)
	{
		double number{ 0 };
		from_chars(value.data(), value.data() + value.size(), number);
		return number;
	}

	SpreadsheetCell operator+(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs)
	{
		auto result{ lhs };  // Local copy
		result += rhs;       // Forward to +=()
		return result;

		//return SpreadsheetCell { lhs.getValue() + rhs.getValue() };
	}

	SpreadsheetCell operator-(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs)
	{
		auto result{ lhs };  // Local copy
		result -= rhs;       // Forward to -=()
		return result;

		//return SpreadsheetCell { lhs.getValue() - rhs.getValue() };
	}

	SpreadsheetCell operator*(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs)
	{
		auto result{ lhs };  // Local copy
		result *= rhs;       // Forward to *=()
		return result;

		//return SpreadsheetCell { lhs.getValue() * rhs.getValue() };
	}

	SpreadsheetCell operator/(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs)
	{
		auto result{ lhs };  // Local copy
		result /= rhs;       // Forward to /=()
		return result;

		//if (rhs.getValue() == 0) {
		//	throw invalid_argument { "Divide by zero." };
		//}
		//return SpreadsheetCell { lhs.getValue() / rhs.getValue() };
	}

	SpreadsheetCell& SpreadsheetCell::operator+=(const SpreadsheetCell& rhs)
	{
		set(getValue() + rhs.getValue());
		return *this;
	}

	SpreadsheetCell& SpreadsheetCell::operator-=(const SpreadsheetCell& rhs)
	{
		set(getValue() - rhs.getValue());
		return *this;
	}

	SpreadsheetCell& SpreadsheetCell::operator*=(const SpreadsheetCell& rhs)
	{
		set(getValue() * rhs.getValue());
		return *this;
	}

	SpreadsheetCell& SpreadsheetCell::operator/=(const SpreadsheetCell& rhs)
	{
		if (rhs.getValue() == 0) {
			throw invalid_argument{ "Divide by zero." };
		}
		set(getValue() / rhs.getValue());
		return *this;
	}


	template <std::equality_comparable T>
	size_t Find(const T& value, const T* arr, size_t size)
	{
		for (size_t i{ 0 }; i < size; i++) {
			if (arr[i] == value) {
				return i; // Found it; return the index.
			}
		}
		return NOT_FOUND; // Failed to find it; return NOT_FOUND.
	}

	template <typename T> requires std::equality_comparable<T> && std::floating_point<T>
	bool AreEqual(T x, T y, int precision = 2)
	{
		// Scale the machine epsilon to the magnitude of the given values and multiply
		// by the required precision.
		return fabs(x - y) <= numeric_limits<T>::epsilon() * fabs(x + y) * precision
			|| fabs(x - y) < numeric_limits<T>::min(); // The result is subnormal.
	}

	template <typename T> requires std::equality_comparable<T> && std::floating_point<T>
	size_t Find(const T& value, const T* arr, size_t size)
	{
		for (size_t i{ 0 }; i < size; i++) {
			if (AreEqual(arr[i], value)) {
				return i; // Found it; return the index.
			}
		}
		return NOT_FOUND; // Failed to find it; return NOT_FOUND.
	}

	template <typename T, size_t N> requires std::equality_comparable<T>
	size_t Find(const T& value, const T(&arr)[N])
	{
		return Find(value, arr, N);
	}

	void TestFind() {
		// Test with a C-style array
		int intArray[] = { 1, 2, 3, 4, 5 };
		size_t index = Find(3, intArray, 5);
		cout << "Index of 3 in intArray: " << (index != NOT_FOUND ? to_string(index) : "Not Found") << endl;

		// Test with std::vector
		vector<double> doubleVector = { 1.1, 2.2, 3.3, 4.4, 5.5 };
		index = Find(3.3, doubleVector.data(), doubleVector.size());
		cout << "Index of 3.3 in doubleVector: " << (index != NOT_FOUND ? to_string(index) : "Not Found") << endl;

		// Test with std::array
		array<string, 3> stringArray = { "hello", "world", "test" };
		index = Find(string("world"), stringArray.data(), stringArray.size());
		cout << "Index of 'world' in stringArray: " << (index != NOT_FOUND ? to_string(index) : "Not Found") << endl;

		// Test with floating point precision
		float floatArray[] = { 1.0f, 1.5f, 2.0f };
		index = Find(1.5001f, floatArray, 3);
		cout << "Index of 1.5001 in floatArray: " << (index != NOT_FOUND ? to_string(index) : "Not Found") << endl;

		int myInt{ 3 }, intArray_2[]{ 1, 2, 3, 4 };
		const size_t sizeIntArray{ size(intArray_2) };

		size_t res;
		res = Find(myInt, intArray_2, sizeIntArray);        // calls Find<int> by deduction.
		res = Find<int>(myInt, intArray_2, sizeIntArray);   // calls Find<int> explicitly.
		res = Find(myInt, intArray_2);
		if (res != NOT_FOUND) { cout << res << endl; }
		else { cout << "Not found" << endl; }

		double myDouble{ 5.6 }, doubleArray[]{ 1.2, 3.4, 5.7, 7.5 };
		const size_t sizeDoubleArray{ size(doubleArray) };

		res = Find(myDouble, doubleArray, sizeDoubleArray);         // calls Find<double> by deduction.
		res = Find<double>(myDouble, doubleArray, sizeDoubleArray); // calls Find<double> explicitly.
		if (res != NOT_FOUND) { cout << res << endl; }
		else { cout << "Not found" << endl; }

		//res = Find(myInt, doubleArray, sizeDoubleArray);        // DOES NOT COMPILE! Arguments are different types.
		res = Find<double>(myInt, doubleArray, sizeDoubleArray);  // calls Find<double> explicitly, even with myInt.

		SpreadsheetCell cell1{ 10 };
		SpreadsheetCell cellArray[]{ SpreadsheetCell{ 4 }, SpreadsheetCell{ 10 } };
		const size_t sizeCellArray{ size(cellArray) };

		res = Find(cell1, cellArray, sizeCellArray);                  // calls Find<SpreadsheetCell> by deduction.
		res = Find<SpreadsheetCell>(cell1, cellArray, sizeCellArray); // calls Find<SpreadsheetCell> explicitly.

		cout << "Index of cell1{ 10 } in cellArray: " << (res != NOT_FOUND ? to_string(res) : "Not Found") << endl;
	}
}