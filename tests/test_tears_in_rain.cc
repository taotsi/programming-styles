#include <catch2/catch.hpp>
#include "monolithic.h"

TEST_CASE("small text", "[TearsInRain]")
{
  std::vector<std::pair<std::string, int>> expected{
    {"in", 2}
  };
  SECTION("monolithic")
  {
    auto monolithic_result = monolithic::word_frequency(
      "../tests/tears_in_rain.txt", "../tests/tears_in_rain_stop_words.txt");
  }
}

