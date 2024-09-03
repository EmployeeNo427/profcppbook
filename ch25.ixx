export module ch25;
import std;

export namespace ch25 {
	namespace exercises {
		namespace ex1 {
			namespace myanswer {
				using namespace std;
				template <forward_iterator ForwardIterator,
					output_iterator<typename std::iterator_traits<ForwardIterator>::value_type> OutputIterator,
					indirect_unary_predicate<ForwardIterator> Predicate,
					typename TransformFunc>
				OutputIterator tranform_if(ForwardIterator first, ForwardIterator last,
					OutputIterator dest, Predicate pred, TransformFunc func) {
					while (first != last) {
						if (invoke(pred, *first)) {
							*dest = invoke(func, *first);
						}
						++first;
						++dest;
					}
					return dest;
				}


				void test() {
					array arr{ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20 };
					auto odd{ [](int i) { return i % 2 != 0; } };
					auto multiply_two{ [](int i) { return i * 2; } };
					tranform_if(begin(arr), end(arr), begin(arr), odd, multiply_two);

					// Print each element of the array
					for (const auto& elem : arr) {
						print("{} ", elem);
					}
					println("");  // For a newline after printing all elements
				}

			}
		}
	}
}