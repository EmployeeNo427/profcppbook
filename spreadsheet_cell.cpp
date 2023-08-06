module spreadsheet_cell;
import std;
using namespace std;

SpreadsheetCell::SpreadsheetCell(double initialValue)
{
	setValue(initialValue);
}

SpreadsheetCell::SpreadsheetCell(std::string_view initialValue)
{
	setString(initialValue);
}

SpreadsheetCell::SpreadsheetCell(const SpreadsheetCell& src)
{

}

SpreadsheetCell& SpreadsheetCell::operator=(const SpreadsheetCell& rhs)
{
	if(this == &rhs) {
		return *this;
	}
	m_value = rhs.m_value;
	return *this;
}

void SpreadsheetCell::setValue(double value)
{
	m_value = value;
}



void SpreadsheetCell::setString(string_view value)
{
	m_value = stringToDouble(value);
}



std::string SpreadsheetCell::doubleToString(double value)
{
	return to_string(value);
}

double SpreadsheetCell::stringToDouble(std::string_view value)
{
	double number{ 0 };
	from_chars(value.data(), value.data() + value.size(), number);
	return number;
}
