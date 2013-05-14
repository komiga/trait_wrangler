/**
@file test.hpp
@brief Trait testing.

@author Tim Howard
@copyright 2013 Tim Howard under the MIT license;
see @ref index or the accompanying LICENSE file for full text.
*/

#ifndef TRAIT_WRANGLER_TEST_HPP_
#define TRAIT_WRANGLER_TEST_HPP_

#include "./config.hpp"
#include "./detail/test.hpp"
#include "./traits.hpp"

namespace trait_wrangler {

/**
	@addtogroup test
	@{
*/

/**
	Require instantiated traits.

	@tparam ...TraitP Traits.
*/
template<
	class... TraitP
>
struct require
	: ::trait_wrangler::detail::test<true, TraitP...>
{};

/**
	Disallow trait templates instantiated with type @a T.

	@tparam T Type to apply to @a TplP.
	@tparam TplP Trait templates.
*/
template<
	typename T,
	template<typename> class... TplP
>
struct require_t
	: ::trait_wrangler::detail::test_t<true, T, TplP...>
{};

/**
	Disallow instantiated traits.

	@tparam ...TraitP Traits.
*/
template<
	class... TraitP
>
struct disallow
	: ::trait_wrangler::detail::test<false, TraitP...>
{};

/**
	Disallow trait templates instantiated with type @a T.

	@tparam T Type to apply to @a TplP.
	@tparam TplP Trait templates.
*/
template<
	typename T,
	template<typename> class... TplP
>
struct disallow_t
	: ::trait_wrangler::detail::test_t<false, T, TplP...>
{};

/*template<
	class... TraitP
>
constexpr bool and_value() {
	return ::trait_wrangler::op_and<TraitP...>::value;
}

template<
	typename T,
	template<typename> class... TplP
>
constexpr bool and_value_t() {
	return ::trait_wrangler::op_and_t<T, TplP...>::value;
}

template<
	class... TraitP
>
constexpr bool or_value() {
	return ::trait_wrangler::op_or<TraitP...>::value;
}*/

/** @} */ // end of doc-group test

} // namespace trait_wrangler

#endif // TRAIT_WRANGLER_TEST_HPP_
