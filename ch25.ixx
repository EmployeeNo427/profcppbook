export module ch25;
import std;

export namespace ch25 {
	namespace exercises {
		namespace ex1 {
			namespace myanswer {
				using namespace std;

				template <forward_iterator ForwardIterator,
					output_iterator<iter_reference_t<ForwardIterator>> OutputIterator,
					indirect_unary_predicate<ForwardIterator> Predicate,
					invocable<iter_reference_t<ForwardIterator>> Transform>
				OutputIterator tranform_if(ForwardIterator first, ForwardIterator last,
					OutputIterator dest, Predicate pred, Transform func) {
					while (first != last) {
						if (std::invoke(pred, *first)) {
							*dest = std::invoke(func, *first);
						}
						else {
							*dest = *first;
						}
						++first;
						++dest;
					}
					return dest;
				}

				void test() {
					array<int, 20> arr;
					iota(arr.begin(), arr.end(), 1);

					vector<int> result;
					auto odd{ [](int i) { return i % 2 != 0; } };
					auto multiply_two{ [](int i) { return i * 2; } };
					tranform_if(cbegin(arr), cend(arr), back_inserter(result), odd, multiply_two);
					for (int i : result) { print("{} ", i); }
					println("");
				}
			}
		}
		namespace ex2 {
			namespace myanswer {
				using namespace std;


				template <ranges::input_range Range>
				void generate_fibonacci(Range&& range)
				{
					int prev{ -1 };
					int val{ 1 };
					generate(std::ranges::begin(range), std::ranges::end(range), 
						[&prev, &val] {
							auto temp{ val };
							val = prev + val; 
							prev = temp;
							return val;
						});
				}

				void test() {
					vector<int> vi(12);
					generate_fibonacci(vi);
					println("fibonacci");
					for (const auto& i : vi) { print("{} ", i); }
				}
			}
		}
	}
}

