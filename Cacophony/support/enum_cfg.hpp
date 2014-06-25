/**
@file support/enum_cfg.hpp
@brief Enum serialization configuration.

@author Timothy Howard
@copyright 2014 Timothy Howard under the MIT license;
see @ref index or the accompanying LICENSE file for full text.
*/

#pragma once

#include <Cacophony/config.hpp>
#include <Cacophony/types.hpp>
#include <Cacophony/traits.hpp>
#include <Cacophony/utility.hpp>

#include <type_traits>

namespace Cacophony {
//namespace support {

// Forward declarations
template<
	class T,
	class B
>
struct enum_cfg;

/**
	@addtogroup support
	@{
*/

/**
	Enum serialization configuration.

	@note @a T must be an enum. @a B must satisfy @c std::is_integral.

	@tparam T Enum type.
	@tparam B Integral type to serialize to/from.
*/
template<
	class T,
	class B = typename std::underlying_type<T>::type
>
struct enum_cfg final {
	static_assert(
		std::is_enum<T>::value,
		"T must be an enum type"
	);
	static_assert(
		std::is_integral<B>::value,
		"B must be an integral type"
	);

	/** Value type. */
	using value_type = T;
	/** Binary type. */
	using binary_type = B;

	/** Reference to value. */
	value_type& value;
};

/**
	Make enum config.

	@tparam B Integral type to serialize to/from.
	@param value Enum value.
*/
template<
	class B,
	class T
>
inline enum_cfg<T, B>
make_enum_cfg(
	T& value
) noexcept {
	return {value};
}

/** @cond INTERNAL */

template<class Ser, class T, class B>
inline ser_result_type
read(
	tag_read,
	Ser& ser,
	enum_cfg<T, B>& cfg
) {
	B ebin{};
	ser(ebin);
	cfg.value = static_cast<T>(ebin);
}

template<class Ser, class T, class B>
inline ser_result_type
write(
	tag_write,
	Ser& ser,
	enum_cfg<T, B> const& cfg
) {
	B const ebin{static_cast<B const>(cfg.value)};
	ser(ebin);
}

/** @endcond */ // INTERNAL

/** @} */ // end of doc-group support

//} // namespace support
} // namespace Cacophony

