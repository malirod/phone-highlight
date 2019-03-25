// Copyright [2019] <Malinovsky Rodion> (rodionmalino@gmail.com)
#include "PhoneHighlightUtil.h"

#include <catch2/catch.hpp>

TEST_CASE("Ranges converter", "[highlight]")
{
    REQUIRE(rms::HighlightRangesToString({ { 1u, 1u }, { 5u, 9u } }) == "1-1;5-9");
    REQUIRE(rms::HighlightRangesToString({ { 6u, 6u } }) == "6-6");
}
