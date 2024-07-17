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
					print("expect: {");
					for (const auto& s : *expect) {
						print(" {} ", s);
					}
					println("}");
				}
				else { println("expect contains an error: {}", expect.error().get_message()); }
			}
			void test() {
				handle_result(get_data(true));
				handle_result(get_data(false));
			}

		}
	}
}