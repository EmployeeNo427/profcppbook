export module ch18;
import std;
import phone_book_ch18;

export namespace ch18 {
	namespace exercises {
		namespace ex1 {
			using namespace std;
			void test(){
				vector<int> values{ 2,5 };
				values.insert(cbegin(values) + 1, 3);
				values.insert(cbegin(values) + 2, 4);

				for (const auto& value : values) { print("{} ", value); }
				println("");

				vector<int> vi{ 0,1 };
				values.insert(cbegin(values), cbegin(vi), cend(vi));

				for (const auto& value : values) { print("{} ", value); }
				println("");

				vector<int> vreverse;
				vreverse.insert(cbegin(vreverse), crbegin(values), crend(values));


				//println("{}", vreverse)
				for (const auto& value : vreverse) { print("{} ", value); }
				println("");
			}
			void test_textbook() {
				vector<int> values{ 2, 5 };

				// 1
				values.insert(begin(values) + 1, 3);
				values.insert(begin(values) + 2, 4);

				// 2
				vector<int> v2{ 0, 1 };
				values.insert(begin(values), cbegin(v2), cend(v2));

				// 3
				vector<int> v3;
				for (auto riter{ crbegin(values) }; riter != crend(values); ++riter) {
					v3.push_back(*riter);
				}

				// 4
				//println("{}", v3);

				// 5
				for (const auto& element : v3) {
					print("{} ", element);
				}
				println("");
			}
		}
		namespace ex2 {
			using namespace std;
			void test() {
				PhoneBook pb;
				pb.addNumber("Zijian Guan"_p, "1234567");
				pb.addNumber("Zijian Guan"_p, "6915974555");
				pb.addNumber("Zijian Guan"_p, "234234");
				pb.addNumber("Pob Gob"_p, "111111123");
				pb.addNumber("Zijian Guan"_p, "4563457");
				pb.addNumber("Pob Gob"_p, "111111123");
				pb.addNumber("Pob Gob"_p, "111111123");
				pb.addNumber("Pob Gob"_p, "111111123");
				pb.addNumber("Pob Gob"_p, "234234");
				pb.addNumber("Zijian Guan"_p, "4563457");
				pb.removeNumber("Pob Gob"_p, "234234");
				pb.removeNumber("Zijian Guan"_p, "1234567");

				auto zgnumber{ pb.getAllPhoneNumber("Zijian Guan"_p) };
				auto pgnumber{ pb.getAllPhoneNumber("Pob Gob"_p) };
				println("Zijian Guan's numbers: ");
				for (const auto& num : zgnumber) {
					println("\t{}", num);
				}
				println("Pob Gob's numbers: ");
				for (const auto& num : pgnumber) {
					println("\t{}", num);
				}
			}
		}
	}
}