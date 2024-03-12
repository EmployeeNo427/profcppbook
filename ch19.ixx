export module ch19;
import std;

export namespace ch19 {
	namespace exercises {
		namespace ex1 {
			using namespace std;
			template<predicate<int, int> Matcher, invocable<size_t, int, int> MatchHandler>
			void findMatches(span<const int> values1, span<const int> values2,
				Matcher matcher, MatchHandler handler)
			{
				if (values1.size() != values2.size()) { return; } // Must be same size.

				for (size_t i{ 0 }; i < values1.size(); ++i) {
					if (matcher(values1[i], values2[i])) {
						handler(i, values1[i], values2[i]);
					}
				}
			}

			/*void printMatch(size_t position, int value1, int value2)
			{
				println("Match found at position {} ({}, {})", position, value1, value2);
			}

			class IsLargerThan
			{
			public:
				explicit IsLargerThan(int value) : m_value{ value } {}

				bool operator()(int value1, int value2) const {
					return value1 > m_value && value2 > m_value;
				}

			private:
				int m_value;
			};*/

			void test()
			{
				vector values1{ 2, 500, 6, 9, 10, 101, 1 };
				vector values2{ 4, 4, 2, 9, 0, 300, 1 };
				double value{ 100 };
				auto IsLargerThan{ 
					[value](int value1, int value2) {return value1 > value && value2 > value; }
				};
				auto printMatch{
					[](size_t position, int value1, int value2) {
						println("Match found at position {} ({}, {})", position, value1, value2);
						}
				};


				findMatches(values1, values2, IsLargerThan, printMatch);
			}
		}
		namespace ex2 {
			using namespace std;
			/*void func(int num, string_view str)
			{
				println("func({}, {})", num, str);
			}*/
			void test() {
				// Bind second argument to a fixed value.
				string myString{ "abc" };
				auto f1{ bind([](int num, string_view str) {println("func({}, {})", num, str); }, placeholders::_1, myString) };
				f1(16);

				// Rearrange arguments
				auto f2{ bind([](int num, string_view str) {println("func({}, {})", num, str); }, placeholders::_2, placeholders::_1) };
				f2("Test", 32);
			}
			void test_textbook() {
				// Bind second argument to a fixed value.
				string myString{ "abc" };
				auto f1{ [&myString](int num) { println("func({}, {})", num, myString); } };
				f1(16);

				// Rearrange arguments
				auto f2{ [](string_view str,int num) {println("func({}, {})", num, str); }};
				f2("Test", 32);
			}
		}
		namespace ex3 {
			using namespace std;
			template<predicate<int, int> Matcher, invocable<size_t, int, int> MatchHandler>
			void findMatches(span<const int> values1, span<const int> values2,
				Matcher matcher, MatchHandler handler)
			{
				if (values1.size() != values2.size()) { return; } // Must be same size.

				for (size_t i{ 0 }; i < values1.size(); ++i) {
					if (matcher(values1[i], values2[i])) {
						handler(i, values1[i], values2[i]);
					}
				}
			}

			bool intEqual(int value1, int value2)
			{
				return value1 == value2;
			}

			bool bothOdd(int value1, int value2)
			{
				return value1 % 2 == 1 && value2 % 2 == 1;
			}

			class Handler
			{
			public:
				void handleMatch(size_t position, int value1, int value2)
				{
					println("Match found at position {} ({}, {})",
						position, value1, value2);
				}
			};

			void test() {
				Handler handler;

				vector values1{ 2, 5, 6, 9, 10, 1, 1 };
				vector values2{ 4, 4, 2, 9, 0, 3, 1 };
				println("Calling findMatches() using intEqual():");
				findMatches(values1, values2, intEqual,
					[&handler](size_t position, int value1, int value2) {handler.handleMatch(position, value1, value2); });

				println("Calling findMatches() using bothOdd():");
				findMatches(values1, values2, bothOdd,
					[&handler](size_t position, int value1, int value2) {handler.handleMatch(position, value1, value2); });
			}
		}
		namespace ex4 {
			using namespace std;
			void printRange(string_view message, auto& range)
			{
				cout << message;
				for (const auto& value : range) { cout << value << " "; }
				cout << endl;
			}
			void test() {
				vector values{ 1, 2, 3, 2, 1, 2, 4, 5 };
				printRange("Before erase: ", values);
				erase_if(values, [](auto& value) {return value % 2 != 0; }); 
				printRange("After erase: ", values);
			}
		}
		namespace ex5 {
			using namespace std;
			class Processor {
			public:
				Processor(auto callback) :cb{ callback } {}
				int operator()(int i1) { return cb(i1); }
			private:
				function<int(int)> cb{};
			};

			int square(int value) { return value * value; }
			int cube(int value) { return value * value * value; }

			void test() {
				Processor p1([](int i1) {return i1 * 2; });
				Processor p2([](int i1) {return i1*i1*i1; });
				cout<<p1(1)<<" "<<p2(3)<<endl;
				{
					Processor processor{ square };
					println("{}", processor(2));
				}

				{
					Processor processor{ cube };
					println("{}", processor(2));
				}
			}
		}
		namespace ex6 {
			using namespace std;
			
			void test() {
				auto power{ [](this auto& self, int n, int exponent) {
					if (exponent == 0) { return static_cast<double>(1); }
					if (exponent < 0) { return static_cast<double>(1 / (n * self(n, abs(exponent) - 1))); }
					return static_cast<double>(n * self(n, exponent - 1));
					}
				};
				println("Powers of two with exponents between -10 and 10");
				for (int i{ -10 }; i < 11; ++i) { println("({},{})", i, power(2,i)); }
			}
			void test_textbook() {
				auto power{ [](this auto& self, double value, int exponent) {
					if (exponent == 0) { return 1.0; }
					else if (exponent < 0) { return 1.0 / self(value, -exponent); }
					else { return value * self(value, exponent - 1); }
				} };

				const double value{ 2.0 };
				for (int exponent{ -10 }; exponent <= 10; ++exponent) {
					println("{}^{} = {}", value, exponent, power(value, exponent));
				}
			}

		}
	}
}