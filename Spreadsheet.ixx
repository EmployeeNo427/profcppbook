export module Spreadsheet;

import std;

export import spreadsheet_cell;

using namespace std;

export class SpreadsheetApplication {};

export class Spreadsheet
{
public:
    Spreadsheet(size_t width, size_t height,
        const SpreadsheetApplication& theApp);
    Spreadsheet(const Spreadsheet& src);
    Spreadsheet& operator=(const Spreadsheet& rhs);
    void swap(Spreadsheet& other) noexcept;
    Spreadsheet(Spreadsheet&& src) = delete; // Move constructor
    Spreadsheet& operator=(Spreadsheet&& rhs) = delete; // Move assign
    ~Spreadsheet();
    void setCellAt(size_t x, size_t y, const SpreadsheetCell& cell);
    SpreadsheetCell& getCellAt(size_t x, size_t y);
    const SpreadsheetCell& getCellAt(size_t x, size_t y) const;
    size_t getId() const { return m_id; }
private:
    static inline size_t ms_counter { 0 };
    void verifyCoordinate(size_t x, size_t y) const;
    size_t m_width{ 0 };
    size_t m_height{ 0 };
    static const size_t MaxHeight{100};
    static const size_t MaxWidth{100};
    const size_t m_id{ 0 };
    SpreadsheetCell** m_cells{ nullptr };
    const SpreadsheetApplication& m_theApp;
};

export void swap(Spreadsheet& first, Spreadsheet& second) noexcept;

void swap(Spreadsheet& first, Spreadsheet& second) noexcept
{
    first.swap(second);
}

void Spreadsheet::swap(Spreadsheet& other) noexcept
{
    std::swap(m_width, other.m_width);
    std::swap(m_height, other.m_height);
    std::swap(m_cells, other.m_cells);
}

Spreadsheet& Spreadsheet::operator=(const Spreadsheet& rhs)
{
    Spreadsheet temp{ rhs }; // Do all the work in a temporary instance
    swap(temp);               // Commit the work with only non-throwing operations
    return *this;
}

Spreadsheet::Spreadsheet(size_t width, size_t height,
    const SpreadsheetApplication& theApp)
    : m_id{ ms_counter++ }, 
    m_width{ std::min(width, MaxWidth) }, 
    m_height{ std::min(height,MaxHeight) },
    m_theApp{ theApp }
{
    m_cells = new SpreadsheetCell * [m_width];
    for (size_t i{ 0 }; i < m_width; i++) {
        m_cells[i] = new SpreadsheetCell[m_height];
    }
}

Spreadsheet::Spreadsheet(const Spreadsheet& src)
    : Spreadsheet{src.m_width, src.m_height, src.m_theApp}
{
    for (size_t i{ 0 }; i < m_width; i++) {
        for (size_t j{ 0 }; j < m_height; j++) {
            m_cells[i][j] = src.m_cells[i][j];
        }
    }
}

void Spreadsheet::verifyCoordinate(size_t x, size_t y) const
{
    if (x >= m_width) {
        throw out_of_range { format("{} must be less than {}.", x, m_width) };
    }
    if (y >= m_height) {
        throw out_of_range { format("{} must be less than {}.", y, m_height) };
    }
}

void Spreadsheet::setCellAt(size_t x, size_t y, const SpreadsheetCell& cell)
{
    verifyCoordinate(x, y);
    m_cells[x][y] = cell;
}

const SpreadsheetCell& Spreadsheet::getCellAt(size_t x, size_t y) const
{
    verifyCoordinate(x, y);
    return m_cells[x][y];
}

SpreadsheetCell& Spreadsheet::getCellAt(size_t x, size_t y)
{
    return const_cast<SpreadsheetCell&>(as_const(*this).getCellAt(x, y));
}

Spreadsheet::~Spreadsheet()
{
    for (size_t i{ 0 }; i < m_width; i++) {
        delete[] m_cells[i];
    }
    delete[] m_cells;
    m_cells = nullptr;
}

//Spreadsheet::Spreadsheet(Spreadsheet&& src) noexcept
//{
//    /*swap(*this, src);*/
//    swap(src);
//}
//
//Spreadsheet& Spreadsheet::operator=(Spreadsheet&& rhs) noexcept
//{
//    /*swap(*this, rhs);*/
//    swap(rhs);
//    return *this;
//}