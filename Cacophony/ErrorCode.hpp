/**
@copyright MIT license; see @ref index or the accompanying LICENSE file.

@file
@brief %Error codes.
*/

#pragma once

#include <Cacophony/config.hpp>

namespace Cacophony {

// Forward declarations
enum class ErrorCode : unsigned;

/**
	@addtogroup error
	@{
*/

// FIXME: Doxygen borks all over itself
// when name-groups are used inside enums.

/**
	%Error codes.

	@sa Error
*/
enum class ErrorCode : unsigned {
/** @name General */ /// @{
	/**
		Unknown/unspecified.
	*/
	unknown = 0u,
/// @}

/** @name Serialization */ /// @{
	/**
		Read or write operation failed during serialization.
	*/
	serialization_io_failed,
/// @}

/** @cond INTERNAL */
	LAST
/** @endcond */
};

/** @} */ // end of doc-group error

} // namespace Cacophony
