
#ifndef CACOPHONY_TEST_COMMON_DEBUGSERIALIZER_HPP_
#define CACOPHONY_TEST_COMMON_DEBUGSERIALIZER_HPP_

#include <Cacophony/types.hpp>
#include <Cacophony/traits.hpp>
#include <Cacophony/support/sequence.hpp>
#include <Cacophony/BaseSerializer.hpp>
#include <Cacophony/InputSerializer.hpp>
#include <Cacophony/OutputSerializer.hpp>

#include <iostream>

#include "./demangle.hpp"

template<
	template<class> class Base
>
class GenericDebugSerializer
	: public Base<GenericDebugSerializer<Base>>
{
private:
	using this_type = GenericDebugSerializer<Base>;
	using base_type = Base<this_type>;

	signed m_depth;

	std::string
	tabulate(signed const depth) {
		return std::string(2 * depth, ' ');
	}

public:
	~GenericDebugSerializer() = default;

	GenericDebugSerializer(GenericDebugSerializer const&) = default;
	GenericDebugSerializer(GenericDebugSerializer&&) = default;
	GenericDebugSerializer& operator=(GenericDebugSerializer const&) = default;
	GenericDebugSerializer& operator=(GenericDebugSerializer&&) = default;

	GenericDebugSerializer()
		: base_type(*this)
		, m_depth(0)
	{}

public:
	template<class T>
	void
	process_before(T const& /*value*/) noexcept {
		std::cout
			<< '\n'
			<< tabulate(m_depth)
			<< '[' << demangle<T>() << "] "
		;
	}

	template<class... P>
	void
	operator()(P&&... args) {
		std::cout << "{";
		++m_depth;
		base_type::process(std::forward<P>(args)...);
		--m_depth;
		std::cout
			<< '\n'
			<< tabulate(m_depth)
			<< "}"
		;
		if (0 == m_depth) {
			std::cout << std::endl;
		}
	}
};

using DebugInputSerializer = GenericDebugSerializer<Cacophony::InputSerializer>;
using DebugOutputSerializer = GenericDebugSerializer<Cacophony::OutputSerializer>;

// arithmetic

template<class T>
inline Cacophony::enable_ser<
	std::is_arithmetic<Cacophony::bare_type<T>>::value
>
read(
	DebugInputSerializer& /*ser*/,
	T&& /*value*/
) {}

template<class T>
inline Cacophony::enable_ser<
	std::is_arithmetic<Cacophony::bare_type<T>>::value
>
write(
	DebugOutputSerializer& /*ser*/,
	T const& value
) {
	std::cout << '(' << value << ") ";
}

// binary-serializable sequence

template<class T>
inline Cacophony::enable_ser<
	Cacophony::is_binary_serializable<Cacophony::bare_type<T>>::value
>
read(
	DebugInputSerializer& /*ser*/,
	Cacophony::sequence<T>& /*seq*/
) {}

template<class T>
inline Cacophony::enable_ser<
	Cacophony::is_binary_serializable<Cacophony::bare_type<T>>::value
>
write(
	DebugOutputSerializer& /*ser*/,
	Cacophony::sequence<T> const& /*seq*/
) {}

#endif // CACOPHONY_TEST_COMMON_DEBUGSERIALIZER_HPP_
