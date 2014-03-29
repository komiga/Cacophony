/**
@file InputSerializer.hpp
@brief Input serializer.

@author Timothy Howard
@copyright 2014 Timothy Howard under the MIT license;
see @ref index or the accompanying LICENSE file for full text.
*/

#ifndef CACOPHONY_INPUTSERIALIZER_HPP_
#define CACOPHONY_INPUTSERIALIZER_HPP_

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

public:
/** @name Value processing */ /// @{
	/**
		Base input process_impl().

		Calls accessor::in() with the serializer implementation and
		given value.
	*/
	template<class T>
	enable<1u == (
		has_member_serialize<impl_type, T>::value +
		has_non_member_serialize<impl_type, T>::value +
		has_member_read<impl_type, T>::value +
		has_non_member_read<impl_type, T>::value
	)>
	process_impl(T&& value) {
		accessor::in(base_type::impl(), std::forward<T>(value));
	}
/// @}
};

/** @} */ // end of doc-group serializer

} // namespace Cacophony

#endif // CACOPHONY_INPUTSERIALIZER_HPP_
