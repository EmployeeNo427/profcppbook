import <iostream>;
import <format>;
import <string>;
import <compare>;
import <string_view>;

using namespace std;

// The parameters are const references to avoid unnecessary copying.
string replace_all_needle(string_view haystack, string_view needle, string_view replacement)
{
    // Make a copy of the haystack.
    string result{ haystack };
    
    auto position{ result.find(needle) };
    while (position != string::npos) {
        result.replace(position, needle.length(), replacement);
        position = result.find(needle);
    }
    return result;
}

int main() {
    
    string strSource;
    cout << "Type a source string:" << endl;
    getline(cin, strSource);

    string strFind;
    cout << "Type a string to find:" << endl;
    getline(cin, strFind);

    string strReplace;
    cout << "Type a string to replace:" << endl;
    getline(cin, strReplace);

    string result{ replace_all_needle(strSource, strFind, strReplace) };
    cout << "Source:" << strSource << endl;
    cout << "Find:" << strFind << endl;
    cout << "Replace:" << strReplace << endl;
    cout << "Result:" << result << endl;
}