#pragma once
#include <bits/stdc++.h>

namespace location_tracker {
#ifdef LOCAL_DEBUG
std::span<std::source_location> get_locations();
namespace detail {
void push(std::source_location loc);
void pop();
} // namespace detail
struct location {
  bool is_constant;
  constexpr location(std::source_location loc)
      : is_constant(std::is_constant_evaluated()) {
    if (!is_constant) {
      detail::push(loc);
    }
  }
  constexpr ~location() {
    if (!is_constant) {
      detail::pop();
    }
  }
  location(location const&) = delete;
  location(location&&) = delete;
};
#else
struct location {
  constexpr location(std::source_location) {}
  constexpr ~location() = default;
  location(location const&) = delete;
  location(location&&) = delete;
};
#endif
} // namespace location_tracker
#define FROM_LOCATION                                                          \
  [[maybe_unused]] location_tracker::location _from =                          \
      std::source_location::current()
