/**
@copyright MIT license; see @ref index or the accompanying LICENSE file.

@file
@brief Vector serialization configuration.
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

	@par
	@note Serialization:
	-# size
	-# sequence{elements}

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
inline ser_result_type
read(
	tag_read,
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
inline ser_result_type
write(
	tag_write,
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
