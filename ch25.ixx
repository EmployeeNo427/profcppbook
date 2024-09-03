export module ch25;
import std;

export namespace ch25 {
	namespace exercises {
		namespace ex1 {
			namespace myanswer {
				using namespace std;

				template <forward_iterator ForwardIterator,
					output_iterator<typename iterator_traits<ForwardIterator>::value_type> OutputIterator,
					predicate<typename iterator_traits<ForwardIterator>::reference> Predicate,
					invocable<typename iterator_traits<ForwardIterator>::reference> Transform>
				OutputIterator tranform_if(ForwardIterator first, ForwardIterator last,
					OutputIterator dest, Predicate pred, Transform func) {
					while (first != last) {
						if (std::invoke(pred, *first)) {
							*dest = std::invoke(func, *first);
						}
						++first;
						++dest;
					}
					return dest;
				}

				void test() {
					array<int, 20> arr;
					iota(arr.begin(), arr.end(), 1);
					auto odd{ [](int i) { return i % 2 != 0; } };
					auto multiply_two{ [](int i) { return i * 2; } };
					tranform_if(cbegin(arr), cend(arr), begin(arr), odd, multiply_two);
					for (int i : arr) { print("{} ", i); }
				}
			}
		}
	}
}

