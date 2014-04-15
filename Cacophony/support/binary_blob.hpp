/**
@file support/binary_blob.hpp
@brief Binary blob.

@author Timothy Howard
@copyright 2014 Timothy Howard under the MIT license;
see @ref index or the accompanying LICENSE file for full text.
*/

#ifndef CACOPHONY_SUPPORT_BINARY_BLOB_HPP_
#define CACOPHONY_SUPPORT_BINARY_BLOB_HPP_

#include <Cacophony/config.hpp>

#include <type_traits>

namespace Cacophony {
//namespace support {

// Forward declarations
template<bool const C>
struct binary_blob;

/**
	@addtogroup support
	@{
*/

/**
	Binary blob.

	@tparam C Whether the blob is immutable.
*/
template<bool const C>
struct binary_blob final {
	/** Whether the blob is immutable. */
	static constexpr bool const
	is_const = C;

	/** Pointer type. */
	using type = typename std::conditional<
		is_const,
		void const*,
		void*
	>::type;

	/** Pointer to blob. */
	type ptr;
	/** Size of blob (in bytes). */
	std::size_t size;
};

/**
	Make binary blob.

	@param ptr Pointer to blob.
	@param size Size of blob in bytes.
*/
template<
	class T
>
inline binary_blob<std::is_const<T>::value>
make_binary_blob(
	T* const ptr,
	std::size_t const size
) noexcept {
	return {
		static_cast<
			typename binary_blob<std::is_const<T>::value>::type
		>(ptr),
		size
	};
}

/** @} */ // end of doc-group support

//} // namespace support
} // namespace Cacophony

#endif // CACOPHONY_SUPPORT_BINARY_BLOB_HPP_
