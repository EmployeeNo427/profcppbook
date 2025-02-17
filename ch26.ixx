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

				consteval unsigned long long fibonacci(unsigned int n) {
					unsigned long long a{ 0 };
					unsigned long long b{ 1 };

					unsigned long long temp{0};

					for (unsigned long long ull{ 0 }; ull < n;++ull) {
						temp = a + b;
						swap(a, b);
						swap(b,temp);
					}
					return a;
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
		namespace ex4 {
			namespace myanswer {
				using namespace std;

				template<typename T, typename... Us>
				concept SameTypes = (same_as<T, Us> && ...);

				template<typename T, typename... Tn>
					requires SameTypes<T, Tn...>
				void push_back_values(vector<T>& vt, const Tn&... args) {
					(vt.push_back(args), ...);
				}

				template<typename T, typename... Tn>
					requires SameTypes<T, Tn...>
				void insert_values(vector<T>& vt, const Tn&... args) {
					(vt.insert(end(vt), args), ...);
				}

				void test() {
					vector<int> vi;
					vector<string> vs;
					vector<double> vd;

					push_back_values(vi, 1, 5, 6, 6, 7, 3);
					insert_values(vi, 1, 5, 6, 6, 7, 3);
					push_back_values(vs, "asdasd"s, "asdcv"s, "cvbbcv"s, "vxcvxcv"s, "Hello vbbi"s, "kop"s);
					insert_values(vs, "asdasd"s, "asdcv"s, "cvbbcv"s, "vxcvxcv"s, "Hello vbbi"s, "kop"s);
					push_back_values(vd, 4.5, 6.872, 3.14159, 75.0);
					insert_values(vd, 4.5, 6.872, 3.14159, 75.0);

					/*for (auto& i : vi) {
						print("{} ", i);
					}
					println("");
					for (auto& s : vs) {
						print("{} ", s);
					}
					println("");
					for (auto& d : vd) {
						print("{} ", d);
					}
					println("");*/

					println("{:n}", vi);
					println("{:n}", vs);
					println("{:n}", vd);

				}
			}
		}
		namespace ex5 {
			namespace myanswer {
				using namespace std;

				template<typename T1, typename T2>
				decltype(auto) multiply(T1 t1, T2 t2) {
					if constexpr (is_arithmetic_v<T1> && is_arithmetic_v<T2>) {
						return t1 * t2;
					}
					else {
						throw invalid_argument{
							"Either " + string{typeid(T1).name()} + " or " + string{typeid(T2).name()} + " is not arithmetic value."
						};
					}
				}

				void test() {
					try {
						println("ex5:");
						println("{}", multiply(1, 2));
						println("{}", multiply(4.23, 6.789));
						println("{}", multiply(2, 3));
						println("{}", multiply(4.12, 2));
						println("{}", multiply(0, 9.815));
						println("{}", multiply(-1, 67.12));
						
						//Testing thowring exception
						//multiply("what", 67.12);
						//multiply(3, "boo!");
						//multiply("good", "job!");
					}
					catch (const exception& e) {
						cerr << e.what() << endl;
					}
				}

				
			}
		}
		namespace ex6 {
			namespace myanswer {
				using namespace std;

				template <typename T>
				concept Arithmeticable = is_arithmetic_v<T>;

				decltype(auto) multiply(const Arithmeticable auto& t1, const Arithmeticable auto& t2)
				{
					return t1 * t2;
				}

				void test() {
					println("ex6:");
					println("{}", multiply(1, 2));
					println("{}", multiply(4.23, 6.789));
					println("{}", multiply(2, 3));
					println("{}", multiply(4.12, 2));
					println("{}", multiply(0, 9.815));
					println("{}", multiply(-1, 67.12));

					//Testing concepts validation
					/*multiply("what", 67.12);
					multiply(3, "boo!");
					multiply("good", "job!");*/
				}


			}
		}
	}
}