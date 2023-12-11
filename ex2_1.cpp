import <iostream>;
import <format>;
import <string>;
import <compare>;

int main() {
	using namespace std;

	string s1;
	string s2;

	cout << "Type first strings" << endl;
	getline(cin, s1);
	cout << "Type second strings" << endl;
	getline(cin, s2);

	auto result{ s1 <=> s2 };
	if (is_lt(result)) { cout << s1 << " is lexicographically prior than " << s2 << endl; }
	if (is_gt(result)) { cout << s2 << " is lexicographically prior than " << s1 << endl; }
	if (is_eq(result)) { cout << s1 << " is lexicographically equal with " << s2 << endl; }

}