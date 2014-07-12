/**
@file utility.hpp
@brief Utilities.

@author Timothy Howard
@copyright 2014 Timothy Howard under the MIT license;
see @ref index or the accompanying LICENSE file for full text.
*/

#pragma once

#include <Cacophony/config.hpp>
#include <Cacophony/types.hpp>
#include <Cacophony/traits.hpp>

#include <type_traits>

namespace Cacophony {

// Forward declarations

/**
	@addtogroup etc
	@{
*/
/**
	@addtogroup utility
	@{
*/

	// @tparam Ser Serializer type.
	// @tparam T Object type; inferred from @a obj.
/**
	Make reference const-safe by serializer type.
*/
template<
	class Ser,
	class T
>
inline typename std::conditional<
	is_output_serializer<Ser>::value,
	T const&,
	T&
>::type
const_safe(T& obj) {
	return obj;
}

/**
	Cast reference to base-class.

	@remarks This preserves constness of @a obj.
*/
template<
	class B,
	class D
>
inline typename std::conditional<
	std::is_const<D>::value,
	B const&,
	B&
>::type
base_cast(D& obj) {
	return obj;
}

/** @} */ // end of doc-group utility
/** @} */ // end of doc-group etc

} // namespace Cacophony
