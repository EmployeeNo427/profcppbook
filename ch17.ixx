export module ch17;
import std;

export namespace ch17 {
	namespace exercises {
		namespace ex1 {
			using namespace std;
			using namespace ranges;
			void printRange(string_view message, auto& range)
			{
				cout << message;
				for (const auto& value : range) { cout << value << " "; }
				cout << endl;
			}
			void test() {
				auto result{ views::iota(10,101)
					| views::transform([](const auto& value) { return static_cast<int>(pow(value, 2)); })
					| views::filter([](const auto& value) { return value % 5 != 0; })
					| views::transform([](const auto& value) { return to_string(value); }) };
				printRange("Result: ", result);
			}
			void test_textbook() {
				auto result{ views::iota(10, 100)
					| views::transform([](const auto& v) { return v * v; })
					| views::filter([](const auto& v) { return v % 5 != 0; })
					| views::transform([](const auto& v) { return to_string(v); }) 
				};
				cout << "book answer:\n";
				for (const auto& v : result) {
					cout << v << " ";
				}
				cout << endl;
			}
		}
		namespace ex2 {
			using namespace std;
			class Person
			{
			public:
				Person(string first, string last)
					: m_firstName{ move(first) }, m_lastName{ move(last) } { }
				const string& getFirstName() const { return m_firstName; }
				const string& getLastName() const { return m_lastName; }
			private:
				string m_firstName;
				string m_lastName;
			};
			template <typename InputIter>
			auto sum(InputIter begin, InputIter end)
			{
				auto sum{ *begin };
				for (auto iter{ ++begin }; iter != end; ++iter) { sum += *iter; }
				return sum;
			}
			void printRange(string_view message, auto& range)
			{
				cout << message;
				for (const auto& value : range) { cout << value << " "; }
				cout << endl;
			}
			void test() {
				using Age = int;
				vector<pair<Person, Age>> persons{
					pair{ Person {"John", "White"} ,32 },
						pair{ Person {"Chris", "Blue"} ,46 },
						pair{ Person {"Zijian", "Guan"} ,23 },
						pair{ Person {"df", "dv"} ,12 },
						pair{ Person {"ff", "sdvv"} ,11 },
						pair{ Person {"ff", "sdv"} ,65 },
						pair{ Person {"vbb", "vbb"} ,89 }
				};
				auto result{ persons
					| ranges::views::values
					| ranges::views::filter([](const auto& value) { return value >= 12 && value <= 65; })
				};
				printRange("filtered ages", result);
				cout << sum(begin(result), end(result))/ ranges::distance(result);
			}
			void test_textbook() {
				vector persons{
					pair{ Person{ "Izzie", "Fellows" }, 11 },
					pair{ Person{ "Eshaan", "Cooper" }, 15 },
					pair{ Person{ "Rick", "Crouch" }, 48 },
					pair{ Person{ "Faye", "Pittman" }, 35 },
					pair{ Person{ "Jude", "Bone" }, 69 },
					pair{ Person{ "Ella-Louise", "Byers" }, 60 },
					pair{ Person{ "Jad", "Lott" }, 75 },
					pair{ Person{ "Teddie", "Love" }, 24 },
					pair{ Person{ "Niko", "Silva" }, 16 },
					pair{ Person{ "Bryan", "Melendez" }, 42 },
				};

				auto filteredAges{ ranges::views::common( // Convert the resulting range to a common range.
					persons
					| ranges::views::values   // Only interested in the second element of each pair, the values.
					| ranges::views::filter([](const auto& age) { return age >= 12 && age <= 65; })) }; // Filter on age.

				auto count{ distance(begin(filteredAges), end(filteredAges)) }; // Cannot use ranges::size(filteredAges) here.

				auto average{ sum(begin(filteredAges), end(filteredAges)) /
					static_cast<double>(count) };

				cout << "Average: " << average << endl;
			}
			void test_mix() {
				vector persons{
					pair{ Person{ "Izzie", "Fellows" }, 11 },
					pair{ Person{ "Eshaan", "Cooper" }, 15 },
					pair{ Person{ "Rick", "Crouch" }, 48 },
					pair{ Person{ "Faye", "Pittman" }, 35 },
					pair{ Person{ "Jude", "Bone" }, 69 },
					pair{ Person{ "Ella-Louise", "Byers" }, 60 },
					pair{ Person{ "Jad", "Lott" }, 75 },
					pair{ Person{ "Teddie", "Love" }, 24 },
					pair{ Person{ "Niko", "Silva" }, 16 },
					pair{ Person{ "Bryan", "Melendez" }, 42 },
				};
				auto result{ persons
					| ranges::views::values
					| ranges::views::filter([](const auto& value) { return value >= 12 && value <= 65; })
				};
				printRange("filtered ages\n", result);
				cout << "sum:";
				cout << sum(begin(result), end(result)) / static_cast<double>(ranges::distance(result));
			}
		}
		namespace ex3 {
			using namespace std;
			class Person
			{
			public:
				Person(string first, string last)
					: m_firstName{ move(first) }, m_lastName{ move(last) } { }
				const string& getFirstName() const { return m_firstName; }
				const string& getLastName() const { return m_lastName; }
			private:
				string m_firstName;
				string m_lastName;
			};
			ostream& operator<<(ostream& ostr, const Person& person)
			{
				ostr << quoted(person.getFirstName()) << quoted(person.getLastName());
				return ostr;
			}
			template <typename InputIter, typename OutputIter>
			void myCopy(InputIter begin, InputIter end, OutputIter target)
			{
				for (auto iter{ begin }; iter != end; ++iter, ++target) { *target = *iter; }
			}
			void test() {
				vector persons{
					pair{ Person{ "Izzie", "Fellows" }, 11 },
					pair{ Person{ "Eshaan", "Cooper" }, 15 },
					pair{ Person{ "Rick", "Crouch" }, 48 },
					pair{ Person{ "Faye", "Pittman" }, 35 },
					pair{ Person{ "Jude", "Bone" }, 69 },
					pair{ Person{ "Ella-Louise", "Byers" }, 60 },
					pair{ Person{ "Jad", "Lott" }, 75 },
					pair{ Person{ "Teddie", "Love" }, 24 },
					pair{ Person{ "Niko", "Silva" }, 16 },
					pair{ Person{ "Bryan", "Melendez" }, 42 },
				};

				auto result{ ranges::views::common( // Convert the resulting range to a common range.
					persons
					| ranges::views::keys   // Only interested in the first element of each pair
					| ranges::views::take(4)) 
				}; 
				myCopy(cbegin(result), cend(result), ostream_iterator<Person> { cout, "\n" });
				auto lastNameResult{ ranges::views::common( // Convert the resulting range to a common range.
					persons
					| ranges::views::keys   // Only interested in the first element of each pair
					| ranges::views::take(4)
					| ranges::views::transform([](const auto& person) { return person.getLastName(); })
				)
				};
				myCopy(cbegin(lastNameResult), cend(lastNameResult), ostream_iterator<string> { cout, "\n" });
			}
		}
	}
}