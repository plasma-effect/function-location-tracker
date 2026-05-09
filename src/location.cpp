#include "tracker/location.hpp"

namespace {
thread_local int depth = 0;
thread_local std::source_location locations[MAX_DEPTH];
} // namespace

namespace location_tracker {
std::span<std::source_location> get_locations() {
  return std::span(locations).subspan(0, depth);
}
namespace detail {
void push(std::source_location loc) {
  assert(depth < MAX_DEPTH);
  locations[depth++] = loc;
}
void pop() {
  --depth;
}
} // namespace detail
} // namespace location_tracker
