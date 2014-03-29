/**
@file types.hpp
@brief Common types.

@author Timothy Howard
@copyright 2014 Timothy Howard under the MIT license;
see @ref index or the accompanying LICENSE file for full text.
*/

#ifndef CACOPHONY_TYPES_HPP_
#define CACOPHONY_TYPES_HPP_

#include <Cacophony/config.hpp>

#include <type_traits>

namespace Cacophony {

/**
	@addtogroup types
	@{
*/

/**
	Result type of serialization functions.
*/
using ser_result_type = void;

/**
	Default size type for collections.
*/
using default_size_type = std::uint32_t;

/**
	SFINAE.

	@tparam value Boolean to enable or disable.
*/
template<
	bool const value,
	class T = void
>
using enable = typename std::enable_if<
	value,
	T
>::type;

/**
	SFINAE with type @c ser_result_type.

	@tparam value Boolean to enable or disable.
*/
template<
	bool const value
>
using enable_ser = enable<value, ser_result_type>;

/** @} */ // end of doc-group types

} // namespace Cacophony

#endif // CACOPHONY_TYPES_HPP_
