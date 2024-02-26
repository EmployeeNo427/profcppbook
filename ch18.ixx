export module ch18;
import std;
import phone_book_ch18;

export namespace ch18 {
	namespace exercises {
		namespace ex1 {
			using namespace std;
			void test(){
				vector<int> values{ 2,5 };
				values.insert(cbegin(values) + 1, 3);
				values.insert(cbegin(values) + 2, 4);

				for (const auto& value : values) { print("{} ", value); }
				println("");

				vector<int> vi{ 0,1 };
				values.insert(cbegin(values), cbegin(vi), cend(vi));

				for (const auto& value : values) { print("{} ", value); }
				println("");

				vector<int> vreverse;
				vreverse.insert(cbegin(vreverse), crbegin(values), crend(values));


				//println("{}", vreverse)
				for (const auto& value : vreverse) { print("{} ", value); }
				println("");
			}
			void test_textbook() {
				vector<int> values{ 2, 5 };

				// 1
				values.insert(begin(values) + 1, 3);
				values.insert(begin(values) + 2, 4);

				// 2
				vector<int> v2{ 0, 1 };
				values.insert(begin(values), cbegin(v2), cend(v2));

				// 3
				vector<int> v3;
				for (auto riter{ crbegin(values) }; riter != crend(values); ++riter) {
					v3.push_back(*riter);
				}

				// 4
				//println("{}", v3);

				// 5
				for (const auto& element : v3) {
					print("{} ", element);
				}
				println("");
			}
		}
		namespace ex2 {
			using namespace std;
			void test() {
				PhoneBook pb;
				pb.addNumber("Zijian Guan"_p, "1234567");
				pb.addNumber("Zijian Guan"_p, "6915974555");
				pb.addNumber("Zijian Guan"_p, "234234");
				pb.addNumber("Pob Gob"_p, "111111123");
				pb.addNumber("Zijian Guan"_p, "4563457");
				pb.addNumber("Pob Gob"_p, "111111123");
				pb.addNumber("Pob Gob"_p, "111111123");
				pb.addNumber("Pob Gob"_p, "111111123");
				pb.addNumber("Pob Gob"_p, "234234");
				pb.addNumber("Zijian Guan"_p, "4563457");
				pb.removeNumber("Pob Gob"_p, "234234");
				pb.removeNumber("Zijian Guan"_p, "1234567");

				auto zgnumber{ pb.getAllPhoneNumber("Zijian Guan"_p) };
				auto pgnumber{ pb.getAllPhoneNumber("Pob Gob"_p) };
				println("Zijian Guan's numbers: ");
				for (const auto& num : zgnumber) {
					println("\t{}", num);
				}
				println("Pob Gob's numbers: ");
				for (const auto& num : pgnumber) {
					println("\t{}", num);
				}
			}
		}
		namespace ex3 {
			using namespace std;
			void test() {
				map<string,int> myArray;
				myArray["Key 1"] = 11;
				myArray["Key 2"] = 22;
				myArray["Key 3"] = 33;

				try {
					println("{}", myArray.at("Key 1"));
					println("{}", myArray.at("Key 2"));

					// Test const operator[]
					const map<string,int>& c{ myArray };
					println("{}", c.at("Key 3"));
					println("{}", c.at("Key 4"));
				}
				catch (const exception& ex) {
					println("Caught exception: {}", ex.what());
				}
			}
		}
		namespace ex4 {
			using namespace std;
			double average(span<double> sd) {
				double sum{};
				for (const auto& d : sd) {
					sum += d;
				}
				return sum/sd.size();
			}
			void test() {
				vector<double> vi{ 1,2,3,4,5,6 };
				array<double, 4> ai{ 3.1,4.8,9.2,5.4 };
				println("{}", average(vi));
				println("{}", average(ai));

				vector values1{ 1.1, 2.2, 3.3, 4.4 };
				println("{}", average(values1));

				array values2{ 1.1, 2.2, 3.3, 4.4 };
				println("{}", average(values2));
				println("{}", average({ values2.data() + 2, 2 }));
				println("");

			}
		}
		namespace ex_bonus {
			using namespace std;
			template <typename T>
				requires is_arithmetic_v<T>
			double average(span<const T> sd) {
				double sum{};
				for (const auto& d : sd) {
					sum += d;
				}
				return sum / sd.size();
			}
			void test() {
				vector<double> vi{ 1,2,3,4,5,6 };
				array<double, 4> ai{ 3.1,4.8,9.2,5.4 };
				vector<int> vi2{ 1,2,3,4,5,6 };
				array<int, 4> ai2{ 3,4,9,5 };
				array<long long, 4> ai3{ 3456456ll,4345345ll,9345345ll,5ll };
				println("{}", average(span<const double>{vi.begin(), vi.end()}));
				println("{}", average(span<const double>{ai.begin(), ai.end()}));
				println("{}", average(span<const int>{vi2.begin(), vi2.end()}));
				println("{}", average(span<const int>{ai2.begin(), ai2.end()}));
				println("{}", average(span<const long long>{ai3.begin(), ai3.end()}));

				vector values1{ 1.1, 2.2, 3.3, 4.4 };
				//// The parameter of the function template is span<const T>.
				//// This cannot be automatically deduced from the function arguments.
				//// So, we need to specify the template type argument explicitly.
				println("{}", average<double>(values1));

				array values2{ 1, 2, 3, 4 };
				println("{}", average<int>(values2));
				println("{}", average<int>({ values2.data() + 2, 2 }));
			}
		}
	}
}