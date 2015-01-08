/**
@copyright MIT license; see @ref index or the accompanying LICENSE file.

@file
@brief Input serializer.
*/

#pragma once

#include <Cacophony/config.hpp>
#include <Cacophony/types.hpp>
#include <Cacophony/traits.hpp>
#include <Cacophony/utility.hpp>
#include <Cacophony/BaseSerializer.hpp>

namespace Cacophony {

// Forward declarations
template<class Impl>
class InputSerializer;

/**
	@addtogroup serializer
	@{
*/

/**
	Base input serializer.

	@remarks This class uses CRTP.

	@tparam Impl Implementation.
*/
template<class Impl>
class InputSerializer
	: public BaseSerializer<Impl>
{
private:
	using impl_type = Impl;
	using this_type = InputSerializer<impl_type>;
	using base_type = BaseSerializer<impl_type>;

protected:
/** @name Special member functions */ /// @{
	/** Destructor. */
	~InputSerializer() = default;

	/** Default constructor. */
	InputSerializer() = default;
	/** Copy constructor. */
	InputSerializer(InputSerializer const&) = default;
	/** Move constructor. */
	InputSerializer(InputSerializer&&) = default;
	/** Copy assignment operator. */
	InputSerializer& operator=(InputSerializer const&) = default;
	/** Move assignment operator. */
	InputSerializer& operator=(InputSerializer&&) = default;
/// @}

private:
	template<class T>
	static constexpr unsigned
	traits() noexcept {
		return
			has_member_serialize		<impl_type, T>::value +
			has_non_member_serialize	<impl_type, T>::value +
			has_member_read				<impl_type, T>::value +
			has_non_member_read			<impl_type, T>::value
		;
	}

public:
/** @name Value processing */ /// @{
	/**
		Base input process_impl().

		Calls accessor::in() with the serializer implementation and
		given value.
	*/
	template<class T>
	enable<1u == traits<T>()>
	process_impl(T&& value) {
		accessor::in(base_type::impl(), std::forward<T>(value));
	}

	template<class T>
	enable<1u != traits<T>()>
	process_impl(T&&) {
		static_assert(
			0u != traits<T>(),
			"neither serialize() nor read() have been defined for T"
		);
		static_assert(
			1u >= traits<T>(),
			"serialization of T is ambiguous because it has multiple"
			" input serialization function definitions"
		);
	}
/// @}
};

/** @} */ // end of doc-group serializer

} // namespace Cacophony
