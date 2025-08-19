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
		namespace ex4 {

			using namespace std;

			class Logger
			{
			public:
				static void enableLogging(bool enable) { ms_loggingEnabled = enable; }
				static bool isLoggingEnabled() { return ms_loggingEnabled; }

				template<typename... Args>
				static void log(const source_location& location, const Args&... args)
				{
					if (!ms_loggingEnabled) { return; }

					ofstream logfile{ ms_debugFilename, ios_base::app };
					if (logfile.fail()) {
						println(cerr, "Unable to open debug file!");
						return;
					}
					print(logfile, "{:L} UTC: ", chrono::system_clock::now());
					print(logfile, "{}({}): {}: ", location.file_name(),
						location.line(), location.function_name());
					// Use a fold-expression; see Chapter 26.
					(logfile << ... << args);
					logfile << endl;
				}

			private:
				static inline const string ms_debugFilename{ "debugfile.out" };
				static inline bool ms_loggingEnabled{ false };
			};

			struct log {
				std::source_location loc = std::source_location::current();
				
				template<class... Args>
				explicit log(Args&&... args) {
					Logger::log(loc, std::forward<Args>(args)...);
				}
			};


			bool isDebugSet(int argc, char** argv)
			{
				auto parameters{ views::counted(argv, argc) };
				return ranges::contains(parameters, string_view{ "-d" });
			}



			class ComplicatedClass
			{
				// Class details omitted for brevity.
			};
			ostream& operator<<(ostream& outStream, const ComplicatedClass& /* src */)
			{
				outStream << "ComplicatedClass";
				return outStream;
			}

			class UserCommand
			{
				// Class details not shown for brevity.
			};
			ostream& operator<<(ostream& outStream, const UserCommand& /* src */)
			{
				outStream << "UserCommand";
				return outStream;
			}



			UserCommand getNextCommand(ComplicatedClass* /* obj */)
			{
				UserCommand cmd;
				return cmd;
			}

			void processUserCommand(const UserCommand& /* cmd */)
			{
				// Details omitted for brevity.
			}

			void trickyFunction(ComplicatedClass* obj)
			{
				log("given argument: ", *obj);

				for (size_t i{ 0 }; i < 100; ++i) {
					UserCommand cmd{ getNextCommand(obj) };
					log("retrieved cmd ", i, ": ", cmd);

					try {
						processUserCommand(cmd);
					}
					catch (const exception& e) {
						log("exception from processUserCommand(): ", e.what());
					}
				}
			}

			void test(int argc, char** argv)
			{
				Logger::enableLogging(isDebugSet(argc, argv));

				if (Logger::isLoggingEnabled()) {
					// Print the command-line arguments to the trace.
					for (size_t i{ 0 }; i < argc; ++i) {
						log("Argument: ", argv[i]);
					}
				}

				ComplicatedClass obj;
				trickyFunction(&obj);

				// Rest of the function not shown.
			}
		}
	}
}