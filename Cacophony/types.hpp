/**
@file types.hpp
@brief Common types.

@author Timothy Howard
@copyright 2014 Timothy Howard under the MIT license;
see @ref index or the accompanying LICENSE file for full text.
*/

#pragma once

#include <Cacophony/config.hpp>

#include <type_traits>

#include <duct/utility.hpp>

namespace Cacophony {

// Forward declarations
enum class tag_serialize : unsigned;
enum class tag_read : unsigned;
enum class tag_write : unsigned;

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
	serialize() function tag.
*/
enum class tag_serialize : unsigned {};

/**
	read() function tag.
*/
enum class tag_read : unsigned {};

/**
	write() function tag.
*/
enum class tag_write : unsigned {};

/**
	SFINAE.

	@tparam C Constraints.
*/
template<
	bool const C,
	class T = void
>
using enable = typename std::enable_if<
	C,
	T
>::type;

/**
	SFINAE with type @c ser_result_type.

	@tparam C Constraints.
*/
template<
	bool const C
>
using enable_ser = enable<C, ser_result_type>;

/**
	SFINAE with type @c ser_result_type for specific serializers.

	@tparam Ser Serializer type.
	@tparam ...M Serializers to match.
*/
template<
	class Ser,
	class... M
>
using enable_ser_of = enable<
	duct::is_same_any<Ser, M...>::value,
	ser_result_type
>;

/** @} */ // end of doc-group types

} // namespace Cacophony

