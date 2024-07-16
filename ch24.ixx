export module ch24;
import std;

export namespace ch24 {
	namespace exercises {
		namespace ex1 {
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
	}
}