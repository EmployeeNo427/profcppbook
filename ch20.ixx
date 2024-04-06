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
	}
}