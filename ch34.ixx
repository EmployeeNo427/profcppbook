export module ch34;

import std;
import <cstdint>;

export namespace ch34 {
	namespace exercises {
		namespace ex1 {
			namespace myanswer {
                /*https://godbolt.org/z/1z1EjP6TW */
                void std_int_size_inspect() {
                    using namespace std;

                    cout << "signed char: " << sizeof(signed char) << endl;
                    cout << "unsigned char: " << sizeof(unsigned char) << endl;
                    cout << "short int: " << sizeof(short int) << endl;
                    cout << "unsigned short int: " << sizeof(unsigned short int) << endl;
                    cout << "int: " << sizeof(int) << endl;
                    cout << "unsigned int: " << sizeof(unsigned int) << endl;
                    cout << "long int: " << sizeof(long int) << endl;
                    cout << "unsigned long int: " << sizeof(unsigned long int) << endl;
                    cout << "long long int: " << sizeof(long long int) << endl;
                    cout << "unsigned long long int: " << sizeof(unsigned long long int) << endl;
                }
                void test() {
                    std_int_size_inspect();
                }
			}
		}
        namespace ex2 {
            namespace myanswer {
                /* https://godbolt.org/z/1z1EjP6TW */
                std::string big_and_little_endian_uint16_t(uint16_t input) {
                    using namespace std;

                    std::bitset<16> result_bitset((input << 8) | (input >> 8));

                    // Print the binary representation
                    std::cout << "Binary representation of " << input << " after endian conversion: " << result_bitset << std::endl;

                    // Convert to a string
                    std::string result = result_bitset.to_string();

                    switch (endian::native)
                    {
                    case endian::little:
                        cout << "Native ordering is little-endian. Result is big-endian." << endl;

                        break;
                    case endian::big:
                        cout << "Native ordering is big-endian.Result is little-endian." << endl;
                        break;
                    }
                    return result;
                }
                std::string big_and_little_endian_uint32_t(uint32_t input) {
                    using namespace std;

                    std::bitset<32> result_bitset(
                        ((input & 0x000000FFu) << 24) |  // lowest  byte → highest
                        ((input & 0x0000FF00u) << 8) |  // 2nd-lowest → 2nd-highest
                        ((input & 0x00FF0000u) >> 8) |  // 2nd-highest → 2nd-lowest
                        ((input & 0xFF000000u) >> 24)
                    );

                    // Print the binary representation
                    std::cout << "Binary representation of " << input << " after endian conversion: " << result_bitset << std::endl;

                    // Convert to a string
                    std::string result = result_bitset.to_string();

                    switch (endian::native)
                    {
                    case endian::little:
                        cout << "Native ordering is little-endian. Result is big-endian." << endl;

                        break;
                    case endian::big:
                        cout << "Native ordering is big-endian.Result is little-endian." << endl;
                        break;
                    }
                    return result;
                }
                void test() {
                    big_and_little_endian_uint16_t(uint16_t{ 513 });
                    big_and_little_endian_uint32_t(uint32_t{ 51398751 });
                }
            }
        }
        namespace ex3 {
            namespace myanswer {
                void test() {
                    /* https://godbolt.org/z/beTosjYxe */
                }
            }
		}
	}
}