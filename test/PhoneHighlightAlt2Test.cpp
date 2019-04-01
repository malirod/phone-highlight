// Copyright [2019] <Malinovsky Rodion> (rodionmalino@gmail.com)
#include "PhoneHighlightAlt2.h"

#include "PhoneHighlightUtil.h"

#include <catch2/catch.hpp>

TEST_CASE("Positive cases (Alt2)", "[highlight]")
{
    REQUIRE(rms::HighlightRangesToString(rms::GetPhoneHighlightAlt2(U"(124) 59 34", U"35")).empty());
    REQUIRE(rms::HighlightRangesToString(rms::GetPhoneHighlightAlt2(U"(123) 59 35", U"35")) == "3-3;6-6;9-10");
    REQUIRE(rms::HighlightRangesToString(rms::GetPhoneHighlightAlt2(U"+49 (0) 56 56 5618", U"565618")) == "11-12;14-17");
    REQUIRE(rms::HighlightRangesToString(rms::GetPhoneHighlightAlt2(U"1111111111", U"1")) == "0-0;1-1;2-2;3-3;4-4;5-5;6-6;7-7;8-8;9-9");
    REQUIRE(rms::HighlightRangesToString(rms::GetPhoneHighlightAlt2(U"111 11111 11", U"1")) == "0-0;1-1;2-2;4-4;5-5;6-6;7-7;8-8;10-10;11-11");
    REQUIRE(rms::HighlightRangesToString(rms::GetPhoneHighlightAlt2(U"8991891", U"891")) == "4-6");
    REQUIRE(rms::HighlightRangesToString(rms::GetPhoneHighlightAlt2(U"09340932", U"0932")) == "4-7");
    REQUIRE(rms::HighlightRangesToString(rms::GetPhoneHighlightAlt2(U"0934093257", U"0932")) == "4-7");
    REQUIRE(rms::HighlightRangesToString(rms::GetPhoneHighlightAlt2(U"+38 (0) 97 3545 123", U"+380973545123")) == "0-2;5-5;8-9;11-14;16-18");
    REQUIRE(rms::HighlightRangesToString(rms::GetPhoneHighlightAlt2(U"+38\u00A0(0)\u00A097\u00A03545\u00A0123", U"+380973545123")) == "0-2;5-5;8-9;11-14;16-18");
}

TEST_CASE("Invalid input (Alt2)", "[highlight]")
{
    REQUIRE(rms::HighlightRangesToString(rms::GetPhoneHighlightAlt2(U"", U"35")).empty());
    REQUIRE(rms::HighlightRangesToString(rms::GetPhoneHighlightAlt2(U"(123) 59 35", U"")).empty());
}
