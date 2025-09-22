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
				explicit Pointer(T* src) : m_ptr{ exchange(src,nullptr) } {}
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
					if (m_ptr) { 
						delete m_ptr; 
						m_ptr = nullptr;
					}
					m_ptr = ptr;
				}

				T& operator*() noexcept
				{
					return *m_ptr;
				}
			private:
				T* m_ptr{ nullptr };
			};

			void test() {
				Pointer<string> str_ptr{ new string{"Hello"}};
				print("str_ptr:{}", *str_ptr);
				str_ptr.reset(new string{ "World!" });
				print("str_ptr:{}", *str_ptr);
				string str3{ *str_ptr.release() };
				print("str3:{}", str3);

				Pointer<int> int_ptr{ new int{34} };
				print("int_ptr:{}", *int_ptr);
				int_ptr.reset(new int{ 96 });
				print("int_ptr:{}", *int_ptr);
				int_ptr.reset();
			}
		}
	}
}