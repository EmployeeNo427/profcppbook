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
        namespace ex4 {
            namespace myanswer {
                void test() {
                    /* https://godbolt.org/z/vEsraYrz7

## 1. What the exercise was really about

**Goal:**
Show that you can make C and C++ call each other safely, in *both* directions, using only C-compatible types.

Call chain:

```text
main (C++) → writeTextFromC (C) → writeTextFromCpp (C++)
```

And the C++ function must use the C++ Standard Library (`std::println` / `std::cout`) to print.

So the exercise is primarily about:

* **Linkage and name mangling** (`extern "C"`)
* **Separating C and C++ translation units**
* **Using headers correctly to share declarations between languages**

---

## 2. Final architecture that works

You ended up with the same structure as the author, just different filenames:

* `main.cpp`      – C++ `main`, calls `writeTextFromC`.
* `clib.c`        – C function `writeTextFromC`, calls `writeTextFromCpp`.
* `clib.h`        – C header for `writeTextFromC`, wrapped in `extern "C"` for C++.
* `cpplib.cpp`    – C++ function `writeTextFromCpp`, implements the printing.
* `cpplib.hpp`    – C header for `writeTextFromCpp`, wrapped in `extern "C"` for C++.
* `CMakeLists.txt` – builds one executable from `main.cpp`, `clib.c`, `cpplib.cpp`.

This matches the author’s split:

* `writeTextC.{h,c}`   ↔ your `clib.{h,c}`
* `writeTextCpp.{h,cpp}` ↔ your `cpplib.{hpp,cpp}`
* `test.cpp` ↔ your `main.cpp`

The *pattern* is what matters.

---

## 3. The key technical ideas (what you should remember)

### 3.1 C vs C++ translation units

* Files ending in `.c` are compiled as **C**.
* Files ending in `.cpp` are compiled as **C++**.
* A `.c` file **cannot** contain C++ syntax (`std::println`, templates, etc.).
* C++ features must live in `.cpp` files; C files should only see C-style declarations.

You tripped on this once by including a C++ header (with C++ code) into `clib.c`. The fix was:

* Make headers that are **pure declarations**, no C++-only constructs.
* Put the actual C++ implementation in `.cpp` files.

---

### 3.2 Why `extern "C"` is needed

Normal C++ function:

```cpp
void writeTextFromCpp(const char*);
```

is compiled with **C++ linkage**, meaning the symbol name is mangled (e.g. `_Z15writeTextFromCppPKc`). C code would look for a plain `writeTextFromCpp` symbol and fail to link.

Declaring with `extern "C"`:

```cpp
extern "C" void writeTextFromCpp(const char*);
```

tells the C++ compiler:

> “Use **C linkage**: do not mangle the name; use the C calling convention.”

Both your solution and the author’s use the idiomatic pattern in headers:

```cpp
#ifdef __cplusplus
extern "C" {
#endif

void writeTextFromC(const char* text);
void writeTextFromCpp(const char* text);

#ifdef __cplusplus
} // matches extern "C"
#endif
```

* When included from **C++**: `__cplusplus` is defined → the declarations are inside `extern "C" { … }`.
* When included from **C**: `__cplusplus` is not defined → the declarations are just plain C functions.

**Takeaway:** any function that will be *implemented in C++* but *called from C* must be **declared** with `extern "C"` on the C++ side (via header) so both languages agree on the same C-style symbol.

In this exercise, that’s:

* `writeTextFromC` (declared in `clib.h`, used by `main.cpp` and `clib.c`)
* `writeTextFromCpp` (declared in `cpplib.hpp`, used by `clib.c` and `cpplib.cpp`)

---

### 3.3 Clean separation of roles

* **Headers (`.h` / `.hpp`)**

  * Only **declarations**.
  * Must be valid C when included from C (no `std::`, no templates, no C++ keywords except in `#ifdef __cplusplus` sections).
  * Use `extern "C"` guards so the same header works for both C and C++.

* **Implementations**

  * `clib.c` → implements `writeTextFromC` (pure C), calls `writeTextFromCpp`.
  * `cpplib.cpp` → implements `writeTextFromCpp` (C++), uses `std::println` or I/O.

That separation is what allows both languages to work together cleanly.

---

### 3.4 Build system / linking

CMake:

```cmake
project(CppInterfacingC C CXX)

add_executable(the_executable
    main.cpp
    clib.c
    cpplib.cpp
)
```

Key points:

* Both the C file and the C++ files are part of **one executable**.
* GCC is invoked in C mode for `clib.c` and in C++ mode for the `.cpp` files.
* Because both headers declared the functions with `extern "C"`, all translation units agree on the same function symbols, so linking succeeds.

---

### 3.5 C++ Standard Library usage

* To use `std::println`, you need:

  * A compiler and standard library that support `<print>` (C++23), which you solved by switching to GCC 15.2 and `-std=c++23`.
* The call itself:

  ```cpp
  #include <print>
  #include "cpplib.hpp"

  void writeTextFromCpp(const char* input) {
      std::println("writeTextFromCpp:{}", input);
  }
  ```

The older alternative (usable on older compilers) is to use `<iostream>` and `std::cout`; the interop pattern stays identical.

---

## 4. Pitfalls you encountered (and how you fixed them)

These are worth remembering because they’re easy to repeat:

1. **Including a C++ header in C code that contained C++ constructs**

   * Problem: C compiler chokes on `std::println` and templates.
   * Lesson: headers shared with `.c` files must be **C-only declarations** (plus guarded `extern "C"`).

2. **Using `<cpplib.hpp>` instead of `"cpplib.hpp"`**

   * With `<...>` the compiler only searches system include paths; your project header wasn’t found.
   * Lesson: use `"..."` for project-local headers.

3. **Using `<print>` on an older compiler / standard**

   * Problem: GCC 10 didn’t have `<print>`.
   * Solution: either upgrade to a C++23-capable compiler or fall back to `<iostream>`.

4. **Confusion around what needs `extern "C"`**

   * You learned that:

     * The **declarations** in headers that will be seen by both C and C++ must use the `#ifdef __cplusplus extern "C"` idiom.
     * Implementations in `.c` files are naturally C; implementations in `.cpp` files match the declarations.

---

## 5. A mental template you can reuse

Next time you need “C calls C++” or “C++ calls C”:

1. **Decide the call chain.**
   Here: C++ `main` → C wrapper → C++ implementation.

2. **Create C-compatible headers** for each direction:

   ```cpp
   // my_api.h or my_api.hpp
   #pragma once
   #ifdef __cplusplus
   extern "C" {
   #endif

   void someFunction(const char*);

   #ifdef __cplusplus
   }
   #endif
   ```

3. **Implement C wrappers in `.c`** files, C++ logic in `.cpp` files.

4. **Add all `.c` + `.cpp` files** to the same target in your build system.

If you remember that pattern and the purpose of `extern "C"`, you can reconstruct this entire exercise without opening any of the original code.
 */
                }
			}
	}
}