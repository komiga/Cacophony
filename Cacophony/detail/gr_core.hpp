/**
@copyright MIT license; see @ref index or the accompanying LICENSE file.

@file
@brief GR core configuration.
*/

#ifndef CACOPHONY_DETAIL_GR_CORE_HPP_
#define CACOPHONY_DETAIL_GR_CORE_HPP_

#include <Cacophony/config.hpp>
#include <Cacophony/ErrorCode.hpp>
#include <Cacophony/String.hpp>
#include <Cacophony/Error.hpp>

#ifndef CACOPHONY_DETAIL_GR_CORE_NS_GUARD_
#define CACOPHONY_DETAIL_GR_CORE_NS_GUARD_

namespace Cacophony {
namespace detail {
namespace GR {
	using Error = ::Cacophony::Error;
}}}

#endif // CACOPHONY_DETAIL_GR_CORE_NS_GUARD_

#define DUCT_GR_ROOT_NAMESPACE \
	::Cacophony::detail::GR

#define DUCT_GR_STR_LIT(s_) \
	CACOPHONY_STR_LIT(s_)

#define DUCT_GR_MSG_IMPL_(s_, m_) \
	"{" s_ "} " m_

#define DUCT_GR_SCOPE_PREFIX \
	Cacophony::

#define DUCT_GR_SCOPE_CLASS \
	CACOPHONY_SCOPE_CLASS

#define DUCT_GR_SCOPE_FUNC \
	CACOPHONY_SCOPE_FUNC

#define CACOPHONY_SCOPE_FQN_STR \
	DUCT_GR_SCOPE_FQN_STR

#define CACOPHONY_SCOPE_FQN_STR_LIT \
	DUCT_GR_SCOPE_FQN_STR_LIT

#include <duct/GR/common.hpp>
#include <duct/GR/throw.hpp>

#define CACOPHONY_THROW(ec_, m_) \
	DUCT_GR_THROW(ec_, m_)

#define CACOPHONY_THROW_CLASS(ec_, m_) \
	DUCT_GR_THROW_CLASS(ec_, m_)

#define CACOPHONY_THROW_FUNC(ec_, m_) \
	DUCT_GR_THROW_FUNC(ec_, m_)

#define CACOPHONY_THROW_FQN(ec_, m_) \
	DUCT_GR_THROW_FQN(ec_, m_)

#endif // CACOPHONY_DETAIL_GR_CORE_HPP_
