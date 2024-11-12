export module ch26;

import std;

export namespace ch26 {
	namespace exercises {
		namespace ex1 {
			namespace myanswer {
				using namespace std;

				export template <typename KeyType, typename ValueType>
					class KeyValuePair {
					public:
						KeyValuePair(const KeyType& key, const ValueType& value) :m_key{ key }, m_value{ value } {}
						const KeyType& getkey() const { return m_key; }
						const ValueType& getvalue() const { return m_value; }
						void setkey(const KeyType& key) { m_key = key; }
						void setvalue(const ValueType& value) { m_value = value; }
					private:
						KeyType m_key;
						ValueType m_value;
				};

				export template<typename KeyType>
					class KeyValuePair<KeyType, const char*> {
					public:
						KeyValuePair(const KeyType& key, const char* value) :m_key{ key }, m_value{ value } {}
						const KeyType& getkey() { return m_key; }
						const string& getvalue() { return m_value; }
						void setkey(const KeyType& key) { m_key = key; }
						void setvalue(const string& value) { m_value = value; }
					private:
						KeyType m_key;
						string m_value;
				};

				KeyValuePair(const char*, const char*)->KeyValuePair<const char*, const char*>;

				void test() {
					using namespace std;

					KeyValuePair<int, string> intstr_pair{ 1,"Hello" };
					cout << format("key: {}, value: {}\n", intstr_pair.getkey(), intstr_pair.getvalue());
					intstr_pair.setkey(2);
					intstr_pair.setvalue("walawalabong");
					cout << format("key: {}, value: {}\n", intstr_pair.getkey(), intstr_pair.getvalue());

					KeyValuePair charstr_pair{ 'a',"Hello"s };
					cout << format("key: {}, value: {}\n", charstr_pair.getkey(), charstr_pair.getvalue());
					charstr_pair.setkey('b');
					charstr_pair.setvalue("walawalabong"s);
					cout << format("key: {}, value: {}\n", charstr_pair.getkey(), charstr_pair.getvalue());

					KeyValuePair intint_pair{ 3,4 };
					cout << format("key: {}, value: {}\n", intint_pair.getkey(), intint_pair.getvalue());
					intint_pair.setkey(1);
					intint_pair.setvalue(2);
					cout << format("key: {}, value: {}\n", intint_pair.getkey(), intint_pair.getvalue());

					KeyValuePair strstr_pair{ "nice","job" };//would save as string
					cout << format("key: {}, value: {}\n", strstr_pair.getkey(), strstr_pair.getvalue());
					strstr_pair.setkey("good");
					strstr_pair.setvalue("work");
					cout << format("key: {}, value: {}\n", strstr_pair.getkey(), strstr_pair.getvalue());

				};
			}
		}
	}
}