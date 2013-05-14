/**
@file traits.hpp
@brief Non-standard traits and trait operators.

@author Tim Howard
@copyright 2013 Tim Howard under the MIT license;
see @ref index or the accompanying LICENSE file for full text.
*/

#ifndef TRAIT_WRANGLER_TRAITS_HPP_
#define TRAIT_WRANGLER_TRAITS_HPP_

#include "./config.hpp"
#include "./detail/traits.hpp"

#include <type_traits>

namespace trait_wrangler {

/**
	@addtogroup traits
	@{
*/

/**
	@name Trait operators
	@{
*/

/**
	Logical AND of traits.

	@param ...TraitP Traits.
*/
template<class... TraitP>
struct op_and
	: public ::trait_wrangler::detail::op_and<TraitP...>
{};

/**

*/
template<template<typename> class... TplP>
struct op_and_t final {
	/**
		Trait template adapter.

		@tparam T Type to apply to @a TplP.
	*/
	template<typename T>
	struct type
		: public ::trait_wrangler::detail::op_and_t<T, TplP...>
	{};
};

/**
	Logical OR of traits.

	@param ...TraitP Traits.
*/
template<class... TraitP>
struct op_or
	: public ::trait_wrangler::detail::op_or<TraitP...>
{};

/**

*/
template<template<typename> class... TplP>
struct op_or_t final {
	/**
		Trait template adapter.

		@tparam T Type to apply to @a TplP.
	*/
	template<typename T>
	struct type
		: public ::trait_wrangler::detail::op_or_t<T, TplP...>
	{};
};

/**
	Logical NOT of a trait.

	@tparam Trait Trait to negate.
*/
template<class Trait>
struct op_not
	: public std::integral_constant<bool,
		!Trait::value
	>
{};

/**
	Logical NOT of a trait template.

	@tparam TraitTpl Trait template to negate.
*/
template<template<typename> class TraitTpl>
struct op_not_t final {
	/**
		Trait template adapter.

		@tparam T Type to apply to @a TraitTpl.
	*/
	template<typename T>
	struct type
		: public std::integral_constant<bool,
			!TraitTpl<T>::value
		>
	{};
};

/** @} */ // end of name-group Trait operators

/**
	@name Traits
	@{
*/

/**
	Whether a type is either copy constructible or copy assignable.

	@tparam T Type to test.
*/
template<typename T>
struct is_copyable
	: public std::integral_constant<bool,
		std::is_copy_constructible<T>::value ||
		std::is_copy_assignable   <T>::value
	>
{};

/**
	Whether a type is either move constructible or move assignable.

	@tparam T Type to test.
*/
template<typename T>
struct is_moveable
	: public std::integral_constant<bool,
		std::is_move_constructible<T>::value ||
		std::is_move_assignable   <T>::value
	>
{};

/** @} */ // end of name-group Traits

/** @} */ // end of doc-group traits

} // namespace trait_wrangler

#endif // TRAIT_WRANGLER_TRAITS_HPP_
