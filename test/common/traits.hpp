
#pragma once

#include "./demangle.hpp"

#include <Cacophony/types.hpp>
#include <Cacophony/traits.hpp>

#include <iomanip>
#include <iostream>

namespace {
constexpr inline char const*
boolname(bool const value) noexcept {
	return value
		? "true "
		: "false"
	;
}
}

template<
	class ISer,
	class OSer,
	class T
>
void
print_traits() {
	using namespace Cacophony;
	std::cout
		<< std::left
		<< demangle<T>() << " (ISer, OSer):\n"
		<< "is_{in,out}put_serializable = "
		<< boolname(is_input_serializable<ISer, T>::value) << ", "
		<< boolname(is_output_serializable<OSer, T>::value) << '\n'
		<< "has_member_serialize        = "
		<< boolname(has_member_serialize<ISer, T>::value) << ", "
		<< boolname(has_member_serialize<OSer, T>::value) << '\n'
		<< "has_non_member_serialize    = "
		<< boolname(has_non_member_serialize<ISer, T>::value) << ", "
		<< boolname(has_non_member_serialize<OSer, T>::value) << '\n'
		<< "has_member_read             = "
		<< boolname(has_member_read<ISer, T>::value) << ", "
		<< boolname(has_member_read<OSer, T>::value) << '\n'
		<< "has_non_member_read         = "
		<< boolname(has_non_member_read<ISer, T>::value) << ", "
		<< boolname(has_non_member_read<OSer, T>::value) << '\n'
		<< "has_member_write            = "
		<< boolname(has_member_write<ISer, T>::value) << ", "
		<< boolname(has_member_write<OSer, T>::value) << '\n'
		<< "has_non_member_write        = "
		<< boolname(has_non_member_write<ISer, T>::value) << ", "
		<< boolname(has_non_member_write<OSer, T>::value) << '\n'
		<< std::endl
	;
}
