/**
@copyright MIT license; see @ref index or the accompanying LICENSE file.

@file
@brief Auxiliary stdlib specializations.
*/

#pragma once

#include <Cacophony/config.hpp>

#include <string>

namespace Cacophony {
namespace aux {

/**
	@addtogroup etc
	@{
*/
/**
	@addtogroup aux
	@{
*/

/**
	@c std::basic_string<CharT, Traits>.
*/
template<
	typename CharT,
	class Traits = std::char_traits<CharT>
>
using basic_string
= std::basic_string<
	CharT, Traits,
	CACOPHONY_AUX_ALLOCATOR<CharT>
>;

/** @} */ // end of doc-group aux
/** @} */ // end of doc-group etc

} // namespace aux
} // namespace Cacophony
