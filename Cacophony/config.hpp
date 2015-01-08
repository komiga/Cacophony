/**
@copyright MIT license; see @ref index or the accompanying LICENSE file.

@file
@brief Configuration.
*/

#pragma once

#include <cstddef>
#include <cstdint>

namespace Cacophony {

/**
	@addtogroup config
	@{
*/

#ifdef DOXYGEN_CONSISTS_SOLELY_OF_UNICORNS_AND_CONFETTI
	/**
		Allocator for auxiliary specializations.

		@note Defaults to @c std::allocator.
	*/
	#define CACOPHONY_AUX_ALLOCATOR
#else // -
	#ifndef CACOPHONY_AUX_ALLOCATOR
		#define CACOPHONY_AUX_ALLOCATOR std::allocator
	#endif
#endif

/** @} */ // end of doc-group config

} // namespace Cacophony
