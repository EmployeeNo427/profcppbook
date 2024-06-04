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
		namespace ex2 {
			using namespace std;
			using namespace std::chrono;
			void test() {
				regex reg{ "^(\\d{4})-(0?[1-9]|1[0-2])-(0?[1-9]|[1-2][0-9]|3[0-1])$" };
				while (true) {
					print("Enter a date (yyyy-mm-dd) (q=quit): ");
					string str;
					if (!getline(cin, str) || str == "q") { break; }

					const sregex_iterator end;
					for (sregex_iterator iter{ cbegin(str),cend(str),reg };
						iter != end; ++iter) {
						year y{ stoi((*iter)[1].str()) };
						month m{ static_cast<unsigned int>(stoi((*iter)[2].str())) };
						day d{ static_cast<unsigned int>(stoi((*iter)[3].str())) };
						println("Year: {}", y);
						println("Month: {}", m);
						println("Day: {}", d);
						year_month_day fulldate{ y,m,d };
						println("{:L}", fulldate);
					}
				}
			}
			void test_textbook() {
				regex r{ "(\\d{4})-(\\d{2})-(\\d{2})" };
				while (true) {
					print("Enter a date (yyyy-mm-dd) (q=quit): ");
					string str;
					if (!getline(cin, str) || str == "q") {
						break;
					}

					if (smatch m; regex_match(str, m, r)) {
						println("	Parsed date, now validating...");
						year_month_day date{ year{stoi(m[1])},
							month{stoul(m[2])},
							day{stoul(m[3])} 
						};
						println("	date is {}", (date.ok() ? "valid." : "not valid!"));

					}
					else {
						println("	Can not parse date!");
					}
				}
			}
		}
	}
}