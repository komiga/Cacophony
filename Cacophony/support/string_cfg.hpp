/**
@file support/string_cfg.hpp
@brief String serialization configuration.

@author Timothy Howard
@copyright 2014 Timothy Howard under the MIT license;
see @ref index or the accompanying LICENSE file for full text.
*/

#pragma once

#include <Cacophony/config.hpp>
#include <Cacophony/types.hpp>
#include <Cacophony/traits.hpp>
#include <Cacophony/utility.hpp>
#include <Cacophony/support/sequence.hpp>

#include <duct/debug.hpp>

#include <limits>

namespace Cacophony {
//namespace support {

// Forward declarations
template<
	class S,
	class T,
	bool const C
>
struct string_cfg;

/**
	@addtogroup support
	@{
*/

/**
	String serialization configuration.

	@note @a S must satisfy is_size_type, which requires an unsigned
	integral type by default. @a T must have the same interface as
	@c std::string for the default serialization to work.

	@par
	@note Serialization:
	-# size
	-# string data

	@tparam S Size type.
	@tparam T Vector type.
	@tparam C Whether the value type is immutable.
*/
template<
	class S,
	class T,
	bool const C
>
struct string_cfg final {
	static_assert(
		is_size_type<S>::value,
		"S must satisfy cacophony::is_size_type"
	);

	/** Size type. */
	using size_type = S;
	/** Vector type. */
	using string_type = T;
	/** Value type. */
	using value_type = typename string_type::value_type;

	/** Whether the value type is immutable. */
	static constexpr bool const
	is_const = C;

	/** Reference to string. */
	string_type& str;
};

/** @} */ // end of doc-group support

//} // namespace support
} // namespace Cacophony
