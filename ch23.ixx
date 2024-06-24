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
	}
}