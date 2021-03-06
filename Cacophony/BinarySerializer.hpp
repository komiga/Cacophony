/**
@copyright MIT license; see @ref index or the accompanying LICENSE file.

@file
@brief Binary serializers.
*/

#pragma once

#include <Cacophony/config.hpp>
#include <Cacophony/traits.hpp>
#include <Cacophony/utility.hpp>
#include <Cacophony/InputSerializer.hpp>
#include <Cacophony/OutputSerializer.hpp>
#include <Cacophony/support/binary_blob.hpp>
#include <Cacophony/support/sequence.hpp>

#include <duct/EndianUtils.hpp>
#include <duct/IO/arithmetic.hpp>

#include <type_traits>
#include <iostream>

#include <Cacophony/detail/gr_core.hpp>

namespace Cacophony {

// Forward declarations
class BinaryInputSerializer;
class BinaryOutputSerializer;

/**
	@addtogroup serializer
	@{
*/

/**
	Binary input serializer.
*/
class BinaryInputSerializer
	: public InputSerializer<BinaryInputSerializer>
{
private:
	using this_type = BinaryInputSerializer;
	using base_type = InputSerializer<this_type>;

	std::istream& m_stream;
	duct::Endian m_endian;

	BinaryInputSerializer() = delete;
	BinaryInputSerializer(BinaryInputSerializer const&) = delete;
	BinaryInputSerializer& operator=(BinaryInputSerializer const&) = delete;

public:
/** @name Special member functions */ /// @{
	/** Destructor. */
	~BinaryInputSerializer() = default;

	/** Move constructor. */
	BinaryInputSerializer(BinaryInputSerializer&&) = default;
	/** Move assignment operator. */
	BinaryInputSerializer& operator=(BinaryInputSerializer&&) = default;

	/**
		Constructor with stream and endian.
	*/
	BinaryInputSerializer(
		std::istream& stream,
		duct::Endian const endian
	)
		: base_type(*this)
		, m_stream(stream)
		, m_endian(endian)
	{}
/// @}

/** @name Properties */ /// @{
	/**
		Get stream.
	*/
	std::istream&
	stream() noexcept {
		return m_stream;
	}

	/**
		Get endian.
	*/
	duct::Endian
	endian() const noexcept {
		return m_endian;
	}
/// @}
};

/**
	Binary input serializer.
*/
class BinaryOutputSerializer
	: public OutputSerializer<BinaryOutputSerializer>
{
private:
	using this_type = BinaryOutputSerializer;
	using base_type = OutputSerializer<this_type>;

	std::ostream& m_stream;
	duct::Endian m_endian;

	BinaryOutputSerializer() = delete;
	BinaryOutputSerializer(BinaryOutputSerializer const&) = delete;
	BinaryOutputSerializer& operator=(BinaryOutputSerializer const&) = delete;

public:
/** @name Special member functions */ /// @{
	/** Destructor. */
	~BinaryOutputSerializer() = default;

	/** Move constructor. */
	BinaryOutputSerializer(BinaryOutputSerializer&&) = default;
	/** Move assignment operator. */
	BinaryOutputSerializer& operator=(BinaryOutputSerializer&&) = default;

	/**
		Constructor with stream and endian.
	*/
	BinaryOutputSerializer(
		std::ostream& stream,
		duct::Endian const endian
	)
		: base_type()
		, m_stream(stream)
		, m_endian(endian)
	{}
/// @}

/** @name Properties */ /// @{
	/**
		Get stream.
	*/
	std::ostream&
	stream() noexcept {
		return m_stream;
	}

	/**
		Get endian.
	*/
	duct::Endian
	endian() const noexcept {
		return m_endian;
	}
/// @}
};

/** @cond INTERNAL */

#define CACOPHONY_CHECK_IO_ERROR(m_) \
	if (ser.stream().fail()) {										\
		CACOPHONY_THROW_FUNC(ErrorCode::serialization_io_failed, m_);	\
	}

// arithmetic

#define CACOPHONY_SCOPE_FUNC read
template<class T>
inline enable_ser<
	std::is_arithmetic<bare_type<T>>::value
>
read(
	tag_read,
	BinaryInputSerializer& ser,
	T& value
) {
	duct::IO::read_arithmetic(ser.stream(), value, ser.endian());
	CACOPHONY_CHECK_IO_ERROR(
		"failed to read arithmetic type from stream"
	);
}
#undef CACOPHONY_SCOPE_FUNC

#define CACOPHONY_SCOPE_FUNC write
template<class T>
inline enable_ser<
	std::is_arithmetic<bare_type<T>>::value
>
write(
	tag_write,
	BinaryOutputSerializer& ser,
	T const& value
) {
	duct::IO::write_arithmetic(ser.stream(), value, ser.endian());
	CACOPHONY_CHECK_IO_ERROR(
		"failed to write arithmetic type to stream"
	);
}
#undef CACOPHONY_SCOPE_FUNC

// arithmetic sequence

#define CACOPHONY_SCOPE_FUNC read
template<class T>
inline enable_ser<
	std::is_arithmetic<bare_type<T>>::value
>
read(
	tag_read,
	BinaryInputSerializer& ser,
	sequence<T>& seq
) {
	duct::IO::read_arithmetic_array(
		ser.stream(),
		seq.ptr, seq.size,
		ser.endian()
	);
	CACOPHONY_CHECK_IO_ERROR(
		"failed to read arithmetic sequence from stream"
	);
}
#undef CACOPHONY_SCOPE_FUNC

#define CACOPHONY_SCOPE_FUNC write
template<class T>
inline enable_ser<
	std::is_arithmetic<bare_type<T>>::value
>
write(
	tag_write,
	BinaryOutputSerializer& ser,
	sequence<T> const& seq
) {
	duct::IO::write_arithmetic_array(
		ser.stream(),
		seq.ptr, seq.size,
		ser.endian()
	);
	CACOPHONY_CHECK_IO_ERROR(
		"failed to write arithmetic sequence to stream"
	);
}
#undef CACOPHONY_SCOPE_FUNC

// binary-serializable sequence

#define CACOPHONY_SCOPE_FUNC read
template<class T>
inline enable_ser<
	!std::is_arithmetic<bare_type<T>>::value &&
	is_binary_serializable<bare_type<T>>::value
>
read(
	tag_read,
	BinaryInputSerializer& ser,
	sequence<T>& seq
) {
	ser.stream().read(
		reinterpret_cast<char*>(seq.ptr),
		seq.size * sizeof(T)
	);
	CACOPHONY_CHECK_IO_ERROR(
		"failed to read binary sequence from stream"
	);
}
#undef CACOPHONY_SCOPE_FUNC

#define CACOPHONY_SCOPE_FUNC write
template<class T>
inline enable_ser<
	!std::is_arithmetic<bare_type<T>>::value &&
	is_binary_serializable<bare_type<T>>::value
>
write(
	tag_write,
	BinaryOutputSerializer& ser,
	sequence<T> const& seq
) {
	ser.stream().write(
		reinterpret_cast<char const*>(seq.ptr),
		seq.size * sizeof(T)
	);
	CACOPHONY_CHECK_IO_ERROR(
		"failed to write arithmetic sequence to stream"
	);
}
#undef CACOPHONY_SCOPE_FUNC

// binary_blob

#define CACOPHONY_SCOPE_FUNC read
inline ser_result_type
read(
	tag_read,
	BinaryInputSerializer& ser,
	binary_blob<false>& blob
) {
	ser.stream().read(
		static_cast<char*>(blob.ptr),
		blob.size
	);
	CACOPHONY_CHECK_IO_ERROR(
		"failed to read binary blob from stream"
	);
}
#undef CACOPHONY_SCOPE_FUNC

#define CACOPHONY_SCOPE_FUNC write
template<bool const C>
inline ser_result_type
write(
	tag_write,
	BinaryOutputSerializer& ser,
	binary_blob<C> const& blob
) {
	ser.stream().write(
		static_cast<char const*>(blob.ptr),
		blob.size
	);
	CACOPHONY_CHECK_IO_ERROR(
		"failed to write binary blob to stream"
	);
}
#undef CACOPHONY_SCOPE_FUNC

#undef CACOPHONY_CHECK_IO_ERROR

/** @endcond */ // INTERNAL

/** @} */ // end of doc-group serializer

} // namespace Cacophony

#include <Cacophony/detail/gr_unconfigure.hpp>
