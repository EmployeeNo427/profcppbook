export module ch23;
import std;

export namespace ch23 {
	namespace exercises {
		namespace ex1 {
			using namespace std;
			auto createDiceValueGenerator() {
				random_device seeder;
				const auto seed{ seeder.entropy() ? seeder() : time(nullptr)};
				mt19937 engine{ static_cast<mt19937::result_type>(seed) };

				uniform_int_distribution<int> distribution{ 1,6 };

				return bind(distribution, engine);
			}
			void test() {
				auto generator{ createDiceValueGenerator() };

				while (true) {
					println("Should dice be thrown: (type \"yes\" or \"no\")");
					string answer{};

					getline(cin, answer);
					if(answer == "no") {
						break;
					}
					else if (answer == "yes") {
						println("Dice number 1:{}", generator());
						println("Dice number 2:{}", generator());
					}
					else {
						println("please type \"yes\" or \"no\"");
					}
				}
			}
		}
		namespace ex2 {
			using namespace std;
			auto createDiceValueGenerator() {
				random_device seeder;
				const auto seed{ seeder.entropy() ? seeder() : time(nullptr) };
				ranlux48 engine{ static_cast<ranlux48::result_type>(seed) };

				uniform_int_distribution<int> distribution{ 1,6 };

				return bind(distribution, engine);
			}
			void test() {
				auto generator{ createDiceValueGenerator() };

				while (true) {
					println("Should dice be thrown: (type \"yes\" or \"no\")");
					string answer{};

					getline(cin, answer);
					if (answer == "no") {
						break;
					}
					else if (answer == "yes") {
						println("Dice number 1:{}", generator());
						println("Dice number 2:{}", generator());
					}
					else {
						println("please type \"yes\" or \"no\"");
					}
				}
			}
		}
		namespace ex3 {
			using namespace std;
			auto createDiceValueGenerator() {
				random_device seeder;
				const auto seed{ seeder.entropy() ? seeder() : time(nullptr) };
				mt19937 engine{ static_cast<mt19937::result_type>(seed) };
				shuffle_order_engine<mt19937, 30> engine_adapter{ engine };

				uniform_int_distribution<int> distribution{ 1,6 };

				return bind(distribution, engine_adapter);
			}
			void test() {
				auto generator{ createDiceValueGenerator() };

				while (true) {
					println("Should dice be thrown: (type \"yes\" or \"no\")");
					string answer{};

					getline(cin, answer);
					if (answer == "no") {
						break;
					}
					else if (answer == "yes") {
						println("Dice number 1:{}", generator());
						println("Dice number 2:{}", generator());
					}
					else {
						println("please type \"yes\" or \"no\"");
					}
				}
			}
		}
		namespace ex4 {
			using namespace std;
			void test_1() {
				const unsigned int Start{ 1 };
				const unsigned int End{ 99 };
				const unsigned int Iterations{ 1'000'000 };
				const unsigned int Visualization_Scale{ 500 };

				// Uniform distributed Mersenne Twister.
				random_device seeder;
				mt19937 engine{ seeder() };
				uniform_int_distribution<int> distribution{ Start, End };
				auto generator{ bind(distribution, engine) };
				map<int, int> histogram;
				for (unsigned int i{ 0 }; i < Iterations; ++i) {
					int randomNumber{ generator() };
					// Search map for a key=randomNumber. If found, add 1 to the value associated
					// with that key. If not found, add the key to the map with value 1.
					++(histogram[randomNumber]);
				}

				// Write to a CSV file.
				ofstream of{ "ch23_ex4_output/ch23_ex4_test1.csv" };
				for (unsigned int i{ Start }; i <= End; ++i) {
					println("{:2}: {}", i, string(static_cast<int>(histogram[i]/ Visualization_Scale), '*'));
					of << i << ";" << histogram[i] << endl;
				}
			}
			void test_2()
			{
				const unsigned int Start{ 1 };
				const unsigned int End{ 99 };
				const unsigned int Iterations{ 1'000'000 };
				const unsigned int Visualization_Scale{ 500 };

				// Normal distributed Mersenne Twister.
				random_device seeder;
				mt19937 engine{ seeder() };
				normal_distribution<double> distribution{ 50, 10 };
				auto generator{ bind(distribution, engine) };
				map<int, int> histogram;
				for (unsigned int i{ 0 }; i < Iterations; ++i) {
					int randomNumber{ static_cast<int>(generator()) };
					// Search map for a key=randomNumber. If found, add 1 to the value associated
					// with that key. If not found, add the key to the map with value 1.
					++(histogram[randomNumber]);
				}

				// Write to a CSV file.
				ofstream of{ "ch23_ex4_output/ch23_ex4_test2.csv" };
				for (unsigned int i{ Start }; i <= End; ++i) {
					println("{:2}: {}", i, string(static_cast<int>(histogram[i] / Visualization_Scale), '*'));
					of << i << ";" << histogram[i] << endl;
				}
			}
			void test_3()
			{
				const unsigned int Start{ 1 };
				const unsigned int End{ 99 };
				const unsigned int Iterations{ 1'000'000 };
				const unsigned int Visualization_Scale{ 500 };

				// Normal distributed Mersenne Twister.
				random_device seeder;
				mt19937 engine{ seeder() };
				exponential_distribution<double> distribution(1.0);
				auto generator{ bind(distribution, engine) };
				map<int, int> histogram;
				for (unsigned int i{ 0 }; i < Iterations; ++i) {
					int randomNumber{ static_cast<int>(generator()) };
					// Search map for a key=randomNumber. If found, add 1 to the value associated
					// with that key. If not found, add the key to the map with value 1.
					++(histogram[randomNumber]);
				}

				// Write to a CSV file.
				ofstream of{ "ch23_ex4_output/ch23_ex4_test3.csv" };
				for (unsigned int i{ Start }; i <= End; ++i) {
					println("{:2}: {}", i, string(static_cast<int>(histogram[i] / Visualization_Scale), '*'));
					of << i << ";" << histogram[i] << endl;
				}
			}
			void test_4() {
				const unsigned int Start{ 1 };
				const unsigned int End{ 99 };
				const unsigned int Iterations{ 1'000'000 };
				const unsigned int Visualization_Scale{ 500 };

				// Uniform distributed Mersenne Twister.
				random_device seeder;
				mt19937 engine{ seeder() };
				negative_binomial_distribution<int> distribution(1,0.5);
				auto generator{ bind(distribution, engine) };
				map<int, int> histogram;
				for (unsigned int i{ 0 }; i < Iterations; ++i) {
					int randomNumber{ generator() };
					// Search map for a key=randomNumber. If found, add 1 to the value associated
					// with that key. If not found, add the key to the map with value 1.
					++(histogram[randomNumber]);
				}

				// Write to a CSV file.
				ofstream of{ "ch23_ex4_output/ch23_ex4_test4.csv" };
				for (unsigned int i{ Start }; i <= End; ++i) {
					println("{:2}: {}", i, string(static_cast<int>(histogram[i] / Visualization_Scale), '*'));
					of << i << ";" << histogram[i] << endl;
				}
			}
		}
	}
}