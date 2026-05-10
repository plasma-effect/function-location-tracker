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
  constexpr location(std::source_location loc) {
    if !consteval {
      detail::push(loc);
    }
  }
  constexpr ~location() {
    if !consteval {
      detail::pop();
    }
  }
  location(location const&) = delete;
  location(location&&) = delete;
};
#else
struct location {
  constexpr location(std::source_location loc) {}
  constexpr ~location() = default;
  location(location const&) = delete;
  location(location&&) = delete;
};
#endif
#define FROM_LOCATION                                                          \
  [[maybe_unused]] location_tracker::location _from =                          \
      std::source_location::current()
} // namespace location_tracker
