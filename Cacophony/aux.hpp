/**
@file aux.hpp
@brief Auxiliary stdlib specializations.

@author Timothy Howard
@copyright 2014 Timothy Howard under the MIT license;
see @ref index or the accompanying LICENSE file for full text.
*/

#ifndef CACOPHONY_AUX_HPP_
#define CACOPHONY_AUX_HPP_

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

#endif // CACOPHONY_AUX_HPP_
