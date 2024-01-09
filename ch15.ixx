export module ch15;
import std;

export namespace ch15 {
    namespace examples {
        namespace overload_subscript_original {
            using namespace std;
            template <typename T>
            class Array
            {
            public:
                // Creates an array with a default size that will grow as needed.
                Array();
                virtual ~Array();

                // Disallow assignment and pass-by-value.
                Array& operator=(const Array& rhs) = delete;
                Array(const Array& src) = delete;

                // Move constructor and move assignment operator.
                Array(Array&& src) noexcept;
                Array& operator=(Array&& rhs) noexcept;

                // Returns the value at index x. Throws an exception of type
                // out_of_range if index x does not exist in the array.
                const T& getElementAt(size_t x) const;

                // Sets the value at index x. If index x is out of range,
                // allocates more space to make it in range.
                void setElementAt(size_t x, const T& value);

                // Returns the number of elements in the array.
                size_t getSize() const noexcept;
            private:
                static const size_t AllocSize{ 4 };
                void resize(size_t newSize);
                T* m_elements{ nullptr };
                size_t m_size{ 0 };
            };
            template <typename T> Array<T>::Array()
            {
                m_size = AllocSize;
                m_elements = new T[m_size]{}; // Elements are zero-initialized! 
            }

            template <typename T> Array<T>::~Array()
            {
                delete[] m_elements;
                m_elements = nullptr;
            }

            template <typename T> Array<T>::Array(Array&& src) noexcept
                : m_elements{ std::exchange(src.m_elements, nullptr) }
                , m_size{ std::exchange(src.m_size, 0) }
            {
            }

            template <typename T> Array<T>& Array<T>::operator=(Array<T>&& rhs) noexcept
            {
                if (this == &rhs) { return *this; }
                delete[] m_elements;
                m_elements = std::exchange(rhs.m_elements, nullptr);
                m_size = std::exchange(rhs.m_size, 0);
                return *this;
            }

            template <typename T> void Array<T>::resize(size_t newSize)
            {
                // Create new bigger array with zero-initialized elements.
                auto newArray{ std::make_unique<T[]>(newSize) };

                // The new size is always bigger than the old size (m_size).
                for (size_t i{ 0 }; i < m_size; i++) {
                    // Move the elements from the old array to the new one.
                    newArray[i] = std::move(m_elements[i]);
                }

                // Delete the old array, and set the new array.
                delete[] m_elements;
                m_size = newSize;
                m_elements = newArray.release();
            }

            template <typename T> const T& Array<T>::getElementAt(size_t x) const
            {
                if (x >= m_size) { throw std::out_of_range{ "" }; }
                return m_elements[x];
            }

            template <typename T> void Array<T>::setElementAt(size_t x, const T& val)
            {
                if (x >= m_size) {
                    // Allocate AllocSize past the element the client wants.
                    resize(x + AllocSize);
                }
                m_elements[x] = val;
            }

            template <typename T> size_t Array<T>::getSize() const noexcept
            {
                return m_size;
            }

            void test() {
                Array<int> myArray;
                for (size_t i{ 0 }; i < 10; i++) {
                    myArray.setElementAt(i, 100);
                }
                for (size_t i{ 0 }; i < 10; i++) {
                    cout << myArray.getElementAt(i) << " ";
                }
            }
        }
        namespace overload_subscript {
            using namespace std;
            template <typename T>
            class Array
            {
            public:
                // Creates an array with a default size that will grow as needed.
                Array();
                virtual ~Array();

                // Disallow assignment and pass-by-value.
                Array& operator=(const Array& rhs) = delete;
                Array(const Array& src) = delete;

                // Move constructor and move assignment operator.
                Array(Array&& src) noexcept;
                Array& operator=(Array&& rhs) noexcept;

                // Returns the value at index x. Throws an exception of type
                // out_of_range if index x does not exist in the array.
                const T& getElementAt(size_t x) const;

                // Sets the value at index x. If index x is out of range,
                // allocates more space to make it in range.
                void setElementAt(size_t x, const T& value);

                // Returns the number of elements in the array.
                size_t getSize() const noexcept;
                T& operator[](size_t x);
            private:
                static const size_t AllocSize{ 4 };
                void resize(size_t newSize);
                T* m_elements{ nullptr };
                size_t m_size{ 0 };
            };
            template <typename T> Array<T>::Array()
            {
                m_size = AllocSize;
                m_elements = new T[m_size]{}; // Elements are zero-initialized! 
            }

            template <typename T> Array<T>::~Array()
            {
                delete[] m_elements;
                m_elements = nullptr;
            }

            template <typename T> Array<T>::Array(Array&& src) noexcept
                : m_elements{ std::exchange(src.m_elements, nullptr) }
                , m_size{ std::exchange(src.m_size, 0) }
            {
            }

            template <typename T> Array<T>& Array<T>::operator=(Array<T>&& rhs) noexcept
            {
                if (this == &rhs) { return *this; }
                delete[] m_elements;
                m_elements = std::exchange(rhs.m_elements, nullptr);
                m_size = std::exchange(rhs.m_size, 0);
                return *this;
            }

            template <typename T> void Array<T>::resize(size_t newSize)
            {
                // Create new bigger array with zero-initialized elements.
                auto newArray{ std::make_unique<T[]>(newSize) };

                // The new size is always bigger than the old size (m_size).
                for (size_t i{ 0 }; i < m_size; i++) {
                    // Move the elements from the old array to the new one.
                    newArray[i] = std::move(m_elements[i]);
                }

                // Delete the old array, and set the new array.
                delete[] m_elements;
                m_size = newSize;
                m_elements = newArray.release();
            }

            template <typename T> const T& Array<T>::getElementAt(size_t x) const
            {
                if (x >= m_size) { throw std::out_of_range{ "" }; }
                return m_elements[x];
            }

            template <typename T> void Array<T>::setElementAt(size_t x, const T& val)
            {
                if (x >= m_size) {
                    // Allocate AllocSize past the element the client wants.
                    resize(x + AllocSize);
                }
                m_elements[x] = val;
            }

            template <typename T> size_t Array<T>::getSize() const noexcept
            {
                return m_size;
            }

            template <typename T> T& Array<T>::operator[](size_t x)
            {
                if (x >= m_size) {
                    // Allocate AllocSize past the element the client wants.
                    resize(x + AllocSize);
                }
                return m_elements[x];
            }

            void test() {
                Array<int> myArray;
                for (size_t i{ 0 }; i < 10; i++) {
                    myArray[i] = 100;
                }
                for (size_t i{ 0 }; i < 10; i++) {
                    cout << myArray[i] << " ";
                }
                Array<Array<int>> a;
                a[2][4] = 24;
                cout << a[2][4] << endl;
            }
        }
    }
    namespace exercises {
        namespace ex1 {
            using namespace std;
            template <typename T>
            class AssociativeArray {
                using Element = pair<string, T>;
            public:
                AssociativeArray() = default;
                virtual ~AssociativeArray() = default;
                AssociativeArray(initializer_list<Element> elms) :m_vector{ elms } {};
                T& operator[](string_view s) {
                    for (auto& elm : m_vector) {
                        if (elm.first == s) {
                            return elm.second;
                        }
                    }
                    m_vector.push_back(Element{ std::string{ s }, T{} });
                    return m_vector.back().second;
                }
                const T& operator[](string_view s) const {
                    for (const auto& elm : m_vector) {
                        if (elm.first == s) {
                            return elm.second;
                        }
                    }
                    throw invalid_argument{ format("did not find element with key name: \"{}\"",s.data()) };
                }
            private:
                vector<Element> m_vector{};
            };
            void test() {
                AssociativeArray<int> aint{ pair{"three",3},pair{"two",2}, pair{"five",5} };
                cout << aint["two"] << endl;
                aint["two"] = 45;
                cout << aint["three"] << endl;
                cout << aint["two"] << endl;

                AssociativeArray<string> astr{ pair{"three","threeups"},pair{"two","twoups"}, pair{"five","foup"}};
                cout << astr["two"] << endl;
                astr["two"] = "halahala";
                cout << astr["three"] << endl;
                cout << astr["two"] << endl;
            }
            void test_textbook() {
                AssociativeArray<int> myArray;
                myArray["Key 1"] = 11;
                myArray["Key 2"] = 22;
                myArray["Key 3"] = 33;

                try {
                    cout << myArray["Key 1"] << endl;
                    cout << myArray["Key 2"] << endl;

                    // Test const operator[]
                    const AssociativeArray<int>& c{ myArray };
                    cout << c["Key 3"] << endl;
                    cout << c["Key 4"] << endl;
                }
                catch (const exception& ex) {
                    cout << "Caught exception: " << ex.what() << endl;
                }
            }
        }
    }
}