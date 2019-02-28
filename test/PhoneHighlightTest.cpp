// Copyright [2019] <Malinovsky Rodion> (rodionmalino@gmail.com)
#include "PhoneHighlight.h"

#include <catch2/catch.hpp>

TEST_CASE("Ranges converter", "[highlight]")
{
    REQUIRE(rms::HighlightRangesToString({ std::make_pair(1u, 1u), std::make_pair(5u, 9u) }) == "1-1;5-9");
    REQUIRE(rms::HighlightRangesToString({ std::make_pair(6u, 6u) }) == "6-6");
}

TEST_CASE("Positive cases", "[highlight]")
{
    REQUIRE(rms::GetPhoneHighlight("(123) 59 35", "35") == "3-3;6-6;9-10");
    REQUIRE(rms::GetPhoneHighlight("+49 (0) 56 56 5618", "565618") == "11-12;14-17");
    REQUIRE(rms::GetPhoneHighlight("1111111111", "1") == "0-0;1-1;2-2;3-3;4-4;5-5;6-6;7-7;8-8;9-9");
    REQUIRE(rms::GetPhoneHighlight("111 11111 11", "1") == "0-0;1-1;2-2;4-4;5-5;6-6;7-7;8-8;10-10;11-11");
    REQUIRE(rms::GetPhoneHighlight("8991891", "891") == "4-6");
    REQUIRE(rms::GetPhoneHighlight("09340932", "0932") == "4-7");
    REQUIRE(rms::GetPhoneHighlight("0934093257", "0932") == "4-7");
    REQUIRE(rms::GetPhoneHighlight("+38 (0) 97 3545 123", "+380973545123") == "0-2;5-5;8-9;11-14;16-18");
    REQUIRE(rms::GetPhoneHighlight("+38\u00A0(0)\u00A097\u00A03545\u00A0123", "+380973545123") == "0-2;5-5;8-9;11-14;16-18");
}

TEST_CASE("Invalid input", "[highlight]")
{
    REQUIRE(rms::GetPhoneHighlight("", "35").empty());
    REQUIRE(rms::GetPhoneHighlight("(123) 59 35", "").empty());
}
