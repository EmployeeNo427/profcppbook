export module ch26;

import std;

export namespace ch26 {
	namespace exercises {
		namespace ex1 {
			namespace myanswer {
				using namespace std;

				template <typename KeyType, typename ValueType>
					class KeyValuePair {
					public:
						explicit KeyValuePair(KeyType key, ValueType value) :m_key{ move(key) }, m_value{ move(value) } {}
						const KeyType& getkey() const { return m_key; }
						const ValueType& getvalue() const { return m_value; }
						void setkey(KeyType key) { m_key = move(key); }
						void setvalue(ValueType value) { m_value = move(value); }
					private:
						KeyType m_key;
						ValueType m_value;
				};

				template<typename KeyType>
					class KeyValuePair<KeyType, const char*> {
					public:
						explicit KeyValuePair(KeyType key, const char* value) :m_key{ move(key) }, m_value{ value } {}
						const KeyType& getkey() const { return m_key; }
						const string& getvalue() const { return m_value; }
						void setkey(KeyType key) { m_key = move(key); }
						void setvalue(const char* value) { m_value = value; }
					private:
						KeyType m_key;
						string m_value;
				};

				void test() {
					using namespace std;

					{
						KeyValuePair<int, string> intstr_pair{ 1,"Hello" };
						cout << format("key: {}, value: {}\n", intstr_pair.getkey(), intstr_pair.getvalue());
						intstr_pair.setkey(2);
						intstr_pair.setvalue("walawalabong");
						cout << format("key: {}, value: {}\n", intstr_pair.getkey(), intstr_pair.getvalue());
					}

					{
						KeyValuePair intstr_pair{ 6,"Hello"s };
						cout << format("key: {}, value: {}\n", intstr_pair.getkey(), intstr_pair.getvalue());
						intstr_pair.setkey(9);
						intstr_pair.setvalue("somethingstratigtaion");
						cout << format("key: {}, value: {}\n", intstr_pair.getkey(), intstr_pair.getvalue());
					}

					{
						KeyValuePair charstr_pair{ 'a',"Hello" };
						cout << format("key: {}, value: {}\n", charstr_pair.getkey(), charstr_pair.getvalue());
						charstr_pair.setkey('b');
						charstr_pair.setvalue("walawalabong");
						cout << format("key: {}, value: {}\n", charstr_pair.getkey(), charstr_pair.getvalue());
					}

					{
						KeyValuePair intint_pair{ 3,4 };
						cout << format("key: {}, value: {}\n", intint_pair.getkey(), intint_pair.getvalue());
						intint_pair.setkey(1);
						intint_pair.setvalue(2);
						cout << format("key: {}, value: {}\n", intint_pair.getkey(), intint_pair.getvalue());
					}

					{
						KeyValuePair strstr_pair{ "nice","job" };//would save as string
						cout << format("key: {}, value: {}\n", strstr_pair.getkey(), strstr_pair.getvalue());
						strstr_pair.setkey("good");
						strstr_pair.setvalue("work");
						cout << format("key: {}, value: {}\n", strstr_pair.getkey(), strstr_pair.getvalue());
					}

				};
			}
		}
		namespace ex2 {
			namespace myanswer {
				using namespace std;

				template <unsigned int f>
				class Fibonacci
				{
				public:
					static constexpr unsigned long long value{ Fibonacci<f - 2>::value + Fibonacci<f - 1>::value };
				};

				template <>
				class Fibonacci<0>
				{
				public:
					static constexpr unsigned long long value{ 0 };
				};

				template <>
				class Fibonacci<1>
				{
				public:
					static constexpr unsigned long long value{ 1 };
				};

				template <unsigned int f>
				inline constexpr unsigned long long Fibonacci_v = Fibonacci<f>::value;

				void test()
				{
					println("{}", Fibonacci_v<6>);
					println("{}", Fibonacci_v<7>);
					println("{}", Fibonacci_v<8>);
					println("{}", Fibonacci_v<9>);
					println("{}", Fibonacci_v<10>);
					println("{}", Fibonacci_v<11>);
					println("{}", Fibonacci_v<12>);
				}
			}
		}
		namespace ex3 {
			namespace myanswer {
				using namespace std;

				consteval unsigned long long fibonacci(int n) {

					if (n == 0) { return 0; }
					else if (n == 1) { return 1; }
					else {
						unsigned long long minus_two{ 0 };
						unsigned long long minus_one{ 1 };
						unsigned long long result{};

						for (unsigned long long ull{ 1 }; ull < n; ++ull) {
							result = minus_two + minus_one;
							swap(minus_two, minus_one);
							minus_one = result;
						}
						return result;
					}				
				}

				void test(){
					println("{}", fibonacci(0));
					println("{}", fibonacci(1));
					println("{}", fibonacci(2));
					println("{}", fibonacci(3));
					println("{}", fibonacci(4));
					println("{}", fibonacci(5));
					println("{}", fibonacci(6));
					println("{}", fibonacci(7));
					println("{}", fibonacci(8));
					println("{}", fibonacci(9));
					println("{}", fibonacci(10));
					println("{}", fibonacci(11));
					println("{}", fibonacci(12));
				}
			}
		}
	}
}