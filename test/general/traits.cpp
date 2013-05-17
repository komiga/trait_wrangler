
#include <trait_wrangler/traits.hpp>
#include <trait_wrangler/test.hpp>

namespace tw=trait_wrangler;


struct only_copyable final {
	only_copyable()=delete;
	~only_copyable()=delete;

	only_copyable(only_copyable const&)=default;
	only_copyable& operator=(only_copyable const&)=default;

	only_copyable(only_copyable&&)=delete;
	only_copyable& operator=(only_copyable&&)=delete;
};

// normal
template struct tw::require<
	tw::is_copyable<only_copyable>,
	tw::op_not<tw::is_moveable<only_copyable>>
>;
template struct tw::disallow<
	tw::op_not<tw::is_copyable<only_copyable>>,
	tw::is_moveable<only_copyable>
>;

// template
template struct tw::require_t<
	only_copyable,
	tw::is_copyable,
	tw::op_not_t<tw::is_moveable>::type
>;
template struct tw::disallow_t<
	only_copyable,
	tw::op_not_t<tw::is_copyable>::type,
	tw::is_moveable
>;

// normal - logical operators
template struct tw::require<tw::op_and<
	tw::is_copyable<only_copyable>,
	tw::op_not<tw::is_moveable<only_copyable>>
>>;
template struct tw::disallow<tw::op_or<
	tw::op_not<tw::is_copyable<only_copyable>>,
	tw::is_moveable<only_copyable>
>>;

// template - logical operators
template struct tw::require_t<
	only_copyable,
	tw::op_and_t<
		tw::is_copyable,
		tw::op_not_t<tw::is_moveable>::type
	>::type
>;
template struct tw::disallow_t<
	only_copyable,
	tw::op_or_t<
		tw::op_not_t<tw::is_copyable>::type,
		tw::is_moveable
	>::type
>;


struct only_moveable final {
	only_moveable()=delete;
	~only_moveable()=delete;

	only_moveable(only_moveable const&)=delete;
	only_moveable& operator=(only_moveable const&)=delete;

	only_moveable(only_moveable&&)=default;
	only_moveable& operator=(only_moveable&&)=default;
};

// normal
template struct tw::require<
	tw::op_not<tw::is_copyable<only_moveable>>,
	tw::is_moveable<only_moveable>
>;
template struct tw::disallow<
	tw::is_copyable<only_moveable>,
	tw::op_not<tw::is_moveable<only_moveable>>
>;

// template
template struct tw::require_t<
	only_moveable,
	tw::op_not_t<tw::is_copyable>::type,
	tw::is_moveable
>;
template struct tw::disallow_t<
	only_moveable,
	tw::is_copyable,
	tw::op_not_t<tw::is_moveable>::type
>;

// normal - logical operators
template struct tw::require<tw::op_and<
	tw::op_not<tw::is_copyable<only_moveable>>,
	tw::is_moveable<only_moveable>
>>;
template struct tw::disallow<tw::op_or<
	tw::is_copyable<only_moveable>,
	tw::op_not<tw::is_moveable<only_moveable>>
>>;

// template - logical operators
template struct tw::require_t<
	only_moveable,
	tw::op_and_t<
		tw::op_not_t<tw::is_copyable>::type,
		tw::is_moveable
	>::type
>;
template struct tw::disallow_t<
	only_moveable,
	tw::op_or_t<
		tw::is_copyable,
		tw::op_not_t<tw::is_moveable>::type
	>::type
>;

struct Base {};
struct Derived final : public Base {};
using DerivedAlias=Derived;

template struct tw::require_t<
	Derived,
	tw::capture<std::is_same, DerivedAlias>::type,
	tw::capture_post<std::is_base_of, Base>::type
>;

int main() {
	return 0;
}
