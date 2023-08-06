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

export class Person
{
public:
    Person(std::string_view first_name, std::string_view last_name, std::string_view initials)
        :m_first_name{ first_name }, m_last_name{ last_name }, m_initials{ initials } {}
    Person(std::string_view first_name, std::string_view last_name)
        :Person{ first_name ,last_name, std::format("{}{}.", first_name[0], last_name[0]) } {}
    Person() = default;
    /*Person()
        :m_first_name{ "N/A first name" }, m_last_name{ "N/A last name" } {}
    Person(const Person& src)
        :m_first_name{ src.m_first_name }, m_last_name{ src.m_last_name }
    {
        std::cout <<"Copy constructor called with src argument " << src.get_first_name() << ", "<<
            src.get_last_name()<<std::endl;
    }
    Person& operator=(const Person& rhs) {
        if (this == &rhs) {
            return *this;
        }
        m_first_name = rhs.get_first_name();
        m_last_name = rhs.get_last_name();

        std::cout << "Assignment Operator called with rhs argument " << rhs.get_first_name() << ", " <<
            rhs.get_last_name() << std::endl;
        return *this;

    };
    ~Person() {
        std::cout << "Destructor of Person called."  << std::endl;
    }*/
    void set_first_name(std::string_view first_name) { m_first_name = first_name; }
    void set_last_name(std::string_view last_name) { m_last_name = last_name; }
    void set_initials(std::string_view initials) { m_initials = initials; }
    std::string_view get_first_name() const { return m_first_name; }
    std::string_view get_last_name() const { return m_last_name; }
    std::string_view get_initials() const { return m_initials; }
private:
    std::string m_first_name, m_last_name, m_initials;
};


