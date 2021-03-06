/**
@copyright MIT license; see @ref index or the accompanying LICENSE file.

@file
@brief Trait internals.
*/

#pragma once

#include "../config.hpp"

#include <type_traits>

namespace trait_wrangler {
namespace detail {

/** @cond INTERNAL */

// trait pack, logical AND

template<class... TraitP>
struct op_and;

template<class Trait>
struct op_and<Trait>
	: public std::integral_constant<bool,
		Trait::value
	>
{};

template<class Trait, class... TraitP>
struct op_and<Trait, TraitP...>
	: public std::integral_constant<bool,
		Trait::value && op_and<TraitP...>::value
	>
{};

// trait template pack, logical AND

template<class T, template<class> class... TplP>
struct op_and_t;

template<class T, template<class> class TraitTpl>
struct op_and_t<T, TraitTpl>
	: public std::integral_constant<bool,
		TraitTpl<T>::value
	>
{};

template<
	class T,
	template<class> class TraitTpl,
	template<class> class... TplP
>
struct op_and_t<T, TraitTpl, TplP...>
	: public std::integral_constant<bool,
		TraitTpl<T>::value && op_and_t<T, TplP...>::value
	>
{};


// trait pack, logical OR

template<class... TraitP>
struct op_or;

template<class Trait>
struct op_or<Trait>
	: public std::integral_constant<bool,
		Trait::value
	>
{};

template<class Trait, class... TraitP>
struct op_or<Trait, TraitP...>
	: public std::integral_constant<bool,
		Trait::value || op_or<TraitP...>::value
	>
{};

// trait template pack, logical OR

template<class T, template<class> class... TplP>
struct op_or_t;

template<class T, template<class> class TraitTpl>
struct op_or_t<T, TraitTpl>
	: public std::integral_constant<bool,
		TraitTpl<T>::value
	>
{};

template<
	class T,
	template<class> class TraitTpl,
	template<class> class... TplP
>
struct op_or_t<T, TraitTpl, TplP...>
	: public std::integral_constant<bool,
		TraitTpl<T>::value || op_or_t<T, TplP...>::value
	>
{};

/** @endcond */

} // namespace detail
} // namespace trait_wrangler
