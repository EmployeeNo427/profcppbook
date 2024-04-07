export module ch20;
import std;

export namespace ch20 {
	namespace exercises {
		namespace ex1 {
			using namespace std;
			void println(std::vector<int> const& vi)
			{
				for (int e : vi)
					std::cout << e << ' ';
				std::cout << '\n';
			}
			void test(){ 
				{
					int num;
					print("Enter a number for range::fill(): ");
					cin >> num;


					vector<int> vi(10);
					ranges::fill(vi, num);
					println(vi);
				}
				{
					int num;
					print("Enter a number for std::fill(): ");
					cin >> num;

					vector<int> vi(10);
					fill(vi.begin(),vi.end(), num);
					println(vi);
				}
			}
			
			
		}
		namespace ex2 {
			using namespace std;
			auto print_range = [](auto const& v, char term = ' ')
				{
					cout << "{ ";
					for (const auto& e : v)
						cout << e << ' ';
					cout << '}' << term;
				};
			void test() {
				{
					vector<double> vd;
					double input;
					print("Enter numbers and enter a non-numeric value to stop: ");
					while (cin >> input) { vd.push_back(input); }

					// Clear std::cin so it can be used again later
					cin.clear(); // Clear the error flags
					cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the line

					ranges::sort(vd);//necessary for the permutation to work correctly

					print("Sorted sequence:\n");
					print_range(vd);
					println("");

					do print_range(vd);
					while (ranges::next_permutation(vd.begin(), vd.end()).found);
				}
				{
					vector<double> vd;
					double input;
					print("Enter numbers and enter a non-numeric value to stop: ");
					while (cin >> input) { vd.push_back(input); }

					// Clear std::cin so it can be used again later
					cin.clear(); // Clear the error flags
					cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the line

					sort(begin(vd),end(vd));//necessary for the permutation to work correctly

					print("Sorted sequence:\n");
					print_range(vd);
					println("");

					do print_range(vd);
					while (std::next_permutation(vd.begin(), vd.end()));
				}
			}
			void test_textbook() {

				vector<int> values;
				while (true) {
					print("Enter a number to add (0 to stop): ");
					int number;
					cin >> number;
					if (number == 0) {
						break;
					}
					values.push_back(number);
				}

				// The permutation algorithms require the sequence to be sorted.
				ranges::sort(values);

				// Print initial sorted sequence.
				print_range(values);

				// Loop over all permutations.
				while (ranges::next_permutation(values).found) {
					print_range(values);
				}
			}


		}
		namespace ex3 {
			using namespace std;
			bool is_space(char q) noexcept
			{
				static constexpr auto ws = { ' ', '\t', '\n', '\v', '\r', '\f' };
				return std::ranges::any_of(ws, [q](auto p) { return p == q; });
			};
			constexpr string trim(string_view sv) {
				auto result{ sv | views::drop_while(is_space) | views::reverse | views::drop_while(is_space) | views::reverse };
				return {begin(result),end(result)};
			}
			void test() {
				{
					string str1{ "      Left space content" };
					cout << "original: (" << str1 << ")\n";
					cout << "result: (" << trim(str1) << ")\n";
				}
				{
					string str1{ "      Left space content Right Space          " };
					cout << "original: (" << str1 << ")\n";
					cout << "result: (" << trim(str1) << ")\n";
				}
				{
					string str1{ "no space" };
					cout << "original: (" << str1 << ")\n";
					cout << "result: (" << trim(str1) << ")\n";
				}
				{
					string str1{ "" };
					cout << "original: (" << str1 << ")\n";
					cout << "result: (" << trim(str1) << ")\n";
				}
				{
					string str1{ " " };
					cout << "original: (" << str1 << ")\n";
					cout << "result: (" << trim(str1) << ")\n";
				}
			}
			string textbook_trim(string_view sv) {
				auto isNotWhiteSpace{ [](char c) {return !isspace(c); } };
				auto firstNonWhiteSpace{ ranges::find_if(sv,isNotWhiteSpace) };
				auto lastNonWhiteSpace{ ranges::find_last_if(sv,isNotWhiteSpace) };
				return { firstNonWhiteSpace, lastNonWhiteSpace.begin() + 1};
			}
			void test_textbook() {
				println("'{}'", textbook_trim("   Hello World!   "));
				println("'{}'", textbook_trim("Hello World!   "));
				println("'{}'", textbook_trim("   Hello World!"));
				println("'{}'", textbook_trim("Hello World!"));
				println("'{}'", textbook_trim(" \t Hello World! \n"));
			}


		}
		namespace ex4 {
			using namespace std;
			auto print_range = [](auto const& v, char term = ' ')
				{
					cout << "{ ";
					for (const auto& e : v)
						cout << e << ' ';
					cout << '}' << term;
				};
			void test() {
				auto nextNumber{ [counter = 0] () mutable { return ++counter; } };
				vector<int> values(20);
				ranges::generate(values, nextNumber);
				print_range(values);

				list<int> odds;
				list<int> evens;
				auto pairIters{ ranges::partition_copy(values,back_inserter(evens),front_inserter(odds),[](int i) {return i % 2 == 0; }) };
				print_range(evens,'\n');
				print_range(odds, '\n');

			}


		}
		namespace ex5 {
			using namespace std;
			string trim(string_view text)
			{
				auto isNonWhitespace{ [](char c) { return !isspace(c); } };
				auto firstNonWhitespace{ find_if(begin(text), end(text), isNonWhitespace) };
				auto lastNonWhitespace{ find_if(rbegin(text), rend(text), isNonWhitespace) };
				return string{ firstNonWhitespace, lastNonWhitespace.base()};
			}

			void test()
			{
				println("'{}'", trim("   Hello World!   "));
				println("'{}'", trim("Hello World!   "));
				println("'{}'", trim("   Hello World!"));
				println("'{}'", trim("Hello World!"));
				println("'{}'", trim(" \t Hello World! \n"));
			}
		}
	}
}