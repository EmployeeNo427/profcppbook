export module ch31;

import std;

export namespace ch31 {

	namespace exercises {

		namespace ex2 {
			using namespace std;
			int* getData(int value) { return new int{ value * 2 }; }
			void test()
			{
				int* data{ getData(21) };
				println("{}", *data);
				delete data;
				data = nullptr;

				data = getData(42);
				println("{}", *data);
				delete data;
				data = nullptr;
			}
		}
		namespace ex3 {
			using namespace std;
			int sum(int* values, int count)
			{
				int total{ 0 };
				for (int i{ 0 }; i < count; ++i) { total += values[i]; }
				return total;
			}
			void test()
			{
				int values[]{ 1, 2, 3 };
				//int total{ sum(values, sizeof(values)/sizeof(int)) };
				int total{ sum(values, size(values)) };
				println("{}", total);
			}
		}
	}
}