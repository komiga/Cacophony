/**
@file traits.hpp
@brief Traits.

@author Timothy Howard
@copyright 2014 Timothy Howard under the MIT license;
see @ref index or the accompanying LICENSE file for full text.
*/

#ifndef CACOPHONY_TRAITS_HPP_
#define CACOPHONY_TRAITS_HPP_

#include <Cacophony/config.hpp>
#include <Cacophony/types.hpp>

#include <duct/traits.hpp>

#include <type_traits>
#include <utility>

/** @cond INTERNAL */

namespace Cacophony {
namespace detail {
struct unimplemented {};
}
}

// captures
template<class... P>
Cacophony::detail::unimplemented
serialize(P&&...);

template<class... P>
Cacophony::detail::unimplemented
read(P&&...);

template<class... P>
Cacophony::detail::unimplemented
write(P&&...);

/** @endcond */ // INTERNAL

namespace Cacophony {

// Forward declarations
class accessor;
template<class>
class OutputSerializer; // external
template<class>
class InputSerializer; // external

/**
	@addtogroup traits
	@{
*/

/**
	Remove reference from type.
*/
template<class T>
using refless_type = typename std::remove_reference<T>::type;

/**
	Remove reference and const qualifier from type.
*/
template<class T>
using bare_type = typename std::remove_const<refless_type<T>>::type;

/**
	Check if a type is a size type.

	@note The default definition only accepts unsigned integrals.
	Specialize this for user-defined types.
*/
template<class T>
struct is_size_type
	: public std::integral_constant<
		bool,
		std::is_integral<bare_type<T>>::value &&
		std::is_unsigned<bare_type<T>>::value
	>
{};

/**
	Check if class is an input serializer.
*/
template<class Ser>
struct is_input_serializer
	: public std::integral_constant<
		bool,
		std::is_base_of<InputSerializer<bare_type<Ser>>, bare_type<Ser>>::value
	>
{};

/**
	Check if class is an output serializer.
*/
template<class Ser>
struct is_output_serializer
	: public std::integral_constant<
		bool,
		std::is_base_of<OutputSerializer<bare_type<Ser>>, bare_type<Ser>>::value
	>
{};

/**
	Check if class is a serializer.
*/
template<class Ser>
struct is_serializer
	: public std::integral_constant<
		bool,
		is_input_serializer <Ser>::value ||
		is_output_serializer<Ser>::value
	>
{};

/** @cond INTERNAL */

template<class Ser, class T>
struct has_non_member_serialize_impl {
	using ser_type = bare_type<Ser>;
	using value_type = bare_type<T>;
	using reversed_type = std::is_same<
		detail::unimplemented,
		decltype(serialize(
			std::declval<ser_type&>(),
			std::declval<value_type&>()
		))
	>;
	using type = std::integral_constant<bool, !reversed_type::value>;
	static constexpr bool const value = type::value;
};

template<class Ser, class T>
struct has_non_member_read_impl {
	using ser_type = bare_type<Ser>;
	using value_type = T;
	using reversed_type = std::is_same<
		detail::unimplemented,
		decltype(read(
			std::declval<ser_type&>(),
			std::declval<value_type&>()
		))
	>;
	using type = std::integral_constant<bool, !reversed_type::value>;
	static constexpr bool const value = type::value;
};

template<class Ser, class T>
struct has_non_member_write_impl {
	using ser_type = bare_type<Ser>;
	using value_type = T;
	using reversed_type = std::is_same<
		detail::unimplemented,
		decltype(write(
			std::declval<ser_type&>(),
			std::declval<value_type const&>()
		))
	>;
	using type = std::integral_constant<bool, !reversed_type::value>;
	static constexpr bool const value = type::value;
};
/** @endcond */ // INTERNAL

/**
	Class access injector.

	Friend this class within a class if its member serialization
	functions are private or protected.
*/
class accessor
	: public duct::traits::restrict_all
{
public:
/** @cond INTERNAL */
	template<class Ser, class T>
	struct has_member_serialize_impl {
		using ser_type = bare_type<Ser>;
		using value_type = bare_type<T>;

		template<class U>
		static auto match(void(U::*)(ser_type&)) -> U;

		template<class U>
		using is_t = typename std::is_same<value_type, U>::type;

		template<class U>
		static auto test(int) -> is_t<decltype(match(
			&U::template serialize<ser_type>
		))>;
		template<class U>
		static auto test(int) -> is_t<decltype(match(&U::serialize))>;
		template<class U>
		static auto test(...) -> std::false_type;

		using type = decltype(test<value_type>(0));
		static constexpr bool const value = type::value;
	};

	template<class Ser, class T>
	struct has_member_read_impl {
		using ser_type = bare_type<Ser>;
		using value_type = bare_type<T>;

		template<class U>
		static auto match(void(U::*)(ser_type&)) -> U;

		template<class U>
		using is_t = typename std::is_same<value_type, U>::type;

		template<class U>
		static auto test(int) -> is_t<decltype(match(
			&U::template read<ser_type>
		))>;
		template<class U>
		static auto test(int) -> is_t<decltype(match(&U::read))>;
		template<class U>
		static auto test(...) -> std::false_type;

		using type = decltype(test<value_type>(0));
		static constexpr bool const value = type::value;
	};

	template<class Ser, class T>
	struct has_member_write_impl {
		using ser_type = bare_type<Ser>;
		using value_type = bare_type<T>;

		template<class U>
		static auto match(void(U::*)(ser_type&) const) -> U;

		template<class U>
		using is_t = typename std::is_same<value_type, U>::type;

		template<class U>
		static auto test(int) -> is_t<decltype(match(
			&U::template write<ser_type>
		))>;
		template<class U>
		static auto test(int) -> is_t<decltype(match(&U::write))>;
		template<class U>
		static auto test(...) -> std::false_type;

		using type = decltype(test<value_type>(0));
		static constexpr bool const value = type::value;
	};
/** @endcond */ // INTERNAL

	/**
		Read a value from an input serializer.

		@note This function is enabled by the availability of the
		@c serialize() and @c read() serialization functions. A call
		will be ambiguous if both are available.
		@{
	*/
	template<class Ser, class T>
	static inline enable_ser<has_member_serialize_impl<Ser, bare_type<T>>::value>
	in(Ser& ser, T&& value) {
		value.serialize(ser);
	}

	template<class Ser, class T>
	static inline enable_ser<has_non_member_serialize_impl<Ser, bare_type<T>>::value>
	in(Ser& ser, T&& value) {
		serialize(ser, value);
	}

	template<class Ser, class T>
	static inline enable_ser<has_member_read_impl<Ser, bare_type<T>>::value>
	in(Ser& ser, T&& value) {
		value.read(ser);
	}

	template<class Ser, class T>
	static inline enable_ser<has_non_member_read_impl<Ser, bare_type<T>>::value>
	in(Ser& ser, T&& value) {
		read(ser, value);
	}
	/** @} */

	/**
		Write a value to an output serializer.

		@note This function is enabled by the availability of the
		@c serialize() and @c write() serialization functions. A call
		will be ambiguous if both are available.
		@{
	*/
	template<class Ser, class T>
	static inline enable_ser<has_member_serialize_impl<Ser, T>::value>
	out(Ser& ser, T const& value) {
		const_cast<bare_type<T>&>(value).serialize(ser);
	}

	template<class Ser, class T>
	static inline enable_ser<has_non_member_serialize_impl<Ser, T>::value>
	out(Ser& ser, T const& value) {
		serialize(ser, const_cast<bare_type<T>&>(value));
	}

	template<class Ser, class T>
	static inline enable_ser<has_member_write_impl<Ser, T>::value>
	out(Ser& ser, T const& value) {
		value.write(ser);
	}

	template<class Ser, class T>
	static inline enable_ser<has_non_member_write_impl<Ser, T>::value>
	out(Ser& ser, T const& value) {
		write(ser, value);
	}
	/** @} */
};

/**
	Whether there is a serialize() member function for a
	serializer-value pair.
*/
template<class Ser, class T>
struct has_member_serialize
	: public accessor::has_member_serialize_impl<Ser, T>::type
{};

/**
	Whether there is a serialize() non-member function for a
	serializer-value pair.
*/
template<class Ser, class T>
struct has_non_member_serialize
	: public has_non_member_serialize_impl<Ser, T>::type
{};

/**
	Whether there is a read() member function for a serializer-value
	pair.
*/
template<class Ser, class T>
struct has_member_read
	: public accessor::has_member_read_impl<Ser, T>::type
{};

/**
	Whether there is a read() non-member function for a
	serializer-value pair.
*/
template<class Ser, class T>
struct has_non_member_read
	: public has_non_member_read_impl<Ser, T>::type
{};

/**
	Whether there is a write() member function for a serializer-value
	pair.
*/
template<class Ser, class T>
struct has_member_write
	: public accessor::has_member_write_impl<Ser, T>::type
{};

/**
	Whether there is a write() non-member function for a
	serializer-value pair.
*/
template<class Ser, class T>
struct has_non_member_write
	: public has_non_member_write_impl<Ser, T>::type
{};

// serializable by type

/**
	Whether a type is serializable with a specific input serializer.
*/
template<class Ser, class T>
struct is_input_serializable
	: public std::integral_constant<
		bool,
		is_input_serializer<Ser>::value && (
		// serialize()
		has_member_serialize		<Ser, T>::value ||
		has_non_member_serialize	<Ser, T>::value ||
		// write()
		has_member_read				<Ser, T>::value ||
		has_non_member_read			<Ser, T>::value
	)>
{
	//static_assert();
};

/**
	Whether a type is serializable with a specific output serializer.
*/
template<class Ser, class T>
struct is_output_serializable
	: public std::integral_constant<
		bool,
		is_output_serializer<Ser>::value && (
		// serialize()
		has_member_serialize		<Ser, T>::value ||
		has_non_member_serialize	<Ser, T>::value ||
		// read()
		has_member_write			<Ser, T>::value ||
		has_non_member_write		<Ser, T>::value
	)>
{
	//static_assert();
};

template<class T>
struct is_binary_serializable
	: public std::integral_constant<
		bool,
		!std::is_same<bool, bare_type<T>>::value &&
		std::is_arithmetic<bare_type<T>>::value
	>
{};

/**
	@c serialize() function return tag.

	@note This always constrains by is_serializer.

	@tparam Ser %Serializer type.
	@tparam constraints Additional constraints.
*/
template<class Ser, bool const constraints = true>
using tag_serialize = enable_ser<
	is_serializer<Ser>::value &&
	constraints
>;

/**
	@c read() function return tag.

	@note This always constrains by is_input_serializer.

	@tparam Ser %Serializer type.
	@tparam constraints Additional constraints.
*/
template<class Ser, bool const constraints = true>
using tag_read = enable_ser<
	is_input_serializer<Ser>::value &&
	constraints
>;

/**
	@c write() function return tag.

	@note This always constrains by is_output_serializer.

	@tparam Ser %Serializer type.
	@tparam constraints Additional constraints.
*/
template<class Ser, bool const constraints = true>
using tag_write = enable_ser<
	is_output_serializer<Ser>::value &&
	constraints
>;

/** @} */ // end of doc-group traits

} // namespace Cacophony

#endif // CACOPHONY_TRAITS_HPP_
