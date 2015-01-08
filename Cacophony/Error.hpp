/**
@file
@brief %Error class.

@author Timothy Howard
@copyright 2014 Timothy Howard under the MIT license;
see @ref index or the accompanying LICENSE file for full text.
*/

#pragma once

#include <Cacophony/config.hpp>
#include <Cacophony/ErrorCode.hpp>
#include <Cacophony/String.hpp>

#include <duct/utility.hpp>
#include <duct/GR/Error.hpp>

#include <type_traits>
#include <utility>

namespace Cacophony {

// Forward declarations

/**
	@addtogroup error
	@{
*/

/**
	%Error.

	See @c duct::GR::Error for documentation.
*/
using Error
= duct::GR::Error<
	Cacophony::ErrorCode,
	Cacophony::String
>;

/** @cond INTERNAL */
namespace {
static char const
s_error_invalid[]{CACOPHONY_STR_LIT("INVALID")},
* const s_error_names[]{
	CACOPHONY_STR_LIT("unknown"),

// serialization
	CACOPHONY_STR_LIT("serialization_io_failed"),
};
} // anonymous namespace

static_assert(
	duct::enum_cast(ErrorCode::LAST)
	== std::extent<decltype(s_error_names)>::value,
	"ErrorCode name list is incomplete"
);
/** @endcond */ // INTERNAL

/**
	Get the name of an error.

	@returns C-string containing the name of @a error_code or
	"INVALID" if somehow @a error_code is not actually an ErrorCode.
	@param error_code ErrorCode.
*/
inline char const*
get_error_name(
	ErrorCode const error_code
) noexcept {
	std::size_t const index = static_cast<std::size_t>(error_code);
	if (index < std::extent<decltype(s_error_names)>::value) {
		return s_error_names[index];
	} else {
		return s_error_invalid;
	}
}

/** @} */ // end of doc-group error

} // namespace Cacophony
