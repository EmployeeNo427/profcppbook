export module person;
import std;

export class Person
{
public:
    Person(std::string first_name, std::string last_name, std::string initials)
        :m_first_name{ std::move(first_name) }, m_last_name{ std::move(last_name) }, m_initials{ std::move(initials) } {}
    Person(std::string first_name, std::string last_name)
        :Person{ std::move(first_name) ,std::move(last_name), std::format("{}{}.", std::move(first_name[0]), std::move(last_name[0])) } {}
    Person(const Person&) = default;
    Person() = default;
    Person(Person&& src) noexcept
    {
        std::cout << "Move constructor called. " << std::endl;
        swap(src);
        std::cout << std::format("Result of Move constructor: this->first_name:{}, this->last_name:{}, this->initials:{}",
            this->get_first_name(), this->get_last_name(), this->get_initials()) << std::endl;

    }

    Person& operator=(Person&& rhs) noexcept
    {
        std::cout << "Move assignment called. " << std::endl;
        swap(rhs);
        std::cout << std::format("Result of Move assignment: this->first_name:{}, this->last_name:{}, this->initials:{}\nrhs.first_name:{}, rhs.last_name:{}, rhs.initials:{}",
            this->get_first_name(), this->get_last_name(), this->get_initials(), rhs.get_first_name(), rhs.get_last_name(), rhs.get_initials()) << std::endl;
        return *this;
    }
    Person& operator =(const Person&) = default;
    void swap(Person& other) noexcept
    {
        std::swap(m_first_name, other.m_first_name);
        std::swap(m_last_name, other.m_last_name);
        std::swap(m_initials, other.m_initials);
    }
    void set_first_name(std::string first_name) { m_first_name = std::move(first_name); }
    void set_last_name(std::string last_name) { m_last_name = std::move(last_name); }
    void set_initials(std::string initials) { m_initials = std::move(initials); }
    std::string_view get_first_name() const { return m_first_name; }
    std::string_view get_last_name() const { return m_last_name; }
    std::string_view get_initials() const { return m_initials; }
private:
    std::string m_first_name, m_last_name, m_initials;
};

void swap(Person& first, Person& second) noexcept
{
    first.swap(second);
}

