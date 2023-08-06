export module hello_world;

import std;

using namespace std;

export void hello_world_test() {
	
	
	cout << "Hello World!" << endl;
	cout << "There are " << 219 << " ways I love you." << endl;
	cout << format("There are {} ways I love you.", 219) << endl;

	vector<char> char_set{ '-','\\','|','/' };
	for (unsigned int i = 0; i<30; ++i) {
		cout << char_set[i%char_set.size()] << '\r';
		this_thread::sleep_for(chrono::microseconds(200000));
	}
	cout << "Type in a integer and I will print it: " << endl;
	int value;
	cin >> value;
	cout << value;

	cout << "Permutation of 7: " << 7 * 6 * 5 * 4 * 3 * 2 * 1 << '\n';
};

export void test_uninitialized_variable() {
	

	int uninitializedInt;
	int initializedInt{ 7 };
	cout << format("{} is a random value", uninitializedInt) << endl;
	cout << format("{} was assigned an initial value", initializedInt) << endl;
}

export void test_limit() {
	
	
	cout << "int:\n";
	cout << format("Max int value: {}\n", numeric_limits<int>::max());
	cout << format("Min int value: {}\n", numeric_limits<int>::min());
	cout << format("Lowest int value: {}\n", numeric_limits<int>::lowest());

	cout << "\ndouble:\n";
	cout << format("Max double value: {}\n", numeric_limits<double>::max());
	cout << format("Min double value: {}\n", numeric_limits<double>::min());
	cout << format("Lowest double value: {}\n", numeric_limits<double>::lowest());
}

export void test_conversion() {
	

	cout << "int:\n";
	cout << format("Max int value: {}\n", numeric_limits<int>::max());

	cout << "\nshort:\n";
	cout << format("Max short value: {}\n", numeric_limits<short>::max());

	cout << "\nlong:\n";
	cout << format("Max short value: {}\n", numeric_limits<long>::max());

	cout << "\nfloat:\n";
	cout << format("Max float value: {}\n", numeric_limits<float>::max());

	cout << "\ndouble:\n";
	cout << format("Max double value: {}\n", numeric_limits<double>::max());

	int someInteger{ 256 };
	short someShort;
	long someLong;
	float someFloat;
	double someDouble;

	someInteger++;
	someInteger *= 2;
	someShort = static_cast<short>(someInteger);
	someLong = someShort * 10000;
	someFloat = someLong + 0.785f;
	someDouble = static_cast<double>(someFloat) / 100000;
	cout << someDouble << endl;
}

export void brilliant_calculation() {
	vector<int> socks_num{ 11,10,9,8,7,6,5,4,3,2 };
	cout << "total sock inspections:\n";
	cout << accumulate(socks_num.begin(), socks_num.end(),0) << '\n';
	cout << log2(16000) << '\n';
	cout << log2(38) << '\n';
}

export void test_switch() {
	enum class Mode {Default, Custom, Standard};

	int value{ 42 };
	Mode mode{ /* ... */ };
	switch (Mode mode{ Mode::Custom }) {
		using enum Mode;

		case Custom:
			value = 84;
			cout << "In custom;\t" << value<<"\n";
			[[fallthrough]];
		case Standard:
			cout << "In Standard;\t" << value << "\n";
		case Default:
			cout << "In Default;\t" << value << "\n";
			break;
	}
}

export void myFunction(int i, char c)
{
	cout << format("the value of i is {}", i) << endl;
	cout << format("the value of c is {}", c) << endl;
}

export auto addNumbers_1(int number1, int number2)
{
	cout << format("Entering function {}", __func__) << endl;
	return number1 + number2;
}

export int addNumbers_2(int a, int b) { cout << "int version called\n"; return a + b; }

export double addNumbers_2(double a, double b) { cout << "double version called\n"; return a + b; }

export [[nodiscard]] int func()
{
	return 42;
}

export optional<int> getData(bool giveIt)
{
	if (giveIt) {
		return 42;
	}
	return nullopt;  // or simply return {};
}

export double divideNumbers(double numerator, double denominator)
{
	if (denominator == 0) {
		throw invalid_argument{ "Denominator cannot be 0." };
	}
	return numerator / denominator;
}

