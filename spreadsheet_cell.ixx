export module spreadsheet_cell;
import std;

export class SpreadsheetCell {
public:
	SpreadsheetCell(double initialValue);
	SpreadsheetCell(std::string_view initialValue);
	SpreadsheetCell(const SpreadsheetCell& src);
	SpreadsheetCell() = default;
    SpreadsheetCell& operator=(const SpreadsheetCell& rhs);
	void setValue(double value);
	double getValue() const;

	void setString(std::string_view value);
	std::string getString() const;

    enum class Color { Red = 1, Green, Blue, Yellow };
    void setColor(Color color);
    Color getColor() const;
private:
	static std::string doubleToString(double value);
	static double stringToDouble(std::string_view value);
    mutable size_t m_numAccesses{ 0 };
	double m_value{0};
    Color m_color{ Color::Red };
};

void SpreadsheetCell::setColor(Color color) { m_color = color; }
SpreadsheetCell::Color SpreadsheetCell::getColor() const { return m_color; }

inline double SpreadsheetCell::getValue() const
{
    m_numAccesses++;
    return m_value;
}

inline std::string SpreadsheetCell::getString() const
{
    m_numAccesses++;
    return doubleToString(m_value);
}

export class EvenSequence
{
public:
    EvenSequence(std::initializer_list<double> args)
    {
        if (args.size() % 2 != 0) {
            throw std::invalid_argument { "initializer_list should "
                "contain even number of elements." };
        }
        m_sequence.reserve(args.size());
        for (const auto& value : args) {
            m_sequence.push_back(value);
        }
    }

    void dump() const
    {
        for (const auto& value : m_sequence) {
            std::cout << value << ", ";
        }
       std:: cout << std::endl;
    }
private:
    std::vector<double> m_sequence;
};


