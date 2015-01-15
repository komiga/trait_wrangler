/**
@copyright MIT license; see @ref index or the accompanying LICENSE file.

@file
@brief Tester internals.
*/

#pragma once

#include "../config.hpp"

namespace trait_wrangler {
namespace detail {

/** @cond INTERNAL */

template<bool, class Trait>
struct trait_assert;

template<class Trait>
struct trait_assert<true, Trait> {
	static_assert(
		true == Trait::value,
		"required trait is not satisfied"
	);
};

template<class Trait>
struct trait_assert<false, Trait> {
	static_assert(
		false == Trait::value,
		"disallowed trait is present"
	);
};

// trait pack

template<bool K, class... TraitP>
struct test;

template<bool K, class Trait>
struct test<K, Trait>
	: trait_assert<K, Trait>
{};

template<
	bool K,
	class Trait,
	class... TraitP
>
struct test<K, Trait, TraitP...>
	: trait_assert<K, Trait>
	, test<K, TraitP...>
{};

// trait template pack

template<
	bool K,
	class T,
	template<class> class... TplP
>
struct test_t;

template<
	bool K,
	class T,
	template<class> class TraitTpl
>
struct test_t<K, T, TraitTpl>
	: trait_assert<K, TraitTpl<T>>
{};

template<
	bool K,
	class T,
	template<class> class TraitTpl,
	template<class> class... TplP
>
struct test_t<K, T, TraitTpl, TplP...>
	: trait_assert<K, TraitTpl<T>>
	, test_t<K, T, TplP...>
{};

/** @endcond */

} // namespace detail
} // namespace trait_wrangler
