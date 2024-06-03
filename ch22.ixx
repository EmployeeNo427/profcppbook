export module ch22;
import std;

export namespace ch22 {
	namespace exercises {
		namespace ex1 {
			using namespace std;
			using namespace std::chrono;
			void test() {
				duration<long> d1{42};
				duration<double,ratio<60>> d2{ 1.5 };

				duration<double,ratio<60>> sum_min{ d1 + d2 };
				auto sum_sec{ d1 + d2 };

				println("{}({})+{}({}) = {}({})", d1, d1.count(), d2, d2.count(), sum_min, sum_min.count());
				println("{}({})+{}({}) = {}({})", d1, d1.count(), d2, d2.count(), sum_sec, sum_sec.count());

			}
			void test_textbook(){
				seconds d1{ 42 };
				duration<double,ratio<60,1>> d2{ 1.5 };

				auto sum{ d1 + d2 };
				println("{} or {}", sum, duration<double, ratio<60, 1>>{ sum });
			}
		}
	}
}