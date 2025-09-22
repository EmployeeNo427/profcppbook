export module ch32;

import std;

export namespace ch32 {

	namespace exercises {

		namespace ex1 {
			using namespace std;
			
			template <typename T>
			class Pointer 
			{
			public:
				explicit Pointer(T* src) : m_ptr{ src } {}
				~Pointer() { reset(); }

				//Prevent copy construction and copy assignment.
				Pointer(const Pointer& src) = delete;
				Pointer& operator=(const Pointer& rhs) = delete;

				//Allow move construction.
				Pointer(Pointer&& src) noexcept : m_ptr{ exchange(src.m_ptr,nullptr) } 
				{
				}

				//Allow move assignment.
				Pointer& operator=(Pointer&& rhs) noexcept
				{
					if (this != &rhs) {
						reset();
						m_ptr = exchange(rhs.m_ptr, nullptr);
					}
					return *this;
				}

				//get(), release(), and reset()
				T* get() const noexcept { return m_ptr; }

				[[nodiscard]] T* release() noexcept 
				{
					return exchange(m_ptr, nullptr);
				}

				void reset(T* ptr = nullptr) noexcept 
				{
					if (ptr!=m_ptr) { 
						delete m_ptr; 
						m_ptr = ptr;
					}
				}

				T& operator*() noexcept
				{
					return *m_ptr;
				}
				const T& operator*() const noexcept
				{
					return *m_ptr;
				}
			private:
				T* m_ptr{ nullptr };
			};

			void test() {
				Pointer<string> str_ptr{ new string{"Hello"}};
				println("str_ptr:{}", *str_ptr);
				str_ptr.reset(new string{ "World!" });
				println("str_ptr:{}", *str_ptr);
				if (auto raw = str_ptr.release()) {
					string str3{ *raw };
					delete raw;
					println("str3:{}", str3);
				}
				

				Pointer<int> int_ptr{ new int{34} };
				println("int_ptr:{}", *int_ptr);
				int_ptr.reset(new int{ 96 });
				println("int_ptr:{}", *int_ptr);
				int_ptr.reset();

				{
					Pointer pointer{ new int{ 42 } };
					println("{}", *pointer);

					Pointer pointer2{ std::move(pointer) };
					println("{}", *pointer2);

					Pointer<int> pointer3{ nullptr };
					pointer3 = std::move(pointer2);
					println("{}", *pointer3);

					pointer3 = std::move(pointer3);
					println("{}", *pointer3);
				}
			}
		}
		namespace ex2 {
			using namespace std;

			template <typename T>
			class Pointer
			{
			public:
				explicit Pointer(T* src) : m_ptr{ src } {
					if (!src) {
						throw runtime_error{ "src is nullptr." };
					}
				}
				~Pointer() { reset(); }

				//Prevent copy construction and copy assignment.
				Pointer(const Pointer& src) = delete;
				Pointer& operator=(const Pointer& rhs) = delete;

				//Allow move construction.
				Pointer(Pointer&& src) noexcept : m_ptr{ exchange(src.m_ptr,nullptr) }
				{
				}

				//Allow move assignment.
				Pointer& operator=(Pointer&& rhs) noexcept
				{
					if (this != &rhs) {
						reset();
						m_ptr = exchange(rhs.m_ptr, nullptr);
					}
					return *this;
				}

				//get(), release(), and reset()
				T* get() const noexcept { return m_ptr; }

				[[nodiscard]] T* release() noexcept
				{
					return exchange(m_ptr, nullptr);
				}

				void reset(T* ptr = nullptr) noexcept
				{
					if (ptr != m_ptr) {
						delete m_ptr;
						m_ptr = ptr;
					}
				}

				T& operator*() noexcept
				{
					return *m_ptr;
				}
				const T& operator*() const noexcept
				{
					return *m_ptr;
				}
			private:
				T* m_ptr{ nullptr };
			};

			void test() {
				Pointer<string> str_ptr{ new string{"Hello"} };
				println("str_ptr:{}", *str_ptr);
				str_ptr.reset(new string{ "World!" });
				println("str_ptr:{}", *str_ptr);
				if (auto raw = str_ptr.release()) {
					string str3{ *raw };
					delete raw;
					println("str3:{}", str3);
				}


				Pointer<int> int_ptr{ new int{34} };
				println("int_ptr:{}", *int_ptr);
				int_ptr.reset(new int{ 96 });
				println("int_ptr:{}", *int_ptr);
				int_ptr.reset();

				{
					Pointer pointer{ new int{ 42 } };
					println("{}", *pointer);

					Pointer pointer2{ std::move(pointer) };
					println("{}", *pointer2);

					try {
						Pointer<int> pointer3{ nullptr };
						pointer3 = std::move(pointer2);
						println("{}", *pointer3);

						pointer3 = std::move(pointer3);
						println("{}", *pointer3);
					}
					catch (const runtime_error& e) {
						println(cerr, "Caught exception:{}", e.what());
					}
				}
			}
		}
	}
}