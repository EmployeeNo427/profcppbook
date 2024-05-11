export module ch21;
import std;

export namespace ch21 {
	namespace exercises {
		namespace ex1 {
			using namespace std;
			void test() {
				{
					wcout << "Your decimal separator is "
						<< use_facet<numpunct<wchar_t>>(locale{ "" }).
						decimal_point() << '\n';

					wcout << "Your separator between digit groups is "
						<< use_facet<numpunct<wchar_t>>(locale{ "" }).
						thousands_sep() << '\n';
				}
				{
					locale userLocale{ "" };
					auto& facet{ use_facet<numpunct<char>>(userLocale) };
					println("Decimal separator: {}", facet.decimal_point());
				}
			}
		}
	}
}