#include "tracker/assert.hpp"

namespace location_tracker::detail {
[[noreturn]] void
fail(const char* expr, std::source_location loc,
     std::vector<std::pair<std::string, std::string>> const& values) {
  std::println(std::cerr, "assertion failed: \"{}\"", expr);
  for (auto const& [name, expr] : values) {
    std::println("  {} = {}", name, expr);
  }
  std::println(std::cerr, "where: line {} in {}", loc.line(),
               loc.function_name());
  for (auto floc : get_locations() | std::views::reverse) {
    std::println(std::cerr, " from: line {} in {}", floc.line(),
                 floc.function_name());
  }
  throw std::logic_error("location_tracker assertion failed");
}
} // namespace location_tracker::detail
