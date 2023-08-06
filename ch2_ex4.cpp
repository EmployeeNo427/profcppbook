import <iostream>;
import <format>;
import <string>;
import <compare>;
import <string_view>;
import <vector>;

using namespace std;

int main() 
try
{
	vector<double> inputs;
	while (true) {
		double value;
		cout << "Enter a double(enter 0 to stop):";
		cin >> value;
		if (value == 0) {
			break;
		}
		else {
			inputs.push_back(value);
		}
	}
	for (auto x : inputs) {
		cout << format("|{0:24e}|{0:<24f}|{0:_>24g}|{0:_^#24}|", x)<<endl;
	}
}
catch (const format_error& caught_exception) {
	cout << caught_exception.what();
}