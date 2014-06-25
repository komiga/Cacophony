/**
@file support/std_vector.hpp
@brief Serialization support for @c std::vector.

@author Timothy Howard
@copyright 2014 Timothy Howard under the MIT license;
see @ref index or the accompanying LICENSE file for full text.
*/

#pragma once

#include <Cacophony/config.hpp>
#include <Cacophony/types.hpp>
#include <Cacophony/support/vector_cfg.hpp>

#include <vector>

namespace Cacophony {
//namespace support {

/**
	@addtogroup support
	@{
*/

/**
	Make @c std::vector config.

	@tparam S Size type.
	@param vec Vector.
	@sa vector_cfg
	@{
*/
template<class S, class T, class Alloc>
vector_cfg<S, std::vector<T, Alloc>, false>
make_vector_cfg(
	std::vector<T, Alloc>& vec
) noexcept {
	return {vec};
}

template<class S, class T, class Alloc>
vector_cfg<S, std::vector<T, Alloc> const, true>
make_vector_cfg(
	std::vector<T, Alloc> const& vec
) noexcept {
	return {vec};
}
/** @} */

/** @cond INTERNAL */

template<class Ser, class T, class Alloc>
inline ser_result_type
read(
	tag_read,
	Ser& ser,
	std::vector<T, Alloc>& vec
) {
	ser(make_vector_cfg<default_size_type>(vec));
}

template<class Ser, class T, class Alloc>
inline ser_result_type
write(
	tag_write,
	Ser& ser,
	std::vector<T, Alloc> const& vec
) {
	ser(make_vector_cfg<default_size_type>(vec));
}

/** @endcond */ // INTERNAL

/** @} */ // end of doc-group support

//} // namespace support
} // namespace Cacophony

