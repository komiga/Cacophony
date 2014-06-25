/**
@file support/sequence.hpp
@brief Sequence.

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
template<class T>
struct sequence;

/**
	@addtogroup support
	@{
*/

/**
	Sequence of objects.

	@note Serialization:
	-# elements

	@tparam T Value type.
*/
template<class T>
struct sequence final {
	static_assert(
		!std::is_void<T>::value,
		"T must be a non-void type"
	);

	/** Value type. */
	using value_type = T;

	/** Pointer to sequence. */
	value_type* ptr;
	/** Number of elements. */
	std::size_t size;
};

/**
	Make sequence.

	@param ptr Pointer to sequence.
	@param size Number of elements.
*/
template<
	class T
>
inline sequence<T>
make_sequence(
	T* const ptr,
	std::size_t const size
) noexcept {
	return {ptr, size};
}

/** @cond INTERNAL */

template<class Ser, class T>
inline enable_ser<
	!is_binary_serializable<bare_type<T>>::value
>
serialize(
	tag_serialize,
	Ser& ser,
	sequence<T>& seq
) {
	auto& self = const_safe<Ser>(seq);
	T const* const end = self.ptr + self.size;
	for (auto* it = self.ptr; end > it; ++it) {
		ser(*it);
	}
}

/** @endcond */ // INTERNAL

/** @} */ // end of doc-group support

//} // namespace support
} // namespace Cacophony

