
#include <trait_wrangler/traits.hpp>
#include <trait_wrangler/test.hpp>

#include <type_traits>

namespace tw = trait_wrangler;

template struct tw::require_t<
	int,
	tw::capture<std::is_same, int>::type,
	std::is_arithmetic,
	std::is_fundamental,
	std::is_integral,
	tw::op_not_t<std::is_floating_point>::type,
	std::is_scalar,
	std::is_trivial,
	std::is_literal_type,
	std::is_pod,
	tw::is_fully_copyable,
	tw::is_fully_moveable
>;

signed
main() {
	return 0;
}
