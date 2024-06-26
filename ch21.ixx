export module ch21;
import std;

export namespace ch21 {
	namespace exercises {
		namespace ex1 {
			using namespace std;
			void test() {
				{
					wcout << "Your decimal separator is "
						<< use_facet<numpunct<wchar_t>>(locale{ "" }).
						decimal_point() << '\n';

					wcout << "Your separator between digit groups is "
						<< use_facet<numpunct<wchar_t>>(locale{ "" }).
						thousands_sep() << '\n';
				}
				{
					locale userLocale{ "" };
					auto& facet{ use_facet<numpunct<char>>(userLocale) };
					println("Decimal separator: {}", facet.decimal_point());
				}
			}
		}
		namespace ex2 {
			using namespace std;
			void test() {
				{
					regex reg{ "(\\d{3})-(\\d{3})-(\\d{4})" };
					const string replacement{ "$1\n$2\n$3" };
					while (true) {
						print("Enter a phone number (xxx-xxx-xxxx) (q=quit):");
						string str;
						if (!getline(cin, str) || str == "q") { break; }
						if (regex_match(str, reg)) {
							println("Valid phone number.");
							cout << regex_replace(str, reg, replacement,
								regex_constants::format_no_copy) << endl;
						}
						else { println(" Invalid phone number!"); }
					}
				}
				{
					regex r{ "(\\d{3})-(\\d{3})-(\\d{4})" };
					while (true) {
						print("Enter a US phone number (xxx-xxx-xxxx) (q=quit): ");
						string str;
						if (!getline(cin, str) || str == "q") {
							break;
						}

						if (smatch m; regex_match(str, m, r)) {
							println("  Valid phone number:");
							println("{}\n{}\n{}", m[1].str(), m[2].str(), m[3].str());
						}
						else {
							println("  Invalid phone number!");
						}
					}
				}
			}
		}
		namespace ex3 {
			using namespace std;
			void clearInputBuffer() {
				cin.clear(); // Clear any error flags
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore remaining input
			}
			void test() {
				regex r{ "//\\s*(.+)$" };
				const string replacement{ "" };
				
				while (true) {
					print("Enter a multiple line code snippet that contains single line comment with @ as end(type \"q@\" to quit):\n");
					string str;
					clearInputBuffer(); // Clear the input buffer before reading
					if (!getline(cin, str, '@') || str=="q") {
						break;
					}
					string result{ regex_replace(str,r,replacement) };

					println("Original string: '{}'", str);
					println("New string : '{}'", result);

				}
			}
			void test_answer() {
				regex r{ "^(.*?)//.*$" };
				const string replacement{ "$1" };
				while (true) {
					println("Enter a source code snippet, terminated with @:");
					string str;
					if (!getline(cin, str, '@')) {
						break;
					}

					println("{}", regex_replace(str, r, replacement));
				}
			}
		}
		namespace ex4 {
			using namespace std;
			void test() {
				regex reg{ "(?=.*[[:lower:]])(?=.*[[:upper:]])(?=.*[[:punct:]])(?=(.*[[:digit:]]){2,}).{8,}" };
				while (true) {
					print("Enter a password, that consists of at least one lowercase letter,\n"
						"at least one uppercase letter, at least one punctuation character,\n" 
						"at least two digits, and is at least eight characters long(q = quit) :\n");
					string str;
					if (!getline(cin, str) || str == "q") { break; }
					if (regex_match(str, reg)) {
						println("Valid password.");
					}
					else { println(" Invalid password!"); }
				}
			}
		}
	}
}