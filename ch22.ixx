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

				duration<double, ratio<60>> d1_min{ duration_cast<duration<double,ratio<60>>>(d1) };
				duration<long> d2_sec{ duration_cast<duration<long>>(d2) };

				duration<double,ratio<60>> sum_min{ d1_min + d2 };
				duration<long> sum_sec{ d1 + d2_sec };

				println("{}({})+{}({}) = {}({})", d1_min, d1_min.count(), d2, d2.count(), sum_min, sum_min.count());
				println("{}({})+{}({}) = {}({})", d1, d1.count(), d2_sec, d2_sec.count(), sum_sec, sum_sec.count());

			}
		}
	}
}