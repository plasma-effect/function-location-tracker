#pragma once

#include "tracker/location.hpp"

#ifdef LOCAL_DEBUG
namespace location_tracker::detail {
[[noreturn]] void
fail(const char* expr, std::source_location loc,
     std::vector<std::pair<std::string, std::string>> const& values);
} // namespace location_tracker::detail
#define TRACKER_ASSERT(...)                                                    \
  (static_cast<bool>(__VA_ARGS__)                                              \
       ? void(0)                                                               \
       : location_tracker::detail::fail(#__VA_ARGS__,                          \
                                        std::source_location::current(), {}))
#define TRACKER_EXPECT_1(value0, ...)                                          \
  (static_cast<bool>(__VA_ARGS__)                                              \
       ? void(0)                                                               \
       : location_tracker::detail::fail(                                       \
             #__VA_ARGS__, std::source_location::current(),                    \
             {                                                                 \
                 {#value0, std::format("{}", value0)},                         \
  }))
#define TRACKER_EXPECT_2(value0, value1, ...)                                  \
  (static_cast<bool>(__VA_ARGS__)                                              \
       ? void(0)                                                               \
       : location_tracker::detail::fail(                                       \
             #__VA_ARGS__, std::source_location::current(),                    \
             {                                                                 \
                 {#value0, std::format("{}", value0)},                         \
                 {#value1, std::format("{}", value1)},                         \
  }))
#else
#define TRACKER_ASSERT(...)                                                    \
  assert(__VA_ARGS__);                                                         \
  [[assume((__VA_ARGS__))]]
#define TRACKER_EXPECT_1(value0, ...) TRACKER_ASSERT(__VA_ARGS__)
#define TRACKER_EXPECT_2(value0, value1, ...) TRACKER_ASSERT(__VA_ARGS__)
#endif
