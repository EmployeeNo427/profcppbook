export module ch24;
import std;

export namespace ch24 {
	namespace exercises {
		namespace ex1 {
			namespace myanswer {
				using namespace std;
				class Error
				{
				public:
					//Error() = default;
					explicit Error(string me) : message{ move(me) } {};
					const string& get_message() const { return message; };
				private:
					string message;
				};

				variant<vector<string>, Error> get_data(bool fail) {
					if (!fail) { return vector<string>{"example", "string"}; }
					else { return Error{ "\"fail\" is true" }; }
				}

				class MyVisitor
				{
				public:
					void operator()(const vector<string>& vs) {
						println("vector<string>: ");
						for (const auto& s : vs) { println("{}", s); }
					}
					void operator()(const Error& e) { println("Error: {}", e.get_message()); }
				};
				void test() {
					visit(MyVisitor{}, get_data(true));
					visit(MyVisitor{}, get_data(false));

				}
			}
			namespace textbook {
				using namespace std;

				class Error
				{
				public:
					explicit Error(string message) : m_message{ move(message) } { }
					const string& getMessage() const { return m_message; }

				private:
					string m_message;
				};

				variant<vector<int>, Error> getData(bool fail)
				{
					if (fail) {
						return Error{ "An error occurred." };
					}
					else {
						return vector{ 11, 22, 33 };
					}
				}

				void handleResult(const variant<vector<int>, Error>& result)
				{
					if (holds_alternative<Error>(result)) {
						println("Error: {}", get<Error>(result).getMessage());
					}
					else {
						auto& data{ get<vector<int>>(result) };
						for (const auto& s : data) { println("{}", s); }
					}
				}

				void test()
				{
					handleResult(getData(false));
					handleResult(getData(true));
				}
			}
		}
		namespace ex2 {
			using namespace std;
			class Error
			{
			public:
				//Error() = default;
				explicit Error(string me) : m_message{ move(me) } {};
				const string& get_message() const { return m_message; };
			private:
				string m_message;
			};

			expected<vector<string>, Error> get_data(bool fail) {
				if (!fail) { return vector<string>{"example", "string"}; }
				else { return unexpected{ Error{ "\"fail\" is true" } }; }
			}

			void handle_result(const expected<vector<string>, Error>& expect) {
				if (expect) {
					print("expect: {{");
					for (const auto& s : *expect) {
						print(" {} ", s);
					}
					println("}}");
				}
				else { println("expect contains an error: {}", expect.error().get_message()); }
			}
			void test() {
				handle_result(get_data(true));
				handle_result(get_data(false));
			}

		}
		namespace ex3 {
			using namespace std;

			pair<string, variant<bool, int, string>> parse_single_param(string param) {
				regex reg{ R"(([^=]+)=([^=]+)$)" };
				smatch m;
				if (regex_match(param, m, reg)) {
					string first{ m[1] };
					string second{ m[2] };

					if (second == "true") {
						return make_pair(first, true);
					}
					else if (second == "false") {
						return make_pair(first, false);
					}
					else {
						try {
							int int_value = stoi(second);
							return make_pair(first, int_value);
						}
						catch (const invalid_argument&) {
							// Not an integer, treat as string
							return make_pair(first, second);
						}
						catch (const out_of_range&) {
							// Not an integer, treat as string
							return make_pair(first, second);
						}
					}
				}
				else {
					throw invalid_argument("Invalid parameter format");
				}
			}

			void test(int argc, char** argv) {
				for (int i{ 1 }; i < argc; ++i) {  // Start from 1 to skip the program name
					try {
						auto result = parse_single_param(argv[i]);
						if (holds_alternative<bool>(result.second)) {
							cout << "First: " << result.first << ", Second is a bool: " << get<bool>(result.second) << endl;
						}
						else if (holds_alternative<int>(result.second)) {
							cout << "First: " << result.first << ", Second is an int: " << get<int>(result.second) << endl;
						}
						else if (holds_alternative<string>(result.second)) {
							cout << "First: " << result.first << ", Second is a string: " << get<string>(result.second) << endl;
						}
					}
					catch (const exception& e) {
						cerr << "Error parsing parameter: " << argv[i] << " - " << e.what() << endl;
					}
				}
			}
		}
		namespace ex4 {
			using namespace std;

			using Parameter = pair<string, variant<bool, int, string>>;

			Parameter parseParameter(const char* parameter)
			{
				regex r{ "(.*)=(.*)" };
				if (cmatch m; regex_match(parameter, m, r)) {
					const auto& name{ m[1].str() };
					const auto& value{ m[2].str() };

					// Try to parse as Boolean.
					if (value == "true") { return { name, true }; }
					else if (value == "false") { return { name, false }; }

					// Try to parse as integer.
					try {
						int parsedInteger{ stoi(value) };
						return { name, parsedInteger };
					}
					catch (const exception&) {
						// Could not parse as integer.
					}

					// Just interpret as string.
					return { name, value };
				}
				throw invalid_argument{ "Cannot parse parameter." };
			}

			class MyVisitor
			{
			public:
				MyVisitor(string s): name { move(s) } {}
				void operator()(const bool& bo) {
					println("Boolean: {} -> {}",
						name,
						bo);
				}
				void operator()(const int& i) {
					println("Integer: {} -> {}",
						name,
						i);
				}
				void operator()(const string& s) {
					println("String: {} -> {}",
						name,
						s);
				}
			private:
				string name;
			};

			void test(int argc, char** argv)
			{
				println("ch24_ex4:");
				for (int i{ 0 }; i < argc; ++i) {
					try {
						auto parameter{ parseParameter(argv[i]) };
						visit(MyVisitor{ parameter.first }, parameter.second);
					}
					catch (const invalid_argument&) {
						// Could not parse parameter, ignore it.
					}
				}
			}
		}
		namespace ex5 {
				using namespace std;

				using Parameter = tuple<string, variant<bool, int, string>>;

				Parameter parseParameter(const char* parameter)
				{
					regex r{ "(.*)=(.*)" };
					if (cmatch m; regex_match(parameter, m, r)) {
						const auto& name{ m[1].str() };
						const auto& value{ m[2].str() };

						// Try to parse as Boolean.
						if (value == "true") { return { name, true }; }
						else if (value == "false") { return { name, false }; }

						// Try to parse as integer.
						try {
							int parsedInteger{ stoi(value) };
							return { name, parsedInteger };
						}
						catch (const exception&) {
							// Could not parse as integer.
						}

						// Just interpret as string.
						return { name, value };
					}
					throw invalid_argument{ "Cannot parse parameter." };
				}

				class MyVisitor
				{
				public:
					MyVisitor(string s) : name{ move(s) } {}
					void operator()(const bool& bo) {
						println("Boolean: {} -> {}",
							name,
							bo);
					}
					void operator()(const int& i) {
						println("Integer: {} -> {}",
							name,
							i);
					}
					void operator()(const string& s) {
						println("String: {} -> {}",
							name,
							s);
					}
				private:
					string name;
				};

				void test(int argc, char** argv)
				{
					println("ch24_ex5:");
					for (int i{ 0 }; i < argc; ++i) {
						try {
							auto parameter{ parseParameter(argv[i]) };
							visit(MyVisitor{ get<0>(parameter) }, get<1>(parameter));
						}
						catch (const invalid_argument&) {
							// Could not parse parameter, ignore it.
						}
					}
				}
			}
		}
	}