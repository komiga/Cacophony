/**
@file support/std_string.hpp
@brief Serialization support for @c std::string.

@author Timothy Howard
@copyright 2014 Timothy Howard under the MIT license;
see @ref index or the accompanying LICENSE file for full text.
*/

#ifndef CACOPHONY_SUPPORT_STD_STRING_HPP_
#define CACOPHONY_SUPPORT_STD_STRING_HPP_

#include <Cacophony/config.hpp>
#include <Cacophony/traits.hpp>
#include <Cacophony/detail/gr_core.hpp>
#include <Cacophony/support/string_cfg.hpp>

#include <duct/IO/unicode.hpp>

#include <string>

namespace Cacophony {

// Forward declarations
class BinaryInputSerializer; // external
class BinaryOutputSerializer; // external

//namespace support {

/**
	@addtogroup support
	@{
*/

/**
	Make @c std::basic_string config.

	@tparam S Size type.
	@param str String.
	@sa string_cfg
	@{
*/
template<class S, class T, class Traits, class Alloc>
string_cfg<S, std::basic_string<T, Traits, Alloc>, false>
make_string_cfg(
	std::basic_string<T, Traits, Alloc>& str
) noexcept {
	return {str};
}

template<class S, class T, class Traits, class Alloc>
string_cfg<S, std::basic_string<T, Traits, Alloc> const, true>
make_string_cfg(
	std::basic_string<T, Traits, Alloc> const& str
) noexcept {
	return {str};
}
/** @} */

/** @cond INTERNAL */

#define CACOPHONY_CHECK_IO_ERROR(m_) \
	if (ser.get_stream().fail()) {										\
		CACOPHONY_THROW_FUNC(ErrorCode::serialization_io_failed, m_);	\
	}

#define CACOPHONY_SCOPE_FUNC read
template<class S, class T>
inline tag_read_loose<>
read(
	BinaryInputSerializer& ser,
	string_cfg<S, T, false>& cfg
) {
	S size{};
	ser(size);

	if (0 < size) {
		duct::IO::read_string_copy(
			ser.get_stream(),
			cfg.str,
			size,
			ser.get_endian()
		);
		CACOPHONY_CHECK_IO_ERROR(
			"failed to read string data from stream"
		);
	} else {
		cfg.str.clear();
	}
}
#undef CACOPHONY_SCOPE_FUNC

#define CACOPHONY_SCOPE_FUNC write
template<class S, class T, bool const C>
inline tag_write_loose<>
write(
	BinaryOutputSerializer& ser,
	string_cfg<S, T, C> const& cfg
) {
	DUCT_ASSERTE(std::numeric_limits<S>::max() >= cfg.str.size());
	ser(static_cast<S>(cfg.str.size()));
	if (!cfg.str.empty()) {
		duct::IO::write_string_copy(
			ser.get_stream(),
			cfg.str,
			ser.get_endian()
		);
		CACOPHONY_CHECK_IO_ERROR(
			"failed to write string data to stream"
		);
	}
}
#undef CACOPHONY_SCOPE_FUNC

#undef CACOPHONY_CHECK_IO_ERROR

template<class Ser, class T, class Traits, class Alloc>
inline tag_read<Ser>
read(
	Ser& ser,
	std::basic_string<T, Traits, Alloc>& str
) {
	ser(make_string_cfg<default_size_type>(str));
}

template<class Ser, class T, class Traits, class Alloc>
inline tag_write<Ser>
write(
	Ser& ser,
	std::basic_string<T, Traits, Alloc> const& str
) {
	ser(make_string_cfg<default_size_type>(str));
}

/** @endcond */ // INTERNAL

/** @} */ // end of doc-group support

//} // namespace support
} // namespace Cacophony

#include <Cacophony/detail/gr_unconfigure.hpp>

#endif // CACOPHONY_SUPPORT_STD_STRING_HPP_
