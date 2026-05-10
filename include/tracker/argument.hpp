#pragma once
#include "tracker/location.hpp"

namespace location_tracker {
template <typename T> struct argument {
  T value;
  location loc_;
  template <typename U>
  constexpr argument(U&& u,
                     std::source_location loc = std::source_location::current())
      : value(std::forward<U>(u)), loc_(loc) {}
};
} // namespace location_tracker
