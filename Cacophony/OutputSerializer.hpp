/**
@file OutputSerializer.hpp
@brief Output serializer.

@author Timothy Howard
@copyright 2014 Timothy Howard under the MIT license;
see @ref index or the accompanying LICENSE file for full text.
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
class OutputSerializer;

/**
	@addtogroup serializer
	@{
*/

/**
	Base output serializer.

	@remarks This class uses CRTP.

	@tparam Impl Implementation.
*/
template<class Impl>
class OutputSerializer
	: public BaseSerializer<Impl>
{
private:
	using impl_type = Impl;
	using this_type = OutputSerializer<impl_type>;
	using base_type = BaseSerializer<impl_type>;

protected:
/** @name Special member functions */ /// @{
	/** Destructor. */
	~OutputSerializer() = default;

	/** Default constructor. */
	OutputSerializer() = default;
	/** Copy constructor. */
	OutputSerializer(OutputSerializer const&) = default;
	/** Move constructor. */
	OutputSerializer(OutputSerializer&&) = default;
	/** Copy assignment operator. */
	OutputSerializer& operator=(OutputSerializer const&) = default;
	/** Move assignment operator. */
	OutputSerializer& operator=(OutputSerializer&&) = default;
/// @}

private:
	template<class T>
	static constexpr unsigned
	traits() noexcept {
		return
			has_member_serialize	<impl_type, T>::value +
			has_non_member_serialize<impl_type, T>::value +
			has_member_write		<impl_type, T>::value +
			has_non_member_write	<impl_type, T>::value
		;
	}

public:
/** @name Value processing */ /// @{
	/**
		Base output process_impl().

		Calls accessor::out() with the serializer implementation and
		given value.
	*/
	template<class T>
	enable<1u == traits<T>()>
	process_impl(T const& value) {
		accessor::out(base_type::impl(), value);
	}

	template<class T>
	enable<1u != traits<T>()>
	process_impl(T const&) {
		static_assert(
			0u != traits<T>(),
			"neither serialize() nor write() have been defined for T"
		);
		static_assert(
			1u >= traits<T>(),
			"serialization of T is ambiguous because it has multiple"
			" output serialization function definitions"
		);
	}
/// @}
};

/** @} */ // end of doc-group serializer

} // namespace Cacophony

