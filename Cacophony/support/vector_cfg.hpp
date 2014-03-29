/**
@file support/vector_cfg.hpp
@brief Vector serialization configuration.

@author Timothy Howard
@copyright 2014 Timothy Howard under the MIT license;
see @ref index or the accompanying LICENSE file for full text.
*/

#ifndef CACOPHONY_SUPPORT_VECTOR_CFG_HPP_
#define CACOPHONY_SUPPORT_VECTOR_CFG_HPP_

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
	class V,
	bool const C
>
struct vector_cfg;

/**
	@addtogroup support
	@{
*/

/**
	Vector serialization configuration.

	@note @a S must satisfy is_size_type, which requires an unsigned
	integral type by default. @a V must have the same interface as
	@c std::vector for the default serialization to work.

	@tparam S Size type.
	@tparam V Vector type.
	@tparam C Whether the value type is immutable.
*/
template<
	class S,
	class V,
	bool const C
>
struct vector_cfg final {
	static_assert(
		is_size_type<S>::value,
		"S must satisfy cacophony::is_size_type"
	);

	/** Size type. */
	using size_type = S;
	/** Vector type. */
	using vector_type = V;
	/** Value type. */
	using value_type = typename vector_type::value_type;

	/** Whether the value type is immutable. */
	static constexpr bool const
	is_const = C;

	/** Reference to vector. */
	vector_type& vec;
};

/** @cond INTERNAL */

template<class Ser, class S, class V>
inline tag_read<Ser>
read(
	Ser& ser,
	vector_cfg<S, V, false>& cfg
) {
	S size{};
	ser(size);

	if (0 < size) {
		cfg.vec.resize(size);
		ser(make_sequence(cfg.vec.data(), cfg.vec.size()));
	} else {
		cfg.vec.clear();
	}
}

template<class Ser, class S, class V, bool const C>
inline tag_write<Ser>
write(
	Ser& ser,
	vector_cfg<S, V, C> const& cfg
) {
	DUCT_ASSERTE(std::numeric_limits<S>::max() >= cfg.vec.size());
	ser(static_cast<S>(cfg.vec.size()));
	if (!cfg.vec.empty()) {
		ser(make_sequence(cfg.vec.data(), cfg.vec.size()));
	}
}

/** @endcond */ // INTERNAL

/** @} */ // end of doc-group support

//} // namespace support
} // namespace Cacophony

#endif // CACOPHONY_SUPPORT_VECTOR_CFG_HPP_
