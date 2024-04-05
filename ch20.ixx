export module ch20;
import std;

export namespace ch20 {
	namespace exercises {
		namespace ex1 {
			using namespace std;
			void println(std::vector<int> const& vi)
			{
				for (int e : vi)
					std::cout << e << ' ';
				std::cout << '\n';
			}
			void test(){ 
				{
					int num;
					print("Enter a number for range::fill(): ");
					cin >> num;


					vector<int> vi(10);
					ranges::fill(vi, num);
					println(vi);
				}
				{
					int num;
					print("Enter a number for std::fill(): ");
					cin >> num;

					vector<int> vi(10);
					fill(vi.begin(),vi.end(), num);
					println(vi);
				}
			}
			
			
		}
	}
}