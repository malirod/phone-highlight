// Copyright [2019] <Malinovsky Rodion> (rodionmalino@gmail.com)
#include "UtfUtils.h"

#include <catch2/catch.hpp>

/**
 * Usefull links:
 * UTF-8 string length & byte counter - https://mothereff.in/byte-counter
 * utf8 to utf32 converter - https://onlineutf8tools.com/convert-utf8-to-utf32
 * hexadecimal to utf8 converter - https://onlineutf8tools.com/convert-hexadecimal-to-utf8
 */

TEST_CASE("UTF8ToUtf32", "[UtfToUtf]")
{
    SECTION("ASCII")
    {
        std::string utf8Str = "Hello";
        REQUIRE(utf8Str.length() == 5u);
        auto utf32Str = rms::UTF8ToUTF32(utf8Str);
        REQUIRE(utf32Str.length() == utf8Str.length());
        REQUIRE(utf32Str == U"Hello");
    }

    SECTION("Multibyte - single char")
    {
        std::string const utf8Str = u8"ℵ";
        REQUIRE(utf8Str.length() == 3u);
        auto const utf32Str = rms::UTF8ToUTF32(utf8Str);
        auto const utf32StrDesired = U"ℵ";
        REQUIRE(utf32Str.length() == 1u);
        REQUIRE(utf32Str == utf32StrDesired);
    }

    SECTION("Multibyte - three chars")
    {
        std::string const utf8Str = u8"zß水";
        REQUIRE(utf8Str.length() == 6u);
        auto const utf32Str = rms::UTF8ToUTF32(utf8Str);
        auto const utf32StrDesired = U"zß水";
        REQUIRE(utf32Str.length() == 3u);
        REQUIRE(utf32Str == utf32StrDesired);
    }

    SECTION("Multibyte - non-breaking space")
    {
        std::string const utf8Str = u8" ";
        REQUIRE(utf8Str.length() == 2u);
        REQUIRE(utf8Str == "\u00A0");
        auto const utf32Str = rms::UTF8ToUTF32(utf8Str);
        std::u32string const utf32StrDesired = U" ";
        REQUIRE(utf32StrDesired == U"\u00A0");
        REQUIRE(utf32Str.length() == 1u);
        REQUIRE(utf32Str == utf32StrDesired);
    }
}

TEST_CASE("UTF32ToUtf8", "[UtfToUtf]")
{
    SECTION("ASCII")
    {
        std::u32string utf32Str = U"Hello";
        REQUIRE(utf32Str.length() == 5u);
        auto utf8Str = rms::UTF32ToUTF8(utf32Str);
        REQUIRE(utf32Str.length() == utf8Str.length());
        REQUIRE(utf8Str == u8"Hello");
    }

    SECTION("Multibyte - single char")
    {
        std::u32string const utf32Str = U"ℵ";
        REQUIRE(utf32Str.length() == 1u);
        auto const utf8Str = rms::UTF32ToUTF8(utf32Str);
        auto const utf8StrDesired = u8"ℵ";
        REQUIRE(utf8Str.length() == 3u);
        REQUIRE(utf8Str == utf8StrDesired);
    }

    SECTION("Multibyte - three chars")
    {
        std::u32string const utf32Str = U"zß水";
        REQUIRE(utf32Str.length() == 3u);
        auto const utf8Str = rms::UTF32ToUTF8(utf32Str);
        auto const utf8StrDesired = u8"zß水";
        REQUIRE(utf8Str.length() == 6u);
        REQUIRE(utf8Str == utf8StrDesired);
    }

    SECTION("Multibyte - non-breaking space")
    {
        std::u32string const utf32Str = U" ";
        REQUIRE(utf32Str.length() == 1u);
        auto const utf8Str = rms::UTF32ToUTF8(utf32Str);
        auto const utf8StrDesired = u8" ";
        REQUIRE(utf8Str.length() == 2u);
        REQUIRE(utf8Str == utf8StrDesired);
    }
}
