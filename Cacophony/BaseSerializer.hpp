/**
@file
@brief Base serializer.

@author Timothy Howard
@copyright 2014 Timothy Howard under the MIT license;
see @ref index or the accompanying LICENSE file for full text.
*/

#pragma once

#include <Cacophony/config.hpp>

#include <utility>

namespace Cacophony {

// Forward declarations
template<class Impl>
class BaseSerializer;

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
class BaseSerializer {
private:
	using this_type = BaseSerializer<Impl>;
	using impl_type = Impl;

protected:
/** @name Special member functions */ /// @{
	/** Destructor. */
	~BaseSerializer() = default;

	/** Default constructor. */
	BaseSerializer() = default;
	/** Copy constructor. */
	BaseSerializer(BaseSerializer const&) = default;
	/** Move constructor. */
	BaseSerializer(BaseSerializer&&) = default;
	/** Copy assignment operator. */
	BaseSerializer& operator=(BaseSerializer const&) = default;
	/** Move assignment operator. */
	BaseSerializer& operator=(BaseSerializer&&) = default;
/// @}

protected:
/** @name Properties */ /// @{
	/**
		Get reference to implementation.
	*/
	impl_type&
	impl() noexcept {
		return *static_cast<impl_type*>(this);
	}
/// @}

/** @name Value processing */ /// @{
	/**
		Called before process_impl().
	*/
	template<class T>
	void
	process_before(T const& /*value*/) const noexcept {}

	/**
		Called after process_impl().
	*/
	template<class T>
	void
	process_after(T const& /*value*/) const noexcept {}

	/**
		Process a value.

		@note This calls process_before(), process_impl(), and
		process_after() in order.
	*/
	template<class H>
	void
	process(H&& head) {
		impl().process_before(head);
		impl().process_impl(std::forward<H>(head));
		impl().process_after(head);
	}

	/**
		Peel off and process values.
	*/
	template<
		class H,
		class... R
	>
	void
	process(
		H&& head,
		R&&... rest
	) {
		impl().process(std::forward<H>(head));
		impl().process(std::forward<R>(rest)...);
	}
/// @}

public:
/** @name Operations */ /// @{
	/**
		Serialization operator.

		@remarks Immutable objects will be <code>const_cast</code>-ed
		to be mutable for member- or free-function @c serialize().
		For type safety, use const_safe() within serialization
		functions.

		@param args Objects to serialize.
	*/
	template<class... P>
	void
	operator()(P&&... args) {
		impl().process(std::forward<P>(args)...);
	}
/// @}
};

/** @} */ // end of doc-group serializer

} // namespace Cacophony
