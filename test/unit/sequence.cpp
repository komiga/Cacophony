
#include "./../common/traits.hpp"
#include "./../common/DebugSerializer.hpp"

#include <Cacophony/utility.hpp>
#include <Cacophony/traits.hpp>
#include <Cacophony/support/std_vector.hpp>

#include <vector>

using ISer = DebugInputSerializer;
using OSer = DebugOutputSerializer;

ISer s_iser{};
OSer s_oser{};

struct NonBinary {
public:
	~NonBinary() = default;
	NonBinary() = default;
	NonBinary(NonBinary const&) = delete;
	NonBinary& operator=(NonBinary const&) = delete;
	NonBinary(NonBinary&&) = default;
	NonBinary& operator=(NonBinary&&) = default;
};

template<class Ser>
inline Cacophony::tag_serialize<Ser> serialize(Ser& ser, NonBinary& value) {
	auto& self = Cacophony::const_safe<Ser>(value);
	(void)ser;
	(void)self;
}

template<class T>
void
input(T&& value) {
	std::cout << "input:\n";
	s_iser(value);
	std::cout << std::endl;
}

template<class T>
void
output(T&& value) {
	std::cout << "output:\n";
	s_oser(value);
	std::cout << std::endl;
}

template<class T>
void
both(T&& value) {
	output(std::forward<T>(value));
	input(std::forward<T>(value));
}

signed
main() {
	print_traits<ISer, OSer, Cacophony::sequence<NonBinary>>();
	print_traits<ISer, OSer, Cacophony::sequence<NonBinary> const>();
	print_traits<ISer, OSer, Cacophony::sequence<NonBinary const>>();
	print_traits<ISer, OSer, Cacophony::sequence<int>>();

	NonBinary const nb1{};
	output(nb1);
	NonBinary nb2{};
	both(nb2);

	output(std::vector<NonBinary>{1});
	std::vector<NonBinary> vnb{2};
	both(vnb);

	std::vector<int> vint{2};
	both(vint);

	return 0;
}
