
#include <trait_wrangler/traits.hpp>
#include <trait_wrangler/test.hpp>

namespace tw = trait_wrangler;


struct OnlyCopyable final {
	OnlyCopyable() = default;
	~OnlyCopyable() = default;

	OnlyCopyable(OnlyCopyable const&) = default;
	OnlyCopyable& operator=(OnlyCopyable const&) = default;

	OnlyCopyable(OnlyCopyable&&) = delete;
	OnlyCopyable& operator=(OnlyCopyable&&) = delete;
};

// normal
template struct tw::require<
	tw::is_fully_copyable<OnlyCopyable>,
	tw::op_not<tw::is_moveable<OnlyCopyable>>
>;
template struct tw::disallow<
	tw::op_not<tw::is_copyable<OnlyCopyable>>,
	tw::is_moveable<OnlyCopyable>
>;

// template
template struct tw::require_t<
	OnlyCopyable,
	tw::is_fully_copyable,
	tw::op_not_t<tw::is_moveable>::type
>;
template struct tw::disallow_t<
	OnlyCopyable,
	tw::op_not_t<tw::is_copyable>::type,
	tw::is_moveable
>;

// normal - logical operators
template struct tw::require<tw::op_and<
	tw::is_fully_copyable<OnlyCopyable>,
	tw::op_not<tw::is_moveable<OnlyCopyable>>
>>;
template struct tw::disallow<tw::op_or<
	tw::op_not<tw::is_copyable<OnlyCopyable>>,
	tw::is_moveable<OnlyCopyable>
>>;

// template - logical operators
template struct tw::require_t<
	OnlyCopyable,
	tw::op_and_t<
		tw::is_fully_copyable,
		tw::op_not_t<tw::is_moveable>::type
	>::type
>;
template struct tw::disallow_t<
	OnlyCopyable,
	tw::op_or_t<
		tw::op_not_t<tw::is_copyable>::type,
		tw::is_moveable
	>::type
>;


struct OnlyMoveable final {
	OnlyMoveable() = default;
	~OnlyMoveable() = default;

	OnlyMoveable(OnlyMoveable const&) = delete;
	OnlyMoveable& operator=(OnlyMoveable const&) = delete;

	OnlyMoveable(OnlyMoveable&&) = default;
	OnlyMoveable& operator=(OnlyMoveable&&) = default;
};

// normal
template struct tw::require<
	tw::op_not<tw::is_copyable<OnlyMoveable>>,
	tw::is_fully_moveable<OnlyMoveable>
>;
template struct tw::disallow<
	tw::is_copyable<OnlyMoveable>,
	tw::op_not<tw::is_moveable<OnlyMoveable>>
>;

// template
template struct tw::require_t<
	OnlyMoveable,
	tw::op_not_t<tw::is_copyable>::type,
	tw::is_fully_moveable
>;
template struct tw::disallow_t<
	OnlyMoveable,
	tw::is_copyable,
	tw::op_not_t<tw::is_moveable>::type
>;

// normal - logical operators
template struct tw::require<tw::op_and<
	tw::op_not<tw::is_copyable<OnlyMoveable>>,
	tw::is_fully_moveable<OnlyMoveable>
>>;
template struct tw::disallow<tw::op_or<
	tw::is_copyable<OnlyMoveable>,
	tw::op_not<tw::is_moveable<OnlyMoveable>>
>>;

// template - logical operators
template struct tw::require_t<
	OnlyMoveable,
	tw::op_and_t<
		tw::op_not_t<tw::is_copyable>::type,
		tw::is_fully_moveable
	>::type
>;
template struct tw::disallow_t<
	OnlyMoveable,
	tw::op_or_t<
		tw::is_copyable,
		tw::op_not_t<tw::is_moveable>::type
	>::type
>;

struct Base {};
struct Derived final : public Base {};
using DerivedAlias = Derived;

template struct tw::require_t<
	Derived,
	tw::capture<std::is_same, DerivedAlias>::type,
	tw::capture_post<std::is_base_of, Base>::type
>;

signed
main() {
	return 0;
}
